// AutoClick.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAutoClickApp:
// �йش����ʵ�֣������ AutoClick.cpp
//

class CAutoClickApp : public CWinApp
{
public:
	CAutoClickApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
public:
    virtual int ExitInstance();
};

extern CAutoClickApp theApp;