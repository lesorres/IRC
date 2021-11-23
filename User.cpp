#include "User.hpp"

std::string const & User::getNick( void ) const { return(nickname); }
std::string const & User::getUser( void ) const { return(username); }
std::string const & User::getPass( void ) const { return(password); }
int const & User::getFd( void ) const { return(_fd); }

void User::setNick( std::string const & nick ) { nickname = nick; }
void User::setUser( std::string const & name ) { username = name; }
void User::setPass( std::string const & pass ) { password = pass; }
void User::setFd( int const & fd ) { _fd = fd; }

User::User()
{
    username = "";
    nickname = "";
    password = "";
    registred = false;
}

User::~User() {}