#include "Command.hpp"

Command::Command(){
}

// //коструктор для Server
// Command::Command(Server &serv) : userData(serv.getUserData()) {
//     // setUserData(serv.getUserData());
// }

Command::~Command(){}

void Command::setUserData(std::vector<User*>&userData){
    this->userData = userData;
}

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
		this->msg.prefx = std::string()
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

static void who( std::string const , User & ) {
	
}

static void whois( std::string const , User & ) {
	
}

static void whowas( std::string const , User & ) {
	
}