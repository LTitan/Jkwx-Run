# -*- coding: UTF-8 -*-

# 健康我行云跑步程序
import requests
import datetime
import time
import random
import base64
import urllib
from sqlConnect import *
from MyCode import *


now = datetime.datetime.now().timetuple().tm_yday
source_url = 'http://www.ccxyct.com:8080'
myaes = AESCipher('loaes2019*(#$cry')
session = requests.session()


def get_unix_time(time_str):
    timeArray = time.strptime(time_str, '%Y-%m-%d %H:%M:%S')
    return int(time.mktime(timeArray))

def get_run_time():
    time_now = datetime.datetime.now()
    time_now_str = datetime.datetime.strftime(time_now, '%Y-%m-%d %H:%M:%S')
    time_pre = time_now + datetime.timedelta(minutes=-random.randint(11, 19), seconds=random.randint(10, 50));
    time_pre_str = datetime.datetime.strftime(time_pre, '%Y-%m-%d %H:%M:%S')
    return  time_pre_str,time_now_str

def login_to_getId(stu_number, header):
    stu_password = '123456'
    md5_password = string_md5(stu_password)
    
    user_datas = {
        'stuNum': stu_number,
        'phoneNum': '14312354',
        'passWd': md5_password,
        'schoolId': '60',
        'stuId': '6',
        'token': ''
    }
    login_url = source_url + '/sunShine_Sports-server1/loginSport.action'
    re = session.post(login_url, headers=header, data= user_datas)
    return re.json()
    
def i_wanna_run(sex, stu_id, head):
    post_result_url = source_url+'/sunShine_Sports-server1/xtUploadData.action'
    begin_time,end_time = get_run_time()
    
    unix_time = str(get_unix_time(end_time)) #时间戳
    android = "Android,23,6.1.0, "
    
    bzcode = "["+unix_time+", "+android+header2['IMEI']+", "+header2['IMSI']+"]"
    bzcode = base64.b64encode(bzcode.encode('utf-8'))

    bzcode = myaes.encrypt(bzcode.decode('utf-8'))
    km= 3.982 if sex=='M' else 2.953
    xtcode = string_md5(str(stu_id)+begin_time+str(km)+'androidmu3232chang*^12')
    temp = xtcode[7]+xtcode[3]+xtcode[15]+xtcode[24]+xtcode[9]+xtcode[17]+xtcode[29]+xtcode[23]
    xtcode = myaes.encrypt(temp)
    
    licode = string_md5(xtcode.upper()+bzcode.upper()+'androidmu3232chang*^12')
    temp = licode[7]+licode[3]+licode[11]+licode[20]+licode[9]+licode[14]+licode[29]+licode[21]
    #print("licode1:\t"+licode)
    licode = myaes.encrypt(temp)
    #print(xtcode) 
    #print(bzcode)
    #print("licode2:\t"+licode)
    
    km_datas={
        'results':str(km),
        'beginTime':begin_time,
        'endTime':end_time,
        'isValid':'1',
        'schoolId':'60',
        'xtCode': xtcode.upper(),
        'bz':bzcode.upper(),
        'li':licode.upper()
    }
    
    re = session.post(post_result_url, headers =head, data= km_datas)
    print(re.json())
def how_much(head):
    result_rul = source_url + '/sunShine_Sports-server1/xtGetSportResult.action?flag=0'
    re = session.get(result_rul, headers = head)
    return (re.json()['result'])

xh = query_data(now)

for x in xh:
    imeis, imsis = query_imei_imsi(x[0])
    header = {
        'User-Agent': 'Dalvik/2.2.2 (Linux; U; Android 6.0.1; Mi6x Build/NJH47F)',
        'Content-Type': 'application/x-www-form-urlencoded',
        'app': 'com.ccxyct.sunshinemotion',
        'Ver': '2.2.2',
        'Device': 'Android,23,6.1.0',
        'Screen': '1080x1920',
        'IMEI': imeis,
        'IMSI': imsis,
        'Host': 'www.ccxyct.com:8080',
        'Connection': 'Keep-Alive',
        'Accept-Encoding': 'gzip',
        'UserID': '0',
        'TokenID': '',
        'crack': '0'
    } 
    
    js = login_to_getId(x[0], header)
    
    header2 = {
        'User-Agent': 'Dalvik/2.2.2 (Linux; U; Android 6.0.1; Mi6x Build/NJH47F)',
        'Content-Type': 'application/x-www-form-urlencoded',
        'app': 'com.ccxyct.sunshinemotion',
        'Ver': '2.2.2',
        'Device': 'Android,23,6.0.1',
        'Screen': '1080x1920',
        'IMEI': imeis,
        'IMSI': imsis,
        'Host': 'www.ccxyct.com:8080',
        'Connection': 'Keep-Alive',
        'Accept-Encoding': 'gzip',
        'UserID': str(js['UserInfo']['id']),
        'TokenID': js['TokenID'],
        'crack': '0'
    }        
    #print(how_much(header2))
    #print(x[0])
    i_wanna_run(js['UserInfo']['sex'], js['UserInfo']['id'], header2)
    s = how_much(header2)
    print(str(s))
    update_data(x[0], float(s), now)
    time.sleep(random.randint(5,12))

db_close()