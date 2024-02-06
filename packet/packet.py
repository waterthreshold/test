#!/usr/bin/env python3
import sys
import struct 
MAGIC_CODE='*#$^'
if len(sys.argv) < 4:
    print('must have three paramater about <firmware_name> <firmware_version> <firmware_boardid>')
    sys.exit(127)
firmware_name=sys.argv[1]
firmware_version=sys.argv[2]
firmware_boardid=sys.argv[3]
SKU=1

def calculate_checksum(f_buffer):
    size=len(f_buffer)
    c0,c1=0,0
    for byte in f_buffer:
        c0 += int(byte)
        c1 += c0
    b = (c0 & 65535) + ((c0 >> 16) & 65535 )
    c0 = (( b >> 16) + b ) & 65535
    b = (c1 & 65535) + ((c1 >>16) & 65535)
    c1 = ((b>>16)+b) & 65535
    checksum= ((c1 << 16) | c0)
    return checksum
def validation_version(firmware_version):
    tmp_version = firmware_version.split('_',1)
    main_ver = tmp_version[0]
    sub_ver = tmp_version[1]
    maintmp_ver_list=main_ver.split ('.',3)
    sub_ver_list=sub_ver.split('.',2)
    main_ver_list= maintmp_ver_list + sub_ver_list
    main_ver_list = list (map(int , main_ver_list) )
    if len(main_ver_list) != 7:
        print ('Version must need x.x.x.x_x.x.x')
        sys.exit (127)
    for i in  range(len(main_ver_list)):
        if main_ver_list[i] > 255:
            print('each version number must lower than 255')
            sys.exit(127)
        print (main_ver_list[i])
    
    return bytearray(main_ver_list)



def main ():
    header_length=40 + len(firmware_boardid)
    versionlist = validation_version (firmware_version)
    rootfs_cksum=0
    rootfs_length=0
    chk_firmware_path = firmware_name + ".chk"
    with open(firmware_name,"rb") as f:
        binary_data=f.read()
    print (type(binary_data))
    f_buffer = bytearray(binary_data)
    kernel_cksum=calculate_checksum(f_buffer)
    kernel_length=len(f_buffer)
    image_cksum=kernel_cksum
    header_cksum =0 
    with open(chk_firmware_path,"wb") as f:
        f.write(bytearray(MAGIC_CODE, encoding='ASCII'))
        f.write(struct.pack('<I',header_length)[::-1])
        f.write(struct.pack('B',SKU))
        f.write (versionlist)
        f.write (struct.pack('<I',kernel_cksum)[::-1])
        f.write (struct.pack('<I',rootfs_cksum)[::-1])
        f.write (struct.pack('<I',kernel_length)[::-1])
        f.write (struct.pack('<I',rootfs_length)[::-1])
        f.write (struct.pack('<I',image_cksum)[::-1])
        f.write (struct.pack('<I',header_cksum)[::-1])
        f.write(bytearray(firmware_boardid, encoding='ASCII'))
    with open (chk_firmware_path,"rb") as f:
        header_buffer = f.read()


    header_buffer= bytearray(header_buffer)
    header_cksum= calculate_checksum(header_buffer)
    with open (chk_firmware_path ,"wb") as f:
        f.write(bytearray(MAGIC_CODE, encoding='ASCII'))
        f.write(struct.pack('<I',header_length)[::-1])
        f.write(struct.pack('B',SKU))
        f.write (versionlist)
        f.write (struct.pack('<I',kernel_cksum)[::-1])
        f.write (struct.pack('<I',rootfs_cksum)[::-1])
        f.write (struct.pack('<I',kernel_length)[::-1])
        f.write (struct.pack('<I',rootfs_length)[::-1])
        f.write (struct.pack('<I',image_cksum)[::-1])
        f.write (struct.pack('<I',header_cksum)[::-1])
        f.write(bytearray(firmware_boardid, encoding='ASCII'))
        f.write(f_buffer)

if __name__ == '__main__':
    main()
