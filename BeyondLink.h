#pragma once

struct BeyondStore {
	CString beyond_code;
	CString biz_num;
	CString owner_name;
	CString store_name;
	CString store_addr;
	CString store_phone;
	CString store_mobile;

	CString link_code;
};

struct BeyondResultData {
	CString result_code;
	CString result_message;
};

enum BeyondServiceCode  {    // 열거형 정의
	by_byservice = 0,	// 이즈오케이->비욘드딜리버리
	by_rushcall = 1,	// 최강배달
	by_veteran = 2,	// 베테랑
	by_roadpilot = 3,	//로드파일럿(X)
	by_dsp = 4,		//배달인
	by_fooding = 5,	//레몬콜
	by_kitchen = 6,		//키친딜리버리(X)
	by_mtouch = 7,		// 엠터치
	by_hanaro = 8		// 하나로
};

class CBeyondLink
{
public:
	CBeyondLink();
	~CBeyondLink();

	int StoreSearch(CString bizCode, std::map<CString, BeyondStore*>* result, BeyondResultData* resultData);
	int StoreLink(CString beyondCode, CString storeCode, bool isMapping, BeyondResultData* resultData);
	int ParseJson(std::string input, Json::Value* value);
	void SetServFlag(int flag);
	int GetServFlag();
	
private:
	int servFlag;
};

