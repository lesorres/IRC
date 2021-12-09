#include "Channel.hpp"
#include "Utils.hpp"

void Channel::addUser( User * user )
{
    users.push_back(user);
    countUsers++;
}

void Channel::disconnectUser( User const & user )
{
    eraseUser(users, user.getNick());
    countUsers--;
}

void Channel::setTopic( std::string & _topic ) { topic = _topic; }
std::vector<User*> const & Channel::getUserList( void ) const { return (users); }
std::string Channel::getName( void ) const { return (name); }
std::string Channel::getTopic( void ) const { return (topic); }
unsigned int Channel::getCountUsers( void ) { return(countUsers); }
Channel::Channel(User * creater, std::string channelname, std::string pass)
{
    name = channelname;
    password = pass;
    users.push_back(creater);
    operators.push_back(creater);
    countUsers = 1;
    topic = "";
} 

Channel::~Channel() {}