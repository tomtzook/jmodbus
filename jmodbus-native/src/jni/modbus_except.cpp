
#include <modbus.h>

#include "modbus_except.h"


void throw_modbus_error(jnikit::Env& env, int error_code) {
    auto str_error = modbus_strerror(error_code);

    switch (error_code) {
        case EMBXILFUN:
            env.throwException<IllegalFunctionException>(str_error);
            break;
        case EMBXILADD:
            env.throwException<IllegalDataAddressException>(str_error);
            break;
        case EMBXILVAL:
            env.throwException<IllegalDataValueException>(str_error);
            break;
        case EMBXSFAIL:
            env.throwException<SlaveOrServerFailureException>(str_error);
            break;
        case EMBXSBUSY:
            env.throwException<SlaveOrServerBusyException>(str_error);
            break;
        case EMBXMEMPAR:
            env.throwException<MemoryParityException>(str_error);
            break;
        case EMBXGPATH:
            env.throwException<GatewayPathException>(str_error);
            break;
        case EMBXGTAR:
            env.throwException<GatewayTargetException>(str_error);
            break;
        default:
            env.throwException<ModbusException>(str_error);
            break;
    }
}
