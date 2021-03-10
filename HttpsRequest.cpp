#include "stdafx.h"
#include "HttpsRequest.h"
#include <iostream>
//#include <winhttp.h>

using namespace std;

CString CHttpsRequest::tokenKey = NULL;
//int kaKaoOperCode;
CString CHttpsRequest::inputJson = NULL;
string CHttpsRequest::resultData = "";
InputData* CHttpsRequest::InData = NULL;

CHttpsRequest::CHttpsRequest()
{
}


CHttpsRequest::~CHttpsRequest()
{
}

int CHttpsRequest::SetHttpsHeader(int kaKaoOperCode, CString* httpsHeader, std::vector<CString> v_httpsHeader) {
	int ret = 0;

	std::vector<CString>::iterator itr;

	if (v_httpsHeader.empty()) {
		return -1;
	}

	for (itr = v_httpsHeader.begin(); itr != v_httpsHeader.end(); itr++) {
		httpsHeader->AppendFormat(L"%s\r\n", (*itr));
	}

	return ret;
}

int CHttpsRequest::MyHttpRequest(BOOL isHttps, int port, CString* resultData, CString* errCode, CString* errMessage){
	int ret = 0;
	DWORD d_ret = 0;
	//CString temp;
	CString apiTemp;

	HINTERNET hInternetRoot = WinHttpOpen(NULL,
		WINHTTP_ACCESS_TYPE_NO_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS,
		0);
	if ((ret = GetLastError()) != 0){
		errMessage->Format(L"InternetOpen Fail(%d)", ret);
		return ret;
	}

	HINTERNET hInternetConnect;
	if (port == 0) {
		if (isHttps) {
			hInternetConnect = WinHttpConnect(hInternetRoot,
				this->httpsHost,	// L"test.modoocall.com",
				INTERNET_DEFAULT_HTTPS_PORT, //INTERNET_DEFAULT_HTTP_PORT,
				0);
		}
		else {
			hInternetConnect = WinHttpConnect(hInternetRoot,
				this->httpsHost,	// L"test.modoocall.com",
				INTERNET_DEFAULT_HTTP_PORT,
				0);
		}
	}
	else {
		hInternetConnect = WinHttpConnect(hInternetRoot,
			this->httpsHost,	// L"test.modoocall.com",
			port,
			0);
	}
	
	
	if ((ret = GetLastError()) != 0){
		errMessage->Format(L"InternetConnect Fail(%d)", ret);
		return ret;	
	}

	if(httpsUrlData.IsEmpty())	// Set API URL
		apiTemp.Format(L"%s", this->httpsAPI);
	else
		apiTemp.Format(L"%s%s", this->httpsAPI, this->httpsUrlData);

	HINTERNET hOpenRequest;
	if (isHttps) {
		hOpenRequest = WinHttpOpenRequest(hInternetConnect,
			this->httpsMethod,	// GET, POST
			apiTemp,		// /ext/order/byApp
			L"HTTP/1.1",
			WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			WINHTTP_FLAG_REFRESH | WINHTTP_FLAG_SECURE
		);
	}
	else {
		hOpenRequest = WinHttpOpenRequest(hInternetConnect,
			this->httpsMethod,	// GET, POST
			apiTemp,		// /ext/order/byApp
			L"HTTP/1.1",
			WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			0
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

	if (isHttps) {
		WinHttpSetOption(hOpenRequest, WINHTTP_OPTION_SECURITY_FLAGS, &dwFlags, sizeof(dwFlags));
		if ((ret = GetLastError()) != 0) {
			errMessage->Format(L"InternetSetOption Fail(%d)", ret);
			return ret;
		}
	}
	
	int szl = strlen(CW2A(CT2W(httpsSendBody), CP_UTF8));
	
	// Set post header
	CString szHeader;
	szHeader.Format(L"%s", httpsSendHeader);
	szHeader.AppendFormat(L"Content-length: %d\r\n", szl);
	szHeader.AppendFormat(L"\r\n\r\n");
	
	WinHttpAddRequestHeaders(hOpenRequest, szHeader, -1L, WINHTTP_ADDREQ_FLAG_ADD);
	if ((ret = GetLastError()) != 0){
		errMessage->Format(L"HttpAddRequestHeaders Fail(%d)", ret);
		return ret;
	}

	BOOL bSendRequest = WinHttpSendRequest(hOpenRequest,
		NULL,
		0,
		CW2A(CT2W(httpsSendBody), CP_UTF8),
		szl,
		szl,
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

	char szBuf[10240] = { 0, };
	DWORD dwSize = 0;
	int totalSize = 0;
	BOOL b_Ret = FALSE;
	std::string strBuf;
	 do{
		 memset(szBuf, 0, 10240);
		 b_Ret = WinHttpReadData(hOpenRequest, szBuf, sizeof(szBuf), &dwSize);
		 strBuf.append(szBuf);
		
		//CW2A(CT2W(httpsSendBody), CP_UTF8)
		totalSize += dwSize;
	}while (b_Ret && dwSize != 0);
	//BOOL bRead = WinHttpReadData(hOpenRequest, szBuf, sizeof(szBuf), &dwSize);

	if ((ret = GetLastError()) != 0){
		errMessage->Format(L"InternetReadFile Fail(%d)", ret);
		return ret;
	}
	else {
		resultData->Format(L"%s", CW2T(CA2W(strBuf.c_str(), CP_UTF8)));
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
		*errCode = L"00";
		*errMessage = L"정상처리 되었습니다.";
		ret = 0;
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

// Moacall
int CHttpsRequest::SetMoacall(CString urlData, CString sendBody) {
	this->httpsHost = L"182.162.109.19";
	this->httpsMethod = L"POST";
	this->httpsAPI = L"/pos_api";
	this->httpsUrlData = urlData;
	this->httpsSendHeader.AppendFormat(L"Content-Type: application/json\r\n");
	this->httpsSendBody = sendBody;

	return 0;
}

// Daligo
int CHttpsRequest::SetDaligoFind(int svcd, CString urlData, CString sendBody) {
	if (svcd < 4)
		this->httpsHost = L"delivery.mnzapi.com";
	else
		this->httpsHost = L"delivery.sncapi.com";
	this->httpsMethod = L"POST";
	this->httpsAPI = L"/v1/storefind";
	if (svcd < 4)
		this->httpsAPI += L"/";
	this->httpsUrlData = urlData;
	this->httpsSendHeader.AppendFormat(L"Content-Type: application/json\r\n");
	this->httpsSendBody = sendBody;

	return 0;
}

int CHttpsRequest::SetDaligoLink(int svcd, CString urlData, CString sendBody) {
	if (svcd < 4)
		this->httpsHost = L"delivery.mnzapi.com";
	else
		this->httpsHost = L"delivery.sncapi.com";
	this->httpsMethod = L"POST";
	this->httpsAPI = L"/v1/storereg";
	if (svcd < 4)
		this->httpsAPI += L"/";
	this->httpsUrlData = urlData;
	this->httpsSendHeader.AppendFormat(L"Content-Type: application/json\r\n");
	this->httpsSendBody = sendBody;

	return 0;
}

int CHttpsRequest::SetDaligoUnlink(int svcd, CString urlData, CString sendBody) {
	if (svcd < 4)
		this->httpsHost = L"delivery.mnzapi.com";
	else
		this->httpsHost = L"delivery.sncapi.com";
	this->httpsMethod = L"POST";
	this->httpsAPI = L"/v1/storedel";
	if (svcd < 4)
		this->httpsAPI += L"/";
	this->httpsUrlData = urlData;
	this->httpsSendHeader.AppendFormat(L"Content-Type: application/json\r\n");
	this->httpsSendBody = sendBody;

	return 0;
}

// Roadvoy
int CHttpsRequest::SetRoadvoyFind(CString urlData, CString sendBody) {
	this->httpsHost = L"pos.roadvoy.com";
	this->httpsMethod = L"GET";
	this->httpsAPI = L"/v1/banana/franchise/";
	this->httpsUrlData = urlData;
	this->httpsSendHeader.AppendFormat(L"Content-Type: application/json\r\n");
	this->httpsSendBody = sendBody;

	return 0;
}

int CHttpsRequest::SetRoadvoyLink(CString urlData, CString sendBody) {
	this->httpsHost = L"pos.roadvoy.com";
	this->httpsMethod = L"POST";
	this->httpsAPI = L"/v1/banana/link/";
	this->httpsUrlData = urlData;
	this->httpsSendHeader.AppendFormat(L"Content-Type: application/json\r\n");
	this->httpsSendBody = sendBody;

	return 0;
}

int CHttpsRequest::SetRoadvoyUnlink(CString urlData, CString sendBody) {
	this->httpsHost = L"pos.roadvoy.com";
	this->httpsMethod = L"DELETE";
	this->httpsAPI = L"/v1/banana/link/";
	this->httpsUrlData = urlData;
	this->httpsSendHeader.AppendFormat(L"Content-Type: application/json\r\n");
	this->httpsSendBody = sendBody;

	return 0;
}

// CombineNet
int CHttpsRequest::SetCombineNetFind(int svcd, CString urlData, CString sendBody) {
#ifdef COMBNET_TEST
	this->httpsHost = L"dev.comcall.co.kr";
#else
	if (svcd == 1)
		this->httpsHost = L"scall.comcall.co.kr";
	else if (svcd == 2)
		this->httpsHost = L"hcall.comcall.co.kr";
	else if (svcd == 3)
		this->httpsHost = L"dscall.15223933.com";
	else
		this->httpsHost = L"127.0.0.1";
#endif
	this->httpsMethod = L"POST";
	this->httpsAPI = L"/g/bananapos/shop/find";
	this->httpsUrlData = urlData;
	this->httpsSendHeader.AppendFormat(L"Content-Type: application/json\r\n");
	this->httpsSendBody = sendBody;

	return 0;
}

int CHttpsRequest::SetCombineNetLink(int svcd, CString urlData, CString sendBody) {
#ifdef COMBNET_TEST
	this->httpsHost = L"dev.comcall.co.kr";
#else
	if (svcd == 1)
		this->httpsHost = L"scall.comcall.co.kr";
	else if (svcd == 2)
		this->httpsHost = L"hcall.comcall.co.kr";
	else if (svcd == 3)
		this->httpsHost = L"dscall.15223933.com";
	else
		this->httpsHost = L"127.0.0.1";
#endif
	this->httpsMethod = L"POST";
	this->httpsAPI = L"/g/bananapos/shop/link";
	this->httpsUrlData = urlData;
	this->httpsSendHeader.AppendFormat(L"Content-Type: application/json\r\n");
	this->httpsSendBody = sendBody;

	return 0;
}

// Beyond
int CHttpsRequest::SetBeyond(int flag, CString urlData, CString sendBody) {
#ifdef BEYOND_TEST
	this->httpsHost = L"dev.stds.co.kr";
	this->httpsAPI = L"/byservice/OuterInterfaceJSON.action";
#else
	if (flag == 8)
		this->httpsHost = L"hanaro.stds.co.kr";
	else
		this->httpsHost = L"dv.stds.co.kr";

	if (flag == 0)	// 이즈오케이
		this->httpsAPI = L"/byservice/OuterInterfaceJSON.action";
	else if (flag == 1)	// 최강배달
		this->httpsAPI = L"/rushcall/OuterInterfaceJSON.action";
	else if (flag == 2)	// 베테랑
		this->httpsAPI = L"/veteran/OuterInterfaceJSON.action";
	//else if (flag == 3)	// 로드파일럿
		//this->httpsAPI = L"/roadpilot/OuterInterfaceJSON.action";
	else if (flag == 4)	// 배달인
		this->httpsAPI = L"/dsp/OuterInterfaceJSON.action";
	else if (flag == 5)	// 레몬콜
		this->httpsAPI = L"/fooding/OuterInterfaceJSON.action";
	//else if (flag == 6)	// 키친딜리러비
		//this->httpsAPI = L"/kitchen/OuterInterfaceJSON.action";
	else if (flag == 7)	// 엠터치
		this->httpsAPI = L"/mtouch/OuterInterfaceJSON.action";
	else if (flag == 8)	// 하나로
		this->httpsAPI = L"/hanaro/OuterInterfaceJSON.action";
#endif
	this->httpsMethod = L"POST";
	this->httpsUrlData = urlData;
	this->httpsSendHeader.Format(L"Content-Type: application/json\r\n");
	this->httpsSendHeader.AppendFormat(L"Authorization: Bearer eyJhbGciOiJIUzUxMiJ9.eyJzdWIiOiJCYW5hbmFQb3MiLCJVc2VySWQiOiJiYW5hbmFwb3MiLCJQYXNzd2QiOiJ2ZXRlcmFuOTMwMCIsIkdyYW50VHlwZSI6InJ3IiwiU2VydmljZU5hbWUiOiJCYW5hbmFQb3MiLCJBY2Nlc3NFeHBpcmVEVCI6IjIwMjktMTEtMjYgMTY6MDQ6MDQifQ.7yXlHhoLNTaaKUOd9keYy242S5SXIXRz9HLrduNQ_-rRel2hTfeQi8BJhw5XeuWwMfbEOX472aBBiQh_j4IlpA\r\n");
	this->httpsSendBody = sendBody;

	return 0;
}

// Sanggag
int CHttpsRequest::SetSanggag(CString urlData, CString sendBody) {
#ifdef SANGGAG_TEST
	this->httpsHost = L"testapi.414.co.kr";
#else
	this->httpsHost = L"foodapi.414.co.kr";
#endif
	this->httpsMethod = L"POST";
	this->httpsAPI = L"/WideBeneApi/orders";
	this->httpsUrlData = urlData;
	this->httpsSendHeader.Format(L"Content-Type: application/json\r\n");
	this->httpsSendBody = sendBody;

	return 0;
}

/*
*
*	DelionDlvy Setting
*
*/
int CHttpsRequest::SetDelionDlvy(CString urlData, CString sendBody) {
#ifdef DELION_TEST
	this->httpsHost = L"rndoffice.iptime.org";
#else
	this->httpsHost = L"211.115.127.103";
#endif
	this->httpsAPI = L"/api/shareCall/quick";
	this->httpsMethod = L"GET";
	this->httpsUrlData = urlData;
	this->httpsSendHeader.Format(L"Content-Type: application/json\r\n");
	this->httpsSendBody = sendBody;

	return 0;
}


// Geocode
int CHttpsRequest::SetNGeocode(CString urlData, CString sendBody) {
	this->httpsHost = L"115.68.102.212";
	this->httpsMethod = L"GET";
	this->httpsAPI = L"/bananaPOS/banana/map/t2_ngeocode_winhttp.html";
	this->httpsUrlData = urlData;
	//this->httpsSendHeader.AppendFormat(L"Content-Type: application/json\r\n");
	this->httpsSendBody = sendBody;

	return 0;
}

int CHttpsRequest::SetDGeocode(CString urlData, CString sendBody) {
	this->httpsHost = L"115.68.102.212";
	this->httpsMethod = L"GET";
	this->httpsAPI = L"/bananaPOS/banana/map/t2_dgeocode_winhttp.html";
	this->httpsUrlData = urlData;
	this->httpsSendHeader.AppendFormat(L"Cache-Control: no-cache\r\n");
	this->httpsSendBody = sendBody;

	return 0;
}
