#pragma once

#define CURL_STATICLIB
/*
#include <curl/curl.h>
#include <json/json.h>

#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "ws2_32.lib")

#ifdef _DEBUG
#pragma comment(lib, "libcurld.lib")
#else
#pragma comment(lib, "libcurl.lib")
#endif
*/
#pragma comment(lib, "wininet.lib")

class CHttpsRequest
{
private:
	CString authKey;
public:
	CHttpsRequest();
	~CHttpsRequest();
	CString getAuthKey();
	void setAuthKey(CString authKey);
	int curlRequest(/*CString authKey, int price, CString address, int payType, CString memo, CString phoneNum*/);
	static int httpsPost(int operCode, CString nsId, CString bizCode, CString price, CString address, CString payType, CString memo, CString phoneNum, CString* errCode, CString* errMessage);
	//static int httpsPost(CString authKey, CString price, CString address, CString payType, CString memo, CString phoneNum, CString* errCode, CString* errMessage);
};

