#include "Server.hpp"

int	Server::version( User & user )	{
	if (msg.midParams.size() != 0 && msg.midParams[0] != inf.serverName) {
		errorMEss(402, user);
		return 1;
	}
	else if (msg.midParams.size() == 0 || (msg.midParams.size() != 0 && msg.midParams[0] == inf.serverName))
		replyMEss(351, user);
	return 0;
}

std::string Server::checkTime()	{
    std::time_t result = std::time(nullptr);
    char buffer[32];
    std::strncpy(buffer, std::ctime(&result), 26);
	std::string str(buffer);
	return str;
}

int	Server::time( User & user )	{
	if (msg.midParams.size() != 0 && msg.midParams[0] != inf.serverName) {
		errorMEss(402, user);
		return 1;
	}
	else if (msg.midParams.size() == 0 || (msg.midParams.size() != 0 && msg.midParams[0] == inf.serverName))	{
		std::string str = checkTime();
		replyMEss(391, user, str);
	}
	return 0;
}

int	Server::admin( User & user )	{
	if (msg.midParams.size() != 0 && msg.midParams[0] != inf.serverName) {
		errorMEss(402, user);
		return 1;
	}
	else if (msg.midParams.size() == 0 || (msg.midParams.size() != 0 && msg.midParams[0] == inf.serverName))	{
		replyMEss(256, user);
		replyMEss(257, user);
		replyMEss(259, user);
	}
	return 0;
}

int	Server::info( User & user )	{
	if (msg.midParams.size() != 0 && msg.midParams[0] != inf.serverName) {
		errorMEss(402, user);
		return 1;
	}
	else if (msg.midParams.size() == 0 || (msg.midParams.size() != 0 && msg.midParams[0] == inf.serverName))	{
		replyMEss(371, user, "Server name - " + inf.serverName + "\n");
		replyMEss(371, user, "Server version - " + inf.srvVersion + "\n");
		replyMEss(371, user, "Patchlevel - 1\n");
		replyMEss(371, user, "Server start time - " + inf.srvStartTime);
		replyMEss(374, user);
	}
	return 0;
}
