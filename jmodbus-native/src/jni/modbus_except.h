#pragma once


#include <cerrno>
#include <jnikit.h>
#include <except.h>


DEFINE_OBJECT_TYPE(ModbusException, "jmodbus/ModbusException")
DEFINE_OBJECT_TYPE(IllegalFunctionException, "jmodbus/IllegalFunctionException")
DEFINE_OBJECT_TYPE(IllegalDataAddressException, "jmodbus/IllegalDataAddressException")
DEFINE_OBJECT_TYPE(IllegalDataValueException, "jmodbus/IllegalDataValueException")
DEFINE_OBJECT_TYPE(SlaveOrServerFailureException, "jmodbus/SlaveOrServerFailureException")
DEFINE_OBJECT_TYPE(SlaveOrServerBusyException, "jmodbus/SlaveOrServerBusyException")
DEFINE_OBJECT_TYPE(MemoryParityException, "jmodbus/MemoryParityException")
DEFINE_OBJECT_TYPE(GatewayPathException, "jmodbus/GatewayPathException")
DEFINE_OBJECT_TYPE(GatewayTargetException, "jmodbus/GatewayTargetException")


#define CHECK_ERROR(__env, __VA_ARGS__) \
do {                             \
    auto __rc = __VA_ARGS__;     \
    CHECK_ERROR2(__env, __rc);   \
} while(0)

#define CHECK_ERROR2(__env, __rc) \
do {                             \
    if (__rc < 0) {              \
        throw_modbus_error(__env, errno);   \
    }                                 \
} while(0)

#define CHECK_ERROR_PTR(__env, __ptr) \
do {                             \
    if (nullptr == __ptr) {              \
        throw_modbus_error(__env, errno);   \
    }                                 \
} while(0)


void throw_modbus_error(jnikit::Env& env, int error_code);
