#include "stdafx.h"
#include "Util.h"
#include "JSLogger.h"
#include <vector>

#define LENBOX_SIZE		4
#define OP_MSG_SIZE		10
#define MAC_ADDR_SIZE	20
#define AUTHKEY_SIZE	100

using namespace std;

CUtil::CUtil()
{
}


CUtil::~CUtil()
{
}

int CUtil::parseXML(CString inString, map<CString, CString> *inMap){
	int ret = 0;
	int sPos = 0;
	int ePos = 0;
	int menuCnt = 0;
	int menuCost = 0;
	int subMenuCost = 0;
	int totalCost = 0;
	CString temp;
	CString oLink;
	CString oCost;
	CString oPrice;

	sPos = inString.Find(L"<link>", 0);
	ePos = inString.Find(L"</link>", sPos);
	oLink = inString.Mid(sPos + strlen("<link>"), ePos - (sPos + strlen("<link>")));

	if (!oLink.CompareNoCase(L"baemin") || !oLink.CompareNoCase(L"baedaltong")) { // baemin,  baedaltong
		ePos = 0;
		while ((sPos = inString.Find(L"<menuprice>", ePos)) > 0) {
			ePos = inString.Find(L"</menuprice>", sPos);
			oCost = inString.Mid(sPos + strlen("<menuprice>"), ePos - (sPos + strlen("<menuprice>")));
			oCost.Trim();
			oCost.Remove(',');
			oCost.Remove('.');
			oCost.Remove('+');
			oCost.Remove('-');
			totalCost += _ttoi(oCost);
		}

		if ((sPos = inString.Find(L"<cost>", 0)) > 0) {
			sPos = inString.Find(L"<cost>", 0);
			ePos = inString.Find(L"</cost>", sPos);
			oCost = inString.Mid(sPos + strlen("<cost>"), ePos - (sPos + strlen("<cost>")));
			oCost.Trim();
			oCost.Remove(',');
			oCost.Remove('.');
			oCost.Remove('+');
			oCost.Remove('-');
			totalCost += _ttoi(oCost);
		}

		if ((sPos = inString.Find(L"<discount>", 0)) > 0) {
			sPos = inString.Find(L"<discount>", 0);
			ePos = inString.Find(L"</discount>", sPos);
			oCost = inString.Mid(sPos + strlen("<discount>"), ePos - (sPos + strlen("<discount>")));
			oCost.Trim();
			oCost.Remove(',');
			oCost.Remove('.');
			oCost.Remove('+');
			oCost.Remove('-');
			totalCost -= _ttoi(oCost);
		}
	}
	else {	// yogiyo
		ePos = 0;
		while ((sPos = inString.Find(L"<menucount>", ePos)) > 0) {
			ePos = inString.Find(L"</menucount>", sPos);
			oCost = inString.Mid(sPos + strlen("<menucount>"), ePos - (sPos + strlen("<menucount>")));
			oCost.Trim();
			oCost.Remove(',');
			oCost.Remove('.');
			oCost.Remove('+');
			oCost.Remove('-');
			oCost.Remove('x');
			menuCnt = _ttoi(oCost);

			if ((ret = inString.Find(L"<menuprice>", ePos)) > 0)
				sPos = ret;
			if ((ret = inString.Find(L"</menuprice>", sPos)) > 0)
				ePos = ret;
			if (ret > 0) {
				oCost = inString.Mid(sPos + strlen("<menuprice>"), ePos - (sPos + strlen("<menuprice>")));
				oCost.Trim();
				oCost.Remove(',');
				oCost.Remove('.');
				oCost.Remove('+');
				oCost.Remove('-');
				menuCost = _ttoi(oCost);
			}

			if ((ret = inString.Find(L"<submenuprice>", ePos)) > 0)
				sPos = ret;
			if ((ret = inString.Find(L"</submenuprice>", sPos)) > 0)
				ePos = ret;
			if (ret > 0) {
				oCost = inString.Mid(sPos + strlen("<submenuprice>"), ePos - (sPos + strlen("<submenuprice>")));
				oCost.Trim();
				oCost.Remove(',');
				oCost.Remove('.');
				oCost.Remove('+');
				oCost.Remove('-');
				subMenuCost = _ttoi(oCost);
			}

			totalCost += menuCnt * (menuCost + subMenuCost);
			menuCnt = 0;
			menuCost = 0;
			subMenuCost = 0;
		}

		if ((sPos = inString.Find(L"<cost>", 0)) > 0) {
			sPos = inString.Find(L"<cost>", 0);
			ePos = inString.Find(L"</cost>", sPos);
			oCost = inString.Mid(sPos + strlen("<cost>"), ePos - (sPos + strlen("<cost>")));
			oCost.Trim();
			oCost.Remove(',');
			oCost.Remove('.');
			oCost.Remove('+');
			oCost.Remove('-');
			totalCost += _ttoi(oCost);
		}

		if ((sPos = inString.Find(L"<discount>", 0)) > 0) {
			sPos = inString.Find(L"<discount>", 0);
			ePos = inString.Find(L"</discount>", sPos);
			oCost = inString.Mid(sPos + strlen("<discount>"), ePos - (sPos + strlen("<discount>")));
			oCost.Trim();
			oCost.Remove(',');
			oCost.Remove('.');
			oCost.Remove('+');
			oCost.Remove('-');
			totalCost -= _ttoi(oCost);
		}
	}

	sPos = inString.Find(L"<price>", 0);
	ePos = inString.Find(L"</price>", sPos);
	oPrice = inString.Mid(sPos + strlen("<price>"), ePos - (sPos + strlen("<price>")));

	temp.Format(L"%d", totalCost);
	inMap->insert(pair<CString, CString>(L"price", temp));


	sPos = inString.Find(L"<address>", 0);
	ePos = inString.Find(L"</address>", sPos);
	inMap->insert(pair<CString, CString>(L"address", inString.Mid(sPos + strlen("<address>"), ePos - (sPos + strlen("<address>")))));

	sPos = inString.Find(L"<type>", 0);
	ePos = inString.Find(L"</type>", sPos);
	temp = inString.Mid(sPos + strlen("<type>"), ePos - (sPos + strlen("<type>")));
	if (!temp.Compare(L"만나서결제(현금)") || !temp.Compare(L"만나서 현금결제"))
		temp = L"1";
	else if (!temp.Compare(L"만나서결제(카드)"))
		temp = L"0";
	else if (!temp.Compare(L"바로결제"))
		temp = L"3";
	inMap->insert(pair<CString, CString>(L"type", temp));

	sPos = inString.Find(L"<memo>", 0);
	ePos = inString.Find(L"</memo>", sPos);
	inMap->insert(pair<CString, CString>(L"memo", inString.Mid(sPos + strlen("<memo>"), ePos - (sPos + strlen("<memo>")))));

	sPos = inString.Find(L"<tel>", 0);
	ePos = inString.Find(L"</tel>", sPos);
	temp = inString.Mid(sPos + strlen("<tel>"), ePos - (sPos + strlen("<tel>")));
	temp.Remove('-');
	inMap->insert(pair<CString, CString>(L"tel", temp));

	return 0;
}

