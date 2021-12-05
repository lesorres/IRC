#ifndef Channel_hpp
#define Channel_hpp

#include <iostream>
#include "User.hpp"
#include <vector>

class User;

class Channel
{
    private:
        std::string         name;
        std::vector<User*>  users;
        std::vector<User*>  operators;
        unsigned int        countUsers;
        std::string         password;
        std::string         flags;

        Channel();
        Channel( Channel const & _ot );
        Channel operator=( Channel const & _ot );
    public:

        std::string getName( void ) const;
        void addUser( User * user );
        void disconnectUser( User const & user);
        std::vector<User*> getUserList( void ) const;
        unsigned int getCountUsers( void );

        Channel(User * creater, std::string name, std::string pass = "");
        ~Channel();
};

#endif