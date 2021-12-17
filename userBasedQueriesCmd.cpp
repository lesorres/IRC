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
		replyMEss(RPL_ENDOFWHO, user);
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
		replyMEss(RPL_ENDOFWHO, user);
	}
	return (0);
}

// ERR_NOSUCHSERVER                +ERR_NONICKNAMEGIVEN
// +RPL_WHOISUSER                  +RPL_WHOISCHANNELS
// +RPL_WHOISCHANNELS              RPL_WHOISSERVER
// RPL_AWAY                        +RPL_WHOISOPERATOR
// RPL_WHOISIDLE                   +ERR_NOSUCHNICK
// +RPL_ENDOFWHOIS

int Server::whois( User & user)
{
	// [<server>] parameter of command is not checked
	std::string message;
	std::vector<User *>::iterator userIt = userData.begin();
	std::vector<User *>::iterator endUserIt = userData.end();
	std::vector<std::string>::iterator paramIt = msg.midParams.begin();
	std::vector<std::string>::iterator endPramIt = msg.midParams.end();
	std::vector<std::string>::iterator opListIt;
	std::vector<std::string>::iterator endOpListIt;

	if (msg.midParams.size() < 1)
		return (errorMEss(ERR_NONICKNAMEGIVEN, user));

	while (paramIt != endPramIt)
	{
		while (userIt != endUserIt)
		{
			// rfc1459 319 "The '*' in RPL_WHOISUSER is there as
			// the literal character and not as a wild card."
			if ((*userIt)->getNick() == *paramIt)
			{
				message = (*userIt)->getNick() + " " + (*userIt)->getUser() \
						+ " " + (*userIt)->getHost() + " * :" + (*userIt)->getReal() + "\n";
				replyMEss(RPL_WHOISUSER, user, message);
				if ((*userIt)->getFlags() & OPERATOR)
					replyMEss(RPL_WHOISOPERATOR, user, (*userIt)->getNick());
				if (!(*userIt)->getOpChannelList().empty())
				{
					opListIt = (*userIt)->getOpChannelList().begin();
					endOpListIt = (*userIt)->getOpChannelList().end();
					message = (*userIt)->getNick() + " :";
					while (opListIt != endOpListIt)
						message += "@" + *opListIt + " ";
					replyMEss(RPL_WHOISCHANNELS, user, message);
				}
				if ((*userIt)->getFlags() & AWAY)
				{
					message = 
					replyMEss(RPL_AWAY, user);
				}
				replyMEss(RPL_ENDOFWHOIS, user, (*userIt)->getNick());
			}
			else
				errorMEss(ERR_NOSUCHNICK, user, *paramIt);
		}
	}
	return(0);
}

int Server::whowas( User & )
{
	return 0;
}