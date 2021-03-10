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

enum BeyondServiceCode  {    // ������ ����
	by_byservice = 0,	// ���������->�����������
	by_rushcall = 1,	// �ְ����
	by_veteran = 2,	// ���׶�
	by_roadpilot = 3,	//�ε����Ϸ�(X)
	by_dsp = 4,		//�����
	by_fooding = 5,	//������
	by_kitchen = 6,		//Űģ��������(X)
	by_mtouch = 7,		// ����ġ
	by_hanaro = 8		// �ϳ���
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

