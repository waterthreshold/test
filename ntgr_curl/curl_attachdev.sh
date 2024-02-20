#!/bin/sh
[ -n "$1" ] && IP=$1 || IP=111.250.205.42
curl --silent -X POST http://admin:Password123@${IP}/ajax/devices_table_result -H "Content-Type: application/json" -d ""
exit $?