int CUtil::parseJSON(CString inString, map<CString, CString> *inMap){
	int sPos = 0;
	int ePos = 0;

	sPos = inString.Find(L"\"errorNum\"");
	ePos = inString.Find(L"</price>");
	inMap->insert(pair<CString, CString>(L"price", inString.Mid(sPos + strlen("<price>"), ePos - (sPos + strlen("<price>")))));

	sPos = inString.Find(L"\"errorCode\"");
	ePos = inString.Find(L"</address>");
	inMap->insert(pair<CString, CString>(L"address", inString.Mid(sPos + strlen("<address>"), ePos - (sPos + strlen("<address>")))));

	sPos = inString.Find(L"\"errorMessage\"");
	ePos = inString.Find(L"</type>");
	inMap->insert(pair<CString, CString>(L"type", inString.Mid(sPos + strlen("<type>"), ePos - (sPos + strlen("<type>")))));

	sPos = inString.Find(L"<memo>");
	ePos = inString.Find(L"</memo>");
	inMap->insert(pair<CString, CString>(L"memo", inString.Mid(sPos + strlen("<memo>"), ePos - (sPos + strlen("<memo>")))));

	sPos = inString.Find(L"<tel>");
	ePos = inString.Find(L"</tel>");
	inMap->insert(pair<CString, CString>(L"tel", inString.Mid(sPos + strlen("<tel>"), ePos - (sPos + strlen("<tel>")))));

	return 0;
}

