
#include <modbus.h>

#include "modbus_except.h"
#include "modbus_utils.h"


extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_readInputRegisters
        (JNIEnv* _env, jclass obj, jlong ptr, jint address, jint count, jshortArray jbuffer) {
    jnikit::context<void>(_env, [_env, ptr, address, count, jbuffer](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        jnikit::Array<jnikit::types::Short> valueArray(_env, jbuffer);

        uint16_t buffer[TEMP_BUFFER_SIZE] = {};
        auto rc = modbus_read_input_registers(modbus_ctx, address, count, buffer);
        CHECK_ERROR2(env, rc);

        static_assert(sizeof(uint16_t) == sizeof(jshort));

        valueArray.fill(reinterpret_cast<jshort*>(buffer), count);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_readInputRegisters2
        (JNIEnv* _env, jclass obj, jlong ptr, jint address, jint count, jobject jbuffer) {
    jnikit::context<void>(_env, [_env, ptr, address, count, jbuffer](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        auto buffer = reinterpret_cast<uint16_t*>(_env->GetDirectBufferAddress(jbuffer));

        auto rc = modbus_read_input_registers(modbus_ctx, address, count, buffer);
        CHECK_ERROR2(env, rc);

        static_assert(sizeof(uint16_t) == sizeof(jshort));
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_readInputRegisters3
        (JNIEnv* _env, jclass obj, jlong ptr, jint address, jint count, jbyteArray jbuffer) {
    jnikit::context<void>(_env, [_env, ptr, address, count, jbuffer](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        jnikit::Array<jnikit::types::Byte> valueArray(_env, jbuffer);

        uint16_t buffer[TEMP_BUFFER_SIZE] = {};
        auto rc = modbus_read_input_registers(modbus_ctx, address, count, buffer);
        CHECK_ERROR2(env, rc);

        static_assert(sizeof(uint16_t) == sizeof(jshort));

        for (int i = 0; i < count; ++i) {
            valueArray.setElement(i * 2, static_cast<int8_t>((buffer[i] >> 8) & 0xff));
            valueArray.setElement(i * 2 + 1, static_cast<int8_t>(buffer[i] & 0xff));
        }
    });
}
