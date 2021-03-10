#include "stdafx.h"
#include "RoadvoyLink.h"

CRoadvoyLink::CRoadvoyLink()
{
}


CRoadvoyLink::~CRoadvoyLink()
{
}

int CRoadvoyLink::StoreSearch(CString bizCode, std::map<CString, RoadvoyStore*>* resultMap, RoadvoyResultData* resultData) {
	int ret = 0;
	CString urlData;
	CString retData;
	CString errCode;
	CString errMsg;
	CString temp;
	RoadvoyStore* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	// get Communicate http data
	//bizCode.Remove(L'-');
	urlData = bizCode;

	hReq.SetRoadvoyFind(urlData, L"");
	hReq.MyHttpRequest(0, 0, &retData, &errCode, &errMsg);

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);

		Json::Value ret_franchises = root["RET_FRANCHISES"];

		resultData->ret_code.Format(L"%d", root["RET_CODE"].asInt());
		if (!root["RET_MSG"].isNull())
			resultData->ret_msg = root["RET_MSG"].asCString();

		if (root["RET_CODE"].asInt()) {
			CJSLogger::Logger('e', "Roadvoy StoreSearch fail.");
			return -2;
		}
		
		Json::ValueIterator it = ret_franchises.begin();

		// insert value to map
		while (it != ret_franchises.end())
		{
			if (it->isObject()) // iterator가 객체인 경우
			{
				p_store = new RoadvoyStore;
				p_store->roadvoy_id = (*it)["TEAM_CODE"].asCString();
				p_store->store_name = (*it)["TEAM_NAME"].asCString();
				p_store->biz_num = (*it)["REG_NO"].asCString();
				p_store->store_phone = (*it)["TEL"].asCString();
				p_store->store_mobile = (*it)["MOBILE"].asCString();
				p_store->addr_jibun = (*it)["OLD_ADDR"].asCString();
				p_store->addr_road = (*it)["NEW_ADDR"].asCString();
				p_store->addr_desc = (*it)["ADDR_DESC"].asCString();

				resultMap->insert(pair<CString, RoadvoyStore*>(p_store->roadvoy_id, p_store));
			}
			++it;
		}
	}
	catch (...) {
		CJSLogger::Logger('e', "Roadvoy Parsing StoreSearch fail.");
		ret = -1;
	}

	if (ret) {
		CJSLogger::Logger('e', "[SEND]%s", CW2A(CT2W(urlData), CP_UTF8));
		CJSLogger::Logger('e', "[RECV]%s", CW2A(CT2W(retData), CP_UTF8));
	}

	return ret;
}

int CRoadvoyLink::StoreLink(CString roadvoyId, CString linkCode, RoadvoyResultData* resultData) {
	int ret = 0;
	CString body;
	CString retData;
	CString errCode;
	CString errMsg;
	CString resultCode;
	CString resultMessage;
	CString temp;
	RoadvoyStore* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	// get Communicate http data
	body.Format(L"{\"TEAM_CODE\": \"%s\",", roadvoyId);
	body.AppendFormat(L"\"LINK_SHOP_CODE\": \"%s\"}", linkCode);
	
	hReq.SetRoadvoyLink(L"", body);
	hReq.MyHttpRequest(0, 0, &retData, &errCode, &errMsg);

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);

		resultData->ret_code.Format(L"%d", root["RET_CODE"].asInt());
		if (!root["RET_MSG"].isNull())
			resultData->ret_msg = root["RET_MSG"].asCString();

		if (root["RET_CODE"].asInt()) {
			CJSLogger::Logger('e', "Roadvoy StoreLink fail.");
			return -2;
		}
	}
	catch (...) {
		CJSLogger::Logger('e', "Roadvoy Parsing StoreLink fail.");
		ret = -1;
	}

	if (ret) {
		CJSLogger::Logger('e', "[SEND]%s", CW2A(CT2W(body), CP_UTF8));
		CJSLogger::Logger('e', "[RECV]%s", CW2A(CT2W(retData), CP_UTF8));
	}

	return ret;
}

int CRoadvoyLink::StoreUnlink(CString linkCode, RoadvoyResultData* resultData) {
	int ret = 0;
	CString urlData;
	CString retData;
	CString errCode;
	CString errMsg;
	CString resultCode;
	CString resultMessage;
	CString temp;
	RoadvoyStore* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	// get Communicate http data
	urlData = linkCode;

	hReq.SetRoadvoyUnlink(urlData, L"");
	hReq.MyHttpRequest(0, 0, &retData, &errCode, &errMsg);

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);

		resultData->ret_code.Format(L"%d", root["RET_CODE"].asInt());
		if (!root["RET_MSG"].isNull())
			resultData->ret_msg = root["RET_MSG"].asCString();

		if (root["RET_CODE"].asInt()) {
			CJSLogger::Logger('e', "Roadvoy StoreUnlink fail.");
			return -2;
		}
	}
	catch (...) {
		CJSLogger::Logger('e', "Roadvoy Parsing StoreUnlink fail.");
		ret = -1;
	}

	if (ret) {
		CJSLogger::Logger('e', "[SEND]%s", CW2A(CT2W(urlData), CP_UTF8));
		CJSLogger::Logger('e', "[RECV]%s", CW2A(CT2W(retData), CP_UTF8));
	}

	return ret;
}

int CRoadvoyLink::ParseJson(std::string input, Json::Value* value) {
	Json::Reader reader;
	bool parsingRet = reader.parse(input, *value);
	return 0;
}
