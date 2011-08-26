LIB=lib/libtaasdk.a
LIBD=lib/libtaasdkd.a
OBJS= \
obj/coroutine.o \
obj/error.o \
obj/path.o \
obj/render.o \
obj/semaphore.o \
obj/spinlock.o \
obj/statemachine.o \
obj/system.o \
obj/thread.o \
obj/uri.o \
obj/window.o \
obj/workqueue.o
OBJSD= \
obj/coroutine.d.o \
obj/error.d.o \
obj/path.d.o \
obj/render.d.o \
obj/semaphore.d.o \
obj/spinlock.d.o \
obj/statemachine.d.o \
obj/system.d.o \
obj/thread.d.o \
obj/uri.d.o \
obj/window.d.o \
obj/workqueue.d.o
INCLUDES=-Iinclude
CC=gcc
CCFLAGS=-Wall -O2 -fno-exceptions -DNDEBUG -Dtaa_RENDER_GL11 $(INCLUDES)
CCFLAGSD=-Wall -O0 -ggdb2 -fno-exceptions -DDEBUG -Dtaa_RENDER_GL11 $(INCLUDES)
AR=ar
ARFLAGS=rs

vpath %.c src

$(LIB): obj lib $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(LIBD): obj lib $(OBJSD)
	$(AR) $(ARFLAGS) $@ $(OBJSD)

obj:
	mkdir obj

lib:
	mkdir lib

obj/%.o : %.c
	$(CC) $(CCFLAGS) -c $< -o $@

obj/%.d.o : %.c
	$(CC) $(CCFLAGSD) -c $< -o $@

all: $(LIB) $(LIBD)

clean:
	rm -rf $(LIB) $(LIBD) obj

