#include "Log.h"

Log::Log(const char* FName, bool isConstLog)
:BaseLog(FName, isConstLog)
{
	m_debug = sConf.IntValue[INT_LOG_DEBUG];

	printf("Log system loaded!\n");
}

Log::~Log()
{
}