int CUtil::saveProperty(CString shopCode){
	CFile cfile;
	try{
		cfile.Open(L"o2ns.dat", CFile::modeCreate | CFile::modeWrite);
		char writeBuff[1000];
		memset(writeBuff, 0, 1000);

		if (!shopCode.IsEmpty()) {
			sprintf_s(writeBuff, "%s\n", CW2A(CT2W(shopCode), CP_UTF8));
			cfile.Write(writeBuff, strlen(writeBuff));
		}

		cfile.Flush();
		cfile.Close();
	}
	catch (CFileException* e){
		//MessageBox(NULL, L"설정파일을 저장할 수 없습니다.", L"경고", MB_ICONWARNING);
		TCHAR path[200];
		CString strPath;
		int i = 0;
		GetModuleFileName(NULL, path, sizeof path);
		PathRemoveFileSpec(path);
		strPath = (LPCTSTR)path;
		e->ReportError();
		//MessageBox(NULL, L"Can not find \""+strPath+L"\\o2ns.dat\"", L"경고", MB_ICONWARNING);
		return -1;
	}
	
	return 0;
}

int CUtil::loadProperty(CString* shopCode){
	CFile cfile;
	CString temp;
	try{
		cfile.Open(L"o2ns.dat", CFile::modeCreate | CFile::modeNoTruncate | CFile::modeRead);
		char readBuff[1000];
		memset(readBuff, 0, 1000);
		cfile.Read(readBuff, 1000);
		temp = CW2T(CA2W(readBuff, CP_UTF8));

		if (temp.Compare(L"")){
			AfxExtractSubString(*shopCode, temp, 0, '\n');
		}
		cfile.Close();
	}
	catch (CFileException* e){
		MessageBox(NULL, L"설정파일을 찾을 수 없습니다.", L"경고", MB_ICONWARNING);
		return -1;
	}

	return 0;
}

union Box {    // 공용체 정의
	unsigned int iType;
	char cType[4];
};

