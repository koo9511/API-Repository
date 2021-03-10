#pragma once
#include <string>
class CJSLogger
{
private:
	static CRITICAL_SECTION l_cs;
	static char logMode;
public:
	CJSLogger();
	~CJSLogger();
	
	static void Logger(char mode, const char* format, ...);
	static void setLogMode(char logMode);
	static CString getCurrentPath();
};