#include "stdafx.h"
#include "SanggagLink.h"


CSanggagLink::CSanggagLink()
{
}


CSanggagLink::~CSanggagLink()
{
}

int CSanggagLink::StoreSearch(CString bizCode, std::map<CString, SanggagStore*>* resultMap, SanggagResultData* resultData) {
	int ret = 0;
	CString body;
	CString retData;
	CString errCode;
	CString errMsg;
	CString temp;
	SanggagStore* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	// get Communicate http data
	srand((unsigned int)time(NULL));
	int randNum = rand() % 1000;
	CTime c_time = CTime::GetCurrentTime(); // 현재 시스템으로부터 날짜 및 시간을 얻어 온다.
	CString reqtime;
	reqtime.Format(L"%04d%02d%02d%02d%02d%02d", c_time.GetYear(), c_time.GetMonth(), c_time.GetDay(), c_time.GetHour(), c_time.GetMinute(), c_time.GetSecond());
	body.Format(L"{\"header\": {\"FORMAT\": \"JSON\",");
#ifdef SANGGAG_TEST
	body.AppendFormat(L"\"KEY\": \"N342xN91e5WqFMimTneLww==\",");
#else
	body.AppendFormat(L"\"KEY\": \"piwHtKL9eEE=\",");
#endif
	body.AppendFormat(L"\"TRACE_NO\": \"%s%03d\",", reqtime, randNum);
	body.AppendFormat(L"\"SERVICE_CODE\": \"API_DVRY_API_SHOP_INFO\"},");

	//body.AppendFormat(L"\"body\": {\"in_ACTION_KIND\": \"1\",");
	body.AppendFormat(L"\"body\": {\"in_ACTION_KIND\": \"3\",");
	body.AppendFormat(L"\"in_APP_COM_GBN\": \"BP01\",");
	body.AppendFormat(L"\"in_SHOP_NAME\": \"%s\"}}", bizCode);

	hReq.SetSanggag(L"", body);
	ret = hReq.MyHttpRequest(0, 0, &retData, &errCode, &errMsg);

	if (ret) {
		resultData->ret_cd = errCode;
		resultData->ret_msg = errMsg;
		return ret;
	}

	retData.Replace(L"\"[", L"[");
	retData.Replace(L"]\"", L"]");
	retData.Replace(L"\\\"", L"\"");

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);

		if (!root["header"].isNull()) {
			Json::Value header = root["header"];

			resultData->ret_cd = header["RES_CODE"].asCString();
			resultData->ret_msg = header["RES_MSG"].asCString();
			ret = _ttoi(errCode);
		}

		if (ret) {
			CJSLogger::Logger('e', "[SEND]%s", CW2A(CT2W(body), CP_UTF8));
			CJSLogger::Logger('e', "[RECV]%s", CW2A(CT2W(retData), CP_UTF8));
			return ret;
		}

		if (!root["body"].isNull()) {
			Json::Value body = root["body"];

			Json::Value dataList = body["DATA_LIST"];
			Json::ValueIterator it = dataList.begin();

			if (it == dataList.end()) {
				ret = -3;
				resultData->ret_msg = L"조회된 정보가 없습니다.\n타 포스 연동중인 매장인지 확인해주세요.";
			}
			else {
				while (it != dataList.end())
				{
					if (it->isObject()) // iterator가 객체인 경우
					{
						// insert value to map
						p_store = new SanggagStore;
						if (!(*it)["ADDR"].isNull())
							p_store->store_addr = (*it)["ADDR"].asCString();
                        
						if (!(*it)["SHOP_NAME"].isNull())
							p_store->store_name = (*it)["SHOP_NAME"].asCString();
                        
						if (!(*it)["SHOP_CD"].isNull())
							p_store->store_code = (*it)["SHOP_CD"].asCString();
                        
						if (!(*it)["TELNO"].isNull())
							p_store->store_phone = (*it)["TELNO"].asCString();
                        
						if (!(*it)["MOBILE"].isNull())
							p_store->store_mobile = (*it)["MOBILE"].asCString();
                        
						if (!(*it)["CCCODE"].isNull())
							p_store->branch_code = (*it)["CCCODE"].asCString();
                        
						if (!(*it)["CCNAME"].isNull())
							p_store->branch_name = (*it)["CCNAME"].asCString();
                        
						if (!(*it)["REG_NO"].isNull())
							p_store->biz_num = (*it)["REG_NO"].asCString();

						resultMap->insert(pair<CString, SanggagStore*>(p_store->store_code, p_store));
					}
					++it;
				}
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

int CSanggagLink::StoreLink(CString branch_code, CString storeNum, CString linkCode, SanggagResultData* resultData) {
	int ret = 0;
	CString body;
	CString retData;
	CString errCode;
	CString errMsg;
	CString resultCode;
	CString resultMessage;
	CString temp;
	SanggagStore* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	// get Communicate http data
	srand((unsigned int)time(NULL));
	int randNum = rand() % 1000;
	CTime c_time = CTime::GetCurrentTime(); // 현재 시스템으로부터 날짜 및 시간을 얻어 온다.
	CString reqtime;
	reqtime.Format(L"%04d%02d%02d%02d%02d%02d", c_time.GetYear(), c_time.GetMonth(), c_time.GetDay(), c_time.GetHour(), c_time.GetMinute(), c_time.GetSecond());
	body.Format(L"{\"header\": {\"FORMAT\": \"JSON\",");
#ifdef SANGGAG_TEST
	body.AppendFormat(L"\"KEY\": \"N342xN91e5WqFMimTneLww==\",");
#else
	body.AppendFormat(L"\"KEY\": \"piwHtKL9eEE=\",");
#endif
	body.AppendFormat(L"\"TRACE_NO\": \"%s%03d\",", reqtime, randNum);
	body.AppendFormat(L"\"SERVICE_CODE\": \"API_DVRY_SHOP_CODE_LINK\"},");

	body.AppendFormat(L"\"body\": {\"in_CCCODE\": \"%s\",", branch_code);
	body.AppendFormat(L"\"in_SHOP_CODE\": \"%s\",", storeNum);
	body.AppendFormat(L"\"in_APP_COM_GBN\": \"BP01\",");
	body.AppendFormat(L"\"in_LINK_SHOP_CODE\": \"%s\"}}", linkCode);

	hReq.SetSanggag(L"", body);
	ret = hReq.MyHttpRequest(0, 0, &retData, &errCode, &errMsg);

	if (ret) {
		resultData->ret_cd = errCode;
		resultData->ret_msg = errMsg;
		return ret;
	}

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);

		if (!root["header"].isNull()) {
			Json::Value header = root["header"];

			resultData->ret_cd = header["RES_CODE"].asCString();
			resultData->ret_msg = header["RES_MSG"].asCString();
			ret = _ttoi(errCode);
		}

		if (ret) {
			CJSLogger::Logger('e', "[SEND]%s", CW2A(CT2W(body), CP_UTF8));
			CJSLogger::Logger('e', "[RECV]%s", CW2A(CT2W(retData), CP_UTF8));
			return ret;
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

int CSanggagLink::StoreUnlink(CString bizCode, CString linkCode, SanggagResultData* resultData) {
	int ret = 0;
	CString body;
	CString retData;
	CString errCode;
	CString errMsg;
	CString resultCode;
	CString resultMessage;
	CString temp;
	SanggagStore* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	// get Communicate http data
	/*
	if (this->agency_flag == 1)
		body.Format(L"{\"auth_key\":\"%s\",", DALIGO_AUTHKEY);
	else if (this->agency_flag == 2)
		body.Format(L"{\"auth_key\":\"%s\",", SUPERHERO_AUTHKEY);
	else if (this->agency_flag == 3)
		body.Format(L"{\"auth_key\":\"%s\",", TNB_AUTHKEY);
	body.AppendFormat(L"\"pno\":\"%s\",", bizCode);
	body.AppendFormat(L"\"store_id\":\"%s\"}", linkCode);
	*/
	//hReq.SetDaligoUnlink(L"", body);
	ret = hReq.MyHttpRequest(0, 0, &retData, &errCode, &errMsg);

	if (ret) {
		resultData->ret_cd = errCode;
		resultData->ret_msg = errMsg;
		return ret;
	}

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

int CSanggagLink::ParseJson(std::string input, Json::Value* value) {
	Json::Reader reader;
	bool parsingRet = reader.parse(input, *value);
	return 0;
}

void CSanggagLink::SetAgencyFlag(int flag) {
	this->agency_flag = flag;
}

int CSanggagLink::GetAgencyFlag() {
	return this->agency_flag;
}
