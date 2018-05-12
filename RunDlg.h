
// RunDlg.h : 头文件
//

#pragma once
#include "Cpasswd.h"
#include "afxwin.h"


// CRunDlg 对话框
class CRunDlg : public CDialogEx
{
// 构造
public:
	CRunDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RUN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
