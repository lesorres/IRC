#include "Command.hpp"

std::string Command::parseMsg( std::string cmdStr )
{
	std::string tmp;
	std::string::iterator it_begin = cmdStr.begin();
	std::string::iterator it_end = cmdStr.end();
	
	// two whiles below work as strtrim

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
	if ( *it_begin == ':')
	{
		it_begin++;
		this->msg.prefx = std::string(it_begin, it_begin + cmdStr.find(' ') - 1);
		it_begin = it_begin + cmdStr.find(' ');
	}
	this->msg.cmd = std::string(it_begin, it_begin + cmdStr.find(' '));
	it_begin = it_begin + cmdStr.find(' ') + 1;
	while ( it_begin != it_end)
	{
		
	}
	return (cmdStr);
}

std::string Command::getRidOfCmdName( std::string cmdStr ) {
    return cmdStr;
}

std::string checkCmdNameFormat( std::string cmdStr ) {
    return cmdStr;
}
