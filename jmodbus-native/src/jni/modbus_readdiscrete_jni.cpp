
#include <modbus.h>

#include "modbus_utils.h"
#include "modbus_except.h"


extern "C"
JNIEXPORT jbooleanArray JNICALL Java_jmodbus_ModbusJNI_readDiscreteInputs
        (JNIEnv* env, jclass obj, jlong ptr, jint address, jint count) {
    return jnikit::context<jbooleanArray>(env, [ptr, address, count](jnikit::Env& env) -> jbooleanArray {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        uint8_t buffer[TEMP_BUFFER_SIZE] = {};
        auto rc = modbus_read_input_bits(modbus_ctx, address, count, buffer);
        CHECK_ERROR2(env, rc);

        static_assert(sizeof(uint8_t) == sizeof(jboolean));

        auto resultArray = env.newArray<jnikit::types::Boolean>(count);
        resultArray.fill(reinterpret_cast<jboolean*>(buffer), count);

        return resultArray.array();
    });
}

extern "C"
JNIEXPORT jlong JNICALL Java_jmodbus_ModbusJNI_readDiscreteInputs2
        (JNIEnv* env, jclass obj, jlong ptr, jint address, jint count) {
    return jnikit::context<jlong>(env, [ptr, address, count](jnikit::Env& env) -> jlong {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        uint8_t buffer[TEMP_BUFFER_SIZE] = {};
        auto rc = modbus_read_input_bits(modbus_ctx, address, count, buffer);
        CHECK_ERROR2(env, rc);

        static_assert(sizeof(uint8_t) == sizeof(jboolean));

        jlong value = 0;
        for (int i = 0; i < count; ++i) {
            if (buffer[i]) {
                value |= (1ll << i);
            }
        }

        return value;
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_readDiscreteInputs3
        (JNIEnv* _env, jclass obj, jlong ptr, jint address, jint count, jobject jbuffer) {
    jnikit::context<void>(_env, [_env, ptr, address, count, jbuffer](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        auto buffer = reinterpret_cast<uint8_t*>(_env->GetDirectBufferAddress(jbuffer));

        auto rc = modbus_read_input_bits(modbus_ctx, address, count, buffer);
        CHECK_ERROR2(env, rc);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_readDiscreteInputs4
        (JNIEnv* _env, jclass obj, jlong ptr, jint address, jint count, jbyteArray jbuffer) {
    jnikit::context<void>(_env, [_env, ptr, address, count, jbuffer](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        jnikit::Array<jnikit::types::Byte> valueArray(_env, jbuffer);

        uint8_t buffer[TEMP_BUFFER_SIZE] = {};
        auto rc = modbus_read_input_bits(modbus_ctx, address, count, buffer);
        CHECK_ERROR2(env, rc);

        static_assert(sizeof(jbyte) == sizeof(uint8_t));

        valueArray.fill(reinterpret_cast<jbyte*>(buffer), count);
    });
}
