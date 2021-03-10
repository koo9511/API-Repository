#include "stdafx.h"
#include "MoacallLink.h"


CMoacallLink::CMoacallLink()
{
}


CMoacallLink::~CMoacallLink()
{
}


int CMoacallLink::StoreSearch(CString bizCode, std::map<CString, MoacallStore*>* result, MoaResultData* resultData) {
	int ret = 0;
	CString body;
	CString retData;
	CString errCode;
	CString errMsg;
	CString temp;
	MoacallStore* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	// get Communicate http data
	//bizCode.Remove(L'-');
	body.Format(L"{\"header\":{\"partner_code\":\"B|MOABANANA\", \"task_code\" : \"STORE_SEARCH\"}, \"body\" : {\"req_biz_num\":\"%s\"}}", bizCode);

	hReq.SetMoacall(L"", body);
	hReq.MyHttpRequest(0, 48088, &retData, &errCode, &errMsg);

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);

		if (!root["header"].isNull()) {
			Json::Value header = root["header"];

			resultData->result_code = header["result_code"].asCString();
			resultData->result_message = header["result_message"].asCString();
			ret = _ttoi(resultData->result_code);
		}

		if (ret) {
			return ret;
		}

		if (!root["body"].isNull()) {
			Json::Value body = root["body"];
			Json::Value moacall_store = body["res_moacall_store"];
			Json::ValueIterator it = moacall_store.begin();

			while (it != moacall_store.end())
			{
				if (it->isObject()) // iterator가 객체인 경우
				{
					temp = (*it)["arr_moacall_code"].asCString();
					p_store = new MoacallStore;
					p_store->moacall_code = temp;
					p_store->branch_name = (*it)["arr_branch_name"].asCString();
					p_store->biz_num = (*it)["arr_biz_num"].asCString();
					p_store->owner_name = (*it)["arr_owner_name"].asCString();
					p_store->store_name = (*it)["arr_store_name"].asCString();
					p_store->store_addr = (*it)["arr_store_addr"].asCString();
					p_store->store_phone = (*it)["arr_store_phone"].asCString();
					p_store->store_mobile = (*it)["arr_store_mobile"].asCString();
					result->insert(pair<CString, MoacallStore*>(p_store->moacall_code, p_store));
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

int CMoacallLink::StoreLink(CString* storeCode, CString moacallCode, MoaResultData* resultData) {
	int ret = 0;
	CString body;
	CString retData;
	CString errCode;
	CString errMsg;
	CString resultCode;
	CString resultMessage;
	CString temp;
	MoacallStore* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	// get Communicate http data
	body.Format(L"{\"header\":{\"partner_code\":\"B|MOABANANA\",\"task_code\":\"STORE_LINK\"},\"body\":{\"req_store_code\":\"%s\",\"req_moacall_code\":\"%s\"}}", *storeCode, moacallCode);

	hReq.SetMoacall(L"", body);
	hReq.MyHttpRequest(0, 48088, &retData, &errCode, &errMsg);

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);

		if (!root["header"].isNull()) {
			Json::Value header = root["header"];

			resultData->result_code = header["result_code"].asCString();
			resultData->result_message = header["result_message"].asCString();
			ret = _ttoi(resultData->result_code);
		}

		if (!root["body"].isNull()) {
			Json::Value jbody = root["body"];
			*storeCode = jbody["res_store_code"].asCString();
		}
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

int CMoacallLink::ParseJson(std::string input, Json::Value* value) {
	Json::Reader reader;
	bool parsingRet = reader.parse(input, *value);
	return 0;
}
