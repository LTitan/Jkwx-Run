# -*- coding: UTF-8 -*-
import urllib.request,urllib.error,urllib.parse
import http.cookiejar
import hashlib
import datetime
import random

imeis_lists=[
    '868479023454330','868429023474380','868297025428316','848279063754350',
    '682371158412125','643377758437925'
]

cookie_filename='cookie.txt'
index=0
cookie=http.cookiejar.MozillaCookieJar(cookie_filename)
handler=urllib.request.HTTPCookieProcessor(cookie)

op=urllib.request.build_opener(handler)

source_url = 'http://www.ccxyct.com:8080/sunShine_Sports/'

def string_md5(code):
    hl=hashlib.md5()
    hl.update(code.encode(encoding='utf-8'))
    return hl.hexdigest()


def login_to_getId():
    stu_number = input("输入学号\n")
    stu_password = input("输入密码\n")
    stu_phone = input("输入手机号\n")
    index=int(input("输入1-5之间的幸运数字,注意保存，方便后面使用\n"))
    #  密码md5处理
    md5_password = string_md5(stu_password)

    user_datas = {
        'stuNum': stu_number,
        'phoneNum': stu_phone,
        'passWd': md5_password,
        'schoolId': '60',
        'stuId': '6',
        'token': ''
    }
    # 数据转化
    post_datas = urllib.parse.urlencode(user_datas).encode()

    headers = {
        'User-Agent': ' Dalvik/2.1.0 (Linux; U; Android 7.1.2; Mi6x Build/NJH47F)',
        'Content-Type': 'application/x-www-form-urlencoded',
        'app': 'com.ccxyct.sunshinemotion',
        'Ver': '2.1.0',
        'Device': 'Android,25,7.1.2',
        'Screen': '1080x1920',
        'IMEI': imeis_lists[index],
        'IMSI': '1234567890',
        'Host': 'www.ccxyct.com:8080',
        'Connection': 'Keep-Alive',
        'Accept-Encoding': 'gzip',
        'UserID': '0',
        'TokenID': '',
        'crack': '0'
    }
    login_url = source_url + 'loginSport.action'
    request = urllib.request.Request(login_url, post_datas, headers)
    try:
        respon = op.open(request)
    except urllib.error.URLError as e:
        print(e.code)
    return respon.read().decode('utf-8')

def get_run_time():
    time_now = datetime.datetime.now()
    time_now_str = datetime.datetime.strftime(time_now, '%Y-%m-%d %H:%M:%S')
    time_pre = time_now + datetime.timedelta(minutes=-random.randint(11, 19), seconds=random.randint(10, 50));
    time_pre_str = datetime.datetime.strftime(time_pre, '%Y-%m-%d %H:%M:%S')
    return  time_pre_str,time_now_str


def get_now_run(stu_id,token_id):
    headers_real = {
        'User-Agent': ' Dalvik/2.1.0 (Linux; U; Android 7.1.2; X520 Build/NJH47F)',
        'Content-Type': 'application/x-www-form-urlencoded',
        'app': 'com.ccxyct.sunshinemotion',
        'Ver': '2.1.0',
        'Device': 'Android,25,7.1.2',
        'Screen': '1080x1920',
        'IMEI': imeis_lists[index-1],
        'IMSI': '1234567890',
        'Host': 'www.ccxyct.com:8080',
        'Connection': 'Keep-Alive',
        'Accept-Encoding': 'gzip',
        'UserID': stu_id,
        'TokenID': token_id,
        'crack': '0'
    }

    result_rul = source_url + 'xtGetSportResult.action'
    request = urllib.request.Request(result_rul, b'flag=0', headers_real)
    try:
        respon = op.open(request)
    except urllib.error.URLError as e:
        print(e.code)
    return respon.read().decode('utf-8'),headers_real

text = login_to_getId()

stu_id=text[text.find('id')+4:text.find('inClassID')-2]
pos=text.find('TokenID')
token_id=text[pos+10:pos+42]


text_result ,headers_real = get_now_run(stu_id,token_id)

pos = text_result.find('result')
print('登录成功，您当前已跑'+text_result[pos+8:pos+12]+'公里')


post_result_url = source_url+'xtUploadData.action'

begin_time,end_time = get_run_time()


km=input('输入要跑的公里数(小数点后一位，如2.0)\n')
km += str(random.randint(10,77))

xtcode = string_md5(stu_id+begin_time+km+'stlchang')

km_datas={
    'results':km,
    'beginTime':begin_time,
    'endTime':end_time,
    'isValid':'1',
    'schoolId':'60',
    'xtCode':xtcode[7]+xtcode[3]+xtcode[15]+xtcode[24]+xtcode[9]+xtcode[17]+xtcode[29]+xtcode[23],
    'bz':''
}

post_datas = urllib.parse.urlencode(km_datas).encode()

request=urllib.request.Request(post_result_url,post_datas,headers_real)
try:
    respon=op.open(request)
except urllib.error.URLError as e:
    print(e.code)

run_end=respon.read().decode('utf-8')
if run_end.find('1')!=-1:
    print('已跑完,是否刷新公里数(Y/N)?')
    yes_or_no=input()
    if(yes_or_no=='Y' or yes_or_no=='y'):
        text_result, headers_real = get_now_run(stu_id, token_id)

        pos = text_result.find('result')
        print('刷新成功，您当前已跑' + text_result[pos + 8:pos + 12] + '公里')
    else:
        exit(1)
else:
    print('跑步失败')

