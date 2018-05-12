
// RunDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Run.h"
#include "RunDlg.h"
#include "afxdialogex.h"
#include "GetStuId.h"
#include <afxinet.h> 
#include <wincrypt.h>
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
	, m_how_much_km(_T(""))
	, m_stu_name(_T(""))
	, m_old(_T(""))
	, m_new(_T(""))
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
	DDX_Text(pDX, IDC_KM, m_how_much_km);
	DDX_Control(pDX, IDC_COMBO1, m_Phone_name);
	DDX_Control(pDX, IDC_COMBO2, m_Phone_value);
	DDX_Text(pDX, IDC_STU, m_stu_name);
	DDX_Text(pDX, IDC_EDIT4, m_old);
	DDX_Text(pDX, IDC_EDIT5, m_new);
}

BEGIN_MESSAGE_MAP(CRunDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CRunDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRunDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CRunDlg::OnBnClickedButton3)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CRunDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON4, &CRunDlg::OnBnClickedButton4)
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
	m_passWd = L"请输入密码(不输入默认123456)";

	GetLocalTime(&st);
	m_sysTime = L"系统时间:";
	
	temp.Format(L"%4d-%02d-%02d", st.wYear, st.wMonth, st.wDay);
	m_sysTime += temp;


	m_Phone_name.AddString(L"小米");
	m_Phone_name.AddString(L"华为");
	m_Phone_name.AddString(L"VIVO");
	m_Phone_name.AddString(L"OPPO");
	m_Phone_name.AddString(L"一加");
	m_Phone_name.AddString(L"Iphone");
	m_Phone_name.AddString(L"魅族");
	
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

BOOL CRunDlg::GetMd5(CString strInput, CString &strOutput)
{
	HCRYPTPROV hProv = NULL;
	if (CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT) == FALSE)       //获得CSP中一个密钥容器的句柄  
	{
		return FALSE;
	}
	HCRYPTPROV hHash = NULL;
	//初始化对数据流的hash，创建并返回一个与CSP的hash对象相关的句柄。这个句柄接下来将被    CryptHashData调用。  
	if (CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash) == FALSE)
	{
		return FALSE;
	}

	DWORD lenOfBytes;
	USES_CONVERSION;
	char* input = W2A(strInput);
	lenOfBytes = strlen(input);
	if (CryptHashData(hHash, (BYTE*)input, lenOfBytes, 0) == FALSE)      //hash文件    
	{
		return FALSE;
	}

	BYTE *pbHash = NULL;
	DWORD dwHashLen = sizeof(DWORD);
	if (!CryptGetHashParam(hHash, HP_HASHVAL, NULL, &dwHashLen, 0))
	{
		return FALSE;
	}
	pbHash = (byte*)malloc(dwHashLen);
	if (CryptGetHashParam(hHash, HP_HASHVAL, pbHash, &dwHashLen, 0))//获得md5值   
	{
		for (DWORD i = 0; i < dwHashLen; i++)         //输出md5值   
		{
			TCHAR str[1024] = { 0 };
			CString strFilePartM = _T("");
			_stprintf(str, _T("%02x"), pbHash[i]);
			strOutput += str;
		}
	}
	free(pbHash);

	//善后工作  
	if (CryptDestroyHash(hHash) == FALSE)            
	{
		return FALSE;
	}
	if (CryptReleaseContext(hProv, 0) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

void CRunDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_passWd = L"NULL";
	UpdateData(TRUE);
	//MessageBox(m_passWd[0]);
	bool lg = 0, check = 0;
	string num = CStringA(m_StuNum);
	string passwd;
	CString tem_wd;
	if (m_passWd[0]!=L'请'&&m_passWd!="")
	{
		GetMd5(m_passWd, tem_wd);
	}
	else
	{
		GetMd5(L"123456", tem_wd);
	}
	passwd = CStringA(tem_wd);
	string stu_name;
	connectGetID(num, lg, check, id,stu_name,passwd);
	if (check)
	{
		m_how_much_km = L"已跑公里数:" + flash_how_much(id);
		m_stu_name = L"亲爱的" + CStringW(stu_name.c_str()) + L"同学，欢迎使用！";
		UpdateData(FALSE);
		//MessageBox(CStringW(id.c_str()));
		MessageBox(L"登录成功");
	}
}



void CRunDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!id.length())
		return;
	UpdateData(TRUE);
	bool post = 0;
	postKm(m_km, id, post,st);

	if (!post)
		MessageBox(L"成功");
}


void CRunDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (id.length())
	{
		m_how_much_km = L"已跑公里数:" + flash_how_much(id);
		UpdateData(FALSE);
	}

}


void CRunDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CDialogEx::OnTimer(nIDEvent);
}


void CRunDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Phone_value.ResetContent();
	int pos = m_Phone_name.GetCurSel();
	switch (pos)
	{
	case 0:
		
		m_Phone_value.AddString(L"Mi 6");
		m_Phone_value.AddString(L"Mix 2s");
		m_Phone_value.AddString(L"Mi 5");
		m_Phone_value.AddString(L"Mi 5s");
		m_Phone_value.AddString(L"Mix 2");
		m_Phone_value.AddString(L"Max 2");
		break;
	case 1:
		m_Phone_value.AddString(L"Meta 10");
		m_Phone_value.AddString(L"荣耀 9");
		m_Phone_value.AddString(L"P20");
		m_Phone_value.AddString(L"P10");
		m_Phone_value.AddString(L"畅想 8");
		m_Phone_value.AddString(L"Nova 2");
		break;
	case 2:
		m_Phone_value.AddString(L"垃圾手机");
		break;
	case 3:
		m_Phone_value.AddString(L"垃圾手机");
		break;
	case 4:
		m_Phone_value.AddString(L"一加5T");
		m_Phone_value.AddString(L"一加3");
		break;
	default:
		break;
	}
		
	
}


void CRunDlg::OnBnClickedButton4()
{
	UpdateData(TRUE);
	GetMd5(m_old, old);
	GetMd5(m_new, new_p);
	if (change_passwd(id, old, new_p))
	{
		MessageBox(L"成功");

	}
	else MessageBox(L"失败");
}
