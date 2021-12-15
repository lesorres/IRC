#include "Server.hpp"

int Server::who( User & user)
{
	std::vector<User *>::iterator userIt;
	std::vector<User *>::iterator endIt;
	std::string message;

	userIt = userData.begin();
	endIt = userData.end();

	if (msg.midParams.size() > 2)
		return (errorMEss(1000, user, "invalid number of parameters is given"));
	else if (msg.midParams.size() == 2 && msg.midParams[1] != "o")
		return (errorMEss(1000, user, \
		"second parameters of command is invalid, please put \"o\" as a second parameter if you want to see the list of operators only"));

	//rfc1459 4.5.1 "In the absence of the <name> parameter, all visible
	//(users who aren't invisible (user mode +i) and who don't have a
	//common channel with the requesting client) are listed.  The same
	//result can be achieved by using a <name> of "0" or any wildcard which
	// will end up matching every entry possible."
	if (msg.midParams[0] == "0" || msg.midParams[0] == "*" || msg.midParams.size() == 0 \
	|| (msg.midParams.size() == 1 && msg.midParams[0] == "o"))
	{
		while (userIt != endIt)
		{
			if ((*userIt)->getChannelList().empty())
				message = "* " + (*userIt)->getUser() \
						+ " " + (*userIt)->getHost() + " " + (*userIt)->getServer() + " " \
						+ (*userIt)->getNick() + "\n";
			else
				message = *((*userIt)->getChannelList().end() - 1) + (*userIt)->getUser() \
						+ " " + (*userIt)->getHost() + " " + (*userIt)->getServer() + " " \
						+ (*userIt)->getNick() + "\n";
			if (((msg.midParams.size() == 2 && msg.midParams[1] == "o") \
				|| (msg.midParams.size() == 1 && msg.midParams[0] == "o")) \
				&& !(*userIt)->getOpChannelList().empty())
			{
				replyMEss(RPL_WHOREPLY, user, message);
			}
			else if(!((msg.midParams.size() == 2 && msg.midParams[1] == "o") \
					|| (msg.midParams.size() == 1 && msg.midParams[0] == "o")) )
			{
				replyMEss(RPL_WHOREPLY, user, message);
			}
			userIt++;
		}
		//The RPL_WHOREPLY and RPL_ENDOFWHO pair are used
		//to answer a WHO message.  The RPL_WHOREPLY is only
		//sent if there is an appropriate match to the WHO
		//query.  If there is a list of parameters supplied
		//with a WHO message, a RPL_ENDOFWHO must be sent
		//after processing each list item with <name> being
		//the item.
		replyMEss(RPL_ENDOFWHO, user, "");
	}
	else if (msg.midParams.size() == 1)
	{
		//The <name> passed to WHO is matched against users' host, server, real
		//name and nickname if the channel <name> cannot be found.
		while (userIt != endIt)
		{
			if ((*userIt)->getChannelList().empty())
			{
				message = "* " + (*userIt)->getUser() \
						+ " " + (*userIt)->getHost() + " " + (*userIt)->getServer() + " " \
						+ (*userIt)->getNick() + "\n";
			}
			else
				message = *((*userIt)->getChannelList().end() - 1) + (*userIt)->getUser() \
						+ " " + (*userIt)->getHost() + " " + (*userIt)->getServer() + " " \
						+ (*userIt)->getNick() + "\n";
			if (checkWildcard((*userIt)->getUser().c_str(), msg.midParams[0].c_str()))
				replyMEss(RPL_WHOREPLY, user, message);
			else if (checkWildcard((*userIt)->getHost().c_str(), msg.midParams[0].c_str()))
				replyMEss(RPL_WHOREPLY, user, message);
			else if (checkWildcard((*userIt)->getServer().c_str(), msg.midParams[0].c_str()))
				replyMEss(RPL_WHOREPLY, user, message);
			else if (checkWildcard((*userIt)->getReal().c_str(), msg.midParams[0].c_str()))
				replyMEss(RPL_WHOREPLY, user, message);
			else if (checkWildcard((*userIt)->getNick().c_str(), msg.midParams[0].c_str()))
				replyMEss(RPL_WHOREPLY, user, message);
			userIt++;
		}
		replyMEss(RPL_ENDOFWHO, user, "");
	}
	else
	{
		std::cout << "if_3\n";
		while (userIt != endIt)
		{
			if (!(*userIt)->getOpChannelList().empty())
			{
				if ((*userIt)->getChannelList().empty())
					message = "* " + (*userIt)->getUser() \
							+ " " + (*userIt)->getHost() + " " + (*userIt)->getServer() + " " \
							+ (*userIt)->getNick() + "\n";
				else
					message = *((*userIt)->getChannelList().end() - 1) + (*userIt)->getUser() \
							+ " " + (*userIt)->getHost() + " " + (*userIt)->getServer() + " " \
							+ (*userIt)->getNick() + "\n";
				if (checkWildcard((*userIt)->getUser().c_str(), msg.midParams[0].c_str()))
					replyMEss(RPL_WHOREPLY, user, message);
				else if (checkWildcard((*userIt)->getHost().c_str(), msg.midParams[0].c_str()))
					replyMEss(RPL_WHOREPLY, user, message);
				else if (checkWildcard((*userIt)->getServer().c_str(), msg.midParams[0].c_str()))
					replyMEss(RPL_WHOREPLY, user, message);
				else if (checkWildcard((*userIt)->getReal().c_str(), msg.midParams[0].c_str()))
					replyMEss(RPL_WHOREPLY, user, message);
				else if (checkWildcard((*userIt)->getNick().c_str(), msg.midParams[0].c_str()))
					replyMEss(RPL_WHOREPLY, user, message);
			}
			userIt++;
		}
		replyMEss(RPL_ENDOFWHO, user, "");
	}
	return (0);
}

int Server::whois( User & user)
{
	// [<server>] parameter of command is not checked
	std::string message;

	std::vector<User *>::iterator userIt = userData.begin();
	std::vector<User *>::iterator endUserIt = userData.end();
	std::vector<std::string>::iterator paramIt = msg.midParams.begin();
	std::vector<std::string>::iterator endPramIt = msg.midParams.end();

	while (paramIt != endPramIt)
	{
		message = (*userIt)->getNick() + " " + (*userIt)->getUser() \
				+ " " + (*userIt)->getHost() + " * :" + (*userIt)->getReal() + "\n";
		while (userIt != endUserIt)
		{
			replyMEss(RPL_ENDOFWHO, user, "");
			checkWildcard((*userIt)->getHost().c_str(), msg.midParams[0].c_str())
		}
	}

	if (msg.midParams.size() < 1)
	{
		errorMEss(431, user, 0); 
		return (1);
	}
	if (msg.midParams.size() == 1 || msg.midParams.size() == 0)
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