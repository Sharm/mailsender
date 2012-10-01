
#include "BaseConfig.h"
#include "assert.h"
#include <string.h>

BaseConfig::BaseConfig(std::string cfg_file)
{
	m_ver = VERSION_FULL;
	isOpen = false;
	m_cfg_file = cfg_file;
	f.open(cfg_file.c_str());
	if (!f){
		printf("Cant open cfg file!\n");
		exit(-1);
	}
	assert(f);
	f.close();
	isOpen = true;
}

BaseConfig::~BaseConfig(void)
{
}

std::string BaseConfig::GetStrValue(std::string name, std::string def)
{
	if (!isOpen)
		return def;

	std::string tmp;
	char buf[MAX_SIZE];
	uint32 max = 0;
	uint32 length = 0;

	f.open(m_cfg_file.c_str());
	f.seekg(std::ios::beg);
	name += " =";
	while ( f.getline(buf,MAX_SIZE) )
	{
		tmp = buf;
		max = tmp.find("#");
		if (max != std::string::npos){
			length = tmp.copy(buf,max,0);
			buf[length]='\0';
			tmp = buf;
		}
		if (tmp.find(name) != std::string::npos){	//Если нашли нужный параметр
				length = tmp.copy(buf,MAX_SIZE - tmp.find("=") - 1, tmp.find("=")+1);
				buf[length]='\0';
				tmp = buf;
				for (std::string::iterator itr = tmp.begin(); itr < tmp.end(); /*itr++*/)
				{
					if (*itr == ' ')
						tmp.erase(itr);
					else
						break;
				}
				f.close();
				return tmp;
		}
    }
	f.close();
	return def;
}

void BaseConfig::SetStrValue(std::string name, std::string value)
{
	if (!isOpen)
		return;

	std::string tmp;
	char buf[MAX_SIZE];
	char realbuf[MAX_SIZE];
	uint32 max = 0;
	uint32 length = 0;
	bool isNew = true;

	std::string fout_name = "config.conf.tmp";
	std::ofstream fout;
	fout.open(fout_name.c_str());
	f.open(m_cfg_file.c_str());
	f.seekg(std::ios::beg);
	name += " =";
	while ( f.getline(realbuf,MAX_SIZE) )
	{
		strcpy(buf,realbuf);
		tmp = buf;
		max = tmp.find("#");
		if (max != std::string::npos){
			length = tmp.copy(buf,max,0);
			buf[length]='\0';
			tmp = buf;
		}
		if (tmp.find(name) != std::string::npos){	//Если нашли нужный параметр
			fout << name.c_str() << " " << value.c_str() << std::endl;
			isNew = false;
		}else{
			fout << realbuf << std::endl;
		}

	}
	if (isNew)
		fout << name.c_str() << " " << value.c_str() << std::endl;

	fout.flush();
	fout.close();
	f.close();
	remove("config.conf.old");
	rename(m_cfg_file.c_str(),"config.conf.old");
	rename(fout_name.c_str(),m_cfg_file.c_str());
}

int64 BaseConfig::GetIntValue(std::string name, int64 def)
{
	std::string tmp;
	char* buf = new char[MAX_SIZE];
	sprintf(buf, "%Ld", def);
	tmp = buf;
	delete[] buf;

	return atoi(GetStrValue(name,tmp).c_str());
}

void BaseConfig::SetIntValue(std::string name, int64 value)
{
	char buf[MAX_SIZE];
	sprintf(buf, "%Ld", value);
	SetStrValue(name,buf);
}

std::string BaseConfig::GetStrVersion()
{
	std::string res;
	char	tmp[25], //uint32 size?
			restmp[9];
	sprintf(tmp,"%d",m_ver);
	sprintf(restmp,"%c%c.%c%c.%c%c",tmp[0],tmp[1],(tmp[2] == '0' ? ' ':tmp[2]),tmp[3],(tmp[4] == '0' ? ' ':tmp[4]),tmp[5]);
	res = restmp;
	for (std::string::iterator itr = res.begin(); itr != res.end(); )
	{
		if (*itr == ' ')
			res.erase(itr);
		else
			itr++;
	}
	return res;
}
