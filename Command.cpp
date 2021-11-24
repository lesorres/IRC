#include "Command.hpp"

void Command::pass(std::string const password, User &user) {
	if (password.empty())
		return ERR_NEEDMOREPARAMS;
	else if (user.getPass() == password)
		return ERR_ALREADYREGISTRED;
	else
		user.setPass(password);
}

void Command::nick(std::string const nickname, User &user) {
	std::vector<User *>::iterator it = userData.begin();
	for ( ; it < userData.end(); ++it) {
		if ((*it)->getNick() == nickname)
			break ;
	}
	if (nickname.empty())
		return ERR_NONICKNAMEGIVEN;
	// else if (nickname.)
	//     return ERR_ERRONEUSNICKNAME;
	else if (user.getNick() == nickname)
		return ERR_NICKNAMEINUSE;
	else if ((*it)->getNick() == nickname)
		return ERR_NICKCOLLISION;
	else
		user.setNick(nickname);
}

void Command::user(std::string const nickname, User &user){

}

int main(int args, char **argv) {
	User user;
	if (args < 2)
		std::cerr << "Invalid arguments" << std::endl;
	else {
		Command::pass(argv[1], user);
	}
}

void Command::setUserData(std::vector<User*>&userData){
	this->userData = userData;
}
std::string parseMsg( std::string cmdStr )
{
	std::string tmp;
	std::string::iterator it_begin = cmdStr.begin();
	std::string::iterator it_end = cmdStr.end();
	
	while (*it_begin == ' ')
		it_begin++;
	while (*it_end == ' ')
		it_end--;
	tmp = cmdStr.substr()
}
std::string Command::getRidOfCmdName( std::string cmdStr )
{

}
std::string checkCmdNameFormat( std::string cmdStr )
{

}
static void who( std::string const , User & )
{
	
}
static void whois( std::string const , User & )
{
	
}
static void whowas( std::string const , User & )
{
	
}