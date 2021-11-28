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

class Command;

void Command::pass(std::string const & password, User &user) {
	if (password.empty()){
		std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
		return ERR_NEEDMOREPARAMS;
	}
	else if (user.getRegistred() == true){
		std::cout << "ERR_ALREADYREGISTRED" << std::endl;
		return ERR_ALREADYREGISTRED;
	}
	else {
		user.setPass(password);
		std::cout << user.getPass() << std::endl;
	}
}

void Command::user(std::string const & username, User &user){
//	Параметры: <username> <hostname> <servername> <realname>
	std::string names[4];
	std::string tmp;
	int k = 0;
	std::size_t pos = username.find(" ");
	names[0] = username.substr(k, pos);
	std::cout << names[0] << std::endl;
	tmp = username.substr(pos + 1);
	for (int i = 1; i < 4; ++i){
		pos = tmp.find(" ");
		names[i] = tmp.substr(0, pos);
		tmp = tmp.substr(pos + 1);
		std::cout << names[i] << std::endl;
	}
	if (username.empty()) { //msg.midParams.size() < 4
		std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
		return ERR_NEEDMOREPARAMS;
	}
	else if (user.getRegistred() == true ){
		std::cout << "ERR_ALREADYREGISTRED" << std::endl;
		return ERR_ALREADYREGISTRED;
	}
	else {
		// user.setUser(msg.midParams.at(0));
		// user.setRealn(msg.midParams.at(1));
		// user.setHostn(msg.midParams.at(2));
		// user.setRealn(msg.midParams.at(3));
		user.setUser(names[0]);
		user.setHostn(names[1]);
		user.setServern(names[2]);
		user.setRealn(names[3]);
		// std::cout << user.getUser() << "\n" << user.getRealn() << "\n" << user.getHostn() << "\n" << user.getServern() << std::endl;
	}
}

void Command::nick(std::string const & str, User &user) {
	std::cout << str << std::endl;
	for (int i = 0; i < userData.size(); ++i){
		if (this->userData[i]->getNick() == str){
	    	std::cout << "ERR_NICKCOLLISION" << std::endl;
	    	return ERR_NICKCOLLISION;
		}
	}

	if (str.empty() && str.data()) { //msg.paramN < 1
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
	else {
		if (user.getNick().empty() == false && user.getNick() != str){ 		//msg.midParams.size() < 1 или msg.midParams.empty()
			// записать предыдущий ник если пришел новый для замены: Для умеренной истории, серверу следует хранить предыдущие никнеймы для
			//   каждого известного ему клиента, если они все решатся их изменить. 
		}
		user.setNick(str);
	}
	std::cout << user.getNick() << std::endl;
}

void Command::oper(std::string const & arg, User &user){
//   Параметры: <user> <password>
	std::string::size_type pos = arg.find(" ");
	std::string usr = arg.substr(0, pos);
	std::string pass = arg.substr(pos + 1);
	if (user.getNick() == usr && user.getPass() == pass){
		//  "MODE +o"
		std::cout << ":You are now an IRC operator" << std::endl;
		return RPL_YOUREOPER;
	}
	else if (arg.empty()) { //msg.midParams.size() < 4
		std::cout << "ERR_NEEDMOREPARAMS" << std::endl;
		return ERR_NEEDMOREPARAMS;
	}
	else if (user.getPass() != pass) {
		std::cout << ":Password incorrect" << std::endl;
		return ERR_PASSWDMISMATCH;
	}

}

void Command::quit(std::string const & arg, User &user){
	if (arg.empty())
		std::cout << arg << std::endl;
	exit(1);
}

std::string Command::removeCmd(std::string str){
	std::string tmp;
	std::string::size_type pos = str.find(" ");
	if (pos == std::string::npos)
		tmp = "";
	else
		tmp = str.substr(pos + 1);
	std::cout << "comandline after removeCmd - " << tmp << std::endl;
	return tmp;
}

// int main() {
// 	std::string cmdline;
// 	User *user = new User;
// 	Command cmd;
// 	int i = 0;
// 	cmd.getUserData().push_back(user);
// 	std::getline(std::cin, cmdline);
// 	std::string::size_type pos = cmdline.find(" ");
// 	std::string command = cmdline.substr(0, pos);  //строка для сравнения команды
// 	std::cout << "this is cmd     - " << cmdline << std::endl;
// 	std::cout << "this is command - " << command << std::endl;
// 		if (cmdline.empty())
// 			std::cerr << "Invalid arguments" << std::endl;
// 		else {
// 			std::string tmp;
// 			if (!command.compare("pass")){
// 				tmp = cmd.removeCmd(cmdline);  // удаление названия команды из пришедшей строки
// 				cmd.pass(tmp, *user);
// 			}
// 			else if (!command.compare("nick")){
// 				tmp = cmd.removeCmd(cmdline);   // удаление названия команды из пришедшей строки
// 				cmd.nick(tmp, *user);
// 			}
// 			else if (!command.compare("user")){
// 				tmp = cmd.removeCmd(cmdline);   // удаление названия команды из пришедшей строки
// 				cmd.user(tmp, *user);
// 			}
// 			else if (!command.compare("oper")){
// 				tmp = cmd.removeCmd(cmdline);
// 				cmd.oper(tmp, *user);
// 			}
// 			else if (!command.compare("quit")){
// 				tmp = cmd.removeCmd(cmdline);
// 				cmd.quit(tmp, *user);
// 			}
// 	}
// }