#include "Server.hpp"

// +411 ERR_NORECIPIENT			412 ERR_NOTEXTTOSEND
// 404 ERR_CANNOTSENDTOCHAN		413 ERR_NOTOPLEVEL
// 414 ERR_WILDTOPLEVEL			407 ERR_TOOMANYTARGETS
// +401 ERR_NOSUCHNICK
// 301 RPL_AWAY


static int checkMask(std::string str)
{
	std::string::iterator strIt;
	std::string::iterator strEndIt;
	if(str[0] != '#' && str[0] != '$')
		return(1);
	strIt = str.begin() + str.rfind(".");
	strEndIt = str.end();
	while (strIt != strEndIt)
	{
		if (*strIt == '*')
			return (1);
		strIt++;
	}
	return (0);
}

int Server::privmsg( User & user )
{
	std::string mess = msg.trailing;
	std::vector<std::string>::iterator paramIt = msg.midParams.begin();
	std::vector<std::string>::iterator endPramIt = msg.midParams.end();
	std::vector<User *>::iterator userIt = userData.begin();
	std::vector<User *>::iterator endUserIt = userData.end();
	std::map<std::string, Channel *>::iterator chnIt = channels.begin();
	std::map<std::string, Channel *>::iterator endChnIt = channels.end();

	std::vector<User *> chnUsers;
	bool absenceFlag;

	if (msg.midParams.size() < 1)
		return (errorMEss(ERR_NORECIPIENT, user, "PRIVMSG"));
	while (paramIt != endPramIt)
	{
		absenceFlag = 0;
		//for channels:
		if ((*paramIt)[0] == '#' && (*paramIt).find('.') == std::string::npos)
		{
			while (chnIt != endChnIt)
			{
				std::cout << "here\n";
				if ((*paramIt) == chnIt->first)
				{
					// !!!!! добавить проверки на различные флаги для ERR_CANNOTSENDTOCHAN
					// chnUsers = chnIt->second->getUserList();
					// for (size_t i = 0; i < chnUsers.size(); i++)
					// {
						showMEss(user, chnIt->second);
					// }
					absenceFlag = 1;
				}
				chnIt++;
			}
			if (absenceFlag == 0)
				errorMEss(ERR_NOSUCHNICK, user, *paramIt);
			paramIt++;
		}
		//for nicks, users, host masks and server masks:
		else
		{
			while (userIt != endUserIt)
			{
				if ((*userIt)->getNick() == *paramIt)
				{
					absenceFlag = 1;
					showMEss(user, **userIt);
					// send((*userIt)->getFd(), mess.c_str(), mess.size(), IRC_NOSIGNAL);
				}
				else if ((*userIt)->getUser() == *paramIt)
				{
					absenceFlag = 1;
					showMEss(user, **userIt);
					// send((*userIt)->getFd(), mess.c_str(), mess.size(), IRC_NOSIGNAL);
				}
				else if(checkMask(*paramIt) && (*paramIt)[0] == '#' && checkWildcard((*userIt)->getHost().c_str(), (*paramIt).c_str()))
				{
					absenceFlag = 1;
					showMEss(user, **userIt);
					// send((*userIt)->getFd(), mess.c_str(), mess.size(), IRC_NOSIGNAL);
				}
				else if(checkMask(*paramIt) && (*paramIt)[0] == '$' && checkWildcard((*userIt)->getServer().c_str(), (*paramIt).c_str()))
				{
					absenceFlag = 1;
					showMEss(user, **userIt);
					// send((*userIt)->getFd(), mess.c_str(), mess.size(), IRC_NOSIGNAL);
				}
				userIt++;
			}
			if (absenceFlag == 0)
				errorMEss(ERR_NOSUCHNICK, user, *paramIt);
			paramIt++;
		}
	}
	return(0);
}