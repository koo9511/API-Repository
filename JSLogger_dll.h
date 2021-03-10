// JSLogger.h : JSLogger DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CJSLoggerApp
// �� Ŭ������ ������ ������ JSLogger.cpp�� �����Ͻʽÿ�.
//

class CJSLoggerApp : public CWinApp
{
private:
	static CRITICAL_SECTION l_cs;
	static char logMode;
public:
	CJSLoggerApp();
	~CJSLoggerApp();
// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	static void Logger(char mode, const char* format, va_list args);
	static void setLogMode(char logMode);
	DECLARE_MESSAGE_MAP()
};