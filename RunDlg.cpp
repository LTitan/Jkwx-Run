
// RunDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Run.h"
#include "RunDlg.h"
#include "afxdialogex.h"
#include "GetStuId.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

string id;
CString temp;
SYSTEMTIME st;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRunDlg 对话框



CRunDlg::CRunDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RUN_DIALOG, pParent)
	, m_StuNum(_T(""))
	, m_passWd(_T(""))
	, m_km(0)
	, m_sysTime(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_StuNum);
	DDX_Text(pDX, IDC_EDIT1, m_passWd);
	DDX_Text(pDX, IDC_EDIT3, m_km);
	DDV_MinMaxFloat(pDX, m_km, 0, 4.5);
	DDX_Text(pDX, IDC_TIME, m_sysTime);
}

BEGIN_MESSAGE_MAP(CRunDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CRunDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRunDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CRunDlg 消息处理程序

BOOL CRunDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	login.DoModal();
	init_phone_num();
	my_fill();
	m_passWd = L"请输入默认密码123456";

	GetLocalTime(&st);
	m_sysTime = L"系统时间:";
	
	temp.Format(L"%4d-%02d-%02d", st.wYear, st.wMonth, st.wDay);
	m_sysTime += temp;
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRunDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRunDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRunDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRunDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	bool lg = 0, check = 0;
	string num = CStringA(m_StuNum);
	connectGetID(num, lg, check, id);
	if (check)
		MessageBox(L"登录成功");
}



void CRunDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!id.length())
		return;
	UpdateData(TRUE);
	bool post = 0;
	postKm(m_km, id, post,st);

	if (post)
		MessageBox(L"成功");
	else
		MessageBox(CStringW(id.data()));
}
