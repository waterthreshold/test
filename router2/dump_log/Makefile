CC := /opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc
BIN := dump_log
OBJ := dump_log.o
.PHONY: $(BIN) clean
$(BIN): $(OBJ)
	$(CC) -o $@ $^
clean:
	rm $(BIN) *.o
