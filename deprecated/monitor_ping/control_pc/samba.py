import requests
import json
import os,sys
IP="192.168.7.1"
def main (IP):
    url="http://{0}/ajax/devices_table_result".format(IP)
    header={ "Content-Type": "application/json"}
    print (url )    
    r=requests.post(url,headers=header, data='')
    #print (r.text)
    parsed=json.loads(r.text)
    num=parsed['numberOfDevices']
    for i in range(num):
        #print (parsed['connDevices'][i]['name'])
        if parsed['connDevices'][i]['name'] == "jeff-ThinkPad-E14-Gen-2":
            findmyip=parsed['connDevices'][i]['ip']
            break

    with open  ('netuse.bat','r') as file:
        content= file.read()
        new_content = content.replace('<REPLACE_IP_HERE>',findmyip)
        
    with open ('new_netuse.bat','w') as file: 
        file.write (new_content)
if __name__ == '__main__':
    args = sys.argv[1:]
    if len(args) != 1 :
        print ('please input the gateway IP')
        exit()
    IP=args[0]
    main(IP)
