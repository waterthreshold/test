from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from PIL import Image
from io import BytesIO
import requests
import json
import os 
def get_linetoken():
    file_path=os.environ['HOME'] + "/.config/LineNotify/sensitiveData.json"
    with open(file_path , "r") as f: 
        content = f.read()
        d=json.loads(content)
        return d['token']
    return '.config'

def send_notify(url,image_path):

    msg="Learn more: {}".format(url)
    url='https://notify-api.line.me/api/notify'
    token=get_linetoken()
    headers={"Authorization": token}

    datas= {
        "message" : msg,
    }
    files={
        "imageFile": open(image_path,'rb')
    }
    r = requests.post(url,headers=headers, data=datas,files=files)
    if r.status_code == 200:
        print ('send notify success')
    else:
        print ('send notify failed')

# URL of the webpage containing the div element
url = 'https://tw.dictionary.search.yahoo.com/'

# Path to the Chrome WebDriver executable
webdriver_path = Service ('/snap/bin/chromium.chromedriver')

# Set up Chrome WebDriver
options = webdriver.ChromeOptions()
options.add_argument('--headless')  # Run Chrome in headless mode
driver = webdriver.Chrome(service=webdriver_path, options=options)

# Open the webpage
driver.get(url)

# Find the div element with class="oo xxx"
div_element = driver.find_element(By.CSS_SELECTOR,'.sys_dict_word_card')
#url_captured = driver.find_element(By.CSS_SELECTOR,'[class="sys_dict_word_card"] > div > a[href]')
url_captured = driver.find_element(By.CSS_SELECTOR,'.dd.cardDesign.sys_dict_word_card > div > p > a')
url_text= url_captured.get_attribute('href')
print (url_text)

# Capture the screenshot of the div element
screenshot = div_element.screenshot_as_png

# Close the WebDriver
driver.quit()

# Convert the screenshot bytes to a PIL Image object
image = Image.open(BytesIO(screenshot))

# Save the image
image.save('captured_image.png')
send_notify(url=url_text,image_path='captured_image.png')
print("Image captured successfully.")

