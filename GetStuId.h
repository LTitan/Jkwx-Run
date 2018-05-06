#pragma once
#include "stdafx.h"

#include <afxwin.h>
#include <WinSock2.h>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#pragma comment(lib,"ws2_32.lib")


using namespace std;
string re;

string phoneNum[] = {"131","132","133","134","135","136","137","138","139",
"181","182","183","184","185","186","187","188","189",
"151","152","153","154","155","156","157","158","159"};

string true_num;

string tm_select[60];
string t_early, t_now;

void init_phone_num()
{
	string phone_last="00000000";
	srand((unsigned int)time(NULL));
	int n = rand() % 27;
	for (unsigned int i = 0; i < 8; i++)
	{
		phone_last[i] = rand() % 10 - '0';
	}
	true_num = phoneNum[n] + phone_last;
}
void my_fill()
{
	
	for (int i = 0; i < 60; i++)
	{
		if (i < 10)
		{
			stringstream ss;
			ss << "0" << i;
			tm_select[i] = ss.str();
		}
		else {
			stringstream ss;
			ss << i;
			tm_select[i] = ss.str();
		}
	}
}
void init_time(SYSTEMTIME st,float s)
{
	srand((unsigned int)time(NULL));
	CString t,h_run;
	int bei;
	t.Format(L"%04d-%02d-%02d ", st.wYear, st.wMonth, st.wDay);
	h_run.Format(L"%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond);
	string YMD = CStringA(t),hour;
	hour = CStringA(h_run);
	t_now = YMD + hour;
	if (s >= 2 && s < 3) bei = 20;
	if (s >= 3 && s < 4) bei = 30;
	if (s >= 4) bei = 40;
	bei = st.wMinute - bei;
	if (bei < 0)
	{
		h_run.Format(L"%02d:%02d:", st.wHour-1,60+bei);
		hour = CStringA(h_run);
		t_early = YMD+hour + tm_select[rand() % 60];
	}
	else
	{
		h_run.Format(L"%02d:%02d:", st.wHour, bei);
		hour = CStringA(h_run);
		t_early = YMD+hour + tm_select[rand() % 60];
	}

}
CString flash_how_much(string id)
{
	WSADATA wData;
	::WSAStartup(MAKEWORD(2, 2), &wData);
	SOCKET clientSocket = socket(AF_INET, 1, 0);
	struct sockaddr_in SeverAddr = { 0 };
	int Ret = 0;
	int AddrLen = 0;
	HANDLE hThread = 0;

	string toSend = "POST /sunShine_Sports/xtGetSportResult.action HTTP/1.1\r\n";
	string theId = "UserID:" + id + "\r\n";
	toSend += theId;
	toSend += "crack: 0\r\n"
		"Accept-Encoding:gzip\r\n"
		"Content-Length:6\r\n"
		"Content-Type:application/x-www-form-urlencoded\r\n"
		"Host:www.ccxyct.com:8080\r\n"
		"User-Agent:Dalvik/2.1.0 (Linux; U; Android 7.1.2; XiaoMi Mi6 MIUI/8.4.12)\r\n\r\n"
		"flag=0";
	const char *buff = toSend.c_str();
	SeverAddr.sin_addr.S_un.S_addr = inet_addr("47.95.192.115");
	SeverAddr.sin_port = htons(8080);
	SeverAddr.sin_family = AF_INET;
	char bufRecv[4096] = { 0 };
	int errNo = 0;
	errNo = connect(clientSocket, (sockaddr *)&SeverAddr, sizeof(SeverAddr));
	if (errNo == 0)
	{
		if (send(clientSocket, buff, strlen(buff), 0) > 0)
		{

		}
		if (recv(clientSocket, bufRecv, 4096, 0) > 0)
		{
			string km = bufRecv;
			int t;
			for (int i = 0; i < km.length(); i++)
			{
				if (km[i] == 't'&&km[i + 1] == '\"'&&km[i + 2] == ':')
				{
					t = i;
					break;
				}
			}
			return CStringW(km.substr(t + 3, 5).c_str());
		}
	}
	else
	{
		errNo = WSAGetLastError();
	}
	::WSACleanup();
}
void Check(string a,bool &c,string &id)
{
	int t=0;
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == 'i'&&a[i + 1] == 'd')
		{
			t = i; break;
		}
	}
	int sum = 0,i=t+4;
	while (a[i] != ',')
	{
		sum++;
		i++;
	}
	id = a.substr(t+4,sum);
	c = true;
}
void connectGetID(string num,bool &lg,bool &check,string &id)
{
	WSADATA wData;
	::WSAStartup(MAKEWORD(2, 2), &wData);

	SOCKET clientSocket = socket(AF_INET, 1, 0);
	struct sockaddr_in SeverAddr = { 0 };
	int Ret = 0;
	int AddrLen = 0;
	HANDLE hThread = 0;
	
	/*

	char *bufSend = "POST /sunShine_Sports/loginSport.action HTTP/1.1\r\n"
		"crack: 0\r\n"
		"Accept-Encoding:gzip\r\n"
		"UserID: 0\r\n"
		"Content-Length:96\r\n"
		"Content-Type:application/x-www-form-urlencoded\r\n"
		"Host:www.ccxyct.com:8080\r\n"
		"User-Agent:Dalvik/2.1.0 (Linux; U; Android 7.1.2; XiaoMi Mi6 MIUI/8.4.12)\r\n\r\n"
		"stuNum=041640720&phoneNum=110&passWd=e10adc3949ba59abbe56e057f20f883e&schoolId=60&stuId=1&token=\r\n\r\n";
		
	*/
	string toSend = "POST /sunShine_Sports/loginSport.action HTTP/1.1\r\n"
		"crack: 0\r\n"
		"Accept-Encoding:gzip\r\n"
		"UserID: 0\r\n"
		"Content-Length:96\r\n"
		"Content-Type:application/x-www-form-urlencoded\r\n"
		"Host:www.ccxyct.com:8080\r\n"
		"User-Agent:Dalvik/2.1.0 (Linux; U; Android 7.1.2; XiaoMi Mi6 MIUI/8.4.12)\r\n\r\n";
	string ch = "stuNum=";
	ch += num;
	string postdata=ch+"&phoneNum="+true_num+"&passWd=e10adc3949ba59abbe56e057f20f883e&schoolId=60&stuId=1&token=\r\n\r\n";
	toSend += postdata;

	const char *buff = toSend.c_str();
	SeverAddr.sin_addr.S_un.S_addr = inet_addr("47.95.192.115");
	SeverAddr.sin_port = htons(8080);
	SeverAddr.sin_family = AF_INET;
	char bufRecv[4096] = { 0 };
	int errNo = 0;
	errNo = connect(clientSocket, (sockaddr *)&SeverAddr, sizeof(SeverAddr));
	if (errNo == 0)
	{
		if (send(clientSocket, buff, strlen(buff), 0) > 0)
		{
			lg = true;
		}
		if (recv(clientSocket, bufRecv, 4096, 0) > 0)
		{
			 re= bufRecv;
			if (lg)
			{
				Check(re, check, id);
			}
		}
	}
	else
	{
		errNo = WSAGetLastError();
	}
	::WSACleanup();
}
string toStringf(float a)
{
	stringstream ss;
	ss << a;
	return ss.str();
}
void postKm(float sum, string &id,bool &pan,SYSTEMTIME st)
{
	init_time(st, sum);
	//int temp=0;
	WSADATA wData;
	::WSAStartup(MAKEWORD(2, 2), &wData);
	SOCKET clientSocket = socket(AF_INET, 1, 0);
	struct sockaddr_in SeverAddr = { 0 };
	int Ret = 0;
	int AddrLen = 0;
	HANDLE hThread = 0;

	string toSend = "POST /sunShine_Sports/xtUploadData.action HTTP/1.1\r\n";	
	string theId = "UserID:" + id + "\r\n";
	toSend += theId;
	toSend += "crack: 0\r\n"
		"Accept-Encoding:gzip\r\n"
		"Content-Length:100\r\n"
		"Content-Type:application/x-www-form-urlencoded\r\n"
		"Host:www.ccxyct.com:8080\r\n"
		"User-Agent:Dalvik/2.1.0 (Linux; U; Android 7.1.2; XiaoMi Mi6 MIUI/8.4.12)\r\n\r\n";

	string  postdata;
	 postdata= "results=" + toStringf(sum) + "25052" + "&beginTime=" + t_early +"&endTime="
		+ t_now+"&isValid=1&schoolId=60&bz=\r\n\r\n";
	toSend += postdata;
	const char *buff = toSend.c_str();
	//id = toSend;
	SeverAddr.sin_addr.S_un.S_addr = inet_addr("47.95.192.115");
	SeverAddr.sin_port = htons(8080);
	SeverAddr.sin_family = AF_INET;
	char bufRecv[4096] = { 0 };
	int errNo = 0;
	errNo = connect(clientSocket, (sockaddr *)&SeverAddr, sizeof(SeverAddr));
	if (errNo == 0)
	{
		if (send(clientSocket, buff, strlen(buff), 0) > 0)
		{
			
		}
		if (recv(clientSocket, bufRecv, 4096, 0) > 0)
		{
			//id = bufRecv;
			if (strcmp(bufRecv, "HTTP/1.1 200 OK") == 0)
				pan = 1;
		}
	}
	else
	{
		errNo = WSAGetLastError();
	}
	::WSACleanup();
}