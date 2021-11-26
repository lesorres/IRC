#include "Command.hpp"


//pass + user
#define ERR_NEEDMOREPARAMS 
#define ERR_ALREADYREGISTRED //462      //":You may not reregister"
                                        // - Возвращается сервером любому линку, который пытается
                                        //  изменить часть подробностей регистрации (подобные паролю
                                        //  или пользовательской информацией из второго
                                        //  USER-сообщения).

//nick
#define ERR_NONICKNAMEGIVEN //431       // ":No nickname given"
#define ERR_ERRONEUSNICKNAME //432      // "<nick> :Erroneus nickname"
                                        // - Возвращается после получения NICK-сообщения, которое
                                        // содержит символы, которые запрещены. Смотрите раздел
                                        // х.х.х для более подробной информации.
#define ERR_NICKNAMEINUSE //433         // "<nick> :Nickname is already in use"
                                        // Возвращается при смене никнейма на другой, уже используемый.
#define ERR_NICKCOLLISION //436         // "<nick> :Nickname collision KILL"
                                        //  - Возвращается сервером к клиенту, когда сервер видит
                                        //  конфликт никнейма (зарегистрированный никнейм уже есть).

void Command::pass(std::string const password, User &user) {
	if (password.empty()){
		std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
		return ERR_NEEDMOREPARAMS;
	}
	else if (user.getRegistred() == true){
		std::cout << "ERR_ALREADYREGISTRED" << std::endl;
		return ERR_ALREADYREGISTRED;
	}
	else{
		user.setPass(password);
		std::cout << user.getPass() << std::endl;
	}
}

void Command::user(std::string const username, User &user){
	if (username.empty()) {
		std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
		return ERR_NEEDMOREPARAMS;
	}
	else if (user.getRegistred() == true){
		std::cout << "ERR_ALREADYREGISTRED" << std::endl;
		return ERR_ALREADYREGISTRED;
	}
	else {
		user.setUser(username);
		user.setRealn(username);
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

std::string Command::removeCmd(std::string str){
	std::string tmp;
	std::string::size_type pos = str.find(" ");
	tmp = str.substr(pos + 1);
	return tmp;
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
				std::cout << "after removeCmd - " << tmp << std::endl;
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