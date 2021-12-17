#include "Server.hpp"

int Server::kill( User & user ) {
	if (msg.paramN == 2) {
		if (!(user.getFlags() & OPERATOR))
			return errorMEss(ERR_NOPRIVILEGES, user);
		for (std::vector<User*>::iterator it = userData.begin(); it != userData.end(); ++it) {
			if (msg.midParams[0] != (*it)->getNick())
				return errorMEss(ERR_NOSUCHNICK, user, msg.midParams[0]);
			else if (msg.midParams[0] == (*it)->getNick() && (user.getFlags() & OPERATOR))
				return killUser(user);
			}
		}
	return errorMEss(ERR_NEEDMOREPARAMS, user);
}