#include "Server.hpp"

int	Server::version( User & user ){
	if (msg.midParams.size() != 0 && msg.midParams[0] != serverName) {
		errorMEss(402, user);
		return 1;
	}
	replyMEss(351, user);
	return 0;
}

std::string Server::checkTime() {
    std::time_t result = std::time(nullptr);
    char buffer[32];
    std::strncpy(buffer, std::ctime(&result), 26);
	std::string str(buffer);
	return str;
}

int	Server::time( User & user ){
	if (msg.midParams.size() != 0 && msg.midParams[0] != serverName) {
		errorMEss(402, user);
		return 1;
	}
	std::string str = checkTime();
	replyMEss(391, user, str);
	return 0;
}

int	Server::admin( User & user ){
	return 0;
}

int	Server::info( User & user ){
	if (msg.midParams.size() != 0 && msg.midParams[0] != serverName) {
		errorMEss(402, user);
		return 1;
	}
	std::vector<std::string>::iterator it = servInfo.begin();
	for ( ; it != servInfo.end(); ++it) {
		replyMEss(371, user, *it);
	}
	replyMEss(374, user);
	return 0;
}
