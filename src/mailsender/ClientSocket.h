#pragma once

#include <TcpSocket.h>
#include "Define.h"
#include "Config.h"






class ClientSocket : public TcpSocket
{
public:
	ClientSocket(ISocketHandler& h, std::string email, std::string html, std::string subj);
	~ClientSocket();

	void OnConnect();
	void OnDelete();
	void OnLine(const std::string& line);



private:
	bool m_isDataSend;
	std::string m_email;
	std::string m_html;
	std::string m_subj;

};

