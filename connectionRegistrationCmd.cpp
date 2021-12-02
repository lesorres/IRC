#include "Command.hpp"

#define ERR_NOTREGISTERED 451 //":You have not registered"

//pass + user
#define ERR_NEEDMOREPARAMS 461
#define ERR_ALREADYREGISTRED 462        //":You may not reregister"
                                        // - Возвращается сервером любому линку, который пытается
                                        //  изменить часть подробностей регистрации (подобные паролю
                                        //  или пользовательской информацией из второго
                                        //  USER-сообщения).

//oper
 #define ERR_PASSWDMISMATCH 464 //":Password incorrect"

//nick
#define ERR_NONICKNAMEGIVEN 431         // ":No nickname given"
#define ERR_ERRONEUSNICKNAME 432        // "<nick> :Erroneus nickname"
                                        // - Возвращается после получения NICK-сообщения, которое
                                        // содержит символы, которые запрещены. Смотрите раздел
                                        // х.х.х для более подробной информации.
#define ERR_NICKNAMEINUSE 433           // "<nick> :Nickname is already in use"
                                        // Возвращается при смене никнейма на другой, уже используемый.
#define ERR_NICKCOLLISION 436           // "<nick> :Nickname collision KILL"
                                        //  - Возвращается сервером к клиенту, когда сервер видит
                                        //  конфликт никнейма (зарегистрированный никнейм уже есть).
#define ERR_NOOPERHOST 491				// ":No O-lines for your host"
										// - Если сервер не настроен на поддержку клиентского хоста
                						//  для сообщения OPER, клиенту будет возвращена эта ошибка.
#define DISCONNECT		1				// если количество параметров, необходимых для регистрации пользователя
										// не соответствует требуемому (!= 3), пользователь не должен подключаться

class Command;

int Command::pass(User &user, std::vector<User*>& userData) {
	if (msg.midParams.size() == 1) {
		if (user.getRegistred() == 3) {
			errorMEss(462, user);
			// std::cout << ":You may not reregister" << std::endl;
			// return ERR_ALREADYREGISTRED;
		}
		else if (user.getPass().empty() == true) {
			user.setPass(msg.midParams[0]);
			user.setRegistred(user.getRegistred() + 1);
			// if (user.getNick().empty() && user.getRealn().empty() && user.getUser().empty())
				// user.setRegistred(true);
		}
	}
	else if (msg.midParams.size() < 1) {
		// send(user.getFd(), errorMEss(461, user).c_str(), errorMEss(461, user).size(), 0);
		errorMEss(461, user);
		// std::cout << msg.cmd << " :Not enough parameters" << std::endl;
		// return ERR_NEEDMOREPARAMS;
	}
	return connection(user);
}

int Command::user(User &user, std::vector<User*>& userData){
	if (msg.midParams.size() < 3 && !msg.trailing.empty() ) { //) && msg.paramN != 4) { //msg.midParams.size() < 4
		// send(user.getFd(), errorMEss(461, user).c_str(), errorMEss(461, user).size(), 0);
		errorMEss(461, user);
		// std::cout << msg.cmd << " :Not enough parameters" << std::endl;
		// return ERR_NEEDMOREPARAMS;
	}
	else if (user.getRegistred() == 3){
		errorMEss(462, user);
		// std::cout << ":You may not reregister" << std::endl;
		// return ERR_ALREADYREGISTRED;
	}
	else if (user.getUser().empty() && user.getHostn().empty() && \
			user.getServern().empty() && user.getRealn().empty()) {
		user.setUser(msg.midParams[0]);
		user.setHostn(msg.midParams[1]);
		user.setServern(msg.midParams[2]);
		user.setRealn(msg.trailing);
		user.setRegistred(user.getRegistred() + 1);
	}
	return connection(user);
}

int Command::nick(User &user, std::vector<User*>& userData) {
	if (msg.midParams.size() == 1) {
		for (int i = 0; i < userData.size(); ++i) {
			if (userData[i]->getNick() == msg.midParams[0]){
				// send(user.getFd(), errorMEss(436, user).c_str(), errorMEss(461, user).size(), 0);
				errorMEss(436, user);
		    	// std::cout << msg.midParams[0] << " :Nickname collision KILL" << std::endl;
		    	// return ERR_NICKCOLLISION;
			}
		}
		if (user.getNick() == msg.midParams[0]) {
			// send(user.getFd(), errorMEss(433, user).c_str(), errorMEss(461, user).size(), 0);
			errorMEss(433, user);
			// std::cout << msg.midParams[0] << " :Nickname is already in use" << std::endl;
			// return ERR_NICKNAMEINUSE;
		}
		if (user.getNick().empty() == true ) { // != msg.midParams[0]) { 		//msg.midParams.size() < 1 или msg.midParams.empty()
			user.setNick(msg.midParams[0]);
			user.setRegistred(user.getRegistred() + 1);
		}
		else {
			// записать предыдущий ник если пришел новый для замены: Для умеренной истории, серверу следует хранить предыдущие никнеймы для
			//   каждого известного ему клиента, если они все решатся их изменить. 
			user.setNick(msg.midParams[0]);

		}
		// std::cout << user.getRegistred() << std::endl;
		// if (user.getPass().empty() && user.getRealn().empty() && user.getUser().empty())
			// user.setRegistred(true);

		// else if (msg.midParams[0].){
			// std::cout << "ERR_ERRONEUSNICKNAME" << std::endl;
		//     return ERR_ERRONEUSNICKNAME;
		// }
	}
	else {
		if (msg.midParams.size() < 1 ) {
			errorMEss(431, user);
			// std::cout << ":No nickname given" << std::endl;
			// return ERR_NONICKNAMEGIVEN;
		}
	}
	return connection(user);
}

int Command::oper(User &user, std::vector<User*>& userData){
	if (user.getNick() == msg.midParams[0] && user.getPass() == msg.midParams[1]){
		//  "MODE +o"
		std::cout << ":You are now an IRC operator" << std::endl;
		// return RPL_YOUREOPER;
	}
	else if (msg.midParams.size() < 2) { //msg.midParams.size() < 2
		errorMEss(461, user);
		// std::cout << msg.cmd << " :Not enough parameters" << std::endl;
		// return ERR_NEEDMOREPARAMS;
	}
	else if (user.getPass() != msg.midParams[1]) {
		errorMEss(464, user);
		// std::cout << ":Password incorrect" << std::endl;
		// return ERR_PASSWDMISMATCH;
	}
	return 0;
}

int Command::quit(User &user, std::vector<User*>& userData){
	if (msg.trailing.empty())
		// std::cout <<  << std::endl;
	exit(1);
	return 0;
}

bool Command::connection(User &user){
	if (user.getRegistred() == 3) {
		std::cout << "success! *send MOTD*" << std::endl;
		return 0;
	}
	return DISCONNECT;
}