
// Face_Recognize.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFace_RecognizeApp: 
// �йش����ʵ�֣������ Face_Recognize.cpp
//

class CFace_RecognizeApp : public CWinApp
{
public:
	CFace_RecognizeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFace_RecognizeApp theApp;