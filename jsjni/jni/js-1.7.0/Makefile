PLAT := arm-linux-androideabi-

CC := $(PLAT)gcc 
CPP := $(PLAT)g++
LD := $(PLAT)ld
AR := $(PLAT)ar rcu 
RANLIB := $(PLAT)ranlib
STRIP := $(PLAT)strip
RM := rm -f

CFLAGS := 
CFLAGS += -O2 -DANDROID
# -g
CFLAGS += -Wall -Wno-format
CFLAGS += -DXP_UNIX -DSVR4 -DSYSV -D_BSD_SOURCE -DPOSIX_SOURCE 
CFLAGS += -DHAVE_LOCALTIME_R -DX86_LINUX  -DNDEBUG 
# -DDEBUG
# -DDEBUG_wmt 
# CFLAGS += -DEDITLINE 
# -ILinux_All_DBG.OBJ  

OBJECTS := 
OBJECTS += jsapi.o jsarena.o jsarray.o jsatom.o 
OBJECTS += jsbool.o jscntxt.o jsdate.o jsdbgapi.o 
OBJECTS += jsdhash.o jsdtoa.o jsemit.o jsexn.o 
OBJECTS += jsfun.o jsgc.o jshash.o jsinterp.o 
OBJECTS += jsiter.o jslock.o jslog2.o jslong.o 
OBJECTS += jsmath.o jsnum.o jsobj.o jsopcode.o 
OBJECTS += jsparse.o jsprf.o jsregexp.o jsscan.o 
OBJECTS += jsscope.o jsscript.o jsstr.o jsutil.o 
OBJECTS += jsxdrapi.o jsxml.o prmjtime.o

all : libjs.a js

js : libjs.a 
	$(CC) $(CFLAGS) -o $@ js.c libjs.a -lc -lm
	$(STRIP) $@

libjs.a : $(OBJECTS)
	$(AR) $@ $(OBJECTS) 
	$(RANLIB) $@

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<
	
install : js
	adb shell mkdir data/wmt
	adb push $< data/wmt
	adb shell chmod 744 data/wmt/js

uninstall :
	adb shell rm data/wmt/js
	
clean :
	$(RM) $(OBJECTS) *.a js
