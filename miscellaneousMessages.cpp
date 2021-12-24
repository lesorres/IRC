#include "Server.hpp"

int Server::kill( User & user ) {
	if (msg.paramN == 2) {
		if (!(user.getFlags() & OPERATOR))
			return errorMEss(ERR_NOPRIVILEGES, user);
		for (std::vector<User*>::iterator it = userData.begin(); it != userData.end(); ++it) {
			if ((msg.midParams[0] == (*it)->getNick()) && (user.getFlags() & OPERATOR)) 
				return killUser(*(*it));
			else if (it == userData.end() && msg.midParams[0] != (*it)->getNick())
				return errorMEss(ERR_NOSUCHNICK, user, msg.midParams[0]);
			}
		}
	return errorMEss(ERR_NEEDMOREPARAMS, user);
}

int Server::ping( User & user) {
	if (msg.midParams.size() != 1)
		return errorMEss(ERR_NOORIGIN, user);
	std::string str = ":" + inf.serverName + " PONG :" + msg.midParams[0] + "\n";
	return replyMEss(RPL_PING, user, str);
}

int Server::pong( User & user) {
	if (msg.midParams.size() != 1)  
		return errorMEss(ERR_NOORIGIN, user);
	if (msg.midParams[0] != inf.serverName)
		return errorMEss(ERR_NOSUCHSERVER, user);
	user.unsetFlags(PING);
	return 0;
}


int	Server::restart( User & user ) {
	if (msg.paramN == 0) {
		if (!(user.getFlags() & OPERATOR))
			return errorMEss(ERR_NOPRIVILEGES, user);
		// delete this;
		close(srvFd);
		create();
		run();
	}
	return 0;
}

int	Server::rehash( User & user ) {
	if (msg.paramN == 0) {
		if (!(user.getFlags() & OPERATOR))
			return errorMEss(ERR_NOPRIVILEGES, user);
		parseConf();
		replyMEss(RPL_REHASHING, user, " :Rehashing\n");
	}
	return 0;
}
