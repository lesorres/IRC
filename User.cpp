#include "User.hpp"

std::string const & User::getNick( void ) const { return(nickname); }
std::string const & User::getName( void ) const { return(username); }

void User::setNick( std::string const & nick ) { nickname = nick; }
void User::setName( std::string const & name ) { username = name; }

User::User()
{
    username = "<blank>";
    nickname = "<blank>";
    password = "<blank>";
    registred = false;
}

User::~User() {}