#include "stdafx.h"
#include "DaligoLink.h"


CDaligoLink::CDaligoLink()
{
}


CDaligoLink::~CDaligoLink()
{
}

int CDaligoLink::StoreSearch(CString bizCode, std::map<CString, DaligoStore*>* resultMap, DaligoResultData* resultData) {
	int ret = 0;
	CString body;
	CString retData;
	CString errCode;
	CString errMsg;
	CString temp;
	DaligoStore* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	// get Communicate http data
	if (this->agency_flag == 1)
		body.Format(L"{\"auth_key\":\"%s\",", DALIGO_AUTHKEY);
	else if (this->agency_flag == 2)
		body.Format(L"{\"auth_key\":\"%s\",", SUPERHERO_AUTHKEY);
	else if (this->agency_flag == 3)
		body.Format(L"{\"auth_key\":\"%s\",", TNB_AUTHKEY);
	else if (this->agency_flag == 4)
		body.Format(L"{\"auth_key\":\"%s\",", ZENDELI_AUTHKEY);
    
	body.AppendFormat(L"\"pno\":\"%s\"}", bizCode);

	hReq.SetDaligoFind(this->agency_flag, L"", body);
	hReq.MyHttpRequest(0, 0, &retData, &errCode, &errMsg);

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);

		Json::ValueIterator it = root.begin();

		// insert value to map
		while (it != root.end())
		{
			if (it->isObject()) // iterator가 객체인 경우
			{
				p_store = new DaligoStore;
				p_store->store_addr = (*it)["store_addr"].asCString();
				p_store->store_name = (*it)["store_nm"].asCString();
				p_store->store_num = (*it)["store_num"].asCString();
				p_store->store_phone = (*it)["store_tel"].asCString();

				resultMap->insert(pair<CString, DaligoStore*>(p_store->link_code, p_store));
			}
			++it;
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

int CDaligoLink::StoreLink(CString bizCode, CString storeNum, CString linkCode, DaligoResultData* resultData) {
	int ret = 0;
	CString body;
	CString retData;
	CString errCode;
	CString errMsg;
	CString resultCode;
	CString resultMessage;
	CString temp;
	DaligoStore* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	// get Communicate http data
	if (this->agency_flag == 1)
		body.Format(L"{\"auth_key\":\"%s\",", DALIGO_AUTHKEY);
	else if (this->agency_flag == 2)
		body.Format(L"{\"auth_key\":\"%s\",", SUPERHERO_AUTHKEY);
	else if (this->agency_flag == 3)
		body.Format(L"{\"auth_key\":\"%s\",", TNB_AUTHKEY);
	else if (this->agency_flag == 4)
		body.Format(L"{\"auth_key\":\"%s\",", ZENDELI_AUTHKEY);
	body.AppendFormat(L"\"store_num\":\"%s\",", storeNum);
	body.AppendFormat(L"\"pno\":\"%s\",", bizCode);
	body.AppendFormat(L"\"store_id\":\"%s\"}", linkCode);//teseuteusangjeom19
	//body.AppendFormat(L"\"store_id\":\"teseuteusangjeom19\"}");//teseuteusangjeom19
	hReq.SetDaligoLink(this->agency_flag, L"", body);
	hReq.MyHttpRequest(0, 0, &retData, &errCode, &errMsg);

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);

		Json::ValueIterator it = root.begin();

		// insert value to map
		while (it != root.end())
		{
			if (it->isObject()) // iterator가 객체인 경우
			{
				resultData->ret_cd.Format(L"%d", (*it)["ret_cd"].asInt());
				resultData->ret_msg = (*it)["ret_msg"].asCString();
				ret = _ttoi(resultData->ret_cd);
			}
			++it;
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

int CDaligoLink::StoreUnlink(CString bizCode, CString linkCode, DaligoResultData* resultData) {
	int ret = 0;
	CString body;
	CString retData;
	CString errCode;
	CString errMsg;
	CString resultCode;
	CString resultMessage;
	CString temp;
	DaligoStore* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	// get Communicate http data
	if (this->agency_flag == 1)
		body.Format(L"{\"auth_key\":\"%s\",", DALIGO_AUTHKEY);
	else if (this->agency_flag == 2)
		body.Format(L"{\"auth_key\":\"%s\",", SUPERHERO_AUTHKEY);
	else if (this->agency_flag == 3)
		body.Format(L"{\"auth_key\":\"%s\",", TNB_AUTHKEY);
	else if (this->agency_flag == 4)
		body.Format(L"{\"auth_key\":\"%s\",", ZENDELI_AUTHKEY);
	body.AppendFormat(L"\"pno\":\"%s\",", bizCode);
	body.AppendFormat(L"\"store_id\":\"%s\"}", linkCode);

	hReq.SetDaligoUnlink(this->agency_flag, L"", body);
	hReq.MyHttpRequest(0, 0, &retData, &errCode, &errMsg);

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);

		Json::ValueIterator it = root.begin();

		// insert value to map
		while (it != root.end())
		{
			if (it->isObject()) // iterator가 객체인 경우
			{
				resultData->ret_cd.Format(L"%d", (*it)["ret_cd"].asInt());
				resultData->ret_msg = (*it)["ret_msg"].asCString();
				ret = _ttoi(resultData->ret_cd);
			}
			++it;
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

int CDaligoLink::ParseJson(std::string input, Json::Value* value) {
	Json::Reader reader;
	bool parsingRet = reader.parse(input, *value);
	return 0;
}

void CDaligoLink::SetAgencyFlag(int flag) {
	this->agency_flag = flag;
}

int CDaligoLink::GetAgencyFlag() {
	return this->agency_flag;
}
