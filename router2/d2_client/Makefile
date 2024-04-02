TOOLCHAIN := /opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-

CC = $(TOOLCHAIN)gcc
STRIP =$(TOOLCHAIN)strip
CFLAGS=-I../include -g -DACOS_LIBRARY  -I./include
# CFLAGS += -D__DEBUG__
LDFLAGS=-L../fxcn_lib/lib/ -L../fxcn_lib/usr/lib -lgcc_s -lpthread -ld2lib
VPATH = include
OBJ += main.o
BIN := d2_mock
.PHONY: $(BIN) clean

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -Wl,-rpath-link=. -Wl,-rpath=../fxcn_lib/lib:../fxcn_lib/usr/lib -o $@ $^ $(LDFLAGS) 
	$(STRIP) $(BIN)
clean:
	rm *.o $(BIN)