int CUtil::sendAccessMsg(CString authKey){
	int ret = 0;
	int error = 0;
	int loopCnt = 0;
	int currentLen = 0;
	int totalLen = 0;
	int rtryCnt = 0;
	char RecvBuff[10000];
	char sendBuff[1024];
	char svrRes[OP_MSG_SIZE + 1] = { 0, };
	char tmp[50];	//출력을위해서잠시char 형으로변환
	char fName[100] = { 0, };
	Box lenBox;
	CSocket sock;
	CFile newFile;
	BOOL fOpenFlag = FALSE;

	// Init Socket
	if (!AfxSocketInit())
	{
		error = GetLastError();
		CJSLogger::Logger('e', "Socket Init Fail(error %d).", error);
		return error;
	}
	CJSLogger::Logger('d', "Socket Init Success.");

	CJSLogger::Logger('d', "Creating socket...");
	if (!sock.Create())
	{
		error = GetLastError();
		CJSLogger::Logger('e', "Socket Create Fail(error %d).", error);
		return GetLastError();
	}
	CJSLogger::Logger('d', "Socket Create Success.");

	// Set server IP, Port
	int port = 48011;
	CString address("115.68.102.212");
	//CString address("192.168.231.128");

	wcstombs_s(NULL, tmp, address.GetLength() + 1, address, _TRUNCATE);
	CJSLogger::Logger('d', "Connecting %s, %d", tmp, port);
rty:
	if (!sock.Connect(address, port))	//address를char형으로할수없음
	{
		error = GetLastError();
		CJSLogger::Logger('e', "Socket Connect Fail(error %d).", error);
		if (rtryCnt < 5){
			Sleep(5000);
			rtryCnt++;
			goto rty;
		}
		return GetLastError();
	}
	CJSLogger::Logger('d', "Socket Connect Success.");


	// ***************** Set send message *****************
	loopCnt = 0;
	currentLen = 0;
	totalLen = 0;
	memset(sendBuff, 0, sizeof(sendBuff));

	// message [operating msg 10][MAC Addr 20][current Ver 20][file name 50]
	// Copy Length
	lenBox.iType = OP_MSG_SIZE + MAC_ADDR_SIZE + AUTHKEY_SIZE;
	memcpy(sendBuff, lenBox.cType, LENBOX_SIZE);
	totalLen = lenBox.iType + LENBOX_SIZE;

	// Copy Operating Message
	memcpy(sendBuff + LENBOX_SIZE, "access0000", OP_MSG_SIZE);

	// Copy MAC Address 
	memset(tmp, 0, sizeof(tmp));
	wcstombs_s(NULL, tmp, GetMACAddress().GetLength() + 1, GetMACAddress(), _TRUNCATE);
	memcpy(sendBuff + LENBOX_SIZE + OP_MSG_SIZE, tmp, MAC_ADDR_SIZE);

	// Copy Current Version
	memset(tmp, 0, sizeof(tmp));
	wcstombs_s(NULL, tmp, authKey.GetLength() + 1, authKey, _TRUNCATE);
	memcpy(sendBuff + LENBOX_SIZE + OP_MSG_SIZE + MAC_ADDR_SIZE, tmp, AUTHKEY_SIZE);

	// ***************** Send request dll file download to server *****************
	do{
		ret = sock.Send(sendBuff, lenBox.iType + 4);	//send to server
		currentLen += ret;
		CJSLogger::Logger('d', "[%d]Send to server [%d/%dbytes]", loopCnt, currentLen, totalLen, sendBuff);
	} while (currentLen < totalLen);

	sock.Close();

	ret = GetLastError();

	return ret;
}

CString CUtil::GetMACAddress()
{
	CString strGateWay = _T("");
	CString strMACAddress = _T("");
	IP_ADAPTER_INFO ipAdapterInfo[5];
	DWORD dwBuflen = sizeof(ipAdapterInfo);

	DWORD dwStatus = GetAdaptersInfo(ipAdapterInfo, &dwBuflen);
	if (dwStatus != ERROR_SUCCESS)
	{
		strMACAddress.Format(_T("Error for GetAdaptersInfo : %d"), dwStatus);
		AfxMessageBox(strMACAddress);
		return _T("");
	}
	PIP_ADAPTER_INFO pIpAdapterInfo = ipAdapterInfo;
	do{
		strGateWay = (CString)pIpAdapterInfo->GatewayList.IpAddress.String;
		if (strGateWay[0] == '0')
		{
			pIpAdapterInfo = pIpAdapterInfo->Next;
		}
		else
		{
			strMACAddress.Format(_T("%02X-%02X-%02X-%02X-%02X-%02X"),
				pIpAdapterInfo->Address[0],
				pIpAdapterInfo->Address[1],
				pIpAdapterInfo->Address[2],
				pIpAdapterInfo->Address[3],
				pIpAdapterInfo->Address[4],
				pIpAdapterInfo->Address[5]
				);

			break;
		}
	} while (pIpAdapterInfo);

	return strMACAddress;
}

void hex2char(unsigned char c, unsigned char &hex1, unsigned char &hex2) {
	hex1 = c / 16;
	hex2 = c % 16;
	hex1 += hex1 <= 9 ? '0' : 'a' - 10;
	hex2 += hex2 <= 9 ? '0' : 'a' - 10;
}

