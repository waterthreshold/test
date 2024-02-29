#!/disk2/jeff/mylib/bin/expect
set timeout 300
set host "sftp-v.foxconn.com"
set port 50029
set username "812404"
set password "57j1T1811Z"
set default_dir "temp/jeff"
set config_file "ftpget"
set file [lindex $argv 0]

if { [string compare $file ""] == 0 } {
spawn sftp -P $port $username@$host:$default_dir/$config_file
expect "password:"
send "$password\r"
sleep 2
set f [open "$config_file"]
set file [read $f] 
close $f
}
spawn sftp -P $port $username@$host:$default_dir/$file
expect "password:"
send "$password\r"
expect eof
