LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := js170

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Include

LOCAL_CFLAGS := 
#LOCAL_CFLAGS += -O2 -DANDROID
# -g
#LOCAL_CFLAGS += -Wall -Wno-format
LOCAL_CFLAGS += -DXP_UNIX -DSVR4 -DSYSV -D_BSD_SOURCE -DPOSIX_SOURCE 
LOCAL_CFLAGS += -DHAVE_LOCALTIME_R -DX86_LINUX  -DNDEBUG 
# -DDEBUG
# -DDEBUG_wmt 
# CFLAGS += -DEDITLINE 
# -ILinux_All_DBG.OBJ  

LOCAL_CPP_EXTENSION := .cpp

LOCAL_SRC_FILES := jsapi.c jsarena.c jsarray.c jsatom.c 
LOCAL_SRC_FILES += jsbool.c jscntxt.c jsdate.c jsdbgapi.c 
LOCAL_SRC_FILES += jsdhash.c jsdtoa.c jsemit.c jsexn.c 
LOCAL_SRC_FILES += jsfun.c jsgc.c jshash.c jsinterp.c 
LOCAL_SRC_FILES += jsiter.c jslock.c jslog2.c jslong.c 
LOCAL_SRC_FILES += jsmath.c jsnum.c jsobj.c jsopcode.c  
LOCAL_SRC_FILES += jsparse.c jsprf.c jsregexp.c jsscan.c 
LOCAL_SRC_FILES += jsscope.c jsscript.c jsstr.c jsutil.c  
LOCAL_SRC_FILES += jsxdrapi.c jsxml.c prmjtime.c 

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
LOCAL_EXPORT_CFLAGS := -DXP_UNIX

#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)
