#include "Server.hpp"

#define ERR_NOOPERHOST ":No O-lines for your host\n"				// 491
#define ERR_NICKCOLLISION "<nick> :Nickname collision KILL\n"		// 436
#define ERR_NICKNAMEINUSE " :Nickname is already in use\n"			// 433
#define ERR_ERRONEUSNICKNAME " :Erroneus nickname\n"				// 432
#define ERR_NONICKNAMEGIVEN ":No nickname given\n"					// 431
#define ERR_ALREADYREGISTRED ":You may not reregister\n"			// 462
#define ERR_NEEDMOREPARAMS " :Not enough parameters\n"				// 461
#define ERR_PASSWDMISMATCH ":Password incorrect\n"					// 464
#define ERR_NOTREGISTERED ":You have not registered\n"				// 451
#define ERR_NOMOTD ":MOTD File is missing"							// 422
#define ERR_NOTONCHANNEL  "<channel> :You're not on that channel"	// 442
#define ERR_NOSUCHCHANNEL "<channel name> :No such channel"			// 403

void Server::errorMEss(int err, User &user) {
	std::string messg;
	switch (err) {
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
	case 422:
		messg = ERR_NOMOTD;
		break ;
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
	case 491:
		messg = ERR_NOOPERHOST;
		break ;
	case 442:
		messg = ERR_NOTONCHANNEL;
		break;
	case 403:
		messg = ERR_NOSUCHCHANNEL;
		break;
	default:
		messg = "Something wrong\n";
	}
	send(user.getFd(), messg.c_str(), messg.size(), 0);
}