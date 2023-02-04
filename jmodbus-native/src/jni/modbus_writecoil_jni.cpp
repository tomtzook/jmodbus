
#include <modbus.h>

#include "modbus_except.h"
#include "modbus_utils.h"


extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_writeCoil
        (JNIEnv* env, jclass obj, jlong ptr, jint address, jboolean value) {
    jnikit::context<void>(env, [ptr, address, value](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        static_assert(sizeof(jboolean) <= sizeof(int));

        auto rc = modbus_write_bit(modbus_ctx, address, value);
        CHECK_ERROR2(env, rc);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_writeCoil2
        (JNIEnv* env, jclass obj, jlong ptr, jint address, jbyte value) {
    jnikit::context<void>(env, [ptr, address, value](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        static_assert(sizeof(jbyte) <= sizeof(int));

        auto rc = modbus_write_bit(modbus_ctx, address, value);
        CHECK_ERROR2(env, rc);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_writeCoils
        (JNIEnv* _env, jclass obj, jlong ptr, jint address, jint count, jbooleanArray value) {
    jnikit::context<void>(_env, [_env, ptr, address, count, value](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        uint8_t outArray[TEMP_BUFFER_SIZE] = {};

        jnikit::Array<jnikit::types::Boolean> valueArray(_env, value);
        for (int i = 0; i < count; i++) {
            outArray[i] = valueArray.getElement(i);
        }

        auto rc = modbus_write_bits(modbus_ctx, address, count, outArray);
        CHECK_ERROR2(env, rc);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_writeCoils2
        (JNIEnv* _env, jclass obj, jlong ptr, jint address, jint count, jlong value) {
    jnikit::context<void>(_env, [_env, ptr, address, count, value](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        uint8_t outArray[TEMP_BUFFER_SIZE] = {};
        for (int i = 0; i < count; i++) {
            outArray[i] = (value) & (1ll << i);
        }

        auto rc = modbus_write_bits(modbus_ctx, address, count, outArray);
        CHECK_ERROR2(env, rc);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_writeCoils3
        (JNIEnv* _env, jclass obj, jlong ptr, jint address, jint count, jbyteArray value) {
    jnikit::context<void>(_env, [_env, ptr, address, count, value](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        uint8_t outArray[TEMP_BUFFER_SIZE] = {};

        jnikit::Array<jnikit::types::Byte> valueArray(_env, value);
        for (int i = 0; i < count; i++) {
            outArray[i] = valueArray.getElement(i);
        }

        auto rc = modbus_write_bits(modbus_ctx, address, count, outArray);
        CHECK_ERROR2(env, rc);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_writeCoils4
        (JNIEnv* _env, jclass obj, jlong ptr, jint address, jint count, jobject jbuffer) {
    jnikit::context<void>(_env, [_env, ptr, address, count, jbuffer](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        auto buffer = reinterpret_cast<uint8_t*>(_env->GetDirectBufferAddress(jbuffer));

        auto rc = modbus_write_bits(modbus_ctx, address, count, buffer);
        CHECK_ERROR2(env, rc);
    });
}
