#include <jni.h>
#include <jnikit.h>
#include <modbus.h>

#include "modbus_except.h"


static constexpr size_t TEMP_BUFFER_SIZE = 32;

DEFINE_OBJECT_TYPE(TimeValue, "jmodbus/TimeValue")


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

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_setResponseTimeout
        (JNIEnv* env, jclass obj, jlong ptr, jobject value) {
    jnikit::context<void>(env, [ptr, value](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        auto time_value = env.wrap<TimeValue>(value);
        auto time_secs = time_value.callMethod<jnikit::types::Int>("getSeconds");
        auto time_usecs = time_value.callMethod<jnikit::types::Int>("getMicroseconds");

        CHECK_ERROR(env, modbus_set_response_timeout(modbus_ctx, time_secs, time_usecs));
    });
}

extern "C"
JNIEXPORT jobject JNICALL Java_jmodbus_ModbusJNI_getResponseTimeout
        (JNIEnv* env, jclass obj, jlong ptr) {
    return jnikit::context<jobject>(env, [ptr](jnikit::Env& env) -> jobject  {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        uint32_t time_secs;
        uint32_t time_usecs;
        CHECK_ERROR(env, modbus_get_response_timeout(modbus_ctx, &time_secs, &time_usecs));

        using namespace jnikit::types;
        auto cls = env.getClass<TimeValue>();
        return cls.newInstance<Int, Int>(static_cast<jint>(time_secs), static_cast<jint>(time_usecs));
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_setByteTimeout
        (JNIEnv* env, jclass obj, jlong ptr, jobject value) {
    jnikit::context<void>(env, [ptr, value](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        auto time_value = env.wrap<TimeValue>(value);
        auto time_secs = time_value.callMethod<jnikit::types::Int>("getSeconds");
        auto time_usecs = time_value.callMethod<jnikit::types::Int>("getMicroseconds");

        CHECK_ERROR(env, modbus_set_byte_timeout(modbus_ctx, time_secs, time_usecs));
    });
}

extern "C"
JNIEXPORT jobject JNICALL Java_jmodbus_ModbusJNI_getByteTimeout
        (JNIEnv* env, jclass obj, jlong ptr) {
    return jnikit::context<jobject>(env, [ptr](jnikit::Env& env) -> jobject  {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        uint32_t time_secs;
        uint32_t time_usecs;
        CHECK_ERROR(env, modbus_get_byte_timeout(modbus_ctx, &time_secs, &time_usecs));

        using namespace jnikit::types;
        auto cls = env.getClass<TimeValue>();
        return cls.newInstance<Int, Int>(static_cast<jint>(time_secs), static_cast<jint>(time_usecs));
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_setIndicationTimeout
        (JNIEnv* env, jclass obj, jlong ptr, jobject value) {
    jnikit::context<void>(env, [ptr, value](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        auto time_value = env.wrap<TimeValue>(value);
        auto time_secs = time_value.callMethod<jnikit::types::Int>("getSeconds");
        auto time_usecs = time_value.callMethod<jnikit::types::Int>("getMicroseconds");

        CHECK_ERROR(env, modbus_set_indication_timeout(modbus_ctx, time_secs, time_usecs));
    });
}

extern "C"
JNIEXPORT jobject JNICALL Java_jmodbus_ModbusJNI_getIndicationTimeout
        (JNIEnv* env, jclass obj, jlong ptr) {
    return jnikit::context<jobject>(env, [ptr](jnikit::Env& env) -> jobject  {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        uint32_t time_secs;
        uint32_t time_usecs;
        CHECK_ERROR(env, modbus_get_indication_timeout(modbus_ctx, &time_secs, &time_usecs));

        using namespace jnikit::types;
        auto cls = env.getClass<TimeValue>();
        return cls.newInstance<Int, Int>(static_cast<jint>(time_secs), static_cast<jint>(time_usecs));
    });
}