CC=/opt/toolchains//crosstools-arm-gcc-5.5-linux-4.1-glibc-2.26-binutils-2.28.1/usr/bin/arm-buildroot-linux-gnueabi-gcc
CFLAGS=-I../include -g
LDFLAGS=-L../fxcn_lib/lib/ -L../fxcn_lib/usr/lib   -lgcc_s -lacos_nvram -lwlanUtil -lnvram -lacos_shared -lcms_shell  -lwlmdm -lethctl  -labLit -lshared 

all: wireless_configure
wireless_configure: wireless_configure.o
	$(CC) $(CFLAGS) -Wl,-rpath-link=. -Wl,-rpath=../fxcn_lib/lib:../fxcn_lib/usr/lib -o $@ $^ $(LDFLAGS) 

clean:
	rm wireless_configure *.o

