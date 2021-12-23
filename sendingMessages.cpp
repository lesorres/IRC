#include "Server.hpp"

// +411 ERR_NORECIPIENT			412 ERR_NOTEXTTOSEND
// 404 ERR_CANNOTSENDTOCHAN		413 ERR_NOTOPLEVEL
// 414 ERR_WILDTOPLEVEL			407 ERR_TOOMANYTARGETS
// +401 ERR_NOSUCHNICK
// 301 RPL_AWAY

int Server::privmsg( User & user )
{
	std::string message;
	std::vector<std::string>::iterator paramIt = msg.midParams.begin();
	std::vector<std::string>::iterator endPramIt = msg.midParams.end();
	std::vector<User *>::iterator userIt = userData.begin();
	std::vector<User *>::iterator endUserIt = userData.end();
	std::map<std::string, Channel *>::iterator chnIt = channels.begin();
	std::map<std::string, Channel *>::iterator endChnt = channels.end();
	std::vector<User *>::iterator chnUsersIt;
	std::vector<User *>::iterator endChnUsersIt;

	bool absenceFlag;

	if (msg.midParams.size() < 1)
		return (errorMEss(ERR_NORECIPIENT, user, "PRIVMSG"));

	while (paramIt != endPramIt)
	{
		absenceFlag = 0;
		//for channels:
		if ((*paramIt)[0] == '#' && (*paramIt).find('.') == std::string::npos)
		{
			while (chnIt != endChnt)
			{
				chnUsersIt = chnIt->second->getUserList().begin();
				endChnUsersIt = chnIt->second->getUserList();
				while (/* condition */)
				{
					/* code */
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

				}
				else if ((*userIt)->getNick() == *paramIt)
				{

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