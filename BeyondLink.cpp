#include "stdafx.h"
#include "BeyondLink.h"


CBeyondLink::CBeyondLink()
{
}


CBeyondLink::~CBeyondLink()
{
}

int CBeyondLink::StoreSearch(CString bizCode, std::map<CString, BeyondStore*>* result, BeyondResultData* resultData) {
	int ret = 0;
	//enum ServiceCode serv_code_flag;
	CString body;
	CString retData;
	CString errCode;
	CString errMsg;
	CString temp;
	BeyondStore* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	// get Communicate http data
	//bizCode.Remove(L'-');
#ifdef BEYOND_TEST
	body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"dev\",\"MethodName\":\"API_DVRY_SHOP_FIND\",\"StoreFindText\":\"%s\"}", bizCode);
#else
	if (servFlag == by_byservice)	// ���������
		body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"byservice\",\"MethodName\":\"API_DVRY_SHOP_FIND\",\"StoreFindText\":\"%s\"}", bizCode);
	else if (servFlag == by_rushcall)	// �ְ����
		body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"rushcall\",\"MethodName\":\"API_DVRY_SHOP_FIND\",\"StoreFindText\":\"%s\"}", bizCode);
	else if (servFlag == by_veteran)	// ���׶�
		body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"veteran\",\"MethodName\":\"API_DVRY_SHOP_FIND\",\"StoreFindText\":\"%s\"}", bizCode);
	//else if (servFlag == by_roadpilot)	// �ε����Ϸ�
		//body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"roadpilot\",\"MethodName\":\"API_DVRY_SHOP_FIND\",\"StoreFindText\":\"%s\"}", bizCode);
	else if (servFlag == by_dsp)	// �����
		body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"dsp\",\"MethodName\":\"API_DVRY_SHOP_FIND\",\"StoreFindText\":\"%s\"}", bizCode);
	else if (servFlag == by_fooding)	// ������
		body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"fooding\",\"MethodName\":\"API_DVRY_SHOP_FIND\",\"StoreFindText\":\"%s\"}", bizCode);
	//else if (servFlag == by_kitchen)	// Űģ��������
		//body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"kitchen\",\"MethodName\":\"API_DVRY_SHOP_FIND\",\"StoreFindText\":\"%s\"}", bizCode);
	else if (servFlag == by_mtouch)	// ����ġ
		body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"mtouch\",\"MethodName\":\"API_DVRY_SHOP_FIND\",\"StoreFindText\":\"%s\"}", bizCode);
	else if (servFlag == by_hanaro)	// �ϳ���
		body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"hanaro\",\"MethodName\":\"API_DVRY_SHOP_FIND\",\"StoreFindText\":\"%s\"}", bizCode);
#endif

	hReq.SetBeyond(servFlag, L"", body);
#ifdef BEYOND_TEST
	hReq.MyHttpRequest(0, 8080, &retData, &errCode, &errMsg);
#else
	hReq.SetBeyond(servFlag, L"", body);
	if (servFlag == by_byservice)	// ���������
		hReq.MyHttpRequest(1, 17070, &retData, &errCode, &errMsg);
	else if (servFlag == by_rushcall)	// �ְ����
		hReq.MyHttpRequest(1, 17080, &retData, &errCode, &errMsg);
	else if (servFlag == by_veteran)	// ���׶�
		hReq.MyHttpRequest(1, 17010, &retData, &errCode, &errMsg);
	//else if (servFlag == by_roadpilot)	// �ε����Ϸ�
		//hReq.MyHttpRequest(1, 17060, &retData, &errCode, &errMsg);
	else if (servFlag == by_dsp)	// �����
		hReq.MyHttpRequest(1, 17050, &retData, &errCode, &errMsg);
	else if (servFlag == by_fooding)	// ������
		hReq.MyHttpRequest(1, 17030, &retData, &errCode, &errMsg);
	//else if (servFlag == by_kitchen)	// Űģ��������
		//hReq.MyHttpRequest(1, 17000, &retData, &errCode, &errMsg);
	else if (servFlag == by_mtouch)	// ����_����ġ
		hReq.MyHttpRequest(1, 17020, &retData, &errCode, &errMsg);
	else if (servFlag == by_hanaro)	// ����_�ϳ���
		hReq.MyHttpRequest(1, 16090, &retData, &errCode, &errMsg);
