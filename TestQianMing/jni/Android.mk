LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS :=-llog

LOCAL_MODULE := test

LOCAL_SRC_FILES := \
Sgin.cpp \
Test.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH) 

#�������ֻ�����ʽ  -mllvm -sobf�ַ���ģ������  -mllvm -subָ���滻     -mllvm -bcf  ��ٿ���-bcf -mllvm -bcf -mllvm -fla

#LOCAL_ARM_MODE := arm

include $(BUILD_SHARED_LIBRARY)

#$(call import-module,mmp)