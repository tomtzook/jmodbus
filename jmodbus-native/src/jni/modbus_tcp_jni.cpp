#include <jni.h>
#include <jnikit.h>
#include <modbus.h>
#include <modbus-tcp.h>

#include "modbus_except.h"


extern "C"
JNIEXPORT jlong JNICALL Java_jmodbus_ModbusTcpJNI_newModbusContext
        (JNIEnv* _env, jclass obj, jstring ip, jint port) {
    return jnikit::context<jlong>(_env, [_env, ip, port](jnikit::Env& env) -> jlong {
        const char* native_ip = _env->GetStringUTFChars(ip, nullptr);
        auto ctx = modbus_new_tcp(native_ip, port);
        _env->ReleaseStringUTFChars(ip, native_ip);

        CHECK_ERROR_PTR(env, ctx);

        return reinterpret_cast<jlong>(ctx);
    });
}
