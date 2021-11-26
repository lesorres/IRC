#include "Command.hpp"

std::string Command::parseMsg( std::string cmdStr )
{
	std::string tmp;
	std::string::iterator it_begin = cmdStr.begin();
	std::string::iterator it_end = cmdStr.end();
	
	while (*it_begin == ' ')
	{
		cmdStr.erase(it_begin);
		it_begin++;
	}
	while (*it_end == ' ')
	{
		cmdStr.erase(it_begin);
		it_end--;
	}
	if ( *it_begin == ':')
	{
		it_begin++;
		this->msg.prefx = std::string();
	}
	while ( it_begin != it_end)
	{
			
	}
}

std::string Command::getRidOfCmdName( std::string cmdStr ) {
    return cmdStr;
}

std::string checkCmdNameFormat( std::string cmdStr ) {
    return cmdStr;
}
