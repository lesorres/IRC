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

#define DISCONNECT		1				// если количество параметров, необходимых для регистрации пользователя
										// не соответствует требуемому (!= 3), пользователь не должен подключаться

class Command;

void Command::pass(User &user, std::vector<User*>& userData) {
	std::cout << msg.midParams.size() << std::endl;
	if (msg.midParams.size() == 1) {
		if (user.getRegistred() == true) {
			std::cout << ":You may not reregister" << std::endl;
			return ERR_ALREADYREGISTRED;
		}
		else if (user.getPass().empty() == true) {
			user.setPass(msg.midParams[0]);
			std::cout << user.getPass() << std::endl;
		}
	}
	else {
		std::cout << msg.cmd << " :Not enough parameters" << std::endl;
		return ERR_NEEDMOREPARAMS;
	}
}

void Command::user(User &user, std::vector<User*>& userData){
	std::cout << msg.midParams.size() << std::endl;
	if (msg.midParams.size() < 3 && !msg.trailing.empty() ) { //) && msg.paramN != 4) { //msg.midParams.size() < 4
		std::cout << msg.cmd << " :Not enough parameters" << std::endl;
		return ERR_NEEDMOREPARAMS;
	}
	else if (user.getRegistred() == true ){
		std::cout << ":You may not reregister" << std::endl;
		return ERR_ALREADYREGISTRED;
	}
	else if (!user.getUser().empty() && !user.getHostn().empty() && \
			!user.getServern().empty() && !user.getRealn().empty()) {
		user.setUser(msg.midParams[0]);
		user.setHostn(msg.midParams[1]);
		user.setServern(msg.midParams[2]);
		user.setRealn(msg.trailing);
		if (user.getNick().empty() && user.getPass().empty())
			user.setRegistred(true);
		// std::cout << user.getUser() << "\n" << user.getRealn() << "\n" << user.getHostn() << "\n" << user.getServern() << std::endl;
	}
}

void Command::nick(User &user, std::vector<User*>& userData) {
	std::cout << msg.midParams.size() << std::endl;
	if (msg.midParams.size() < 1) {
		for (int i = 0; i < userData.size(); ++i){
			if (userData[i]->getNick() == msg.midParams[0]){
		    	std::cout << msg.midParams[0] << " :Nickname collision KILL" << std::endl;
		    	return ERR_NICKCOLLISION;
			}
		}
		if (msg.midParams[0].empty()) { //msg.paramN < 1
			std::cout << ":No nickname given" << std::endl;
			return ERR_NONICKNAMEGIVEN;
		}
		// else if (nickname.){
			// std::cout << "ERR_ERRONEUSNICKNAME" << std::endl;
		//     return ERR_ERRONEUSNICKNAME;
		// }
		else if (user.getNick() == msg.midParams[0]){
			std::cout << msg.midParams[0] << " :Nickname is already in use" << std::endl;
			return ERR_NICKNAMEINUSE;
		}
		else {
			if (msg.midParams.size() < 1 && user.getNick() != msg.midParams[0]){ 		//msg.midParams.size() < 1 или msg.midParams.empty()
				// записать предыдущий ник если пришел новый для замены: Для умеренной истории, серверу следует хранить предыдущие никнеймы для
				//   каждого известного ему клиента, если они все решатся их изменить. 
			}
			user.setNick(msg.midParams[0]);
		}
	}
}

void Command::oper(User &user, std::vector<User*>& userData){
//   Параметры: <user> <password>
	// std::string::size_type pos = msg.midParams[0].find(" ");
	// std::string usr = arg.substr(0, pos);
	// std::string pass = arg.substr(pos + 1);
	if (user.getNick() == msg.midParams[0] && user.getPass() == msg.midParams[1]){
		//  "MODE +o"
		std::cout << ":You are now an IRC operator" << std::endl;
		return RPL_YOUREOPER;
	}
	else if (msg.midParams.size() < 2) { //msg.midParams.size() < 2
		std::cout << msg.cmd << " :Not enough parameters" << std::endl;
		return ERR_NEEDMOREPARAMS;
	}
	else if (user.getPass() != msg.midParams[1]) {
		std::cout << ":Password incorrect" << std::endl;
		return ERR_PASSWDMISMATCH;
	}

}

void Command::quit(User &user, std::vector<User*>& userData){
	if (msg.trailing.empty())
		// std::cout <<  << std::endl;
	exit(1);
}

bool Command::connection(User &user){
	if (user.getRegistred() == true) {
		std::cout << "success! *send MOTD*" << std::endl;
		return 0;
	}
	return DISCONNECT;
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