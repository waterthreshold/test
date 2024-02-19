# Monitor disk

For monitor real server disk usage and send notify in webhook to teams fourm

##option 
	-i: net work interface (required)
	-p: the mount system path (required)
	-g: alram threshold (Percent %)

## example 
./monitor_disk -i ens160 -p /disk2 -g 90
