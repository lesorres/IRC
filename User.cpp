#include "User.hpp"

std::string const & User::getNick( void ) const { return(_nickname); }
std::string const & User::getName( void ) const { return(_username); }

void User::setNick( std::string const & nick ) { _nickname = nick; }
void User::setName( std::string const & name ) { _username = name; }

User::User()
{
    _username = "<blank>";
    _nickname = "<blank>";
    _password = "<blank>";
}

User::~User() {}