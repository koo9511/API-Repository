#pragma once


struct MoacallStore {
	CString moacall_code;
	CString branch_name;
	CString biz_num;
	CString owner_name;
	CString store_name;
	CString store_code;
	CString store_addr;
	CString store_phone;
	CString store_mobile;
	CString link_time;
};

struct MoaResultData {
	CString result_code;
	CString result_message;
};


class CMoacallLink
{
public:
	CMoacallLink();
	~CMoacallLink();

	int ParseJson(std::string input, Json::Value* value);
	int StoreSearch(CString bizCode, std::map<CString, MoacallStore*>* result, MoaResultData* resultData);
	int StoreLink(CString* storeCode, CString moacallCode, MoaResultData* resultData);
};

