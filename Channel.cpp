#include "Channel.hpp"
#include "Utils.hpp"

// void Channel::changeFlags( std::vector<std::string> & option )
// {
//     if (newflags[0] == "+")
//     {
//         //up_flags
//         for (size_t j = 1; i < newflags.size(); j++)
//         {
//             switch (newflags[j]) {
//                 case 'o':
                    
//             }
//         }
//     }
//     else if (newflags[0] == "-")
//     {
//         //de_flags
//     }
// }

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
std::string Channel::getPass( void ) const { return(password); }
std::string Channel::getTopic( void ) const { return (topic); }
unsigned int Channel::getCountUsers( void ) const { return(countUsers); }
unsigned int Channel::getUserLimit( void ) const { return (userLimit); }
unsigned int Channel::getFlags( void ) const { return (flags); }

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