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
		send(user.getFd(), "invalid number of parameters is given\n", 39, 0);
		// std::cout << "invalid number of parameters is given\n";
		return (1);
	}

	if (msg.midParams.size() == 1 || msg.midParams.size() == 0)
	{
		while (userIt != endIt)
		{
			if (!(*userIt)->empty())
			{
				message = "* " + (*userIt)->getUser() + " " + (*userIt)->getHost() + " " \
				+ (*userIt)->getServer() + " " + (*userIt)->getNick() + "\n";
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
				message = "* " + (*userIt)->getUser() + " " + (*userIt)->getHost() + " " \
				+ (*userIt)->getServer() + " " + (*userIt)->getNick() + "\n";
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

int Server::whois( User & user)
{
	std::vector<User *>::iterator userIt;
	std::vector<User *>::iterator endUserIt;
	std::vector<std::string>::iterator paramIt;
	std::vector<std::string>::iterator endPramIt;

	// if (msg.midParams.size() < 1)
	// {
	// 	errorMEss(431, user, 0); 
	// 	return (1);
	// }
	// if (msg.midParams.size() == 1 || msg.midParams.size() == 0)
	// {
	// 	while (userIt != endIt)
	// 	{
	// 		if (!(*userIt)->empty())
	// 		{
	// 			message = "* " + (*userIt)->getUser() + " " + (*userIt)->getHostn() + " " \
	// 			+ (*userIt)->getServern() + " " + (*userIt)->getNick() + "\n";
	// 			replyMEss(352, user, message);
	// 		}
	// 		userIt++;
	// 	}
	// 	std::cout << msg.midParams[0] << " :End of /WHO list\n";
	// }
	return 0;	
}

//? ERR_NOSUCHSERVER 402
	// "<server name> :No such server"
    // - Used to indicate the server name given currently
    //   doesn't exist.
//DONE ERR_NONICKNAMEGIVEN 431
    // ":No nickname given"
    // - Returned when a nickname parameter expected for a
    //   command and isn't found.
// RPL_WHOISUSER 311
    // "<nick> <user> <host> * :<real name>"
// RPL_WHOISCHANNELS 319
	// "<nick> :{[@|+]<channel><space>}"
	//   - Replies 311 - 313, 317 - 319 are all replies
    // generated in response to a WHOIS message.  Given that
    // there are enough parameters present, the answering
    // server must either formulate a reply out of the above
    // numerics (if the query nick is found) or return an
    // error reply.  The '*' in RPL_WHOISUSER is there as
    // the literal character and not as a wild card.  For
    // each reply set, only RPL_WHOISCHANNELS may appear
    // more than once (for long lists of channel names).
    // The '@' and '+' characters next to the channel name
    // indicate whether a client is a channel operator or
    // has been granted permission to speak on a moderated
    // channel.  The RPL_ENDOFWHOIS reply is used to mark
    // the end of processing a WHOIS message.
// RPL_WHOISSERVER 312
	// "<nick> <server> :<server info>"
// RPL_AWAY 301
	// "<nick> :<away message>"
// RPL_WHOISOPERATOR 313
	// "<nick> :is an IRC operator"
// RPL_WHOISIDLE 317
	// "<nick> <integer> :seconds idle"
// ERR_NOSUCHNICK 401
	// "<nickname> :No such nick/channel"
    // - Used to indicate the nickname parameter supplied to a
    //   command is currently unused.

// RPL_ENDOFWHOIS 318
	// "<nick> :End of /WHOIS list"

int Server::whowas( User & )
{
	return 0;
}