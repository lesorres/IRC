#include "Server.hpp"

#define ERR_NOSUCHSERVER 402 			//" :No such server\n"		
#define ERR_NOSUCHCHANNEL 403 			//":No such channel\n"		
#define ERR_NOMOTD 422 					//":MOTD File is missing"			
#define ERR_NONICKNAMEGIVEN 431			//":No nickname given\n"	
#define ERR_ERRONEUSNICKNAME 432 		//":Erroneus nickname\n"
#define ERR_NICKNAMEINUSE 433 			//":Nickname is already in use\n"	
#define ERR_NICKCOLLISION 436 			//"<nick> :Nickname collision KILL\n"
#define ERR_NOTONCHANNEL 442			//":You're not on that channel\n"	
#define ERR_NOTREGISTERED 451			//":You have not registered\n"		
#define ERR_NEEDMOREPARAMS 461			//":Not enough parameters\n"		
#define ERR_ALREADYREGISTRED 462		//":You may not reregister\n"	
#define ERR_PASSWDMISMATCH 464			//":Password incorrect\n"			
#define ERR_KEYSET 467					//":Channel key already set\n"				
#define ERR_UNKNOWNMODE 472				//":is unknown mode char to me\n"		
#define ERR_NOPRIVILEGES 481			//":Permission Denied- You're not an IRC operator"
#define ERR_CHANOPRIVSNEEDED 482		//":You're not channel operator\n"	
#define ERR_NOOPERHOST 491				//":No O-lines for your host\n"			
#define ERR_USERSDONTMATCH 502			//":Cant change mode for other users\n"

int Server::errorMEss(int err, User &user, const std::string &str) {
	std::string messg;
	switch (err) {
	case 402:
		messg = msg.midParams[0] + " :No such server\n";
		break ;
	case 403:
		messg = str + " " + ":No such channel\n";
		break;
	case 422:
		messg = ":MOTD File is missing\n";
		break ;
	case 431:
		messg = ":No nickname given\n";
		break ;
	case 432:
		messg = user.getNick() + " :Erroneus nickname\n";
		break ;
	case 433:
		messg = user.getNick() + " :Nickname is already in use\n";
		break ;
	case 436:
		messg = user.getNick() +  " :Nickname collision KILL\n";
		break ;
	case 442:
		messg = str + " :You're not on that channel\n";
		break;
	case 451:
		messg = ":You have not registered\n";
		break ;
	case 461:
		messg = msg.cmd + " :Not enough parameters\n";
		break ;
	case 462:
		messg = ":You may not reregister\n";
		break ;
	case 464:
		messg = ":Password incorrect\n";
		break ;
	case 467:
		messg = str + " " + ":Channel key already set\n";
		break ;
	case 472:
		messg = str + " :is unknown mode char to me\n";
		break ;
	case 481:
		messg = " :Permission Denied- You're not an IRC operator";
		break ;
	case 482:
		messg = str + " :You're not channel operator\n";
		break ;
	case 491:
		messg = ":No O-lines for your host\n";
		break ;
	case 502:
		messg = ":Cant change mode for other users\n";
		break ;
	default:
		messg = "Something wrong\n";
	}
	send(user.getFd(), messg.c_str(), messg.size(), 0);
	std::cout << "\e[31mSend error to " << user.getNick() << "< socket " << user.getFd() << " >:\e[0m " << messg;
	return 1;
}