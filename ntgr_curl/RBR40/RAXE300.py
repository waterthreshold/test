import requests 
from os.path import *
IP="192.168.1.1"
username="admin"
password="Aa_12345678"
def get_newtoken(IP,username,password):
    pega_url="http://{0}/php/db/attachedDevTable_data.php".format(IP)
    r=requests.get(pega_url,auth=(username,password))
    token= r.headers['Set-Cookies']
    return token

def test_connection(IP,username,password,session):
    pega_url="http://{0}/php/db/attachedDevTable_data.php".format(IP)
    r=requests.get(pega_url,auth=(username,password),cookies={'session':session})
    status_code = r.status_code
    if status_code == 401:
        return False
    return True
        
def get_attahdevtable(IP,username,passowrd,session):
    pega_url="http://{0}/php/db/attachedDevTable_data.php".format(IP)
    r=requests.get(pega_url,auth=(username,password),headers={'Cookies':session})
    print (r.text)
def main():
    token="RVDZnNKG1RMdBBz2zzuHlv5nOTOHorO3" 
    success = test_connection(IP,username,password,token) 
    if not success:
        token = get_newtoken (IP,username,password)
    get_attahdevtable(IP,username,password,token)

    

if __name__ == '__main__':
    main()
