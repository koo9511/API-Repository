// HttpsRequest.h : HttpsRequest DLL의 기본 헤더 파일입니다.
//

#pragma once

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "stdafx.h"
#include "resource.h"		// 주 기호입니다.
#pragma comment(lib, "wininet.lib")

// CHttpsRequestApp
// 이 클래스의 구현을 보려면 HttpsRequest.cpp를 참조하십시오.
//

class CHttpsRequest
{
public:
	CHttpsRequest();
	~CHttpsRequest();

// 재정의입니다.
public:
	static int httpsPost(CString authKey, CString price, CString address, CString payType, CString memo, CString phoneNum, CString* errCode, CString* errMessage);

	DECLARE_MESSAGE_MAP()
};

extern "C" {
	AFX_CLASS_EXPORT int httpsPost(CString authKey, CString price, CString address, CString payType, CString memo, CString phoneNum, CString* errCode, CString* errMessage){
		return CHttpsRequest::httpsPost(authKey, price, address, payType, memo, phoneNum, errCode, errMessage);
	}
}