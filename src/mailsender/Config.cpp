
#include "Config.h"
#include "time.h"

Config::Config(std::string cfg_file)
:BaseConfig(cfg_file)
{
	srand(time(NULL));
	Reload();
}

Config::~Config(void)
{
}

void Config::Reload()
{
	StrValue[STR_LOGFILE] = GetStrValue("LogFile","Log.log");
	StrValue[STR_SMTP_HOST] = GetStrValue("SMTP Host","");
	StrValue[STR_REAL_FROM] = GetStrValue("Mail Real From","");
	StrValue[STR_FROM] = GetStrValue("Mail From","");
	StrValue[STR_REPLY_TO] = GetStrValue("Mail Reply-to","");
	
	

	IntValue[INT_LOG_DEBUG] = GetIntValue("LogDebug",0);
	IntValue[INT_SMTP_PORT] = GetIntValue("SMTP Port",0);
	IntValue[INT_IS_CONSTLOG] = GetIntValue("Const LogFile",0);
	
	
	
	printf("Configuration successfuly loaded!\n");
}

uint32 Config::Rand(uint32 start,uint32 end)
{
	return rand() %(end-start+1) + start;
}