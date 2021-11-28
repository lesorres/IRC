#include "Command.hpp"
#include <sstream>

std::string Command::parseMsg(std::string cmdStr)
{
	std::string parsed;
	std::stringstream input(cmdStr);

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