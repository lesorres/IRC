#include "Command.hpp"

void Command::who( User &, std::vector<User*>& userData ) {
	
	// if (this->msg.midParams.size() > 2)
	// {
	// 	std::cout << 
	// 	return()
	// }
	// // if 
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
}

void Command::whois( User &, std::vector<User*>& userData ) {
	
}

void Command::whowas( User &, std::vector<User*>& userData ) {
	
}