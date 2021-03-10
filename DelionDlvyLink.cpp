#include "stdafx.h"
#include "DelionDlvyLink.h"


CDelionDlvyLink::CDelionDlvyLink()
{
}


CDelionDlvyLink::~CDelionDlvyLink()
{
}


int CDelionDlvyLink::StoreSearch(CString bizCode, std::map<CString, StoreInfo*>* resultMap, ResultData* resultData) {
	int ret = 0;
	CString body;
	CString retData;
	CString errCode;
	CString errMsg;
	CString temp;
	StoreInfo* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	// get Communicate http data

	body.Format(L"{\"compName\": \"banana\",");
	body.AppendFormat(L"\"keyword\": \"%s\"}", bizCode);

	hReq.SetDelionDlvy(L"/findStore.do", body);
	hReq.MyHttpRequest(0, 13131, &retData, &errCode, &errMsg);

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);

		ret = root["resultCode"].asInt();
		resultData->ret_cd.Format(L"%d", ret);
		resultData->ret_msg = root["resultMessage"].asCString();
		if (!ret) {
			Json::Value j_list = root["list"];
			Json::ValueIterator it = j_list.begin();

			// insert value to map
			while (it != j_list.end())
			{
				if (it->isObject()) // iterator가 객체인 경우
				{
					p_store = new StoreInfo;

					p_store->biz_num = (*it)["storeBusiNo"].asCString();
					p_store->store_addr = (*it)["storeAddress"].asCString();
					p_store->store_name = (*it)["storeName"].asCString();
					p_store->store_code = (*it)["storeCode"].asCString();
					p_store->store_phone = (*it)["storeTel"].asCString();
					p_store->store_mobile = (*it)["storeMobile"].asCString();

					resultMap->insert(pair<CString, StoreInfo*>(p_store->store_code, p_store));
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

int CDelionDlvyLink::StoreLink(CString storeCode, CString linkCode, ResultData* resultData) {
	int ret = 0;
	CString body;
	CString retData;
	CString errCode;
	CString errMsg;
	CString resultCode;
	CString resultMessage;
	CString temp;
	DelionStore* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	body.Format(L"{\"compName\": \"banana\",");
	body.AppendFormat(L"\"storeCode\": \"%s\",", storeCode);
	body.AppendFormat(L"\"shareStoreCode\": \"%s\"}", linkCode);

	hReq.SetDelionDlvy(L"/updateStoreCode.do", body);
	hReq.MyHttpRequest(0, 13131, &retData, &errCode, &errMsg);

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);

		ret = root["resultCode"].asInt();
		resultData->ret_cd.Format(L"%d", ret);
		resultData->ret_msg = root["resultMessage"].asCString();
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

int CDelionDlvyLink::StoreUnlink(CString storeCode, CString linkCode, ResultData* resultData) {
	int ret = 0;
	CString body;
	CString retData;
	CString errCode;
	CString errMsg;
	CString resultCode;
	CString resultMessage;
	CString temp;
	DelionStore* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	body.Format(L"{\"compName\": \"banana\",");
	body.AppendFormat(L"\"storeCode\": \"%s\",", storeCode);
	body.AppendFormat(L"\"shareStoreCode\": \"%s\"}", linkCode);

	hReq.SetDelionDlvy(L"/deleteStoreCode.do", body);
	hReq.MyHttpRequest(0, 13131, &retData, &errCode, &errMsg);

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);

		ret = root["resultCode"].asInt();
		resultData->ret_cd.Format(L"%d", ret);
		resultData->ret_msg = root["resultMessage"].asCString();
	}
	catch (...) {
		CJSLogger::Logger('e', "Parsing StoreUnlink fail.");
		ret = -1;
	}

	if (ret) {
		CJSLogger::Logger('e', "[SEND]%s", CW2A(CT2W(body), CP_UTF8));
		CJSLogger::Logger('e', "[RECV]%s", CW2A(CT2W(retData), CP_UTF8));
	}

	return ret;
}

int CDelionDlvyLink::ParseJson(std::string input, Json::Value* value) {
	Json::Reader reader;
	bool parsingRet = reader.parse(input, *value);
	return 0;
}
