#include "Server.hpp"

int Server::ison( User & user )	{
	if (msg.paramN == 0) {
		errorMEss(461, user);
		return 1;
	}
	std::string str;
	for (std::vector<std::string>::iterator it = msg.midParams.begin(); it != msg.midParams.end(); ++it) {
		for (std::vector<User*>::iterator i = userData.begin(); i != userData.end(); ++i)	{
			if (*it == (*i)->getNick())
				str += *it + " ";
		}
	}
	replyMEss(303, user, str);
	return 0;
}

int	Server::userhost( User & user) {
	if (msg.paramN > 5 || msg.paramN < 1)
		errorMEss(461, user);
	else	{
		std::string str;
		for (std::vector<std::string>::iterator it = msg.midParams.begin(); it != msg.midParams.end(); ++it) {
			for (std::vector<User*>::iterator i = userData.begin(); i != userData.end(); ++i)	{
				if (*it == (*i)->getNick()) {
					str += *it + "=";
					if ((*i)->getUserFlags() & OPERATOR) str += "*";
					if ((*i)->getUserFlags() & AWAY) str += "+";
					else str += "-";
					str += (*i)->getHostn() + " ";
				}
			}
		}
		replyMEss(302, user, str);
	}
	return 0;
}