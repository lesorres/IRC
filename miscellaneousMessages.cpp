#include "Server.hpp"

int Server::kill( User & user ) {
	if (msg.paramN < 1 || msg.paramN > 2)
		return errorMEss(ERR_NEEDMOREPARAMS, user);
	
}