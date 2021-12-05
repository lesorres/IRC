#include "Server.hpp"

void Server::showMEss( User const & from, Channel const * channel )
{
    std::string mess = "< " + from.getNick() + " >:";
    mess += msg.cmd + " ";
    for (size_t i = 0; i < msg.midParams.size(); i++)
        mess += msg.midParams[i] + " ";
    mess += "\n";
    std::vector<User *> users = channel->getUserList();
    for(unsigned int i = 0; i < users.size(); i++)
    {
        if (users[i]->getNick() != users[i]->getNick())
            send(users[i]->getFd(), mess.c_str(), mess.size(), 0);
    }
}