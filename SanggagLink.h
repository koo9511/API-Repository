#pragma once

struct SanggagStore {
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

struct SanggagResultData {
	CString ret_cd;
	CString ret_msg;
};

class CSanggagLink
{
public:
	CSanggagLink();
	~CSanggagLink();

	int StoreSearch(CString bizCode, std::map<CString, SanggagStore*>* resultMap, SanggagResultData * resultData);
	int StoreLink(CString branch_code, CString storeNum, CString linkCode, SanggagResultData* resultData);
	int StoreUnlink(CString bizCode, CString linkCode, SanggagResultData * resultData);
	int ParseJson(std::string input, Json::Value * value);

	void SetAgencyFlag(int flag);
	int GetAgencyFlag();
private:
	int agency_flag = 0;
};

