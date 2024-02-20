import requests
from os.path import *
import time
IP="192.168.0.20"
username="admin"
password="passwd"
INITIAL_COOKIES={"auth_token":"eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJleHAiOiIyMjA3MDU0IiwiaXNzIjoid3d3Lm5ldGdlYXIuY29tIiwic3ViIjoiY3VybC83LjY4LjAifQ==.af3f924b781302bcc046dbc47d4f12d9f5441c351d225c02487fd11388c9b9f4" , "Path":"/"}
def get_cookies(url,username,password):
    r=requests.get(url,auth=(username,password),cookies=INITIAL_COOKIES)
#    print(r.headers['Set-Cookie'])
    return r.headers['Set-Cookie']
def get_dashinfo(url,username,password,cookie):
    r=requests.get(url,auth=(username,password),headers={"Cookie" : cookie})
    #print(r.text)
    data=r.text
    d=data.split(';')
    print ("Wan Status: ",d[0])
    print ("Satellite Count: ",d[1])
    print ("Connection Device Count: ",d[2])

def device_info(IP,username,password,cookies):
   time_stamp = int(time.time())
   url="http://{0}/DEV_device_info.htm?ts={1}".format(IP,time_stamp)
   r= requests.get(url,auth=(username,password),headers={'Cookie':cookies})
   print (r.text)
def main ():
    if not exists('cookie'):
        url="http://{0}".format(IP)
        cookies=get_cookies(url,username,password)
    else:
        with open('cookie')  as f:
            cookies=str(f.read())
    url="http://{0}/basic_home_result.txt".format(IP)
    get_dashinfo(url,username,password,cookies)
    device_info(IP,username,password,cookies)
    


if __name__ == '__main__':
    main()
