#include "Command.hpp"

Command::Command(){
}

// //коструктор для Server
// Command::Command(Server &serv) : userData(serv.getUserData()) {
//     // setUserData(serv.getUserData());
// }

Command::~Command(){}

void Command::pass(std::string const password, User &user) {
    if (password.empty()){
        std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
        return ERR_NEEDMOREPARAMS;
    }
    else if (user.getPass() == password){
        std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
        return ERR_ALREADYREGISTRED;
    }
    else{
        user.setPass(password);
        std::cout << user.getPass() << std::endl;
    }
}

void Command::nick(std::string const str, User &user) {
    // std::vector<User *>::iterator it = userData.begin();
    // for ( ; it < userData.end(); ++it) {
    //     if ((*it)->getNick() == str)
    //         break ;
    // }

    if (str.empty() && str.data()) {
        std::cout << "ERR_NONICKNAMEGIVEN" << std::endl;
        return ERR_NONICKNAMEGIVEN;
    }
    // else if (nickname.){
        // std::cout << "ERR_ERRONEUSNICKNAME" << std::endl;
    //     return ERR_ERRONEUSNICKNAME;
    // }
    else if (user.getNick() == str){
        std::cout << "ERR_NICKNAMEINUSE" << std::endl;
        return ERR_NICKNAMEINUSE;
    }
    // else if ((*it)->getNick() == str){
    //     std::cout << "ERR_NICKCOLLISION" << std::endl;
    //     return ERR_NICKCOLLISION;
    // }
    else
        user.setNick(str);
    std::cout << user.getNick() << std::endl;
}

void Command::user(std::string const nickname, User &user){
    (void)nickname;
    user.getUser();
    std::cout << "this is user method" << std::endl;
}


void Command::setUserData(std::vector<User*>&userData){
    this->userData = userData;
}

std::string Command::removeCmd(std::string str){
    std::string::size_type pos = str.find(" ");
    str.substr(pos + 1);
    return str;
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

int main() {
    std::string cmdline;
    User user;
    Command cmd;
    int i = 0;
    std::getline(std::cin, cmdline);
    std::string::size_type pos = cmdline.find(" ");
    std::string command = cmdline.substr(0, pos);  //строка для сравнения команды
    std::cout << "this is command - " << command << std::endl;
    std::cout << "this is cmd     - " << cmdline << std::endl;
    while (i < 5) {
        if (cmdline.empty())
            std::cerr << "Invalid arguments" << std::endl;
        else {
            std::string tmp;
            if (!command.compare("pass")){
                // std::cout << "this is pass" << std::endl;
                tmp = cmd.removeCmd(cmdline);  // удаление названия команды из пришедшей строки
                cmd.pass(tmp, user);
            }
            else if (!command.compare("nick")){
                // std::cout << "this is nick" << std::endl;
                tmp = cmd.removeCmd(cmdline);   // удаление названия команды из пришедшей строки
                cmd.nick(tmp, user);
            }
            else if (!command.compare("user")){
                // std::cout << "this is user" << std::endl;
                tmp = cmd.removeCmd(cmdline);   // удаление названия команды из пришедшей строки
                cmd.user(tmp, user);
            }
            i++;
        }
    }
}