#include "Server.hpp"

int Server::who( User & ) {
	
	if (this->msg.midParams.size() > 2)
	{
		// std::cout << ;
		return 0;
	}
	// if 
	// пример команды и возвращаемого значения:

	// WHO *
	// :IRCat 352 kin * 1 127.0.0.1 IRCat nik H :0 4
	// :IRCat 352 kin * 1 127.0.0.1 IRCat kin H :0 4
	// :IRCat 315 kin kin :End of /WHO list

	// WHO
	// :IRCat 461 nik WHO :Not enough parameters

	// WHO ***
	// :IRCat 352 nik * 1 127.0.0.1 IRCat nik H :0 4
	// :IRCat 315 nik nik :End of /WHO list

	// WHO 1 2 3 4
	// :IRCat 315 nik nik :End of /WHO list
	return 1;
}

int Server::whois( User & ) {
	return 0;	
}

int Server::whowas( User & ) {
	return 0;
}