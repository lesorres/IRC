#include "Server.hpp"

int Server::who( User & user)
{
	std::vector<User *>::iterator userIt;
	std::vector<User *>::iterator endIt;
	std::string message;

	userIt = userData.begin();
	endIt = userData.end();

	if (msg.midParams.size() > 2)
	{
		std::cout << "invalid number of parameters is given\n";
		return (1);
	}

	if (msg.midParams.size() == 1)
	{
		while (userIt != endIt)
		{
			if (!(*userIt)->empty())
			{
				message = "* " + (*userIt)->getUser() + " " + (*userIt)->getHostn() + " " \
				+ (*userIt)->getServern() + " " + (*userIt)->getNick() + "\n";
				replyMEss(352, user, message);
			}
			userIt++;
		}
		std::cout << msg.midParams[0] << " :End of /WHO list\n";
	}

	else if (msg.midParams.size() == 2) //имеет смысл объединить с верхним условием
	{
		while (userIt != endIt)
		{
			if (!(*userIt)->empty()) //добавить условие на оператора
			{
				message = "* " + (*userIt)->getUser() + " " + (*userIt)->getHostn() + " " \
				+ (*userIt)->getServern() + " " + (*userIt)->getNick() + "\n";
				replyMEss(352, user, message);
			}
			userIt++;
		}
		if (msg.midParams[2] != "o")
			return (1);
		std::cout << msg.midParams[0] << " :End of /WHO list\n";
	}

	else
	{
	}
	return (0);
}
	// пример команды и возвращаемого значения:

	// WHO *
	// :IRCat 352 kin * 1 127.0.0.1 IRCat nik H :0 4 //The numeric reply must be sent as one message consisting of the sender prefix, the three digit numeric, and the target of the reply. 
	// :IRCat 352 kin * 1 127.0.0.1 IRCat kin H :0 4
	// :IRCat 315 kin kin :End of /WHO list

	// WHO
	// :IRCat 461 nik WHO :Not enough parameters

	// WHO ***
	// :IRCat 352 nik * 1 127.0.0.1 IRCat nik H :0 4
	// :IRCat 315 nik nik :End of /WHO list

	// WHO 1 2 3 4
	// :IRCat 315 nik nik :End of /WHO list


	// WHO
	// :IRCat 461 mynick WHO :Not enough parameters

	// WHO othernick
	// :IRCat 352 mynick * user2 127.0.0.1 IRCat othernick H :0  real2 name2
	// :IRCat 315 mynick mynick :End of /WHO list

	// WHO othernick o
	// :IRCat 315 mynick mynick :End of /WHO list

	// WHO *
	// :IRCat 352 mynick * username 127.0.0.1 IRCat mynick H :0  real name
	// :IRCat 352 mynick * user2 127.0.0.1 IRCat othernick H :0  real2 name2
	// :IRCat 315 mynick mynick :End of /WHO list

	// WHO othernick f
	// :IRCat 352 mynick * user2 127.0.0.1 IRCat othernick H :0  real2 name2
	// :IRCat 315 mynick mynick :End of /WHO list

	// WHO othernick bla bla
	// :IRCat 352 mynick * user2 127.0.0.1 IRCat othernick H :0  real2 name2
	// :IRCat 315 mynick mynick :End of /WHO list

	// WHO noone
	// :IRCat 315 mynick mynick :End of /WHO list

	// WHO noone o
	// :IRCat 315 mynick mynick :End of /WHO list

	// WHO *
	// :IRCat 352 mynick * username 127.0.0.1 IRCat mynick H :0  real name
	// :IRCat 352 mynick * user2 127.0.0.1 IRCat othernick H :0  real2 name2
	// :IRCat 315 mynick mynick :End of /WHO list
	
	// WHO * o
	// :IRCat 315 mynick mynick :End of /WHO list

int Server::whois( User & )
{
	return 0;	
}

// ERR_NOSUCHSERVER
// ERR_NONICKNAMEGIVEN
// RPL_WHOISUSER
// RPL_WHOISCHANNELS
// RPL_WHOISCHANNELS
// RPL_WHOISSERVER
// RPL_AWAY
// RPL_WHOISOPERATOR
// RPL_WHOISIDLE
// ERR_NOSUCHNICK
// RPL_ENDOFWHOIS

int Server::whowas( User & )
{
	return 0;
}