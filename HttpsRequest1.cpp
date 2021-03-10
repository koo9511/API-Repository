#include "stdafx.h"
#include "HttpsRequest.h"
#include <iostream>
#include <winhttp.h>

using namespace std;

//#define _TEST

CHttpsRequest::CHttpsRequest()
{
}


CHttpsRequest::~CHttpsRequest()
{
}

CString CHttpsRequest::getAuthKey(){
	return this->authKey;
}

void CHttpsRequest::setAuthKey(CString authKey){
	this->authKey = authKey;
}

size_t CurlWriteCallback(char* buf, size_t size, size_t nmemb, void* up)
{
	TRACE("CURL - Response received:\n%s", buf);
	TRACE("CURL - Response handled %d bytes:\n%s", size*nmemb);

	// tell curl how many bytes we handled
	return size*nmemb;
}
//#define SKIP_HOSTNAME_VERIFICATION
//#define SKIP_PEER_VERIFICATION
int CHttpsRequest::curlRequest(/*CString authKey, int price, CString address, int payType, CString memo, CString phoneNum*/){
	/*
	CURL *curl = NULL;
	CURLcode res;

	std::string readBuffer;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com/");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		std::cout << readBuffer << std::endl;
	}
	*/
	return 0;
}

int CHttpsRequest::httpsPost(int operCode, CString nsId, CString bizCode, CString price, CString address, CString payType, CString memo, CString phoneNum, CString* errCode, CString* errMessage){
	int ret = 0;
	DWORD d_ret = 0;
	HINTERNET hInternetRoot = WinHttpOpen(NULL,
		WINHTTP_ACCESS_TYPE_NO_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS,
		0);
	if ((ret = GetLastError()) != 0){
		errMessage->Format(L"InternetOpen Fail(%d)", ret);
		return ret;
	}

	HINTERNET hInternetConnect = WinHttpConnect(hInternetRoot,
#ifdef _TEST
		L"store.narsya.emaking.kr",	// L"test.modoocall.com",
#else
		L"store.callme.pylon.kr",	// L"test.modoocall.com",
#endif
		INTERNET_DEFAULT_HTTP_PORT, //INTERNET_DEFAULT_HTTPS_PORT,
		0);
	if ((ret = GetLastError()) != 0){
		errMessage->Format(L"InternetConnect Fail(%d)", ret);
		return ret;	
	}

	HINTERNET hOpenRequest = NULL;
	if (operCode == 0) {	//Check authkey using /storeChk
		hOpenRequest = WinHttpOpenRequest(hInternetConnect,
			L"POST",
			L"/index.php/Store/api/storeChk", //L"/order_sheets/status", //L"/ext/order/byApp",
			L"HTTP/1.1", //L"HTTP/1.1",	//HTTP_VERSION,
			WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES, //access type
			WINHTTP_FLAG_REFRESH //| WINHTTP_FLAG_SECURE
		);
	}
	else if (operCode == 1) {
		hOpenRequest = WinHttpOpenRequest(hInternetConnect,
			L"POST",
			L"/index.php/Store/api/orderInsert", //L"/order_sheets/status", //L"/ext/order/byApp",
			L"HTTP/1.1", //L"HTTP/1.1",	//HTTP_VERSION,
			WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES, //access type
			WINHTTP_FLAG_REFRESH //| WINHTTP_FLAG_SECURE
		);
	}
	
	if ((ret = GetLastError()) != 0){
		errMessage->Format(L"HttpOpenRequest Fail(%d)", ret);
		return ret;
	}

	DWORD dwFlags = 0;
	
	dwFlags = SECURITY_FLAG_IGNORE_CERT_WRONG_USAGE |
		SECURITY_FLAG_IGNORE_UNKNOWN_CA |
		SECURITY_FLAG_IGNORE_CERT_DATE_INVALID |
		SECURITY_FLAG_IGNORE_CERT_CN_INVALID;


	//WinHttpSetOption(hOpenRequest, WINHTTP_OPTION_SECURITY_FLAGS, &dwFlags, sizeof(dwFlags));

	if ((ret = GetLastError()) != 0){
		errMessage->Format(L"InternetSetOption Fail(%d)", ret);
		return ret;
	}
	
	// Setpost body
	CString szPostData = L"";
	
	//Check authkey using /store
	szPostData.AppendFormat(L"{\"saup_no\":\"%s\",", bizCode);
	szPostData.AppendFormat(L"\"narsya_id\":\"%s\"", nsId);
	
	if (operCode == 1) {
		szPostData.AppendFormat(L",\"api_mobile_no\":\"%s\",", phoneNum);
		szPostData.AppendFormat(L"\"api_addr\":\"%s\",", address);
		szPostData.AppendFormat(L"\"api_type\":\"%s\",", payType);
		//szPostData.AppendFormat(L"\"api_type\":\"\",", memo);
		szPostData.AppendFormat(L"\"api_money\":\"%s\",", price);
		szPostData.AppendFormat(L"\"pos_name\":\"banana\"");
	}
	szPostData.AppendFormat(L"}");

	int szl = strlen(CW2A(CT2W(szPostData), CP_UTF8));
	
	// Set post header
	CString szHeader;
#ifdef _TEST
	szHeader.AppendFormat(L"Host: store.narsya.emaking.kr\r\n");	//szHeader.AppendFormat(L"Host: hnb.modoocall.com\r\n");
#else
	szHeader.AppendFormat(L"Host: store.narsya.co.kr\r\n");	//szHeader.AppendFormat(L"Host: hnb.modoocall.com\r\n");
#endif
//	szHeader.AppendFormat(L"auth-key: %s\r\n", authKey);
	szHeader.AppendFormat(L"Cache-Control: no-cache\r\n");
	szHeader.AppendFormat(L"Content-Type:application/json\r\n");
	//szHeader.AppendFormat(L"Content-length: %d", strlen(CW2A(CT2W(szPostData), CP_UTF8)));
	szHeader.AppendFormat(L"\r\n\r\n");
	
	WinHttpAddRequestHeaders(hOpenRequest, szHeader, -1L, WINHTTP_ADDREQ_FLAG_ADD);
	if ((ret = GetLastError()) != 0){
		errMessage->Format(L"HttpAddRequestHeaders Fail(%d)", ret);
		return ret;
	}
	
	BOOL bSendRequest = WinHttpSendRequest(hOpenRequest,
		NULL,
		0,
		CW2A(CT2W(szPostData), CP_UTF8),
		szl,
		szl, //strlen(CW2A(CT2W(szPostData), CP_UTF8)),
		NULL
		);
	if ((ret = GetLastError()) != 0){
		errMessage->Format(L"HttpSendRequest Fail(%lu)", ret);
		BOOL bRet = WinHttpCloseHandle(hOpenRequest);
		bRet = WinHttpCloseHandle(hInternetConnect);
		bRet = WinHttpCloseHandle(hInternetRoot);
		return d_ret;
	}
	
	ret = WinHttpReceiveResponse(hOpenRequest, NULL);
	/*
	if ((ret = GetLastError()) != 0){
		errMessage->Format(L"WinHttpReceiveResponse Fail(%d)", ret);
		BOOL bRet = WinHttpCloseHandle(hOpenRequest);
		bRet = WinHttpCloseHandle(hInternetConnect);
		bRet = WinHttpCloseHandle(hInternetRoot);
		return ret;
	}
	*/

	char szBuf[2048] = { 0, };
	DWORD dwSize = 0;
	BOOL bRead = WinHttpReadData(hOpenRequest,
		szBuf,
		sizeof(szBuf),
		&dwSize);
	if ((ret = GetLastError()) != 0){
		errMessage->Format(L"InternetReadFile Fail(%d)", ret);
		return ret;
	}
	//MessageBox(szBuf);

	//////////////////////////////////////////////////////////////
	LPVOID lpOutBuffer = NULL;
	//char lpOutBuffer[2048] = { 0, };
	DWORD dwStatusCode = -1;
	dwSize = sizeof(dwStatusCode);
	
	//dwSize = 0;

	// This call will fail on the first pass, because
	// no buffer is allocated.
	if (!WinHttpQueryHeaders(hOpenRequest,
		WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
		WINHTTP_HEADER_NAME_BY_INDEX,
		&dwStatusCode, &dwSize, WINHTTP_NO_HEADER_INDEX))
	{
		if (GetLastError() == ERROR_WINHTTP_HEADER_NOT_FOUND)
		{
			// Code to handle the case where the header isn't available.
			errMessage->Format(L"ERROR_WINHTTP_HEADER_NOT_FOUND(%d)", ret);
			return TRUE;
		}
	}
	//////////////////////////////////////////////////////////////

	BOOL bRet = WinHttpCloseHandle(hOpenRequest);
	bRet = WinHttpCloseHandle(hInternetConnect);
	bRet = WinHttpCloseHandle(hInternetRoot);

	if (dwStatusCode == 200){
		CString msg;
		int resCode;
		int pos;
		int curPos = 1;

		msg.Format(L"%s", CW2T(CA2W(szBuf, CP_UTF8)));
		pos = msg.Find(L"msg", 0);
		
		msg.Mid(pos).Tokenize(L":\" ", curPos);
		resCode = _ttoi(msg.Mid(pos).Tokenize(L":\" ", curPos));
		if (resCode == 0) {
			*errCode = L"00";
			*errMessage = L"정상처리 되었습니다.";
			ret = 0;
		}
		else if (resCode == 1000) {
			*errCode = L"E01";
			*errMessage = L"유효하지 않은 매장정보 입니다.";
			ret = 401;
		}
		else if (resCode == 2000) {
			*errCode = L"BAD";
			*errMessage = L"지원하지 않는 메서드 입니다.";
			ret = 405;
		}
		else if (resCode == 3000) {
			*errCode = L"E02";
			*errMessage = L"배달정보가 올바르지 않습니다.";
			ret = 405;
		}
	}
	else if (dwStatusCode == 400){
		*errCode = L"BAD";
		*errMessage = L"Bad Status.";
		ret = 400;
	}
	else if (dwStatusCode == 401){
		*errCode = L"E01";
		*errMessage = L"유효하지 않은 인증키 입니다.";
		ret = 401;
	}
	else if (dwStatusCode == 500){
		*errCode = L"E02";
		*errMessage = L"배달정보가 올바르지 않습니다.";
		ret = 500;
	}
	else{
		errCode->Format(L"%d", dwStatusCode);
		ret = dwStatusCode;
	}

	return ret;
}

