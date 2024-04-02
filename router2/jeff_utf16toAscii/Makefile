BIN := utf16toAscii
CC := /opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc 
.PHONY: clean
$(BIN): utf16toAscii.c
	$(CC) -o $@ $^
clean:
	rm $(BIN) *.o
