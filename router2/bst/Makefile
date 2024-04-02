TOOLCHAIN := /opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-

CC = $(TOOLCHAIN)gcc
STRIP =$(TOOLCHAIN)strip
CFLAGS=-I../include -g -DACOS_LIBRARY  -I./include
# CFLAGS += -D__DEBUG__
LDFLAGS=-L../fxcn_lib/lib/ -L../fxcn_lib/usr/lib -L./lib  -lgcc_s -lpthread -ld2lib -ld2dynlog -ld2bst 
VPATH = include
OBJ += bst.o
BIN := bst
.PHONY: $(BIN) clean

$(BIN): $(OBJ) 
	$(CC) $(CFLAGS) -Wl,-rpath-link=. -Wl,-rpath=../fxcn_lib/lib:../fxcn_lib/usr/lib -o $@ $^ $(LDFLAGS) 
	$(STRIP) $(BIN)
clean:
	rm *.o $(BIN)

