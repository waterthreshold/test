CC := /opt/toolchains/crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc
TARGET := port_check
.PHONY: scan,clean,all


all: $(TARGET)
	
$(TARGET): port_scan.o
	$(CC) -o $@ $^

clean:
	rm $(TARGET) *.o
