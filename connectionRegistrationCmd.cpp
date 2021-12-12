#include "Server.hpp"

#define DISCONNECT		1				// если количество параметров, необходимых для регистрации пользователя
										// не соответствует требуемому (!= 3), пользователь не должен подключаться

bool Server::validNick(User &user) {
	std::string str = msg.midParams[0];
	std::string::iterator it = str.begin();
	if (!std::isalpha(*it))
		return false;
	for ( ; it != str.end(); ++it)	{
		if (!std::isalnum(*it) && *it != '-' && (*it != '[' \
			&& *it != ']' && *it != '\\' && *it !=  '`' \
			&& *it != '^' && *it != '{' && *it !=  '}')) {
				return false;
			}
	}
	return true;
}

int Server::pass(User &user) {
	if (msg.midParams.size() == 1 || !msg.trailing.empty()) {
		if (user.getRegistred() == 3)
			errorMEss(462, user);
		else if (user.getPass().empty() == true) {
			if (msg.trailing.empty())
				user.setPass(msg.midParams[0]);
			else
				user.setPass(msg.trailing);
			if (user.getPass() != srvPass)
				killUser(user);
			user.setRegistred(user.getRegistred() + 1);
			return connection(user);
		}
	}
	else if (msg.midParams.size() < 1)
		errorMEss(461, user);
	return DISCONNECT;
}

int Server::user(User &user){
	if (!((msg.midParams.size() == 3 && !msg.trailing.empty()) \
	|| (msg.midParams.size() == 4 && msg.trailing.empty())))
		errorMEss(461, user);
	else if (user.getRegistred() == 3)
		errorMEss(462, user);
	else if (user.getUser().empty() && user.getHostn().empty() && \
			user.getServern().empty() && user.getRealn().empty()) {
		user.setUser(msg.midParams[0]);
		user.setHostn(msg.midParams[1]);
		user.setServern(msg.midParams[2]);
		if (msg.trailing.empty())
			user.setRealn(msg.midParams[3]);
		else
			user.setRealn(msg.trailing);
		user.setRegistred(user.getRegistred() + 1);
		return connection(user);
	}
	return DISCONNECT;
}

int Server::nick(User &user) {
	std::cout << validNick(user) << std::endl;
	if (msg.midParams.size() == 1) {
		for (int i = 0; i < userData.size(); ++i) {
			if (userData[i]->getNick() == msg.midParams[0])
				errorMEss(436, user);
		}
		if (user.getNick() == msg.midParams[0]) {
			errorMEss(433, user);
		}
		else if (msg.midParams[0].size() > 9 || validNick(user) == false){
			errorMEss(432, user);
		}
		else {
			if (user.getNick().empty() == true ) {
				user.setNick(msg.midParams[0]);
				user.setRegistred(user.getRegistred() + 1);
				return connection(user);
			}
			else if (user.getNick().empty() == false ) {
				history.push_back(new User(user));
				user.setNick(msg.midParams[0]);
				printUserVector(history);
				printUserVector(userData);
			}
		}
	}
	else {
		if (msg.midParams.size() < 1 )
			errorMEss(431, user);
	}
	return DISCONNECT;
}

int Server::oper(User &user) {
	if (user.getNick() == msg.midParams[0] && user.getPass() == msg.midParams[1])
		replyMEss(381, user);
	else if (msg.midParams.size() < 2)
		errorMEss(461, user);
	else if (user.getPass() != msg.midParams[1]) {
		errorMEss(464, user);
	}
	return DISCONNECT;
}

int Server::quit(User &user){
	history.push_back(new User(user));
	if (!msg.trailing.empty()) 
		(*(history.end() - 1))->setQuitMess(msg.trailing);
	killUser(user);
	return DISCONNECT;
}

void Server::motd(User &user) {
	std::ifstream infile("conf/ircd.motd");
	if (infile) {
		std::string message;
		replyMEss(375, user, message);
		while (std::getline(infile, message))
			replyMEss(372, user, message);
		replyMEss(376, user, message);
	}
	else
		errorMEss(422, user);
}

int Server::connection(User &user) {
	if (user.getRegistred() == 3) {
		motd(user);
		return 1;
	}
	return -1;
}

bool Server::notRegistr(User &user) {
	if (user.getRegistred() != 3 && (msg.cmd != "USER" && msg.cmd != "PASS" && msg.cmd != "NICK")) {
		errorMEss(451, user);
		return true;
	}
	return false;
}