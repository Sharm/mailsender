
#include "ClientSocket.h"
#include "ClientHandler.h"
#include "Parse.h"
#include "Utility.h"
#include <iostream> 
#include <sstream> 




ClientSocket::ClientSocket(ISocketHandler& h, std::string email, std::string html, std::string subj)
:TcpSocket(h)
,m_isDataSend(false)
,m_email(email)
,m_html(html)
,m_subj(subj)
{
	SetLineProtocol();
}

ClientSocket::~ClientSocket()
{
}

void ClientSocket::OnConnect()
{
	
}

void ClientSocket::OnDelete()
{

}

void ClientSocket::OnLine(const std::string& line)
{
	Parse pa(line," ");
	uint32 num = pa.getvalue();

	switch (num){
		case 220:
			{
				std::stringstream buf;
				buf << "HELO " << sConf.StrValue[STR_SMTP_HOST].c_str() << "\r\n";
				Send(buf.str());
				break;
			}
		case 250:
			{
				std::string cmd = Utility::ToUpper(pa.getword());

				if (!strcasecmp(cmd.c_str(),"OK") && m_isDataSend){ // 5
					Send("QUIT\r\n");
					SetCloseAndDelete();
					static_cast<ClientHandler&>(Handler()).Release();
					static_cast<ClientHandler&>(Handler()).OkEmail(m_email);
				}

				else
				if (!strcasecmp(cmd.c_str(),"Accepted")) // 3
					Send("DATA\r\n");

				else
				if (!strcasecmp(cmd.c_str(),"OK") && !m_isDataSend){ // 2
					std::stringstream buf;
					buf << "RCPT TO:<" << m_email.c_str() << ">\r\n";
					Send(buf.str());
				}

				else{ // 1 в cmd - каша
					std::stringstream buf;
					buf << "MAIL FROM:<" << sConf.StrValue[STR_REAL_FROM].c_str() << ">\r\n";
					Send(buf.str());
				}

				break;
			}
		case 354:  // 4
			{
				std::stringstream buf;
				buf << "Precedence: bulk\r\n";
				buf << "X-Mailer: SharmMailer\r\n";
				buf << "To: " << m_email.c_str() << "\r\n";
				buf << "From: " << sConf.StrValue[STR_FROM].c_str() << "\r\n";
				buf << "Reply-To: " << sConf.StrValue[STR_REPLY_TO].c_str() << "\r\n";
				buf << "Subject: " << m_subj.c_str() <<"\r\n";
				buf << "Content-Type: text/html;\r\n";
				buf << m_html.c_str() << "\r\n.\r\n";


				Send(buf.str());
				
				m_isDataSend = true;
				break;
			}
		case 550: // 3 if email incorrect
		case 451:
		case 501:
			{
				Send("QUIT\r\n");
				SetCloseAndDelete();
				static_cast<ClientHandler&>(Handler()).Release();
				static_cast<ClientHandler&>(Handler()).BadEmail(m_email);
				break;
			}
		default:
			{
				sLog.outError("Unsupported command!");
				Send("QUIT\r\n");
				SetCloseAndDelete();
				static_cast<ClientHandler&>(Handler()).Release();
				break;
			}
	}


}