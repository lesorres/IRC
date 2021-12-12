#include "Server.hpp"

#define RPL_ADMINME " :Admin name - "													// 256
#define RPL_ADMINLOC1 "Location - Kazan, Republic of Tatarstan, Russian Federation\n" 	// 257
#define RPL_ADMINEMAIL ":Admin email - "												// 259
#define RPL_ISON ":"																	// 303
#define RPL_WHOISUSER "<nick> <user> <host> * :<real name>"								// 311
#define RPL_WHOISSERVER "<nick> <server> :<server info>" 								// 312
#define RPL_WHOISOPERATOR " :is an IRC operator\n"										// 313
#define RPL_WHOISIDLE " <integer> :seconds idle\n"										// 317
#define RPL_ENDOFWHOIS " :End of /WHOIS list\n"											// 318
#define RPL_LISTSTART "Channel :Users  Name\n"											// 321
#define RPL_LIST "<channel> <# visible> :<topic>"										// 322
#define RPL_NOTOPIC ":No topic is set\n" 												// 331 
#define RPL_TOPIC "<channel> :<topic>\n"			 									// 332  
#define RPL_VERSION " :RFC 1459  | May 1993\n"											// 351
#define RPL_NAMREPLY "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]" 					// 353
#define RPL_ENDOFNAMES ":End of /NAMES list\n" 											// 366 
#define RPL_INFO ":"																	// 371
#define RPL_MOTD ":- "																	// 372
#define RPL_ENDOFINFO ":End of /INFO list\n"											// 374
#define RPL_MOTDSTART " Message of the day - \n"										// 375
#define RPL_ENDOFMOTD ":End of /MOTD command\n"											// 376
#define RPL_YOUREOPER ":You are now an IRC operator\n"									// 381
#define RPL_REHASHING ":Rehashing"														// 382
#define RPL_TIME " :Local time - "														// 391


#if __APPLE__
	#define IRC_NOSIGNAL SO_NOSIGPIPE
#else
	#define IRC_NOSIGNAL MSG_NOSIGNAL
#endif
            //    - При ответе на MOTD-сообщение и MOTD-файл найден, файл
                //  отбражается строка к строке с каждой строкой, не длше80
                //  символов, используя RPL_MOTD-формат ответов. Их следует
                //  разместить между RPL_MOTDSTART (перед RPL_MOTD) и
                //  RPL_ENDOFMOTD (после).

void Server::replyMEss(int reply, User &user, const std::string &str) {
	std::string mess;
	std::stringstream ss;
	ss << reply;
	mess = ":" + inf.serverName + " " + ss.str() + " " + user.getNick() + " ";
	switch (reply)
	{
	case 256:
		mess += inf.serverName + RPL_ADMINME + inf.adminName + "\n";
		break ;
	case 257:
		mess += RPL_ADMINLOC1;
		break ;
	case 259:
		mess += RPL_ADMINEMAIL + inf.adminEmail + "\n";
		break ;
	case 303:
		mess += RPL_ISON + str + "\n";
		break ;
	case 311:
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
	case 331:
		mess += str + " " + RPL_NOTOPIC;
		break ;
	case 332:
		mess += str + "\n";
		break ;
	case 351:
		mess += inf.srvVersion + ".1 " + inf.serverName + RPL_VERSION;
		break ;
	case 352:	//нужно добавить канал вместо звездочки
		mess += str;
		break ;
	case 353:
		mess += str + "\n";
		break ;
	case 366:
		mess += str + " " + RPL_ENDOFNAMES;
		break ;
	case 371:
		mess += RPL_INFO + str;
		break ;
	case 372:
		mess += RPL_MOTD + str + "\n";
		break ;
	case 374:
		mess += RPL_ENDOFINFO;
		break ;
	case 375:
		mess += ":- " + inf.serverName + RPL_MOTDSTART;
		break ;
	case 376:
		mess += RPL_ENDOFMOTD;
		break ;
	case 381:
		mess += RPL_YOUREOPER;
		break;
	case 382:
		mess += CONF_NAME;
		mess += RPL_REHASHING;
		break ;
	case 391:
		mess += inf.serverName + RPL_TIME + str;
	}
	send(user.getFd(), mess.c_str(), mess.size(), 0);
}