#ifndef CONF_H
#define CONF_H

#include "BaseConfig.h"


enum StrParams
{
	STR_LOGFILE,
	STR_SMTP_HOST,
	STR_FROM,
	STR_REAL_FROM,
	STR_REPLY_TO,

	STR_PARAM_MAX
};

enum IntParams
{
	INT_LOG_DEBUG,
	INT_SMTP_PORT,
	INT_IS_CONSTLOG,
    INT_SEND_DELAY,

	INT_PARAM_MAX
};

class Config : public BaseConfig
{
public:
	Config(std::string cfg_file);
	~Config(void);

	void Reload();

	uint32 Rand(uint32 start,uint32 end);

	std::string StrValue[STR_PARAM_MAX];
	int32 IntValue[INT_PARAM_MAX];
};

extern Config sConf;

#endif