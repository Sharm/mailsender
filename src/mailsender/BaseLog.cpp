#include "BaseLog.h"

BaseLog::BaseLog(const char* FName, bool isConstLog) : 
	logfile(NULL), m_color(WHITE)
	
{
	if (isConstLog)
		logfile = fopen(FName,"a");
	else
		logfile = fopen(FName,"w");
	if (!logfile)
		printf("ERROR: Log file open fail!");
}

void BaseLog::SetColor(Color color)
{
#ifdef _WIN32
    static WORD WinColorFG[COLOR_COUNT] =
    {
        0,                                                  // BLACK
        FOREGROUND_RED,                                     // RED
        FOREGROUND_GREEN,                                   // GREEN
        FOREGROUND_RED | FOREGROUND_GREEN,                  // BROWN
        FOREGROUND_BLUE,                                    // BLUE
        FOREGROUND_RED |                    FOREGROUND_BLUE,// MAGENTA
        FOREGROUND_GREEN | FOREGROUND_BLUE,                 // CYAN
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,// WHITE
                                                            // YELLOW
        FOREGROUND_RED | FOREGROUND_GREEN |                   FOREGROUND_INTENSITY,
                                                            // RED_BOLD
        FOREGROUND_RED |                                      FOREGROUND_INTENSITY,
                                                            // GREEN_BOLD
        FOREGROUND_GREEN |                   FOREGROUND_INTENSITY,
        FOREGROUND_BLUE | FOREGROUND_INTENSITY,             // BLUE_BOLD
                                                            // MAGENTA_BOLD
        FOREGROUND_RED |                    FOREGROUND_BLUE | FOREGROUND_INTENSITY,
                                                            // CYAN_BOLD
        FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
                                                            // WHITE_BOLD
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
    };

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, WinColorFG[color]);
    #else

    enum ANSITextAttr
    {
        TA_NORMAL=0,
        TA_BOLD=1,
        TA_BLINK=5,
        TA_REVERSE=7
    };

    enum ANSIFgTextAttr
    {
        FG_BLACK=30, FG_RED,  FG_GREEN, FG_BROWN, FG_BLUE,
        FG_MAGENTA,  FG_CYAN, FG_WHITE, FG_YELLOW
    };

    enum ANSIBgTextAttr
    {
        BG_BLACK=40, BG_RED,  BG_GREEN, BG_BROWN, BG_BLUE,
        BG_MAGENTA,  BG_CYAN, BG_WHITE
    };

    static uint8 UnixColorFG[COLOR_COUNT] =
    {
        FG_BLACK,                                           // BLACK
        FG_RED,                                             // RED
        FG_GREEN,                                           // GREEN
        FG_BROWN,                                           // BROWN
        FG_BLUE,                                            // BLUE
        FG_MAGENTA,                                         // MAGENTA
        FG_CYAN,                                            // CYAN
        FG_WHITE,                                           // WHITE
        FG_YELLOW,                                          // YELLOW
        FG_RED,                                             // LRED
        FG_GREEN,                                           // LGREEN
        FG_BLUE,                                            // LBLUE
        FG_MAGENTA,                                         // LMAGENTA
        FG_CYAN,                                            // LCYAN
        FG_WHITE                                            // LWHITE
    };

    fprintf(stdout , "\x1b[%d%sm",UnixColorFG[color],(color>=YELLOW&&color<COLOR_COUNT ?";1":""));
    #endif

}

void BaseLog::outTime(FILE* out)
{
    time_t t = time(NULL);
    tm* aTm = localtime(&t);
    //       YYYY   year
    //       MM     month (2 digits 01-12)
    //       DD     day (2 digits 01-31)
    //       HH     hour (2 digits 00-23)
    //       MM     minutes (2 digits 00-59)
    //       SS     seconds (2 digits 00-59)
    fprintf(out,"[%02d:%02d:%02d] ",aTm->tm_hour,aTm->tm_min,aTm->tm_sec);
}
void BaseLog::outDate(FILE* out)
{
    time_t t = time(NULL);
    tm* aTm = localtime(&t);
    //       YYYY   year
    //       MM     month (2 digits 01-12)
    //       DD     day (2 digits 01-31)
    //       HH     hour (2 digits 00-23)
    //       MM     minutes (2 digits 00-59)
    //       SS     seconds (2 digits 00-59)
	fprintf(out,"[%02d.%02d.%04d]",aTm->tm_mday,aTm->tm_mon+1,aTm->tm_year+1900);
}
void BaseLog::outString( const char * str, FILE* f )
{
	outTime(stdout);

	printf (str);
    printf ("\n");
	fflush(stdout);

    if(f)
    {
		outDate(f);
		outTime(f);
        fprintf(f, str);
        fprintf(f, "\n");
        fflush(f);
    } 

	m_laststr = str;
}


void BaseLog::outString( const char * str, ... )
{
    if( !str )
        return;

	SetColor(LGREEN);

	char res[256];
    va_list ap;
    va_start(ap, str);
	vsnprintf(res,256,str,ap);
	va_end(ap);
	
	outString(res,logfile);

}

void BaseLog::outDebug( const char * str, ... )
{
    if( !str )
        return;
	if (!m_debug)
		return;

	SetColor(LBLUE);

	char res[256];
    va_list ap;
    va_start(ap, str);
	vsnprintf(res,256,str,ap);
	va_end(ap);
	
	outString(res,logfile);


}

void BaseLog::outError( const char * str, ... )
{
    if( !str )
        return;

	SetColor(LRED);

	char res[256];
    va_list ap;
    va_start(ap, str);
	vsnprintf(res,256,str,ap);
	va_end(ap);
	
	outString(res,logfile);

}
