#include "stdafx.h"
#include "CombineNetLink.h"


CCombineNetLink::CCombineNetLink()
{
}


CCombineNetLink::~CCombineNetLink()
{
}

int CCombineNetLink::StoreSearch(CString bizCode, std::map<CString, CombineNetStore*>* resultMap, CombineNetResultData* resultData) {
	int ret = 0;
	CString body;
	CString retData;
	CString errCode;
	CString errMsg;
	CString temp;
	CombineNetStore* p_store;
	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	int randNum;
	srand((unsigned int)time(NULL));
	randNum = rand() % 1000;
	CTime c_time = CTime::GetCurrentTime(); // 현재 시스템으로부터 날짜 및 시간을 얻어 온다.
	temp.Format(L"%04d%02d%02d%02d%02d%02d%03dBANANAPOS", c_time.GetYear(), c_time.GetMonth(), c_time.GetDay(), c_time.GetHour(), c_time.GetMinute(), c_time.GetSecond(), randNum);

	body.Format(L"{\"header\": {\"request_id\":\"%s\"},", temp);
	body.AppendFormat(L"\"body\": {\"keyword\": \"%s\"}}", bizCode);

	// get Communicate http data
	hReq.SetCombineNetFind(agency_flag, L"", body);
#ifdef COMBNET_TEST
	ret = hReq.MyHttpRequest(0, 8181, &retData, &errCode, &errMsg);
#else
	ret = hReq.MyHttpRequest(0, 33331, &retData, &errCode, &errMsg);
#endif

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);

		Json::Value header = root["header"];

		resultData->ret_cd = header["result_code"].asCString();
		resultData->ret_msg = header["result_message"].asCString();
		ret = _ttoi(resultData->ret_cd);
		if (!ret) {
			Json::Value body = root["body"];

			Json::ValueIterator it = body["ShopList"].begin();

			// insert value to map
			while (it != body["ShopList"].end())
			{
				if (it->isObject()) // iterator가 객체인 경우
				{
					p_store = new CombineNetStore;
					p_store->address = (*it)["storeAddress"].asCString();
					p_store->store_name = (*it)["storeName"].asCString();
					p_store->combinenet_id = (*it)["storeCode"].asCString();
					p_store->store_phone = (*it)["storeTel"].asCString();
					p_store->store_mobile = (*it)["storeMobile"].asCString();

					resultMap->insert(pair<CString, CombineNetStore*>(p_store->combinenet_id, p_store));
				}
				++it;
			}
		}
	}
	catch (...) {
		CJSLogger::Logger('e', "Parsing StoreSearch fail.");
		ret = -1;
	}

	if (ret) {
		CJSLogger::Logger('e', "[SEND]%s", CW2A(CT2W(body), CP_UTF8));
		CJSLogger::Logger('e', "[RECV]%s", CW2A(CT2W(retData), CP_UTF8));
	}

	return ret;
}

int CCombineNetLink::StoreLink(CString storeCode, CString linkCode, CombineNetResultData* resultData) {
	int ret = 0;
	CString body;
	CString retData;
	CString errCode;
	CString errMsg;
	CString resultCode;
	CString resultMessage;
	CString temp;
	CombineNetStore* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	// get Communicate http data
	int randNum;
	srand((unsigned int)time(NULL));
	randNum = rand() % 1000;
	CTime c_time = CTime::GetCurrentTime(); // 현재 시스템으로부터 날짜 및 시간을 얻어 온다.
	temp.Format(L"%04d%02d%02d%02d%02d%02d%03dBANANAPOS", c_time.GetYear(), c_time.GetMonth(), c_time.GetDay(), c_time.GetHour(), c_time.GetMinute(), c_time.GetSecond(), randNum);

	body.Format(L"{\"header\": {\"request_id\":\"%s\"},", temp);
	body.AppendFormat(L"\"body\": {\"storeCode\": \"%s\",", storeCode);
	body.AppendFormat(L"\"posStoreCode\": \"%s\",", linkCode);
	body.AppendFormat(L"\"posLinkFlag\" : \"1\"}}");

	hReq.SetCombineNetLink(agency_flag, L"", body);
#ifdef COMBNET_TEST
	ret = hReq.MyHttpRequest(0, 8181, &retData, &errCode, &errMsg);
#else
	ret = hReq.MyHttpRequest(0, 33331, &retData, &errCode, &errMsg);
#endif

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);

		Json::Value header = root["header"];

		resultData->ret_cd = header["result_code"].asCString();
		resultData->ret_msg = header["result_message"].asCString();
		ret = _ttoi(resultData->ret_cd);
	}
	catch (...) {
		CJSLogger::Logger('e', "Parsing StoreLink fail.");
		ret = -1;
	}

	if (ret) {
		CJSLogger::Logger('e', "[SEND]%s", CW2A(CT2W(body), CP_UTF8));
		CJSLogger::Logger('e', "[RECV]%s", CW2A(CT2W(retData), CP_UTF8));
	}

	return ret;
}

int CCombineNetLink::StoreUnlink(CString storeCode, CString linkCode, CombineNetResultData* resultData) {
	int ret = 0;
	CString body;
	CString retData;
	CString errCode;
	CString errMsg;
	CString resultCode;
	CString resultMessage;
	CString temp;
	CombineNetStore* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	// get Communicate http data
	int randNum;
	srand((unsigned int)time(NULL));
	randNum = rand() % 1000;
	CTime c_time = CTime::GetCurrentTime(); // 현재 시스템으로부터 날짜 및 시간을 얻어 온다.
	temp.Format(L"%04d%02d%02d%02d%02d%02d%03dBANANAPOS", c_time.GetYear(), c_time.GetMonth(), c_time.GetDay(), c_time.GetHour(), c_time.GetMinute(), c_time.GetSecond(), randNum);

	body.Format(L"{\"header\": {\"request_id\":\"%s\"},", temp);
	body.AppendFormat(L"\"body\": {\"storeCode\": \"%s\",", storeCode);
	body.AppendFormat(L"\"posStoreCode\": \"%s\",", linkCode);
	body.AppendFormat(L"\"posLinkFlag\" : \"2\"}}");

	hReq.SetCombineNetLink(agency_flag, L"", body);
#ifdef COMBNET_TEST
	ret = hReq.MyHttpRequest(0, 8181, &retData, &errCode, &errMsg);
#else
	ret = hReq.MyHttpRequest(0, 33331, &retData, &errCode, &errMsg);
#endif

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);

		Json::Value header = root["header"];

		resultData->ret_cd = header["result_code"].asCString();
		resultData->ret_msg = header["result_message"].asCString();
	}
	catch (...) {
		CJSLogger::Logger('e', "Parsing StoreLink fail.");
		ret = -1;
	}

	if (ret) {
		CJSLogger::Logger('e', "[SEND]%s", CW2A(CT2W(body), CP_UTF8));
		CJSLogger::Logger('e', "[RECV]%s", CW2A(CT2W(retData), CP_UTF8));
	}

	return ret;
}

int CCombineNetLink::ParseJson(std::string input, Json::Value* value) {
	Json::Reader reader;
	bool parsingRet = reader.parse(input, *value);
	return 0;
}

void CCombineNetLink::SetAgencyFlag(int flag) {
	this->agency_flag = flag;
}

int CCombineNetLink::GetAgencyFlag() {
	return this->agency_flag;
}