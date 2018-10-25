#sql connect
import pymysql

config = {
    'host': '127.0.0.1',
    'port': 3306,
    'user': 'root',
    'passwd': 'lyf110110@LYF',
    'db': 'users_ccu',
    'charset': 'utf8'
}
db = pymysql.connect(**config)
cursor = db.cursor()

def query_imei_imsi(xh):
    sql = 'select imei, imsi from jkwx where jkwx.xh='+ xh +';'
    cursor.execute(sql)
    res = cursor.fetchall()
    return res[0][0], res[0][1]

def query_data(now):
    sql = "select xh from jkwx where jkwx.over=0 and jkwx.date !=%d;" % now
    cursor.execute(sql)
    res = cursor.fetchall()
    #print(res)
    return res
def update_data(xh, s, now):
    if(s>=80.0):
        over = 1
    else:
        over = 0
    sql = "update jkwx set jkwx.km=%.3f, jkwx.over=%d, jkwx.date=%d where jkwx.xh=%s" % (s, over, now, xh)
    try:
        cursor.execute(sql)
        db.commit()
        return True
    except:
        db.rollback()
    return False
def db_close():
    db.close()