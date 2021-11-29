#include "Command.hpp"
#include <sstream>

std::string Command::parseMsg(std::string cmdStr)
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
			if (this->msg.prefx.empty() && parsed[0] == ':')
				this->msg.prefx = parsed;
			else if (this->msg.cmd.empty())
				this->msg.cmd = parsed;
			else
				this->msg.midParams.push_back(parsed);
		}
	}

	//identifying if trailing is presented amond mid parameters
	trailingIt = this->msg.midParams.begin();
	while (trailingIt != this->msg.midParams.end())
	{
		if ((*trailingIt)[0] == ':')
			break;
		trailingIt++;
	}

	//saving iterator to the trailing part in vector
	cutIt = trailingIt;

	//rewriting all mid params from vector to prefix attribute beginning from one with ':'
	while (trailingIt != this->msg.midParams.end())
	{
		this->msg.trailing += " " + *trailingIt;
		trailingIt++;
	}
	this->msg.trailing.erase(this->msg.trailing.begin());

	// cuting trailing part from mid params array
	this->msg.midParams.erase(cutIt, this->msg.midParams.end());

	// // check if command and at least one param are presented in message, return error
	// // if (1)
	// // {
	// // }
	return (cmdStr);
}

std::string Command::getRidOfCmdName( std::string cmdStr ) {
    return cmdStr;
}

std::string checkCmdNameFormat( std::string cmdStr ) {
    return cmdStr;
}