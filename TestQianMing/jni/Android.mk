LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS :=-llog

LOCAL_MODULE := test

LOCAL_SRC_FILES := \
Sgin.cpp \
Test.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH) 

#开启三种混淆方式  -mllvm -sobf字符串模糊处理  -mllvm -sub指令替换     -mllvm -bcf  虚假控制-bcf -mllvm -bcf -mllvm -fla

#LOCAL_ARM_MODE := arm

include $(BUILD_SHARED_LIBRARY)

#$(call import-module,mmp)