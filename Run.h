
// Run.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CRunApp: 
// �йش����ʵ�֣������ Run.cpp
//

class CRunApp : public CWinApp
{
public:
	CRunApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
public:
	
	DECLARE_MESSAGE_MAP()
};

extern CRunApp theApp;