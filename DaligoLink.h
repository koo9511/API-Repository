#pragma once

//#define DALIGO_AUTHKEY L"B8933BD41B"	// test
#define SUPERHERO_AUTHKEY L"1300F0D598"	// superhero
#define DALIGO_AUTHKEY L"2F6148D38A"	// daligo
#define TNB_AUTHKEY L"08CE33C621"		// tnb
#ifdef ZENDELI_TEST
#define ZENDELI_AUTHKEY L"T5372CD27A"
#else
#define ZENDELI_AUTHKEY L"B3ECF3422B"
#endif

struct DaligoStore {
	CString biz_num;
	
	CString owner_name;
	CString store_num;
	CString store_name;
	CString store_phone;
	CString store_addr;
	
	CString link_code;
};

struct DaligoResultData {
	CString ret_cd;
	CString ret_msg;
};

class CDaligoLink
{
public:
	CDaligoLink();
	~CDaligoLink();

	int StoreSearch(CString bizCode, std::map<CString, DaligoStore*>* resultMap, DaligoResultData * resultData);
	int StoreLink(CString bizCode, CString storeNum, CString linkCode, DaligoResultData* resultData);
	int StoreUnlink(CString bizCode, CString linkCode, DaligoResultData * resultData);
	int ParseJson(std::string input, Json::Value * value);

	void SetAgencyFlag(int flag);
	int GetAgencyFlag();
private:
	int agency_flag = 0;	// Daligo:1, Superhero:2, TNB:3
};

