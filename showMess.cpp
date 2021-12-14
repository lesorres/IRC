#include "Server.hpp"

void Server::showMEss( User const & from, Channel const * channel, int andfrom )
{
    std::string prefix = ":" + from.getNick() + "!" + from.getUser() + "@" + from.getIp() + " ";
    std::string mess = msg.cmd + " ";
    for (size_t i = 0; i < msg.midParams.size(); i++)
        mess += msg.midParams[i] + " ";
    mess += msg.trailing + "\n";
    std::vector<User *> users = channel->getUserList();
    for(unsigned int i = 0; i < users.size(); i++)
    {
        if (from.getNick() != users[i]->getNick() || andfrom)
        {
            send(users[i]->getFd(), prefix.c_str(), prefix.size(), 0);
            send(users[i]->getFd(), mess.c_str(), mess.size(), 0);
        }
    }
}