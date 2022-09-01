LOCAL_PATH:=$(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -fPIE
LOCAL_LDFLAGS += -fPIE# -pie

LOCAL_MODULE:=ssim_basic

LOCAL_SRC_FILES:=ssim_basic.c image.c

LOCAL_LDLIBS := 

LOCAL_CFLAGS += -O3

include $(BUILD_EXECUTABLE)
