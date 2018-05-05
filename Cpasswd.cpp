// Cpasswd.cpp : 实现文件
//

#include "stdafx.h"
#include "Run.h"
#include "Cpasswd.h"
#include "afxdialogex.h"


// Cpasswd 对话框

IMPLEMENT_DYNAMIC(Cpasswd, CDialogEx)

Cpasswd::Cpasswd(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PASSWD, pParent)
	, m_edit(_T(""))
{

}

Cpasswd::~Cpasswd()
{
}

void Cpasswd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(Cpasswd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Cpasswd::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cpasswd::OnBnClickedButton2)
END_MESSAGE_MAP()


// Cpasswd 消息处理程序


void Cpasswd::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_edit == "413")
	{
		Cpasswd::OnOK();
	}
	else
	{
		MessageBox(L"密码错误");
	}
}


void Cpasswd::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


//void Cpasswd::OnOK()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//
//	CDialogEx::OnOK();
//}


BOOL Cpasswd::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN&&pMsg->wParam == VK_ESCAPE)
	{
		
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		this->OnBnClickedButton1();
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void Cpasswd::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	exit(0);
}
