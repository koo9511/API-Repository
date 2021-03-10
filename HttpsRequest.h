#pragma once

//#define CURL_STATICLIB
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
#include <winhttp.h>
#include <string>
#include <vector>

//#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "winhttp.lib")

using namespace std;

typedef struct InputData {
	string store_code;
	string food_code;
	string order_no;
}InputData;

class CHttpsRequest
{
private:
	static CString tokenKey;
	//int kaKaoOperCode;
	static CString inputJson;
	static string resultData;
	static InputData* InData;

public:
	CHttpsRequest();
	~CHttpsRequest();

	static CString GetTokenKey();
	static void SetTokenKey(CString tokenKey);
	//int GetkaKaoOperCode();
	//void SetkaKaoOperCode(int kaKaoOperCode);
	/*
	static CString GetInputJson();
	static void SetInputJson(CString inputJson);
	static string GetResultData();
	static void SetResultData(string resultData);
	static void SetInData(InputData* InData);
	
	static size_t CurlWriteCallback(char* ptr, size_t size, size_t nmemb, void* userp);
	static int curlRequest(int kaKaoOperCode);
	
	//static int httpsPost(CString authKey, CString price, CString address, CString payType, CString memo, CString phoneNum, CString* errCode, CString* errMessage);

	static int SetOptionIssueAuthKey(CURL * curl, CString username, CString password);
	static int SetOptionNotices(CURL * curl, const char* postData);
	static int SetOptionStores(CURL * curl, const char* postData);
	static int SetOptionStore(CURL * curl, string store_code);
	static int SetOptionStoreStatusUpdate(CURL * curl, string store_code, const char* postData);
	static int SetOptionMenus(CURL * curl, string store_code);
	static int SetOptionMenu(CURL * curl, string store_code, string food_code);
	static int SetOptionMenuStatusUpdate(CURL * curl, const char* postData, string store_code, string food_code);
	static int SetOptionOrders(CURL * curl, const char* postData);
	static int SetOptionOrder(CURL * curl, string order_no);
	static int SetOptionOrderStatusUpdate(CURL * curl, const char* postData);
	static int SetOptionDeliveryStatusUpdate(CURL * curl, const char* postData);
	static int SetOptionNotiDelay(CURL * curl, const char* postData);
	static int SetOptionTest(CURL * curl, const char* postData);
	*/

	// Http
	int SetHttpsHeader(int kaKaoOperCode, CString* httpsHeader, std::vector<CString> v_httpsHeader);
	int MyHttpRequest(BOOL isHttps,int port, CString* resultData, CString* errCode, CString* errMessage);

	// Moacall
	int SetMoacall(CString urlData, CString sendBody);

	// Daligo
	int SetDaligoFind(int svcd, CString urlData, CString sendBody);
	int SetDaligoLink(int svcd, CString urlData, CString sendBody);
	int SetDaligoUnlink(int svcd, CString urlData, CString sendBody);

	// Roadvoy
	int SetRoadvoyFind(CString urlData, CString sendBody);
	int SetRoadvoyLink(CString urlData, CString sendBody);
	int SetRoadvoyUnlink(CString urlData, CString sendBody);
	
	// CombineNet
	int SetCombineNetFind(int svcd, CString urlData, CString sendBody);
	int SetCombineNetLink(int svcd, CString urlData, CString sendBody);

	// Beyond
	int SetBeyond(int flag, CString urlData, CString sendBody);

	// Sanggag
	int SetSanggag(CString urlData, CString sendBody);

	// DelionDlvy
	int SetDelionDlvy(CString urlData, CString sendBody);

	// Geocode
	int SetNGeocode(CString urlData, CString sendBody);
	int SetDGeocode(CString urlData, CString sendBody);
	
private:
	CString httpsHost;
	CString httpsMethod;
	CString httpsAPI;
	CString httpsUrlData;
	CString httpsSendHeader;
	CString httpsSendBody;
};
