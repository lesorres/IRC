#include "Server.hpp"

#define RPL_YOUREOPER ":You are now an IRC operator\n"			//381
#define RPL_WHOISUSER "<nick> <user> <host> * :<real name>"		//311
#define RPL_WHOISSERVER "<nick> <server> :<server info>" 		//312
#define RPL_WHOISOPERATOR " :is an IRC operator\n"				//313
#define RPL_WHOISIDLE " <integer> :seconds idle\n"				//317
#define RPL_ENDOFWHOIS " :End of /WHOIS list\n"					//318
#define RPL_LISTSTART "Channel :Users  Name\n"					//321
#define RPL_LIST "<channel> <# visible> :<topic>"				//322
#define RPL_MOTD ":- <text>\n"									//372
#define RPL_MOTDSTART ":- <server> Message of the day - \n"		//375
#define RPL_ENDOFMOTD ":End of /MOTD command\n"					//376
#define IRC_NOSIGNAL SO_NOSIGPIPE

            //    - При ответе на MOTD-сообщение и MOTD-файл найден, файл
                //  отбражается строка к строке с каждой строкой, не длше80
                //  символов, используя RPL_MOTD-формат ответов. Их следует
                //  разместить между RPL_MOTDSTART (перед RPL_MOTD) и
                //  RPL_ENDOFMOTD (после).

void Server::replyMEss(int reply, User &user, const std::string &str) {
	std::string mess;
	std::stringstream ss;
	ss << reply;
	mess = ":" + serverName + " " + ss.str() + " " + user.getNick() + " ";
	switch (reply)
	{
	case  311:
		mess += user.getNick() + " " + user.getUser() + " " + user.getHostn() + " " + user.getRealn() + "\n";
		break ;
	case 312:
		mess += user.getNick() + " " + user.getServern() + ":";
		break ;
	case 313:
		mess += user.getNick() + " " + RPL_WHOISOPERATOR;
		break ;
	case 317:
		mess += user.getNick() + RPL_WHOISIDLE;
		break ;
	case 318:
		mess += user.getNick() + RPL_ENDOFWHOIS;
		break ;
	case 321:
		mess = RPL_LISTSTART;
		break ;
	case 322:
		mess = RPL_LIST;
		break ;
	case 352:	//нужно добавить канал вместо звездочки
		mess += str;
		break ;
	case 375:
		mess += str + "\n";
		break ;
	case 372:
		mess += str + "\n";
		break ;
	case 376:
		mess += RPL_ENDOFMOTD;
		break ;
	case 381:
		mess += RPL_YOUREOPER;
		break;
	
	}
	send(user.getFd(), mess.c_str(), mess.size(), IRC_NOSIGNAL);
}