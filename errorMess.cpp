#include "Server.hpp"

#define ERR_NOSUCHSERVER " :No such server\n"						// 402
#define ERR_NOSUCHCHANNEL ":No such channel\n"						// 403
#define ERR_NOMOTD ":MOTD File is missing"							// 422
#define ERR_NONICKNAMEGIVEN ":No nickname given\n"					// 431
#define ERR_ERRONEUSNICKNAME " :Erroneus nickname\n"				// 432
#define ERR_NICKNAMEINUSE " :Nickname is already in use\n"			// 433
#define ERR_NICKCOLLISION "<nick> :Nickname collision KILL\n"		// 436
#define ERR_NOTONCHANNEL  ":You're not on that channel\n"			// 442
#define ERR_NOTREGISTERED ":You have not registered\n"				// 451
#define ERR_NEEDMOREPARAMS " :Not enough parameters\n"				// 461
#define ERR_ALREADYREGISTRED ":You may not reregister\n"			// 462
#define ERR_PASSWDMISMATCH ":Password incorrect\n"					// 464
#define ERR_KEYSET ":Channel key already set\n"						// 467
#define ERR_UNKNOWNMODE ":is unknown mode char to me\n"				// 472
#define ERR_NOPRIVILEGES ":Permission Denied- You're not an IRC operator" // 481
#define ERR_NOOPERHOST ":No O-lines for your host\n"				// 491
#define ERR_CHANOPRIVSNEEDED ":You're not channel operator\n"		// 482
#define ERR_USERSDONTMATCH ":Cant change mode for other users\n"	// 502

int Server::errorMEss(int err, User &user, const std::string &str) {
	std::string messg;
	switch (err) {
	case 402:
		messg = msg.midParams[0] + ERR_NOSUCHSERVER;
		break ;
	case 403:
		messg = str + " " + ERR_NOSUCHCHANNEL;
		break;
	case 422:
		messg = ERR_NOMOTD;
		break ;
	case 431:
		messg = ERR_NONICKNAMEGIVEN;
		break ;
	case 432:
		messg = user.getNick() + ERR_ERRONEUSNICKNAME;
		break ;
	case 433:
		messg = user.getNick() + ERR_NICKNAMEINUSE;
		break ;
	case 436:
		messg = user.getNick() + ERR_NICKCOLLISION;
		break ;
	case 442:
		messg = str + " " + ERR_NOTONCHANNEL;
		break;
	case 451:
		messg = ERR_NOTREGISTERED;
		break ;
	case 461:
		messg = msg.cmd + ERR_NEEDMOREPARAMS;
		break ;
	case 462:
		messg = ERR_ALREADYREGISTRED;
		break ;
	case 464:
		messg = ERR_PASSWDMISMATCH;
		break ;
	case 467:
		messg = str + " " + ERR_KEYSET;
		break ;
	case 472:
		messg = str + " " + ERR_UNKNOWNMODE;
		break ;
	case 481:
		messg = ERR_NOPRIVILEGES;
		break ;
	case 491:
		messg = ERR_NOOPERHOST;
		break ;
	case 482:
		messg = str + " " + ERR_CHANOPRIVSNEEDED;
		break ;
	case 502:
		messg = ERR_USERSDONTMATCH;
		break ;
	default:
		messg = "Something wrong\n";
	}
	send(user.getFd(), messg.c_str(), messg.size(), 0);
	std::cout << "\e[31mSend error to " << user.getNick() << "< socket " << user.getFd() << " >:\e[0m " << messg;
	return 1;
}