CC=/opt/toolchains//crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc
TARGET= dhcp_dump
all: $(TARGET)

$(TARGET): dhcp_dump.o
	$(CC) -o $@ $^

clean:
	rm $(TARGET) *.o
