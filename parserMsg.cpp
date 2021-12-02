#include "Server.hpp"
#include <sstream>

std::string Server::parseMsg(std::string cmdStr)
{
	std::string parsed;
	std::stringstream input(cmdStr);
	std::vector<std::string>::iterator trailingIt;
	std::vector<std::string>::iterator cutIt;

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

	// // check if Server and at least one param are presented in message, return error
	// // if (1)
	// // {
	// // }
	return (cmdStr);
}

std::string Server::getRidOfCmdName( std::string cmdStr ) {
    return cmdStr;
}

std::string checkCmdNameFormat( std::string cmdStr ) {
    return cmdStr;
}