#include <jni.h>
#include <jnikit.h>
#include <modbus.h>

#include "modbus_except.h"


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
JNIEXPORT jbooleanArray JNICALL Java_jmodbus_ModbusJNI_readDiscreteInputs
        (JNIEnv* env, jclass obj, jlong ptr, jint address, jint count) {
    return jnikit::context<jbooleanArray>(env, [ptr, address, count](jnikit::Env& env) -> jbooleanArray {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        uint8_t buffer[32];
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

        uint8_t buffer[32];
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
JNIEXPORT jbooleanArray JNICALL Java_jmodbus_ModbusJNI_readCoils
        (JNIEnv* env, jclass obj, jlong ptr, jint address, jint count) {
    return jnikit::context<jbooleanArray>(env, [ptr, address, count](jnikit::Env& env) -> jbooleanArray {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        uint8_t buffer[32];
        auto rc = modbus_read_bits(modbus_ctx, address, count, buffer);
        CHECK_ERROR2(env, rc);

        static_assert(sizeof(uint8_t) == sizeof(jboolean));

        auto resultArray = env.newArray<jnikit::types::Boolean>(count);
        resultArray.fill(reinterpret_cast<jboolean*>(buffer), count);

        return resultArray.array();
    });
}

extern "C"
JNIEXPORT jlong JNICALL Java_jmodbus_ModbusJNI_readCoils2
        (JNIEnv* env, jclass obj, jlong ptr, jint address, jint count) {
    return jnikit::context<jlong>(env, [ptr, address, count](jnikit::Env& env) -> jlong {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        uint8_t buffer[32];
        auto rc = modbus_read_bits(modbus_ctx, address, count, buffer);
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
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_readCoils3
        (JNIEnv* _env, jclass obj, jlong ptr, jint address, jint count, jobject jbuffer) {
    jnikit::context<void>(_env, [_env, ptr, address, count, jbuffer](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);
        auto buffer = reinterpret_cast<uint8_t*>(_env->GetDirectBufferAddress(jbuffer));

        auto rc = modbus_read_bits(modbus_ctx, address, count, buffer);
        CHECK_ERROR2(env, rc);
    });
}

extern "C"
JNIEXPORT jshortArray JNICALL Java_jmodbus_ModbusJNI_readHoldingRegisters
        (JNIEnv* env, jclass obj, jlong ptr, jint address, jint count) {
    return jnikit::context<jshortArray>(env, [ptr, address, count](jnikit::Env& env) -> jshortArray {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        uint16_t buffer[32];
        auto rc = modbus_read_registers(modbus_ctx, address, count, buffer);
        CHECK_ERROR2(env, rc);

        static_assert(sizeof(uint16_t) == sizeof(jshort));

        auto resultArray = env.newArray<jnikit::types::Short>(count);
        resultArray.fill(reinterpret_cast<jshort*>(buffer), count);

        return resultArray.array();
    });
}


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
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_writeCoils
        (JNIEnv* _env, jclass obj, jlong ptr, jint address, jint count, jbooleanArray value) {
    jnikit::context<void>(_env, [_env, ptr, address, count, value](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        uint8_t outArray[32] = {};

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

        uint8_t outArray[32] = {};
        for (int i = 0; i < count; i++) {
            outArray[i] = (value) & (1ll << i);
        }

        auto rc = modbus_write_bits(modbus_ctx, address, count, outArray);
        CHECK_ERROR2(env, rc);
    });
}

extern "C"
JNIEXPORT void JNICALL Java_jmodbus_ModbusJNI_writeHoldingRegisters
        (JNIEnv* _env, jclass obj, jlong ptr, jint address, jint count, jshortArray value) {
    jnikit::context<void>(_env, [_env, ptr, address, count, value](jnikit::Env& env) -> void {
        auto modbus_ctx = reinterpret_cast<modbus_t*>(ptr);

        uint16_t outArray[32] = {};

        jnikit::Array<jnikit::types::Short> valueArray(_env, value);
        for (int i = 0; i < count; i++) {
            outArray[i] = valueArray.getElement(i);
        }

        auto rc = modbus_write_registers(modbus_ctx, address, count, outArray);
        CHECK_ERROR2(env, rc);
    });
}
