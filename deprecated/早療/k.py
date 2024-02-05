from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from PIL import Image
import pytesseract
#from ps4 import beautifulsoup4
import time
def check_text(txt,style):
    
    ret=False
    if style.find('blue') == -1:
        return ret
    for line in txt.split('\n'):
        #if line.find("初診名額") != -1 and line.find('額滿') == -1:
        if line.find("初診名額") != -1:
            ret=True
            print(line)
            break
    return ret
        
def OCR():
    img=Image.open('XXXXXX') # your path
    text = pytesseract.image_to_string(img)
    print (text)
    return text

chrome_options = webdriver.ChromeOptions()
chrome_options.binary_location = '/usr/bin/chromium-browser' 
driver = webdriver.Chrome('/snap/bin/chromium.chromedriver', options=chrome_options)
driver.get('https://cdaic.tpech.gov.tw/CH/EICN020.aspx')

driver.find_element('id','ctl00_ContentPlaceHolder1_Button4').click()
items = driver.find_elements(By.CLASS_NAME,"block")
#print (type(items),len(items))
for item in items:
    txt=item.text
    style=item.get_attribute('style')
#    print(txt,style)

    if check_text(txt,style):
        item.click()
        print(txt)
        driver.switch_to.frame("ctl00_ContentPlaceHolder1_EICN021Frame")
        driver.find_element(By.ID,'txtPAT_ID').send_keys('') #身分正字號
        driver.find_element(By.ID,'txtBirthday').send_keys('XXX/XX/XX') #生日
        driver.find_element(By.CLASS_NAME,'ui-datepicker-close ').click()
        driver.find_element(By.ID,'txtCELLPHONE').send_keys('09XXXXXXXX') #電話號碼

        driver.find_element(By.ID,'txt_input').send_keys('')
        time.sleep (20)
        break
