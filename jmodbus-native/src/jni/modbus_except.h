#pragma once


#include <cerrno>
#include <jnikit.h>
#include <except.h>


DEFINE_OBJECT_TYPE(ModbusException, "jmodbus/ModbusException")


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
