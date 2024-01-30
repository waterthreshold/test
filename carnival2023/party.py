#!/usr/bin/env python3 
import requests
import json
noticed_list=["endSignup","startDependentsLogin","startLottery","startMap","startNotify","startShow"]
my_list=[]
def query_all_event():
    url='https://d27vkanbfmjob6.cloudfront.net/api/system/v1/event/queryAllEventState'
    r=requests.get(url)
    content=''
    if r.status_code == 200:
        content=r.content
    return content.decode('ascii')

def traverse_json (data,parent_key=''):
    if isinstance(data,dict):
        for key , value in data.items():
            new_key = f"dict {parent_key}.{key}" if parent_key else key
            traverse_json(value,new_key)
    elif isinstance (data,list):
        for i , item in enumerate(data):
            traverse_json(item, f"{parent_key}[{i}]")
    else:
        if parent_key in noticed_list and data:
            my_list.append(parent_key)
            print(f"{parent_key} : {data}")

def getStoreType():
    url='https://icivetapps.foxconn.com/civetpay/yyhe/foxshop/Api/RequestData.ashx?methodName=getStoreType'
    r=requests.get(url)
    if r.status_code == 200:
        print(r.content.decode('utf-8'))

def getStore(pageindex=1,pageSize=12,token='',getMeal=True):
    url='https://icivetapps.foxconn.com/civetpay/yyhe/foxshop/Api/RequestData.ashx?methodName=getStore'
    url+= "&pageIndex=" + str(pageindex) + "&pageSize=" + str(pageSize) + "&token=" +token
    
    r=requests.get(url)
    if r.status_code == 200:
        print(r.content.decode('utf-8'))
        content=r.content.decode('utf-8')
    
    if getMeal:
        d=json.loads(content)        
        #listofsupplier=[ item["supplier_account"] for item in d['Msg'] ]
        #for suppiler_account in listofsupplier:
        for item in d['Msg']:
            suppiler_account=item['supplier_account']
            name=item['name']
            url_getmeal='https://icivetapps.foxconn.com/civetpay/yyhe/foxshop/Api/RequestData.ashx?methodName=getMeal&supplier_account={}'.format(suppiler_account)
            r=requests.get(url_getmeal)
            #print (url_getmeal)
            if r.status_code == 200:
                path = "stall/"+ name +".json"
                with open(path,'w') as f:
                    f.write(r.content.decode('utf-8'))
                #print(r.content.decode('utf-8'))
                #pass
if __name__ == '__main__':
    content=query_all_event()
    d=json.loads(content)
    if d['code'] == 0:
        #print (d['eventData'])
        traverse_json(d['eventData']) 
    else:
        print('something got wrong get code net equal to 0')
    traverse_json(my_list)
    #getStoreType()
    getStore(pageSize=80,getMeal=True)
