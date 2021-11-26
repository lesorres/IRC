#include "User.hpp"

std::string const & User::getNick( void ) const { return(nickname); }
std::string const & User::getUser( void ) const { return(username); }
std::string const & User::getPass( void ) const { return(password); }

std::string const & User::getRealn( void ) const { return(realname); }
std::string const & User::getHostn( void ) const { return(hostname); }
std::string const & User::getServern( void ) const { return(servername); }
int const & User::getFd( void ) const { return(_fd); }

void User::setNick( std::string const & nick ) { nickname = nick; }
void User::setUser( std::string const & name ) { username = name; }
void User::setPass( std::string const & pass ) { password = pass; }

void User::setRealn( std::string const & real ) { realname = real; }
void User::setHostn( std::string const & host ) { hostname = host; }
void User::setServern( std::string const & server ) { servername = server; }
void User::setFd( int const & fd ) { _fd = fd; }

User::User()
{
    username = "";
    nickname = "";
    password = "";
    realname = "";
    hostname = "";
    servername = "";
    registred = false;
}

User::~User() {}