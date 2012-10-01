#ifndef BASELOG_H
#define BASELOG_H

#include "Define.h"
#include <wchar.h>
#include <stdio.h>
#include <time.h>
#include <string>
#ifdef _WIN32
	#include <windows.h>
	#include <WinDef.h>
	#include <WinCon.h>
#else
	#include <stdarg.h>
#endif

enum Color
{
    BLACK,
    RED,
    GREEN,
    BROWN,
    BLUE,
    MAGENTA,
    CYAN,
    GREY,
    YELLOW,
    LRED,
    LGREEN,
    LBLUE,
    LMAGENTA,
    LCYAN,
    WHITE,
	COLOR_COUNT
};

class BaseLog
{
public:
	BaseLog(const char* FName, bool isConstLog);
	~BaseLog()
    {
        if( logfile != NULL )
            fclose(logfile);
        logfile = NULL;
    }


	void outString( const char * str, ... );
    void outDebug( const char * str, ... );
	void outError( const char * str, ... );
	void outTime(FILE* out);
	void outDate(FILE* out);

	std::string GetLastStr(){return m_laststr;}

private:
	FILE* logfile;
	Color m_color;
	std::string m_laststr;

protected:
	bool m_debug;

	void outString( const char * str, FILE* f );
	void SetColor(Color color);
};


#endif //LOG_H

