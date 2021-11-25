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

#include <map>
#include <vector>
#include <iostream>
#include "User.hpp"
// #include "Server.hpp"

// class Server;

class Command {
    std::vector<User*> userData;
    // std::vector<User*> &userData;   // вектор для Server
public:
    Command();
    // Command(Server &);      //коструктор для Server
    void setUserData(std::vector<User*> &);
    void pass( std::string const , User & );
    void nick( std::string const , User & );
    void user( std::string const , User & );
    std::string removeCmd( std::string );
    // static void user(std::string const username, std::string hostname, std::string servname, std::string realname);
    ~Command();
};

#endif