#include "stdafx.h"
#include "JSLogger.h"
#include <cstdio>
#include <fstream>

CJSLogger::CJSLogger()
{
}


CJSLogger::~CJSLogger()
{
}

CString CJSLogger::getCurrentPath(){
	TCHAR path[200];
	CString strPath;
	int i = 0;
	GetModuleFileName(NULL, path, sizeof path);
	PathRemoveFileSpec(path);
	strPath = (LPCTSTR)path;
	return strPath;
}

CRITICAL_SECTION CJSLogger::l_cs;
char CJSLogger::logMode;

void CJSLogger::Logger(char mode, const char * format, ...){
	char  buffer[5000];
	char writeBuffer[100];
	CString filepath;
	va_list args;
	CFile cfile;
	

	memset(buffer, 0, 5000);
	memset(writeBuffer, 0, 100);
	//memset(filepath, 0, 1000);

	switch (CJSLogger::logMode){
	case 'e':
		if (mode == 'w' || mode == 'i' || mode == 'd')
			return;
		break;
	case 'w':
		if (mode == 'i' || mode == 'd')
			return;
		break;
	case 'i':
		if (mode == 'd')
			return;
		break;
	case 'd':
		break;
	default:
		return;
	}

	// Set log String
	va_start(args, format);
	vsprintf_s(buffer, format, args);
	//c_buffer.FormatV(format, args);
	va_end(args);

	CTime cTime = CTime::GetCurrentTime(); // 현재 시스템으로부터 날짜 및 시간을 얻어 온다.

	switch (mode){
	case 'e':
		sprintf_s(writeBuffer, "ERROR   %04d-%02d-%02d %02d:%02d:%02d ", cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
		break;
	case 'w':
		sprintf_s(writeBuffer, "WARNING %04d-%02d-%02d %02d:%02d:%02d ", cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
		break;
	case 'i':
		sprintf_s(writeBuffer, "INFO    %04d-%02d-%02d %02d:%02d:%02d ", cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
		break;
	case 'd':
		sprintf_s(writeBuffer, "DEBUG   %04d-%02d-%02d %02d:%02d:%02d ", cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
		break;
	default:
		break;
	}

	// Create Directory
	filepath.Format(L"%s/logs/", getCurrentPath());
	CreateDirectory(filepath, NULL);
	filepath.AppendFormat(L"%04d/", cTime.GetYear());
	CreateDirectory(filepath, NULL);
	filepath.AppendFormat(L"%02d/", cTime.GetMonth());
	CreateDirectory(filepath, NULL);

	// Set File path
	filepath.AppendFormat(L"o2md_%04d%02d%02d.log", cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());

	// Init Critical Section
	if (l_cs.DebugInfo == NULL)
		InitializeCriticalSection(&l_cs);

	::EnterCriticalSection(&l_cs);
	try{
		cfile.Open(filepath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
		cfile.SeekToEnd();
		cfile.Write(writeBuffer, strlen(writeBuffer));
		cfile.Write(buffer, strlen(buffer));
		cfile.Write("\n", 1);
		cfile.Flush();
		cfile.Close();
	}
	catch (CFileException* e){
		e->ReportError();
		e->Delete();
	}
	::LeaveCriticalSection(&l_cs);
}

void CJSLogger::setLogMode(char logMode){
	CJSLogger::logMode = logMode;
}