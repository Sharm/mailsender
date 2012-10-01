#ifndef LOG_H
#define LOG_H

#include "BaseLog.h"
#include "Config.h"
#ifndef _WIN32
    #include <stdarg.h>
#endif

class Log : public BaseLog
{
public:
	Log(const char* FName, bool isConstLog);
	~Log();

};

extern Log sLog;

#endif