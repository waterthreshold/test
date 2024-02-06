#!/usr/bin/ruby
BEGIN{
  puts "Begin start"
}
END {
  puts "End stop "
}

def validation_version(version)
  version_arr = version.split(/[._]/)
  byte_arr = version_arr.map{ |num| num.to_i }
  #byte_arr_2= byte_arr.map { |num| [num].pack('C*') }
#  puts byte_arr.length
 # puts byte_arr[1].class
  return byte_arr
end
def calculate_checksum (s , size )
  c0, c1 = 0,0 
  puts s[0].class
  for i in 0..size -1 
    c0 += s[i]
    c1 += c0
  end
  b = (c0 & 65535 ) + ( (c0 >> 16) & 65535 )
  c0 = (( b >> 16) + b) & 65535

  b = (c1 & 65535 ) + ((c1 >> 16) & 65535 )
  c1 = ((b >> 16) + b  )  & 65535

  cksum = ( c1 << 16 ) | c0 
  puts "#{cksum.to_s(16)} "  
  return cksum
end 

puts "Hello world!"
$firmware_name=ARGV.at(0)
$version=ARGV.at(1)
$board_id=ARGV.at(2)
$header_length = 40 + $board_id.length
$SKU=1
$version_byte =  []
$kernel_cksun = 0
$rootfs_cksum = 0 
$kernel_length = 0 
$rootfs_length = 0 
$image_cksum = 0
$header_cksum = 0 
$f_buffer = []

MAGIC='*#$^'

header_arr = []
$chk_file_path= $firmware_name + ".chk"
#io=File.new($firmware_name , "rb")
#io=File.open
puts "Firmware name: " +  $firmware_name + ",Version: " + $version + "board id:" +$board_id
f_buffer = IO.binread($firmware_name).bytes
header_arr.concat (MAGIC.bytes)
header_arr.concat([$header_length].pack('L').bytes.reverse)
header_arr.concat([$SKU].pack('C').bytes)
$version_byte = validation_version $version
header_arr.concat($version_byte)
$kernel_cksun = calculate_checksum f_buffer, f_buffer.length
header_arr.concat([$kernel_cksun].pack('L').bytes.reverse)
header_arr.concat([$rootfs_cksum].pack('L').bytes.reverse)
$kernel_length=f_buffer.length
header_arr.concat([$kernel_length].pack('L').bytes.reverse)
header_arr.concat([$rootfs_length].pack('L').bytes.reverse)
$image_cksum=$kernel_cksun
header_arr.concat([$image_cksum].pack('L').bytes.reverse)
header_arr_tmp = header_arr.dup
header_arr.concat([$header_cksum].pack('L').bytes.reverse)
header_arr.concat($board_id.bytes)
$header_cksum = calculate_checksum header_arr , header_arr.length
header_arr=header_arr_tmp.dup
header_arr.concat([$header_cksum].pack('L').bytes.reverse)
header_arr.concat($board_id.bytes)
File.open($chk_file_path,'wb' ) do |file|
  file.write(header_arr.pack('C*'))
  file.write(f_buffer.pack('C*'))
 # header_arr.each { |byte_array| file.write(byte_array ) }
#  file.write(f_buffer)
end
File.open($chk_file_path,'wb' ) do |file|
  file.write(header_arr.pack('C*'))
  file.write(f_buffer.pack('C*'))
 # header_arr.each { |byte_array| file.write(byte_array ) }
#  file.write(f_buffer)
end
