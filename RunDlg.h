
// RunDlg.h : ͷ�ļ�
//

#pragma once
#include "Cpasswd.h"
#include "afxwin.h"


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
	CString m_passWd=L"0";
	afx_msg void OnBnClickedButton1();
private:
	float m_km;
public:
	afx_msg void OnBnClickedButton2();
private:
	CString m_sysTime;
	CString m_how_much_km;
public:
	afx_msg void OnBnClickedButton3();
	CComboBox m_Phone_name;
	CComboBox m_Phone_value;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCbnSelchangeCombo1();
	CString m_stu_name;
	afx_msg BOOL GetMd5(CString strInput, CString &strOutput);
	afx_msg void OnBnClickedButton4();
	CString m_old,old;
	CString m_new,new_p;
};
