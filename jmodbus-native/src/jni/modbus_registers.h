#pragma once

#include <modbus.h>
#include <jni.h>
#include <jnikit.h>


modbus_mapping_t mapping_from_java(JNIEnv* env, jobject registers);
