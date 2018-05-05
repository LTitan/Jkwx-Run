#pragma once


// Cpasswd 对话框

class Cpasswd : public CDialogEx
{
	DECLARE_DYNAMIC(Cpasswd)

public:
	Cpasswd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cpasswd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PASSWD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_edit;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
//	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnCancel();
};