#endif

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);

		if (root["ErrCode"].isInt())
			resultData->result_code.Format(L"%d", root["ErrCode"].asInt());
		else
			resultData->result_code = root["ErrCode"].asCString();
            resultData->result_message = root["ErrMsg"].asCString();
            ret = _ttoi(resultData->result_code);

		if (ret) {
			return ret;
		}

		if (!root["Data"].isNull()) {
			Json::Value data = root["Data"];
			Json::ValueIterator it = data.begin();

			while (it != data.end())
			{
				if (it->isObject()) // iterator�� ��ü�� ���
				{
					temp = (*it)["StoreCode"].asCString();
					p_store = new BeyondStore;
					p_store->beyond_code = temp;
					p_store->biz_num = (*it)["StoreBusNum"].asCString();
					p_store->owner_name = (*it)["StoreCeoName"].asCString();
					p_store->store_name = (*it)["StoreName"].asCString();
					p_store->store_addr = (*it)["StoreJiBunAddr"].asCString();
					p_store->store_phone = (*it)["StorePhone"].asCString();
					p_store->store_mobile = (*it)["StoreCeoMobile"].asCString();
					result->insert(pair<CString, BeyondStore*>(p_store->beyond_code, p_store));
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

int CBeyondLink::StoreLink(CString beyondCode, CString storeCode, bool isMapping, BeyondResultData* resultData) {
	int ret = 0;
	CString body;
	CString retData;
	CString errCode;
	CString errMsg;
	CString resultCode;
	CString resultMessage;
	CString temp;
	BeyondStore* p_store;

	CHttpsRequest hReq;

	_free_locale(LC_ALL);

	// get Communicate http data
	
	

#ifdef BEYOND_TEST
	body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"dev\",\"MethodName\":\"API_DVRY_SHOP_LINK\",");
#else
	if (servFlag == by_byservice)	// ���������
		body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"byservice\",\"MethodName\":\"API_DVRY_SHOP_LINK\",");
	else if (servFlag == by_rushcall)	// �ְ����
		body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"rushcall\",\"MethodName\":\"API_DVRY_SHOP_LINK\",");
	else if (servFlag == by_veteran)	// ���׶�
		body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"veteran\",\"MethodName\":\"API_DVRY_SHOP_LINK\",");
	//else if (servFlag == by_roadpilot)	// �ε����Ϸ�
		//body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"roadpilot\",\"MethodName\":\"API_DVRY_SHOP_LINK\",");
	else if (servFlag == by_dsp)	// �����
		body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"dsp\",\"MethodName\":\"API_DVRY_SHOP_LINK\",");
	else if (servFlag == by_fooding)	// ������
		body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"fooding\",\"MethodName\":\"API_DVRY_SHOP_LINK\",");
	//else if (servFlag == by_kitchen)	// Űģ��������
		//body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"kitchen\",\"MethodName\":\"API_DVRY_SHOP_LINK\",");
	else if (servFlag == by_mtouch)	// ������
		body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"mtouch\",\"MethodName\":\"API_DVRY_SHOP_LINK\",");
	else if (servFlag == by_hanaro)	// Űģ��������
		body.Format(L"{\"VenderName\":\"banana\",\"ServiceCode\":\"hanaro\",\"MethodName\":\"API_DVRY_SHOP_LINK\",");
#endif
	body.AppendFormat(L"\"StoreCode\":\"%s\",", beyondCode);
	body.AppendFormat(L"\"PosStoreCode\":\"%s\",", storeCode);
	if (isMapping)
		body.AppendFormat(L"\"MappingState\":\"N\",");
	else
		body.AppendFormat(L"\"MappingState\":\"C\",");
	body.AppendFormat(L"\"MappingMemo\":\"\"}");

	hReq.SetBeyond(servFlag, L"", body);
#ifdef BEYOND_TEST
	hReq.MyHttpRequest(0, 8080, &retData, &errCode, &errMsg);
#else
	hReq.SetBeyond(servFlag, L"", body);
	if (servFlag == by_byservice)	// ���������
		hReq.MyHttpRequest(1, 17070, &retData, &errCode, &errMsg);
	else if (servFlag == by_rushcall)	// �ְ����
		hReq.MyHttpRequest(1, 17080, &retData, &errCode, &errMsg);
	else if (servFlag == by_veteran)	// ���׶�
		hReq.MyHttpRequest(1, 17010, &retData, &errCode, &errMsg);
	//else if (servFlag == by_roadpilot)	// �ε����Ϸ�
		//hReq.MyHttpRequest(1, 17060, &retData, &errCode, &errMsg);
	else if (servFlag == by_dsp)	// �����
		hReq.MyHttpRequest(1, 17050, &retData, &errCode, &errMsg);
	else if (servFlag == by_fooding)	// ������
		hReq.MyHttpRequest(1, 17030, &retData, &errCode, &errMsg);
	//else if (servFlag == by_kitchen)	// Űģ��������
		//hReq.MyHttpRequest(1, 17000, &retData, &errCode, &errMsg);
	else if (servFlag == by_mtouch)	// ����_����ġ
		hReq.MyHttpRequest(1, 17020, &retData, &errCode, &errMsg);
	else if (servFlag == by_hanaro)	// ����_�ϳ���
		hReq.MyHttpRequest(1, 16090, &retData, &errCode, &errMsg);
#endif

	// parse response
	Json::Value root;
	std::locale::global(std::locale("korean"));

	std::string input = CW2A(retData);

	try {
		ParseJson(input, &root);
		if (root["ErrCode"].isInt())
			resultData->result_code.Format(L"%d", root["ErrCode"].asInt());
		else
			resultData->result_code = root["ErrCode"].asCString();
		resultData->result_message = root["ErrMsg"].asCString();
		ret = _ttoi(resultData->result_code);
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

int CBeyondLink::ParseJson(std::string input, Json::Value* value) {
	Json::Reader reader;
	bool parsingRet = reader.parse(input, *value);
	return 0;
}

void CBeyondLink::SetServFlag(int flag) {
	this->servFlag = flag;
}

int CBeyondLink::GetServFlag() {
	return this->servFlag;
}
