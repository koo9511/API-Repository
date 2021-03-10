// HttpsRequest.h : HttpsRequest DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "stdafx.h"
#include "resource.h"		// �� ��ȣ�Դϴ�.
#pragma comment(lib, "wininet.lib")

// CHttpsRequestApp
// �� Ŭ������ ������ ������ HttpsRequest.cpp�� �����Ͻʽÿ�.
//

class CHttpsRequest
{
public:
	CHttpsRequest();
	~CHttpsRequest();

// �������Դϴ�.
public:
	static int httpsPost(CString authKey, CString price, CString address, CString payType, CString memo, CString phoneNum, CString* errCode, CString* errMessage);

	DECLARE_MESSAGE_MAP()
};

extern "C" {
	AFX_CLASS_EXPORT int httpsPost(CString authKey, CString price, CString address, CString payType, CString memo, CString phoneNum, CString* errCode, CString* errMessage){
		return CHttpsRequest::httpsPost(authKey, price, address, payType, memo, phoneNum, errCode, errMessage);
	}
}