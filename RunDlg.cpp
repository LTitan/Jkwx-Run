
// RunDlg.cpp : ʵ���ļ�
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
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CRunDlg �Ի���



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


// CRunDlg ��Ϣ�������

BOOL CRunDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	login.DoModal();
	init_phone_num();
	my_fill();
	m_passWd = L"����������(������Ĭ��123456)";

	GetLocalTime(&st);
	m_sysTime = L"ϵͳʱ��:";
	
	temp.Format(L"%4d-%02d-%02d", st.wYear, st.wMonth, st.wDay);
	m_sysTime += temp;


	m_Phone_name.AddString(L"С��");
	m_Phone_name.AddString(L"��Ϊ");
	m_Phone_name.AddString(L"VIVO");
	m_Phone_name.AddString(L"OPPO");
	m_Phone_name.AddString(L"һ��");
	m_Phone_name.AddString(L"Iphone");
	m_Phone_name.AddString(L"����");
	
	UpdateData(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRunDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRunDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CRunDlg::GetMd5(CString strInput, CString &strOutput)
{
	HCRYPTPROV hProv = NULL;
	if (CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT) == FALSE)       //���CSP��һ����Կ�����ľ��  
	{
		return FALSE;
	}
	HCRYPTPROV hHash = NULL;
	//��ʼ������������hash������������һ����CSP��hash������صľ��������������������    CryptHashData���á�  
	if (CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash) == FALSE)
	{
		return FALSE;
	}

	DWORD lenOfBytes;
	USES_CONVERSION;
	char* input = W2A(strInput);
	lenOfBytes = strlen(input);
	if (CryptHashData(hHash, (BYTE*)input, lenOfBytes, 0) == FALSE)      //hash�ļ�    
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
	if (CryptGetHashParam(hHash, HP_HASHVAL, pbHash, &dwHashLen, 0))//���md5ֵ   
	{
		for (DWORD i = 0; i < dwHashLen; i++)         //���md5ֵ   
		{
			TCHAR str[1024] = { 0 };
			CString strFilePartM = _T("");
			_stprintf(str, _T("%02x"), pbHash[i]);
			strOutput += str;
		}
	}
	free(pbHash);

	//�ƺ���  
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//m_passWd = L"NULL";
	UpdateData(TRUE);
	//MessageBox(m_passWd[0]);
	bool lg = 0, check = 0;
	string num = CStringA(m_StuNum);
	string passwd;
	CString tem_wd;
	if (m_passWd[0]!=L'��'&&m_passWd!="")
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
		m_how_much_km = L"���ܹ�����:" + flash_how_much(id);
		m_stu_name = L"�װ���" + CStringW(stu_name.c_str()) + L"ͬѧ����ӭʹ�ã�";
		UpdateData(FALSE);
		//MessageBox(CStringW(id.c_str()));
		MessageBox(L"��¼�ɹ�");
	}
}



void CRunDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!id.length())
		return;
	UpdateData(TRUE);
	bool post = 0;
	postKm(m_km, id, post,st);

	if (!post)
		MessageBox(L"�ɹ�");
}


void CRunDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (id.length())
	{
		m_how_much_km = L"���ܹ�����:" + flash_how_much(id);
		UpdateData(FALSE);
	}

}


void CRunDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CDialogEx::OnTimer(nIDEvent);
}


void CRunDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		m_Phone_value.AddString(L"��ҫ 9");
		m_Phone_value.AddString(L"P20");
		m_Phone_value.AddString(L"P10");
		m_Phone_value.AddString(L"���� 8");
		m_Phone_value.AddString(L"Nova 2");
		break;
	case 2:
		m_Phone_value.AddString(L"�����ֻ�");
		break;
	case 3:
		m_Phone_value.AddString(L"�����ֻ�");
		break;
	case 4:
		m_Phone_value.AddString(L"һ��5T");
		m_Phone_value.AddString(L"һ��3");
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
		MessageBox(L"�ɹ�");

	}
	else MessageBox(L"ʧ��");
}
