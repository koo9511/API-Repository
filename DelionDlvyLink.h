#pragma once

struct DelionStore {
	CString biz_num;

	CString owner_name;
	CString store_code;
	CString store_name;
	CString store_phone;
	CString store_mobile;
	CString store_addr;
	CString branch_code;
	CString branch_name;

	CString link_code;
};

struct DelionResultData {
	CString ret_cd;
	CString ret_msg;
};

class CDelionDlvyLink
{
public:
	CDelionDlvyLink();
	~CDelionDlvyLink();

	int StoreSearch(CString bizCode, std::map<CString, StoreInfo*>* resultMap, ResultData * resultData);
	int StoreLink(CString storeCode, CString linkCode, ResultData* resultData);
	int StoreUnlink(CString storeCode, CString linkCode, ResultData * resultData);
	int ParseJson(std::string input, Json::Value * value);
};

