#include <jni.h>
#include <jnikit.h>
#include <modbus.h>
#include <modbus-tcp.h>
#include <netinet/in.h>
#include <cstring>

#include "modbus_except.h"
#include "modbus_registers.h"


DEFINE_OBJECT_TYPE(JPendingDataType, "jmodbus/tcp/server/PendingDataType")

enum LoopStatus {
    LOOP_END,
    LOOP_IN_PROGRESS
};

enum ContextOp {
    OP_NEW_CLIENT,
    OP_NEW_DATA_FROM_CLIENT,
    OP_NONE
};

struct TcpServerContext {
    LoopStatus loop_status;
    ContextOp context_op;

    int socket_server;
    fd_set refset;
    fd_set rdset;
    int fdmax;
    int current_iter_socket;
    modbus_mapping_t reg_mapping;
};

static void server_select(TcpServerContext* server_ctx) {
    server_ctx->rdset = server_ctx->refset;
    if (select(server_ctx->fdmax + 1, &server_ctx->rdset, nullptr, nullptr, nullptr) == -1) {
        // throw java IOException
    }

    server_ctx->current_iter_socket = -1;
    server_ctx->loop_status = LOOP_IN_PROGRESS;
}

static ContextOp server_select_loop(TcpServerContext* server_ctx) {
    server_ctx->current_iter_socket++;
    for (; server_ctx->current_iter_socket <= server_ctx->fdmax; server_ctx->current_iter_socket++) {
        if (!FD_ISSET(server_ctx->current_iter_socket, &server_ctx->rdset)) {
            continue;
        }

        if (server_ctx->current_iter_socket == server_ctx->socket_server) {
            // new client
            return OP_NEW_CLIENT;
        }

        return OP_NEW_DATA_FROM_CLIENT;
    }

    server_ctx->loop_status = LOOP_END;
    return OP_NONE;
}

static jobject contextOpToJava(jnikit::Env& env, TcpServerContext* server_ctx) {
    auto cls = env.getClass<JPendingDataType>();
    switch (server_ctx->context_op) {
        case OP_NEW_CLIENT:
            return cls.getStaticField<JPendingDataType>("NEW_CLIENT");
        case OP_NEW_DATA_FROM_CLIENT:
            return cls.getStaticField<JPendingDataType>("NEW_DATA");
        case OP_NONE:
            env.throwException<jnikit::UnsupportedOperationException>();
            return nullptr;
    }
}

