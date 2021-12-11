#ifndef Channel_hpp
#define Channel_hpp

#include <iostream>
#include "User.hpp"
#include <vector>

// #define OPERATOR    0x001   //o - брать/давать привилегии операторов канала
// #define PRIVATE     0x002   //p - флаг приватности канала;
// #define SECRET      0x004   //s - флаг секретности канала;
// #define INVITE      0x008   //i - флаг канала invite-only;
// #define TOPIC       0x010   //t - при установке этого флага, менять топик могут только операторы;
// #define NO_MESS     0x020   //n - запрещает сообщения на канал от посторонних клиентов;
// #define MODERATE    0x040   //m - модерируемый канал;
// #define LIMITS      0x080   //l - установка ограничения на количество пользователей;
// #define BANMASC     0x100   //b - установка маски бана;
// #define KEY         0x400   //k - установка на канал ключа (пароля).


class User;

class Channel
{
    private:
        std::string             name;
        std::string             topic;
        std::vector<User*>      users;
        std::vector<User*>      operators;
        std::vector<std::string> banmascs;
        std::string             password;
        unsigned int            countUsers;
        unsigned int            userLimit;
        unsigned int            flags;

        Channel();
        Channel( Channel const & _ot );
        Channel operator=( Channel const & _ot );
    public:

        void setTopic( std::string & _topic );
        void addUser( User * user );
        void disconnectUser( User const & user);
        void changeFlags( std::string & newflags );

        std::string getName( void ) const;
        std::string getTopic( void ) const;
        std::string getPass( void ) const;
        unsigned int getFlags( void ) const;
        unsigned int getCountUsers( void ) const;
        unsigned int getUserLimit( void ) const;
        std::vector<User*> const & getUserList( void ) const;

        Channel(User * creater, std::string name, std::string pass = "");
        ~Channel();
};

#endif