#include "Channel.hpp"
#include "Utils.hpp"

void Channel::addUser( User * user )
{
    users.push_back(user);
    countUsers++;
}

void Channel::disconnectUser( User * user )
{
    eraseUser(users, user);
    eraseUser(operators, user);
    eraseUser(invited, user);
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

unsigned int Channel::getCountVisible( void ) const
{
    unsigned int count = 0;
    for (size_t i = 0; i < users.size(); i++)
        if (!(users[i]->getFlags() & INVISIBLE))
            count++;
    return (count);
}

void Channel::invUser( User * user ) { invited.push_back(user); }
void Channel::deinvUser( User * user ) { eraseUser(invited, user); }
bool Channel::isInvited( User * user )
{
    if (contains(invited, user))
        return (true);
    return (false);
}

void Channel::opUser( User * user ) { operators.push_back(user); }
void Channel::deopUser( User * user ) { eraseUser(operators, user); }
bool  Channel::isOperator( User * user )
{
    if (contains(operators, user))
        return (true);
    return (false);
}

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
    flags = NO_MESS;
} 

Channel::~Channel() {}