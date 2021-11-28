#ifndef COMMAND_HPP
# define COMMAND_HPP

//pass
#define ERR_NEEDMOREPARAMS 
#define ERR_ALREADYREGISTRED
//nick
#define ERR_NONICKNAMEGIVEN //431      // ":No nickname given"
#define ERR_ERRONEUSNICKNAME //432     // "<nick> :Erroneus nickname"
                                        // - Возвращается после получения NICK-сообщения, которое
                                        // содержит символы, которые запрещены. Смотрите раздел
                                        // х.х.х для более подробной информации.
#define ERR_NICKNAMEINUSE //433        // "<nick> :Nickname is already in use"
                                        // Возвращается при смене никнейма на другой, уже используемый.
#define ERR_NICKCOLLISION //436        // "<nick> :Nickname collision KILL"
                                        //  - Возвращается сервером к клиенту, когда сервер видит
                                        //  конфликт никнейма (зарегистрированный никнейм уже есть).
//oper
#define RPL_YOUREOPER       // 381 - RPL_YOUREOPER отправляется клиенту, который благополучно
                            //       выполнил OPER-сообщение и получил статус IRC-оператора.
#define ERR_NOOPERHOST      // 491    ":No O-lines for your host"
                            //     - Если сервер не настроен на поддержку клиентского хоста
                            //       для сообщения OPER, клиенту будет возвращена эта ошибка.
#define ERR_PASSWDMISMATCH  // 464   ":Password incorrect"
                            //     - Возвращается при неправильно введеном или неуказанным
                            //       паролем.

#include <map>
#include <vector>
#include <iostream>
#include "User.hpp"
// #include "Server.hpp"

// class Server;
typedef struct s_msg
{
	std::string prefx;
	std::string cmd;
	std::vector <std::string> midParams;
	std::string trailing;
	int paramN;
}				t_msg;

class Command {
private:
    typedef void (Command:: * PType)(std::string const &, User &user);
    std::map<std::string, PType>cmd_map;
    std::vector<User*> userData;
    // std::vector<User*> &userData;   // вектор для Server

	std::string checkMsgFormat( std::string cmdStr );
	std::string getRidOfCmdName( std::string cmdStr );

public:
	t_msg msg;
    void execute(std::string const &, User &);
	std::string parseMsg( std::string cmdStr );
    // Command(Server &);      //коструктор для Server
    std::vector<User *>getUserData();
    void setUserData(std::vector<User*> &);
    void pass( std::string const &, User & );
    void nick( std::string const &, User & );
    void user( std::string const &, User & );
    void oper( std::string const &, User & );
    void quit( std::string const &, User & );

	void who( std::string const &, User & );
	void whois( std::string const &, User & );
	void whowas( std::string const &, User & );
    std::string removeCmd( std::string );
    // static void user(std::string const username, std::string hostname, std::string servname, std::string realname);
    Command();
    ~Command();
};

#endif