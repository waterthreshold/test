#!/usr/bin/env lua
firmware_path= arg[1]
version = arg[2]
board_id = arg[3]
sku=1
kernel_cksum=0
rootfs_cksum=0
kernel_length=0
rootfs_length=0
image_cksum=0
header_cksum=0

function calculate_cksum(s,size)
	local c0 , c1 = 0 , 0
	for i=1,size do 
		local byte = string.byte(s:sub(i,i))
		c0 =  c0+ byte
		c1 = c1 +c0
	end
	b= ( c0 & 65535) + ((c0 >>16) & 65535)
	c0 = (( b >> 16 ) +b ) & 65535
	b= (c1 & 65535 ) + ((c1 >> 16) & 65535)
	c1= ((b >> 16 ) + b ) & 65535

	cksum = ((c1 << 16) | c0 )
	return cksum
end

function validation_version(version ) 
	local t = {}
	local main_ver=""
	local sub_ver=""
	local str= ""
	print (version)
	for k,v in string.gmatch(version, "(.+)_(.+)")  do
		main_ver = k 
		sub_ver = v 
	end
	print ("main version:" .. main_ver .. ", sub version:" .. sub_ver)
	for substring in main_ver:gmatch("[^.]+")  do 
		table.insert (t,substring)
	end
	for substring in sub_ver:gmatch("[^.]+")  do 
		table.insert (t,substring)
	end
	if #t ~= 7 then
		print ("version need 7 column number")
		os.exit()
	end 
	for key, substring in pairs(t) do 
		byte = tonumber (substring)
		print (byte)
		if byte > 255 then
			print ("version number must lower than 255 for each number")
			os.exit ()
		end

		str = str .. string.char(byte)

	end

	return str
end 

function number2sting(n,byte)
	local str="" 
	for i=3,0,-1 do 
		str = str .. string.char (n >> (8*i) & 0xFF )
	end 
	return str
end
function main ()
	print("firmware_path: " .. firmware_path ..", version: " .. version ..",board_id:".. board_id)
	new_firmware_path =  firmware_path .. ".chk"
	file = io.open (firmware_path,"rb")
	if not file then
		print('Failed to open the file')
		return 
	end
	local f_buffer = file:read("*a")
	file:close()
	header_buf = "*#$^"
	--header_len =  40 +string.len(board_id)
	header_len =  40 + #board_id
	header_len_string = string.char (header_len >> ( 8*3 ) & 0xFF , header_len >> 8*2 & 0xFF ,header_len >> 8 * 1 & 0xFF  , header_len >> 8*0 & 0xFF)
	header_buf = header_buf .. header_len_string
	header_buf = header_buf .. string.char (sku)
	version_buf= validation_version (version)
	header_buf = header_buf .. version_buf
	header_buf=header_buf .. number2sting (calculate_cksum (f_buffer,#f_buffer),4) 
	header_buf=header_buf .. number2sting (rootfs_cksum,4) 
	header_buf=header_buf .. number2sting (#f_buffer,4) 
	
	header_buf=header_buf .. number2sting (rootfs_length,4)
	image_cksum=kernel_cksum
	--header_buf=header_buf .. number2sting (image_cksum,4)
	header_buf=header_buf .. number2sting (calculate_cksum (f_buffer,#f_buffer),4) 
	
	header_buf_tmp = header_buf
	header_buf=header_buf .. number2sting (header_cksum,4)
	header_buf = header_buf .. board_id
	header_cksum = number2sting (calculate_cksum (header_buf,#header_buf),4)
	header_buf_tmp = header_buf_tmp.. header_cksum
	header_buf_tmp = header_buf_tmp .. board_id 
	header_buf = header_buf_tmp

	file = io.open(new_firmware_path,"wb")

	file:write(header_buf)
	file:write(f_buffer)
	file:close()

end
if  #arg ~= 3  then
	
	print ("Must include 4 parameter <firmware_path> <version> <board_id>")
	os.exit()
end

main ()