extern "C"
JNIEXPORT jlong JNICALL Java_jmodbus_tcp_server_ModbusTcpServerJNI_init
        (JNIEnv* _env, jclass obj, jlong ptr, jint client_count, jobject registers) {
    return jnikit::context<jlong>(_env, [_env, ptr, client_count, registers](jnikit::Env& env) -> jlong {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        int rc = modbus_tcp_listen(modbus_ctx, client_count);
        CHECK_ERROR2(env, rc);

        // TODO: free rc on error
        auto* server_ctx = new TcpServerContext;
        try {
            server_ctx->socket_server = rc;
            server_ctx->fdmax = server_ctx->socket_server;
            server_ctx->current_iter_socket = 0;
            server_ctx->context_op = OP_NONE;
            server_ctx->loop_status = LOOP_END;
            server_ctx->reg_mapping = mapping_from_java(_env, registers);

            FD_ZERO(&server_ctx->refset);
            FD_SET(server_ctx->socket_server, &server_ctx->refset);
        } catch (...) {
            delete server_ctx;
            modbus_close(modbus_ctx);
            throw;
        }

        return reinterpret_cast<jlong>(server_ctx);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_tcp_server_ModbusTcpServerJNI_close
        (JNIEnv* _env, jclass obj, jlong server_ptr) {
    jnikit::context<void>(_env, [_env, server_ptr](jnikit::Env& env) -> void {
        auto server_ctx = reinterpret_cast<TcpServerContext*>(server_ptr);

        for (server_ctx->current_iter_socket = 0 ; server_ctx->current_iter_socket <= server_ctx->fdmax; server_ctx->current_iter_socket++) {
            if (!FD_ISSET(server_ctx->current_iter_socket, &server_ctx->refset)) {
                continue;
            }

            close(server_ctx->current_iter_socket);
        }

        close(server_ctx->socket_server);

        delete server_ctx;
    });
}

extern "C"
JNIEXPORT jobject JNICALL Java_jmodbus_tcp_server_ModbusTcpServerJNI_waitForNewData
        (JNIEnv* _env, jclass obj, jlong ptr, jlong server_ptr) {
    return jnikit::context<jobject>(_env, [_env, ptr, server_ptr](jnikit::Env& env) -> jobject {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        auto server_ctx = reinterpret_cast<TcpServerContext*>(server_ptr);

        if (server_ctx->context_op != OP_NONE) {
            env.throwException<jnikit::IllegalStateException>();
            return nullptr;
        }

        while (server_ctx->context_op == OP_NONE) {
            switch (server_ctx->loop_status) {
                case LOOP_END:
                    server_select(server_ctx);
                case LOOP_IN_PROGRESS:
                    server_ctx->context_op = server_select_loop(server_ctx);
                    break;
            }
        }

        return contextOpToJava(env, server_ctx);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_tcp_server_ModbusTcpServerJNI_acceptNewClient
        (JNIEnv* _env, jclass obj, jlong ptr, jlong server_ptr) {
    jnikit::context<void>(_env, [_env, ptr, server_ptr](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        auto server_ctx = reinterpret_cast<TcpServerContext*>(server_ptr);

        if (server_ctx->context_op != OP_NEW_CLIENT) {
            env.throwException<jnikit::IllegalStateException>();
            return;
        }

        // new client
        socklen_t addrlen;
        sockaddr_in clientaddr {};
        int newfd;

        // Handle new connections
        addrlen = sizeof(clientaddr);
        memset(&clientaddr, 0, sizeof(clientaddr));
        newfd = accept(server_ctx->socket_server, (sockaddr*) &clientaddr, &addrlen);
        if (newfd == -1) {
            server_ctx->context_op = OP_NONE;
            throw_modbus_io_error(env);
            return;
        }

        FD_SET(newfd, &server_ctx->refset);

        if (newfd > server_ctx->fdmax) {
            // Keep track of the maximum
            server_ctx->fdmax = newfd;
        }

        server_ctx->context_op = OP_NONE;
    });
}

extern "C"
JNIEXPORT jint JNICALL Java_jmodbus_tcp_server_ModbusTcpServerJNI_readNewClientData
        (JNIEnv* _env, jclass obj, jlong ptr, jlong server_ptr, jobject jbuffer) {
    return jnikit::context<jint>(_env, [_env, ptr, server_ptr, jbuffer](jnikit::Env& env) -> jint {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        auto server_ctx = reinterpret_cast<TcpServerContext*>(server_ptr);

        if (server_ctx->context_op != OP_NEW_DATA_FROM_CLIENT) {
            env.throwException<jnikit::IllegalStateException>();
            return -1;
        }

        auto buffer = reinterpret_cast<uint8_t*>(_env->GetDirectBufferAddress(jbuffer));

        modbus_set_socket(modbus_ctx, server_ctx->current_iter_socket);
        int rc = modbus_receive(modbus_ctx, buffer);

        server_ctx->context_op = OP_NONE;
        if (IS_ERROR(rc)) {
            throw_modbus_io_error(env);
            return -1;
        }

        return static_cast<jint>(rc);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_tcp_server_ModbusTcpServerJNI_replyClient
        (JNIEnv* _env, jclass obj, jlong ptr, jlong server_ptr, jobject jbuffer, jint size) {
    jnikit::context<void>(_env, [_env, ptr, server_ptr, jbuffer, size](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        auto server_ctx = reinterpret_cast<TcpServerContext*>(server_ptr);

        auto buffer = reinterpret_cast<uint8_t*>(_env->GetDirectBufferAddress(jbuffer));

        modbus_set_socket(modbus_ctx, server_ctx->current_iter_socket);
        int rc = modbus_reply(modbus_ctx, buffer, size, &server_ctx->reg_mapping);
        if (IS_ERROR(rc)) {
            throw_modbus_io_error(env);
        }
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_tcp_server_ModbusTcpServerJNI_closeCurrentClient
        (JNIEnv* _env, jclass obj, jlong ptr, jlong server_ptr) {
    jnikit::context<void>(_env, [_env, ptr, server_ptr](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        auto server_ctx = reinterpret_cast<TcpServerContext*>(server_ptr);

        close(server_ctx->current_iter_socket);

        FD_CLR(server_ctx->current_iter_socket, &server_ctx->refset);

        if (server_ctx->current_iter_socket == server_ctx->fdmax) {
            server_ctx->fdmax--;
        }
    });
}

