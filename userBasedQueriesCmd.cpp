#include "Server.hpp"
#include "Utils.hpp"

static bool commonChannel(User & user1, User & user2)
{
	std::vector<std::string>::iterator itV1 (user1.getChannelList().begin());
	std::vector<std::string>::iterator itEndV1 (user1.getChannelList().end());
	std::vector<std::string>::iterator itEndV2 (user2.getChannelList().end());

	while (itV1 != itEndV1)
	{
		std::vector<std::string>::iterator itV2 (user2.getChannelList().begin());
		while (itV2 != itEndV2)
		{
			if(*itV1 == *itV2)
				return (1);
			itV2++;
		}
		itV1++;
	}
	return (0);
}

int Server::who( User & user)
{
	std::vector<User *>::iterator userIt;
	std::vector<User *>::iterator endIt;
	std::map<std::string, Channel *>::iterator chnIt = channels.begin();
	std::map<std::string, Channel *>::iterator endChnIt = channels.end();
	std::vector<User *>::iterator chnUsersIt;
	std::vector<User *>::iterator endChnUsersIt;
	
	std::vector<User *> chnUsers;
	std::string message = "";
	std::string opSymbol = "";
	std::string ircOpSymbol = "";
	std::string channel = "*";

	userIt = userData.begin();
	endIt = userData.end();

	if (msg.midParams.size() > 2)
		return (errorMEss(1000, user, "invalid number of parameters is given"));
	else if (msg.midParams.size() == 2 && msg.midParams[1] != "o")
		return (errorMEss(1000, user, \
		"second parameters of command is invalid, please put \"o\" as a second parameter if you want to see the list of operators only"));
	//rfc1459 4.5.1
	// "In the absence of the <name> parameter, all visible are listed.
	// The same result can be achieved by using a <name> of "0" or any
	// wildcard which will end up matching every entry possible."
	if (msg.midParams[0] == "0" || onlyWildcard(msg.midParams[0]) || msg.midParams.size() == 0 \
	|| (msg.midParams.size() == 1 && msg.midParams[0] == "o"))
	{
		while (userIt != endIt)
		{
			//rfc1459 4.5.1
			// In the absence of the <name> parameter, all visible
			// (users who aren't invisible (user mode +i) and who don't have a
			// common channel with the requesting client) are listed.
			if (!((*userIt)->getFlags() & INVISIBLE) && !commonChannel(user, **userIt))
			{
				ircOpSymbol = "";
				opSymbol = "";
				channel = "*";
				if (!(*userIt)->getChannelList().empty()) //checks if user participate in any channel
					channel = *((*userIt)->getChannelList().end() - 1);
				if ((*userIt)->getFlags() & OPERATOR) //checks if user is IRC operator
					ircOpSymbol = "*";
				if (!(*userIt)->getChannelList().empty() && channels[channel]->isOperator((*userIt))) //checks if user is operator of current channel
					opSymbol = "@";
				message = channel + (*userIt)->getUser() + " " + (*userIt)->getHost() + " " \
						+ (*userIt)->getServer() + " " + (*userIt)->getNick() + " H" \
						+ ircOpSymbol + opSymbol + "\n";
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
			replyMEss(RPL_ENDOFWHO, user, (*userIt)->getNick());
			}
			userIt++;
		}
		//The RPL_WHOREPLY and RPL_ENDOFWHO pair are used to answer a WHO message.
		// The RPL_WHOREPLY is only sent if there is an appropriate match to the WHO
		//query.  If there is a list of parameters supplied
		//with a WHO message, a RPL_ENDOFWHO must be sent after processing
		// each list item with <name> being the item.
	}
	else
	{
		if (!channels.empty() && msg.midParams[0][0] == '#')
		{
			while (chnIt != endChnIt)
			{
				if (chnIt->first == msg.midParams[0])
				{
					if (msg.midParams.size() == 1 || (msg.midParams.size() == 2 && msg.midParams[1] == chnIt->second->getPass()))
						chnUsers = chnIt->second->getUserList();
					else if (msg.midParams.size() == 2 && msg.midParams[1] == "o")
						chnUsers = chnIt->second->getOperList();
					for (size_t i = 0; i < chnUsers.size(); i++)
					{
						ircOpSymbol = "";
						opSymbol = "";
						if (chnUsers[i]->getFlags() & OPERATOR) //checks if user is IRC operator
							ircOpSymbol = "*";
						if (chnIt->second->isOperator(chnUsers[i])) //checks if user is operator of current channel
							opSymbol = "@";
						message = *(chnUsers[i]->getChannelList().end() - 1) + " " + chnUsers[i]->getUser() + " " \
						+ chnUsers[i]->getHost() + " " + chnUsers[i]->getServer() + " " + chnUsers[i]->getNick() \
						+ " H" + ircOpSymbol + opSymbol + "\n";
						replyMEss(RPL_WHOREPLY, user, message);
					}
				}
				chnIt++;
			}
		}
		//The <name> passed to WHO is matched against users' host, server, real
		//name and nickname if the channel <name> cannot be found.
		else if (msg.midParams[0][0] != '#')
		{
			while (userIt != endIt)
			{
				if (msg.midParams.size() == 1 \
				|| (!(*userIt)->getOpChannelList().empty() && msg.midParams.size() == 2))
				{
					ircOpSymbol = "";
					opSymbol = "";
					channel = "*";
					if (!(*userIt)->getChannelList().empty()) //checks if user participate in any channel
						channel = *((*userIt)->getChannelList().end() - 1);
					if ((*userIt)->getFlags() & OPERATOR) //checks if user is IRC operator
						ircOpSymbol = "*";
					if (!(*userIt)->getChannelList().empty() && channels[channel]->isOperator((*userIt))) //checks if user is operator of current channel
						opSymbol = "@";
					message = channel + (*userIt)->getUser() + " " + (*userIt)->getHost() + " " \
							+ (*userIt)->getServer() + " " + (*userIt)->getNick() + " H" \
							+ ircOpSymbol + opSymbol + "\n";
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
		}
		replyMEss(RPL_ENDOFWHO, user, msg.midParams[0]);
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
	std::vector<std::string>::iterator opListIt;
	std::vector<std::string>::iterator endOpListIt;
	bool nickAbsenceFlag;

	if (msg.midParams.size() < 1)
		return (errorMEss(ERR_NONICKNAMEGIVEN, user));

	while (paramIt != endPramIt)
	{
		nickAbsenceFlag = 0;
		while (userIt != endUserIt)
		{
			if (checkWildcard((*userIt)->getNick().c_str(), (*paramIt).c_str()))
			{
				nickAbsenceFlag = 1;
				message = (*userIt)->getNick() + " " + (*userIt)->getUser() \
						+ " " + (*userIt)->getHost() + " * :" + (*userIt)->getReal() + "\n";
				replyMEss(RPL_WHOISUSER, user, message);
				replyMEss(RPL_WHOISIDLE, user, ((*userIt)->getNick() + " " + \
				itos((*userIt)->timeChecker() - (*userIt)->getLastMessTime())));
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
				else 
					replyMEss(RPL_WHOISCHANNELS, user, (*userIt)->getNick() + " :");
				awayRpl(user, **userIt);
				replyMEss(RPL_ENDOFWHOIS, user, (*userIt)->getNick());
			}
			userIt++;
		}
		if (nickAbsenceFlag == 0)
			errorMEss(ERR_NOSUCHNICK, user, *paramIt);
		paramIt++;
	}
	return(0);
}

int Server::whowas( User & user)
{
	// [<server>] parameter of command is not checked
	int count;
	int i = 0;
	bool nickAbsenceFlag = 0;
	std::string message;
	std::vector<User *>::reverse_iterator userRBeginIt = history.rbegin();
	std::vector<User *>::reverse_iterator userREndIt = history.rend();

	if (msg.midParams.size() < 1)
		return (errorMEss(ERR_NONICKNAMEGIVEN, user));
	if (msg.midParams.size() > 2)
		return (errorMEss(1000, user, "invalid number of parameters is given"));
	if (msg.midParams.size() == 2 && !(isNumStr(msg.midParams[1])))
		count = atoi(msg.midParams[1].c_str());
	else if (msg.midParams.size() == 2 && isNumStr(msg.midParams[1]))
		return (errorMEss(1000, user, "second parameters is invalid"));

	while (userRBeginIt != userREndIt)
	{
		if (msg.midParams.size() == 2 && count > 0 && i == count)
			break;
		if (msg.midParams[0] == (*userRBeginIt)->getNick())
		{
			message = (*userRBeginIt)->getNick() + " " + (*userRBeginIt)->getUser() \
			+ " " + (*userRBeginIt)->getHost() + " * :" + (*userRBeginIt)->getReal();
			replyMEss(RPL_WHOWASUSER, user, message);
			nickAbsenceFlag = 1;
		}
		userRBeginIt++;
		i++;
	}

	if (nickAbsenceFlag == 0)
		errorMEss(ERR_WASNOSUCHNICK, user, msg.midParams[0]);
	replyMEss(RPL_ENDOFWHOWAS, user, msg.midParams[0]);

	return 0;
}