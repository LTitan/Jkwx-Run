// Cpasswd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Run.h"
#include "Cpasswd.h"
#include "afxdialogex.h"


// Cpasswd �Ի���

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


// Cpasswd ��Ϣ�������


void Cpasswd::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_edit == "413")
	{
		Cpasswd::OnOK();
	}
	else
	{
		MessageBox(L"�������");
	}
}


void Cpasswd::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}


//void Cpasswd::OnOK()
//{
//	// TODO: �ڴ����ר�ô����/����û���
//
//	CDialogEx::OnOK();
//}


BOOL Cpasswd::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ����ר�ô����/����û���

	exit(0);
}
