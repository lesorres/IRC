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
