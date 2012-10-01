#pragma once


#include "Define.h"
#include <SocketHandler.h>
#include <fstream> 
#include "Log.h"



#ifdef USE_SOLID_MAX
#define MAX_MINIONS 10
#endif


class ClientHandler : public SocketHandler
{
public:
	ClientHandler(std::string list, std::string html, std::string subj);
	~ClientHandler();

	//Ready for sending
	bool isReady(){return m_error.empty();}
	std::string error(){return m_error;}

	//Main func that begin sending
	void BeginSend();

	void BadEmail(std::string email){ f_bad_mails << email.c_str() << "\n";}
	void OkEmail(std::string email){ f_ok_mails << email.c_str() << "\n";}
	

private:
	MailMap m_list;
	std::string m_html;
	std::string m_error;
	std::string m_subj;
	std::ofstream f_bad_mails;
	std::ofstream f_ok_mails;

};
