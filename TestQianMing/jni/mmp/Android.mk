LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := mmp_eem_static

LOCAL_MODULE_FILENAME := libeem

LOCAL_SRC_FILES := Sgin.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)

include $(BUILD_STATIC_LIBRARY)

