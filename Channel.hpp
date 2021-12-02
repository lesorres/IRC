#ifndef Channel_hpp
#define Channel_hpp

#include <iostream>
#include "User.hpp"
#include <vector>

class Channel
{
    private:
        std::string         name;
        std::vector<User*>  users;
        std::vector<User*>  operators;
        unsigned int        maxUsers;
        std::string         password;
        std::string         flags;
        
        Channel();
        Channel( Channel const & _ot );
        Channel operator=( Channel const & _ot );
    public:
        Channel(User * creater, std::string _name, std::string _pass);
        ~Channel();
};

#endif