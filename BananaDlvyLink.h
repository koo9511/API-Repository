#pragma once

struct BananaDlvyStore {
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

struct BananaDlvyResultData {
	CString ret_cd;
	CString ret_msg;
};

class CBananaDlvyLink
{
public:
	CBananaDlvyLink();
	~CBananaDlvyLink();

	int StoreSearch(CString bizCode, std::map<CString, BananaDlvyStore*>* resultMap, BananaDlvyResultData * resultData);
	int StoreLink(CString branch_code, CString storeNum, CString linkCode, BananaDlvyResultData* resultData);
	int StoreUnlink(CString bizCode, CString linkCode, BananaDlvyResultData * resultData);
	int ParseJson(std::string input, Json::Value * value);

	void SetAgencyFlag(int flag);
	int GetAgencyFlag();
private:
	int agency_flag = -1;
};

