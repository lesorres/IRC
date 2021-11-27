#include "Command.hpp"

std::string Command::parseMsg(std::string cmdStr)
{
	std::string tmp;
	std::string::iterator it_begin = cmdStr.begin();
	std::string::iterator it_end = cmdStr.end();
	
	// two whiles below work as strtrim function for cmdStr
	while (it_begin != it_end && *it_begin == ' ')
	{
		cmdStr.erase(it_begin);
		it_begin = cmdStr.begin();
	}
	while (it_end != it_begin && *it_end == ' ')
	{
		cmdStr.erase(it_begin);
		it_end = cmdStr.end();
	}

	// extracting prefix from msg if it is presented, moving irerator to the next token after prefix
	if (*it_begin == ':')
	{
		it_begin++;
		this->msg.prefx = std::string(it_begin, it_begin + cmdStr.find(' ') - 1);
		// it_begin = it_begin + cmdStr.find(' ');
	}

	// cutting unnecessary part of cmdStr from left side, moving iterator at the begining of new str
	tmp = cmdStr.substr(cmdStr.find(' ') + 1);
	cmdStr = tmp;
	it_begin = cmdStr.begin();

	// extracting command from msg if it is presented, moving irerator to the next token after message
	this->msg.cmd = std::string(it_begin, it_begin + tmp.find(' '));

	// extracting params from msg if it is presented, moving irerator to the next token after message
	// while (cmdStr.size() > 0)
	// {
		// if (cmdStr.find(' ') == std::string::npos)
		// 	break;

	tmp = cmdStr.substr(cmdStr.find(' ') + 1);
	cmdStr = tmp;
	it_begin = tmp.begin();
	this->msg.midParams.push_back(std::string(it_begin, it_begin + tmp.find(' ')));

	tmp = cmdStr.substr(cmdStr.find(' ') + 1);
	cmdStr = tmp;
	it_begin = tmp.begin();
	this->msg.midParams.push_back(std::string(it_begin, it_begin + tmp.find(' ')));

	tmp = cmdStr.substr(cmdStr.find(' ') + 1);
	cmdStr = tmp;
	it_begin = tmp.begin();
	this->msg.midParams.push_back(std::string(it_begin, it_begin + tmp.find(' ')));
	// }

	// check if command and at least one param are presented in message, return error
	// if (1)
	// {
	// }
	return (cmdStr);
}

std::string Command::getRidOfCmdName( std::string cmdStr ) {
    return cmdStr;
}

std::string checkCmdNameFormat( std::string cmdStr ) {
    return cmdStr;
}