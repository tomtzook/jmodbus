#include <jni.h>
#include <jnikit.h>
#include <modbus.h>
#include <modbus-rtu.h>

#include "modbus_except.h"


DEFINE_OBJECT_TYPE(Parity, "jmodbus/rtu/Parity")
DEFINE_OBJECT_TYPE(Databit, "jmodbus/rtu/Databit")
DEFINE_OBJECT_TYPE(Stopbit, "jmodbus/rtu/Stopbit")
DEFINE_OBJECT_TYPE(SerialMode, "jmodbus/rtu/SerialMode")


extern "C"
JNIEXPORT jlong JNICALL Java_jmodbus_rtu_ModbusRtuJNI_newModbusContext
        (JNIEnv* _env, jclass obj,
         jstring port,
         jint baud,
         jobject parity,
         jobject data_bit,
         jobject stop_bit,
         jobject serial_mode) {
    return jnikit::context<jlong>(_env, [&](jnikit::Env& env) -> jlong {
        using namespace jnikit::types;

        auto parity_n = env.wrap<Parity>(parity).callMethod<Char>("charValue");
        auto data_bit_n = env.wrap<Databit>(data_bit).callMethod<Int>("intValue");
        auto stop_bit_n = env.wrap<Stopbit>(stop_bit).callMethod<Int>("intValue");
        auto serial_mode_n = env.wrap<SerialMode>(serial_mode).callMethod<Int>("intValue");

        const char* native_port = _env->GetStringUTFChars(port, nullptr);

        auto ctx = modbus_new_rtu(native_port, baud, parity_n, data_bit_n, stop_bit_n);
        _env->ReleaseStringUTFChars(port, native_port);
        CHECK_ERROR_PTR(env, ctx);

        auto rc = modbus_rtu_set_serial_mode(ctx, serial_mode_n);
        if (IS_ERROR(rc)) {
            modbus_free(ctx);
            CHECK_ERROR2(env, rc);
        }

        return reinterpret_cast<jlong>(ctx);
    });
}

extern "C"
JNIEXPORT jint JNICALL Java_jmodbus_rtu_ModbusRtuJNI_getDelayMicroseconds
        (JNIEnv* _env, jclass obj, jlong ptr) {
    return jnikit::context<jint>(_env, [ptr](jnikit::Env& env) -> jint {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        int rc = modbus_rtu_get_rts_delay(modbus_ctx);
        CHECK_ERROR2(env, rc);

        return rc;
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_rtu_ModbusRtuJNI_setDelayMicroseconds
        (JNIEnv* _env, jclass obj, jlong ptr, jint delay) {
    jnikit::context<void>(_env, [ptr, delay](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        CHECK_ERROR(env, modbus_rtu_set_rts_delay(modbus_ctx, delay));
    });
}
