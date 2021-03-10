// O2MDHttpsReq.h : O2MDHttpsReq DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.

#pragma comment(lib, "wininet.lib")

// CO2MDHttpsReqApp
// �� Ŭ������ ������ ������ O2MDHttpsReq.cpp�� �����Ͻʽÿ�.
//

class CO2MDHttpsReqApp : public CWinApp
{
public:
	CO2MDHttpsReqApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	static int httpsPost(CString authKey, CString price, CString address, CString payType, CString memo, CString phoneNum, CString* errCode, CString* errMessage);
	static CString getHttpsReqVersion();
	DECLARE_MESSAGE_MAP()
};
