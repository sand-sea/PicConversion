
// PicConversion.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPicConversionApp:
// �йش����ʵ�֣������ PicConversion.cpp
//

class CPicConversionApp : public CWinApp
{
public:
	CPicConversionApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPicConversionApp theApp;