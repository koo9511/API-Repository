#pragma once
#include <map>

using namespace std;

static class CUtil
{
public:
	CUtil();
	~CUtil();
	static int parseXML(CString, map<CString, CString>*);
	static int parseJSON(CString inString, map<CString, CString> *inMap);
	static int saveProperty(CString shopCode);
	static int loadProperty(CString* shopCode);
	static int sendAccessMsg(CString authKey);
	static std::string urlencodeeng(std::string s);
	static std::string urldecodeeng(std::string s);
	static CString SpecialCharacterUrlEncode(wchar_t * source);
	static int ReplaceSpecialCharacter(CString * source);
	static int GetInitialFromHangeul(wchar_t * source, CString * result, int initialCnt);
	static int han2eng(wchar_t *source, CString *result, UINT resultBufferSize);
	static CString GetMACAddress();
};

