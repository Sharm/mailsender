
#include "ClientHandler.h"
#include "Parse.h"
#include <utility> // make_pair
#include "ClientSocket.h"
#include "Utility.h"




ClientHandler::ClientHandler(std::string list, std::string html, std::string subj) : SocketHandler()
,m_error("Not ready")
,m_subj(subj)
{
	EnableRelease();

	/* Prepare private vars */
	/************************/
	f_bad_mails.open("bad_emails.txt");
	f_ok_mails.open("send_emails.txt");



	uint32 fsize;
	/* Prepare to sending  */
	/***********************/
	sLog.outString("1 -> Getting text/html template...");
	std::ifstream f;
	//f.open("list/test.txt");
	f.open(html.c_str());
	if (!f.good()){
		sLog.outError("Can't open '%s'",html.c_str());
		m_error = sLog.GetLastStr();
		goto exit;
	}
	f.seekg (0, std::ios::end);
	fsize = f.tellg();
	f.seekg (0, std::ios::beg);
	{
		char buf[20000];
		f.read(buf,fsize);
		buf[fsize] = 0;
		f.close();
		f.clear();
		m_html = buf;
	}
	sLog.outString("1 -> Ok");

	sLog.outString("2 -> Getting recipients list...");
	f.open(list.c_str());
	if (!f.good()){
		sLog.outError("Can't open '%s'",list.c_str());
		m_error = sLog.GetLastStr();
		goto exit;
	}
	char buf[2000];
	while (f.getline(buf,2000)){
		std::string line = buf;
		Parse pa(line);
		std::string email = pa.getword();
		sLog.outDebug("2 -> Added email '%s'",email.c_str());
		StringVector arg_v;
		std::string arg;
		while ( !(arg = pa.getword()).empty() )
			arg_v.push_back(arg);
		m_list.insert(make_pair(email, arg_v));
	}
	f.close();
	sLog.outString("2 -> Ok");

	sLog.outString("Ready for sending!");
	m_error = "";

exit:;
}

ClientHandler::~ClientHandler()
{
	f_bad_mails.flush();
	f_bad_mails.close();
	f_ok_mails.flush();
	f_ok_mails.close();
}

void PrepareHtml(std::string* html, StringVector arg)
{
	sLog.outDebug(" -> Prepare html/text");
	
	std::string result = "";
	std::string index;
	Parse pa(*html,"{}",1);
	result = pa.getword();

	while ( !(index = pa.getword()).empty()){
		uint32 ind = atoi(index.c_str());
		if (arg.size() > ind)
			result += arg[ind];
		result += pa.getword();
	}
	*html = result;
}

void ClientHandler::BeginSend()
{
	sLog.outString("Start sending...");
    for(MailMap::const_iterator it = m_list.begin(); it != m_list.end(); ++it)
    {
		sLog.outDebug("%s",it->first.c_str());
		std::string html = m_html;
		PrepareHtml(&html,it->second);
		

		ClientSocket* ClientS = new ClientSocket(*this,it->first,html,m_subj);
		ClientS->Open(sConf.StrValue[STR_SMTP_HOST],sConf.IntValue[INT_SMTP_PORT]);
		
		// Add after Open
		Add(ClientS);
		while (ClientS->Connecting())
			Select(1,0);

		if (!ClientS->IsConnected()){
			sLog.outError("Can't connect to SMTP server: %s:%d",sConf.StrValue[STR_SMTP_HOST].c_str(),sConf.IntValue[INT_SMTP_PORT]);
			m_error = sLog.GetLastStr();
			return;
		}

		sLog.outDebug(" -> Sending");

		while (ClientS->Ready())
			Select(5,0);

		sLog.outDebug(" -> Done");

		delete ClientS;
		Utility::Sleep(1000);
	}
	
	m_error = "";
}