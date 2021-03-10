#pragma once

struct RoadvoyStore {
	CString biz_num;

	CString roadvoy_id;
	CString store_name;
	CString store_phone;
	CString store_mobile;
	CString addr_jibun;
	CString addr_road;
	CString addr_desc;

	CString link_code;
};

struct RoadvoyResultData {
	CString ret_code;
	CString ret_msg;
};

class CRoadvoyLink
{
public:
	CRoadvoyLink();
	~CRoadvoyLink();

	int StoreSearch(CString bizCode, std::map<CString, RoadvoyStore*>* resultMap, RoadvoyResultData * resultData);
	int StoreLink(CString roadvoyId, CString linkCode, RoadvoyResultData* resultData);
	int StoreUnlink(CString linkCode, RoadvoyResultData * resultData);
	int ParseJson(std::string input, Json::Value * value);
};

