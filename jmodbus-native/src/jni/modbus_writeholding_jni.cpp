
#include <modbus.h>

#include "modbus_utils.h"
#include "modbus_except.h"


extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_writeHoldingRegister
        (JNIEnv* env, jclass obj, jlong ptr, jint address, jshort value) {
    jnikit::context<void>(env, [ptr, address, value](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        static_assert(sizeof(jshort) <= sizeof(uint16_t));

        auto rc = modbus_write_register(modbus_ctx, address, value);
        CHECK_ERROR2(env, rc);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_writeHoldingRegisters
        (JNIEnv* _env, jclass obj, jlong ptr, jint address, jint count, jshortArray value) {
    jnikit::context<void>(_env, [_env, ptr, address, count, value](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        uint16_t outArray[TEMP_BUFFER_SIZE] = {};

        jnikit::Array<jnikit::types::Short> valueArray(_env, value);
        for (int i = 0; i < count; i++) {
            outArray[i] = valueArray.getElement(i);
        }

        auto rc = modbus_write_registers(modbus_ctx, address, count, outArray);
        CHECK_ERROR2(env, rc);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_writeHoldingRegisters2
        (JNIEnv* _env, jclass obj, jlong ptr, jint address, jint count, jobject jbuffer) {
    jnikit::context<void>(_env, [_env, ptr, address, count, jbuffer](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        auto buffer = reinterpret_cast<uint16_t *>(_env->GetDirectBufferAddress(jbuffer));

        auto rc = modbus_write_registers(modbus_ctx, address, count, buffer);
        CHECK_ERROR2(env, rc);
    });
}
