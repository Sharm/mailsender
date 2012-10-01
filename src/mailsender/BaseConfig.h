#pragma once
#include <fstream> 
#include <stdio.h>
#include <string>
#ifndef _WIN32
    #include <stdlib.h>
#endif
#include "Define.h"

#define MAX_SIZE 256
#define REVISION 1
#define VERSION_FULL 100801

struct StrParamTable
{
	std::string name;
	std::string value;
};

struct IntParamTable
{
	std::string name;
	int64 value;
};

class BaseConfig
{
public:

	BaseConfig(std::string cfg_file);
	~BaseConfig(void);

	std::string GetStrValue(std::string name, std::string def);
	void GetStrValue(StrParamTable& param){ param.value = GetStrValue(param.name,param.value); }
	int64 GetIntValue(std::string name, int64 def);
	void GetIntValue(IntParamTable& param){ param.value = GetIntValue(param.name,param.value); }
	void SetStrValue(std::string name, std::string value);
	void SetStrValue(StrParamTable param) { SetStrValue(param.name, param.value); }
	void SetIntValue(std::string name, int64 value);
	void SetIntValue(IntParamTable param) { SetIntValue(param.name, param.value); }

	uint32 GetIntVersion(){return m_ver;}
	std::string GetStrVersion();
	uint32 GetRevision(){return REVISION;}

private:
	bool isOpen;
	std::ifstream f;
	std::string m_cfg_file;
	uint32 m_ver;
	

};
