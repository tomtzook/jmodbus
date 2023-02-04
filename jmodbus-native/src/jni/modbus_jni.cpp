#include <jni.h>
#include <jnikit.h>
#include <modbus.h>

#include "modbus_except.h"


static constexpr size_t TEMP_BUFFER_SIZE = 32;


extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_connect
        (JNIEnv* env, jclass obj, jlong ptr) {
    jnikit::context<void>(env, [ptr](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        CHECK_ERROR(env, modbus_connect(modbus_ctx));
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_flush
        (JNIEnv* env, jclass obj, jlong ptr) {
    jnikit::context<void>(env, [ptr](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        CHECK_ERROR(env, modbus_flush(modbus_ctx));
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_close
        (JNIEnv* env, jclass obj, jlong ptr) {
    jnikit::context<void>(env, [ptr](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        modbus_close(modbus_ctx);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_free
        (JNIEnv* env, jclass obj, jlong ptr) {
    jnikit::context<void>(env, [ptr](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        modbus_free(modbus_ctx);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_setDebug
        (JNIEnv* env, jclass obj, jlong ptr, jboolean debug_on) {
    jnikit::context<void>(env, [ptr, debug_on](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        CHECK_ERROR(env, modbus_set_debug(modbus_ctx, debug_on ? TRUE : FALSE));
    });
}

extern "C"
JNIEXPORT jint JNICALL Java_jmodbus_ModbusJNI_getSlave
        (JNIEnv* env, jclass obj, jlong ptr) {
    return jnikit::context<jint>(env, [ptr](jnikit::Env& env) -> jint {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        auto rc = modbus_get_slave(modbus_ctx);
        CHECK_ERROR2(env, rc);
        return rc;
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_setSlave
        (JNIEnv* env, jclass obj, jlong ptr, jint slave) {
    jnikit::context<void>(env, [ptr, slave](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        CHECK_ERROR(env, modbus_set_slave(modbus_ctx, slave));
    });
}
