#include "Server.hpp"

int Server::errorMEss(int err, User &user, const std::string &str) {
	std::string messg;
	switch (err) {
	case 401:
		messg = str + " :No such nick/channel";
		break ;
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
	case 483:
		messg = ":You cant kill a server!";
		break ;
	case 491:
		messg = ":No O-lines for your host\n";
		break ;
	case 501:
		messg = ":Unknown MODE flag\n";
		break ;
	case 502:
		messg = ":Cant change mode for other users\n";
		break ;
	case 1000:
		messg = str + "\n";
		break ;
	default:
		messg = "something wrong\n";
	}
	send(user.getFd(), messg.c_str(), messg.size(), 0);
	std::cout << "\e[31mSend error to " << user.getNick() << "< socket " << user.getFd() << " >:\e[0m " << messg;
	return 1;
}