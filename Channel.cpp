#include "Channel.hpp"
#include "Utils.hpp"

int  Channel::isOperator( User * user )
{
    if (contains(operators, user))
        return (1);
    return (0);
}

void Channel::addUser( User * user )
{
    users.push_back(user);
    countUsers++;
}

void Channel::disconnectUser( User * user )
{
    eraseUser(users, user);
    eraseUser(operators, user);
    countUsers--;
}

void Channel::addBanMask( std::string & masc ) 
{ 
    banmascs.push_back(masc); 
}

void Channel::deleteBanMasc( std::string masc )
{
    eraseString(banmascs, masc);
}


void Channel::opUser( User * user ) { operators.push_back(user); }
void Channel::deopUser( User * user ) { eraseUser(operators, user); }
void Channel::setPass( std::string & pass ) { password = pass; }
void Channel::setUserLimit( unsigned int limit ) { userLimit = limit; }
void Channel::setTopic( std::string & _topic ) { topic = _topic; }
std::vector<User*> const & Channel::getUserList( void ) const { return (users); }
std::vector<std::string> Channel::getBanMasc( void ) const { return (banmascs); }
std::string Channel::getName( void ) const { return (name); }
std::string Channel::getPass( void ) const { return(password); }
std::string Channel::getTopic( void ) const { return (topic); }
unsigned int Channel::getCountUsers( void ) const { return(countUsers); }
unsigned int Channel::getUserLimit( void ) const { return (userLimit); }

Channel::Channel(User * creater, std::string channelname, std::string pass)
{
    name = channelname;
    password = pass;
    users.push_back(creater);
    operators.push_back(creater);
    countUsers = 1;
    userLimit = 0;
    topic = "";
    flags = 0;
} 

Channel::~Channel() {}