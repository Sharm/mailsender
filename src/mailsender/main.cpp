
#include "ClientSocket.h"
#include "Utility.h"
#include "Config.h"
#include "Log.h"
#include "ClientHandler.h"


Config sConf("cfg/mail.conf");
Log sLog(sConf.StrValue[STR_LOGFILE].c_str(),sConf.IntValue[INT_IS_CONSTLOG]); 

uint32 m_quit = 0;
int main(int argc,char *argv[])
{
	sLog.outString("\n############# \n Start work \n#############");

	if (argc < 4){
		sLog.outError("Bad arguments!");
		Utility::Sleep(1000);
		return 0;
	}

	std::string subj = argv[3];
	if (argc > 4)
		for (uint32 i = 4; i < argc; i++){
			subj += " ";
			subj += argv[i];
		}

	ClientHandler h(argv[1],argv[2],subj);

	if (!h.isReady())
		return 0;

	h.BeginSend();

	if (h.error().empty())
		sLog.outString("\n############# \n Finish succesfully \n#############\n\n");

	return 0;
}