APP_STL := gnustl_static

#LOCAL_CFLAGS := -mllvm -sub -mllvm -sobf 
APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -DCC_ENABLE_BULLET_INTEGRATION=0 -std=c++11 -fsigned-char
APP_CPPFLAGS += -mllvm -fla -mllvm -sobf 
APP_LDFLAGS := -latomic
APP_PLATFORM :=android-19
NDK_TOOLCHAIN_VERSION = clang-ollvm4.0
#APP_SHORT_COMMANDS:= true