std::string CUtil::urlencodeeng(std::string s) {
	const char *str = s.c_str();
	std::vector<char> v(s.size());
	v.clear();
	for (size_t i = 0, l = s.size(); i < l; i++)
	{
		char c = str[i];
		if ((c >= '0' && c <= '9') ||
			(c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			c == '-' || c == '_' || c == '.' || c == '!' || c == '~' ||
			c == '*' || c == '\'' || c == '(' || c == ')')
		{
			v.push_back(c);
		}
		else if (c == ' ')
		{
			v.push_back('+');
		}
		else
		{
			v.push_back('%');
			unsigned char d1, d2;
			hex2char(c, d1, d2);
			v.push_back(d1);
			v.push_back(d2);
		}
	}

	return std::string(v.cbegin(), v.cend());
}

std::string CUtil::urldecodeeng(std::string s){
	const char *str = s.c_str();
	std::vector<char> v(s.size());
	v.clear();

	int i, j;

	if (!s[0]) return NULL;

	for (size_t i = 0, l = s.size(); i < l; i)
	{
		char c = str[i];
		if (c == '+') {
			c = ' ';
		}
		else if (c == '%') {
			unsigned char d1, d2;
			hex2char(c, d1, d2);
			v.push_back(d1);
			v.push_back(d2);
			i += 2;
		}else{
			v.push_back(c);
		}
	}

	return str;
}

CString CUtil::SpecialCharacterUrlEncode(wchar_t *source) {
	int loopCnt = 0;
	CString result = L"";

	try {
		while (*source != '\0')
		{
			if (0xAC00 > *source || 0xD7A3 < *source || isalnum(*source))
			{
				std::string temp;
				temp = *source;
				temp = urlencodeeng(temp);
				result.AppendFormat(L"%s", temp);
			}
			else {
				result.AppendFormat(L"%c", *source);
			}
			source++;
		}
	}
	catch (...) {
		CJSLogger::Logger('e', "SpecialCharacterUrlEncode(error %d).", GetLastError());
		return NULL;
	}
	
	return result;
}


int CUtil::ReplaceSpecialCharacter(CString* source) {
	try {
		source->Replace(L"\'", L"\\\'");
		source->Replace(L"\"", L"\\\"");
	}
	catch (...) {
		CJSLogger::Logger('e', "SpecialCharacterUrlEncode(error %d).", GetLastError());
		return -1;
	}

	return 0;
}


int CUtil::GetInitialFromHangeul(wchar_t *source, CString *result, int initialCnt)
{
	int loopCnt = 0;

	//초성 
	static const wchar_t wcKHead[] = { L'ㄱ', L'ㄲ', L'ㄴ', L'ㄷ',
		L'ㄸ', L'ㄹ', L'ㅁ', L'ㅂ',
		L'ㅃ', L'ㅅ', L'ㅆ', L'ㅇ',
		L'ㅈ', L'ㅉ', L'ㅊ', L'ㅋ',
		L'ㅌ', L'ㅍ', L'ㅎ' };

	static const CString wcHead[] = { L"G", L"GG", L"N", L"D",
		L"DD", L"R", L"M", L"B",
		L"BB", L"S", L"SS", L"O",
		L"J", L"JJ", L"CH", L"K",
		L"T", L"P", L"H" };

	UINT    pos = 0;

	while (*source != '\0' && loopCnt < initialCnt)
	{
		if (0xAC00 > *source || 0xD7A3 < *source)
		{
			if(isalnum(*source))
				result->AppendFormat(L"%c", *source);
		}
		else
		{
			if (wcHead[(*source - 0xAC00) / (21 * 28)].Compare(L" ")) {
				result->AppendFormat(L"%s", wcHead[(*source - 0xAC00) / (21 * 28)]);
			}
			loopCnt++;
		}
		source++;
	}

	return result->GetLength();
}

int CUtil::han2eng(wchar_t *source, CString *result, UINT resultBufferSize)
{
	int loopCnt = 0;
	//초성 
	static const wchar_t wcKHead[] = { L'ㄱ', L'ㄲ', L'ㄴ', L'ㄷ',
		L'ㄸ', L'ㄹ', L'ㅁ', L'ㅂ',
		L'ㅃ', L'ㅅ', L'ㅆ', L'ㅇ',
		L'ㅈ', L'ㅉ', L'ㅊ', L'ㅋ',
		L'ㅌ', L'ㅍ', L'ㅎ' };

	static const CString wcHead[] = { L"g", L"gg", L"n", L"d",
		L"dd", L"r", L"m", L"b",
		L"bb", L"s", L"ss", L" ",
		L"j", L"jj", L"ch", L"k",
		L"t", L"p", L"h" };

	//중성 
	static const wchar_t wcKMid[] = { L'ㅏ', L'ㅐ', L'ㅑ', L'ㅒ',
		L'ㅓ', L'ㅔ', L'ㅕ', L'ㅖ',
		L'ㅗ', L'ㅘ', L'ㅙ', L'ㅚ',
		L'ㅛ', L'ㅜ', L'ㅝ', L'ㅞ',
		L'ㅟ', L'ㅠ', L'ㅡ', L'ㅢ', L'ㅣ' };

	static const CString wcMid[] = { L"a", L"ae", L"ya", L"yae",
		L"eo", L"e", L"yeo", L"ye",
		L"o", L"wa", L"wae", L"oe",
		L"yo", L"u", L"wo", L"we",
		L"wi", L"yu", L"eu", L"ui", L"i" };

	//종성
	static const wchar_t wcKTail[] = { L' ', L'ㄱ', L'ㄲ', L'ㄳ',
		L'ㄴ', L'ㄵ', L'ㄶ', L'ㄷ',
		L'ㄹ', L'ㄺ', L'ㄻ', L'ㄼ',
		L'ㄽ', L'ㄾ', L'ㄿ', L'ㅀ',
		L'ㅁ', L'ㅂ', L'ㅄ', L'ㅅ',
		L'ㅆ', L'ㅇ', L'ㅈ', L'ㅊ',
		L'ㅋ', L'ㅌ', L'ㅍ', L'ㅎ' };

	static const CString wcTail[] = { L" ", L"k", L"k", L"k",
		L"n", L"n", L"n", L"t",
		L"l", L"l", L"l", L"l",
		L"l", L"l", L"p", L"l",
		L"m", L"p", L"p", L"t",
		L"t", L"ng", L"t", L"t",
		L"k", L"t", L"p", L"k" };

	UINT    pos = 0;

	while (*source != '\0' && loopCnt < resultBufferSize)
	{
		if (*source < 256)
		{
			//if (pos + 2 >= resultBufferSize - 1)
			//	break;

			result->AppendFormat(L"%c", *source);
		}
		else
		{
			//if (pos + 4 >= resultBufferSize - 1)
			//	break;

			if (wcHead[(*source - 0xAC00) / (21 * 28)].Compare(L" ")) {
				result->AppendFormat(L"%s", wcHead[(*source - 0xAC00) / (21 * 28)]);
				//result->append(wcHead[(*source - 0xAC00) / (21 * 28)]);
				loopCnt++;
			}

			result->AppendFormat(L"%s", wcMid[(*source - 0xAC00) % (21 * 28) / 28]);
			loopCnt++;
			//result->append(wcMid[(*source - 0xAC00) % (21 * 28) / 28]);

			if (wcTail[(*source - 0xAC00) % 28].Compare(L" ")) {
				result->AppendFormat(L"%s", wcTail[(*source - 0xAC00) % 28]);
				loopCnt++;
				//result->append(wcTail[(*source - 0xAC00) % 28]);
			}
		}

		++source;
	}

	//result[pos] = '\0';
	result += '\0';
	return pos;
}
