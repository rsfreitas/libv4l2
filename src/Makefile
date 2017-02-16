.PHONY: shared static clean dest_clean install outputdirs dev_install \
	install_headers

CC = gcc
AR = ar

gccversion = 4
ARCH_TEST := $(shell uname -m)
GCCVERSION_TEST := $(shell expr `gcc -dumpversion | cut -f1 -d.` \> 4)

ifeq ($(ARCH_TEST), x86_64)
    ARCH = x86_64
else
    ARCH = i686
endif

ifeq ($(GCCVERSION_TEST), 1)
    gccversion = 5
endif

MAJOR_VERSION := $(shell command grep MAJOR_VERSION ../include/libv4l2.h | awk '{print $$4}')
MINOR_VERSION := $(shell command  grep MINOR_VERSION ../include/libv4l2.h | awk '{print $$4}')
RELEASE := $(shell command grep RELEASE ../include/libv4l2.h | awk '{print $$4}')

USR_DIR = /usr/local/lib
PREFIX = libv4l2
LIBNAME = $(PREFIX).so
SONAME = $(LIBNAME)
SHARED_LIBNAME := $(LIBNAME).$(MAJOR_VERSION).$(MINOR_VERSION).$(RELEASE)
STATIC_LIBNAME := $(PREFIX).a

OUTPUTDIR = ../bin/$(ARCH)
TARGET_SHARED := $(OUTPUTDIR)/$(SHARED_LIBNAME)
TARGET_STATIC := $(OUTPUTDIR)/$(STATIC_LIBNAME)

INCLUDEDIR = -I../include
CFLAGS = -Wall -Wextra -fPIC -ggdb -O0 -g3 \
        -DLIBV4L2_COMPILE -D_GNU_SOURCE $(INCLUDEDIR)

LIBDIR =
LIBS = -lcollections -lpthread

ifeq ($(gccversion), 5)
    CFLAGS += -fgnu89-inline
endif

VPATH = ../include:.

C_FILES := $(wildcard *.c)
OBJS = $(C_FILES:.c=.o)

shared: outputdirs $(OBJS)
	$(CC) -shared -Wl,-soname,$(SONAME),--version-script,$(PREFIX).sym -o $(TARGET_SHARED) $(OBJS) $(LIBDIR) $(LIBS)

static: outputdirs $(OBJS)
	$(AR) -sr $(TARGET_STATIC) $(OBJS)

clean:
	rm -rf $(OBJS) $(TARGET_SHARED) $(TARGET_STATIC) *~ ../include/*~

purge: clean shared

dest_clean:
	rm -f $(USR_DIR)/$(LIBNAME)*

install:
	cp -f $(TARGET_SHARED) $(USR_DIR)
	rm -rf $(USR_DIR)/$(LIBNAME) $(USR_DIR)/$(SONAME)
	ln -sf $(USR_DIR)/$(SHARED_LIBNAME) $(USR_DIR)/$(LIBNAME)

install_headers:
	$(shell [ ! -d /usr/local/include/v4l2_lib ] && mkdir -p /usr/local/include/v4l2_lib)
	$(shell for f in `ls ../include/v4l2_lib/v_*.h | egrep -v 'v_internal.h'`; do cp -f $$f /usr/local/include/v4l2_lib; done)
	cp -f ../include/libv4l2.h /usr/local/include

dev_install: install_headers install

outputdirs: $(OUTPUTDIR)
$(OUTPUTDIR):
	mkdir -p $(OUTPUTDIR)

