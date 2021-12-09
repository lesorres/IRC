  #include "Server.hpp"
#include <sstream>

int Server::parseMsg(std::string cmdStr)
{
	std::string parsed;
	std::stringstream input(cmdStr);
	std::vector<std::string>::iterator trailingIt;
	std::vector<std::string>::iterator cutIt;

	//check message length
	if (cmdStr.size() > 510)
	{
		std::cout << "message length exceeded allowed value of 510 symbols\n";
		return (1);
	}

	//the loop below split string to tokens separated by space
	while (std::getline(input, parsed, ' '))
	{
		if (!parsed.empty())
		{
			if (msg.prefx.empty() && parsed[0] == ':')
				msg.prefx = parsed;
			else if (msg.cmd.empty())
				msg.cmd = parsed;
			else
				msg.midParams.push_back(parsed);
		}
	}
	//identifying if trailing is presented amond mid parameters
	trailingIt = msg.midParams.begin();
	while (trailingIt != msg.midParams.end())
	{
		if ((*trailingIt)[0] == ':')
			break;
		trailingIt++;
	}

	//saving iterator in vector to the trailing part
	cutIt = trailingIt;

	//rewriting all midparams from vector to trailing attribute (starting from first token with ':')
	while (trailingIt != msg.midParams.end())
	{
		msg.trailing += " " + *trailingIt;
		trailingIt++;
	}

	//removing one spase at the begining of trailing
	if (!msg.trailing.empty())
		msg.trailing.erase(msg.trailing.begin());

	// removing trailing part from mid params array
	if (!msg.midParams.empty())
		msg.midParams.erase(cutIt, msg.midParams.end());

	msg.paramN = msg.midParams.size() + !msg.trailing.empty();

	//check tokents validity
	if (checkMsgFormat(cmdStr))
		return(1);

	return (0);
}

int Server::checkMsgFormat( std::string cmdStr )
{
	if ((msg.midParams.size() > 14 && !msg.trailing.empty()) || \
	(msg.midParams.size() > 15 && msg.trailing.empty()))
	{
		std::cout << "number of parameters (including trailing) exceeded allowed value of 15\n";
		return (1);
	}
	if (msg.cmd.empty() && (!msg.prefx.empty() || !msg.midParams.empty() || !msg.trailing.empty()))
	{
		std::cout << "invalid format of message\n";
		return (1);
	}
	// if ()
	// {
	// 	return (1);
	// }
	return (0);
}

void Server::cleanMsgStruct()
{
	msg.prefx.clear();
	msg.cmd.clear();
	msg.midParams.clear();
	msg.trailing.clear();
	msg.paramN = 0;
}

void Server::processWildcard()
{
	
}