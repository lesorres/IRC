#include "User.hpp"

std::string const & User::getNick( void ) const { return(nickname); }
std::string const & User::getUser( void ) const { return(username); }
std::string const & User::getPass( void ) const { return(password); }

std::string const & User::getRealn( void ) const { return(realname); }
std::string const & User::getHostn( void ) const { return(hostname); }
std::string const & User::getServern( void ) const { return(servername); }
int const & User::getFd( void ) const { return(fd); }
bool const & User::getRegistred( void ) const { return(registred); }
bool const & User::getBreakconnect( void ) const { return(breakconnect); }

void User::setNick( std::string const & nick ) { nickname = nick; }
void User::setUser( std::string const & name ) { username = name; }
void User::setPass( std::string const & pass ) { password = pass; }

void User::setRealn( std::string const & real ) { realname = real; }
void User::setHostn( std::string const & host ) { hostname = host; }
void User::setServern( std::string const & server ) { servername = server; }
void User::setFd( int const & _fd ) { fd = _fd; }
void User::setRegistred( bool const & status ) { registred = status; }

void User::checkConnection( std::string const & mess )
{
    if (mess.find_last_of("\n") != mess.size() - 1)
        breakconnect = true;
    else if (breakconnect)
        breakconnect = false;
}

User::User()
{
    username = "";
    nickname = "";
    password = "";
    realname = "";
    hostname = "";
    servername = "";
    registred = false;
    breakconnect = false;
}

User::~User() {}