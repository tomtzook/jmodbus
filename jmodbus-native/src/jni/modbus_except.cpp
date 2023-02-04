
#include <modbus.h>

#include "modbus_except.h"


void throw_modbus_error(jnikit::Env& env, int error_code) {
    auto str_error = modbus_strerror(error_code);
    env.throwException<ModbusException>(str_error);
}
