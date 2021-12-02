#include "Server.hpp"

#define ERR_NOOPERHOST ":No O-lines for your host\n"
#define ERR_NICKCOLLISION "<nick> :Nickname collision KILL\n"
#define ERR_NICKNAMEINUSE " :Nickname is already in use\n"
#define ERR_ERRONEUSNICKNAME " :Erroneus nickname\n"
#define ERR_NONICKNAMEGIVEN ":No nickname given\n"
#define ERR_ALREADYREGISTRED ":You may not reregister\n"
#define ERR_NEEDMOREPARAMS " :Not enough parameters\n"
#define ERR_PASSWDMISMATCH ":Password incorrect\n"
#define ERR_NOTREGISTERED ":You have not registered\n"

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
	}
	send(user.getFd(), messg.c_str(), messg.size(), 0);
}