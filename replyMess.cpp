#include "Server.hpp"


#if __APPLE__
	#define IRC_NOSIGNAL SO_NOSIGPIPE
#else
	#define IRC_NOSIGNAL MSG_NOSIGNAL
#endif
            //    - При ответе на MOTD-сообщение и MOTD-файл найден, файл
                //  отбражается строка к строке с каждой строкой, не длше80
                //  символов, используя RPL_MOTD-формат ответов. Их следует
                //  разместить между RPL_MOTDSTART (перед RPL_MOTD) и
                //  RPL_ENDOFMOTD (после).

int Server::replyMEss(int reply, User &user, const std::string &str) {
	std::string mess = ":" + inf.serverName + " " + itos(reply) + " " + user.getNick() + " ";
	switch (reply)
	{
	case RPL_UMODEIS:
		mess += str + "\n";
		break ;
	case RPL_ADMINME:
		mess += inf.serverName + " :Admin name - " + inf.adminName + "\n";
		break ;
	case RPL_ADMINLOC1:
		mess += "Location - Kazan, Republic of Tatarstan, Russian Federation\n";
		break ;
	case RPL_ADMINEMAIL:
		mess += ":Admin email - " + inf.adminEmail + "\n";
		break ;
	case RPL_AWAY:
		mess += str + "\n";
		break ;
	case RPL_USERHOST:
		mess += ":" + str + "\n";
		break ;
	case RPL_ISON:
		mess += ":" + str + "\n";
		break ;
	case RPL_WHOISUSER:
		mess += str;
		break ;
	case RPL_WHOISSERVER:
		// mess += user.getNick() + " " + user.getServer() + ":";
		break ;
	case RPL_WHOISOPERATOR:
		mess += str + " :is an IRC operator\n";
		break ;
	case RPL_ENDOFWHO:
		mess += msg.midParams[0] + " :End of /WHO list\n";
		break ;
	case RPL_WHOISIDLE:
		// mess += user.getNick() + " <integer> :seconds idle\n";
		break ;
	case RPL_ENDOFWHOIS:
		mess += str + " :End of /WHOIS list\n";
		break ;
	case RPL_WHOISCHANNELS:
		mess += str + "\n";
		break ;
	case RPL_LISTSTART:
		mess += "Channel :Users Name\n";
		break ;
	case RPL_LIST:
		mess += str + "\n";
		break ;
	case RPL_LISTEND:
		mess += ":End of /LIST\n";
		break ;
	case RPL_CHANNELMODEIS:
		mess += str + "\n";
		break ;
	case RPL_NOTOPIC:
		mess += str + " :No topic is set\n" ;
		break ;
	case RPL_TOPIC:
		mess += str + "\n";
		break ;
	case RPL_INVITING:
		mess += str + "\n";
		break ;
	case RPL_VERSION:
		mess += inf.srvVersion + ".1 " + inf.serverName + " :RFC 1459  | May 1993\n";
		break ;
	case RPL_WHOREPLY:
		mess += str;
		break ;
	case RPL_NAMREPLY:
		mess += str + "\n";
		break ;
	case RPL_ENDOFNAMES:
		mess += str + " :End of /NAMES list\n";
		break ;
	case RPL_BANLIST:
		mess += str + " <banid>\n";
		break ;
	case RPL_ENDOFBANLIST:
		mess += str + " :End of channel ban list\n";
		break ;
	case RPL_INFO:
		mess += ":" + str;
		break ;
	case RPL_MOTD:
		mess += ":- " + str + "\n";
		break ;
	case RPL_ENDOFINFO:
		mess += ":End of /INFO list\n";
		break ;
	case RPL_MOTDSTART:
		mess += ":- " + inf.serverName + " Message of the day - \n";
		break ;
	case RPL_ENDOFMOTD:
		mess += ":End of /MOTD command\n"	;
		break ;
	case RPL_YOUREOPER:
		mess += ":You are now an IRC operator\n";
		break;
	case RPL_REHASHING:
		mess += CONF_NAME;
		mess += " :Rehashing\n";
		break ;
	case RPL_TIME:
		mess += inf.serverName + " :Local time - " + str;
	}
	send(user.getFd(), mess.c_str(), mess.size(), IRC_NOSIGNAL);
	return 0;
}