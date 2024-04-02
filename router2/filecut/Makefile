CC := /opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc
BIN := filecut
OBJ := filecut.o
.PHONY: clean $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@  $^
	/opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-strip $(BIN)
clean:
	rm $(BIN) *.o
