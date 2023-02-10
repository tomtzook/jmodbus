cmake_minimum_required(VERSION 3.16)
project(modbus_native CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(jnikit)

find_package(PkgConfig)
pkg_search_module(libmodbus REQUIRED libmodbus)

include_directories(${JNI_INCLUDE_DIRS} ${libmodbus_INCLUDE_DIRS})
link_directories(${libmodbus_LIBDIR})

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(modbus_jni SHARED
        jni/modbus_jni.cpp
        jni/modbus_except.cpp
        jni/modbus_tcp_jni.cpp
        jni/modbus_readcoil_jni.cpp
        jni/modbus_readdiscrete_jni.cpp
        jni/modbus_readinput_jni.cpp
        jni/modbus_readholding_jni.cpp
        jni/modbus_writecoil_jni.cpp
        jni/modbus_writeholding_jni.cpp
        jni/modbus_rtu_jni.cpp
        jni/modbus_tcpserver_jni.cpp
        jni/modbus_registers.cpp
        jni/modbus_registers.h)

if(WIN32)
    message(STATUS "WIN32")
    target_link_libraries(modbus_jni -lwsock32)
endif()

target_link_libraries(modbus_jni ${libmodbus_LIBRARIES} jnikit)
