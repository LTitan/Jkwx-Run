
// RunDlg.h : ͷ�ļ�
//

#pragma once
#include "Cpasswd.h"

// CRunDlg �Ի���
class CRunDlg : public CDialogEx
{
// ����
public:
	CRunDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RUN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	Cpasswd login;

protected:
	CString m_StuNum;
public:
	CString m_passWd;
	afx_msg void OnBnClickedButton1();
private:
	float m_km;
public:
	afx_msg void OnBnClickedButton2();
private:
	CString m_sysTime;
};
