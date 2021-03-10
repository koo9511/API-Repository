#pragma once

struct CombineNetStore {
	CString biz_num;

	CString combinenet_id;
	CString store_name;
	CString store_phone;
	CString store_mobile;
	CString address;

	CString link_code;
};

struct CombineNetResultData {
	CString ret_cd;
	CString ret_msg;
};

enum CombinenetServiceCode {
	cbn_notset = -1,
	cbn_hangbok = 1,	// 행복배달
	cbn_spider = 2,		// 스파이더
	cbn_baena9 = 3		// 배달로나라를구하신
};

class CCombineNetLink
{
public:
	CCombineNetLink();
	~CCombineNetLink();

	int StoreSearch(CString bizCode, std::map<CString, CombineNetStore*>* resultMap, CombineNetResultData * resultData);
	int StoreLink(CString storeNum, CString linkCode, CombineNetResultData* resultData);
	int StoreUnlink(CString storeNum, CString linkCode, CombineNetResultData* resultData);
	int ParseJson(std::string input, Json::Value * value);

	void SetAgencyFlag(int flag);
	int GetAgencyFlag();
private:
	int agency_flag = -1;	// Daligo:1, Superhero:2, TNB:3
};

