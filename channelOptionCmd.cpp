#include "Server.hpp"

int Server::list( User & user )
{
    if (msg.midParams.empty())
    {
        std::string list;
        for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); it++)
        {
            list += it->first + " ";
        }
        list+= "\n";
        send(user.getFd(), list.c_str(), list.size(), 0);
    }
    return (0);
}

int Server::names( User & user )
{
    std::string list;
    std::vector<User *> users;
    if (msg.midParams.empty())
    {
        for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); it++)
        {
            users = (it->second)->getUserList();
            for (size_t i = 0; i < users.size(); i++)
            {
                list += users[i]->getNick() + " ";
            }
            list += "\n";
            send(user.getFd(), (it->first + "\n\n").c_str(), it->first.size() + 2, 0);
            send(user.getFd(), list.c_str(), list.size(), 0);
            list.clear();
        }
    }
    else
    {
        std::vector<std::string> channellist = split(msg.midParams[0], ",");
        for (size_t i = 0; i < channellist.size(); i++)
        {
            if (*(channellist[i].begin()) == '#')
            {
                users = channels[channellist[i]]->getUserList();
                for (size_t i = 0; i < users.size(); i++)
                {
                    list += users[i]->getNick() + " ";
                }
                list += "\n\n";
                send(user.getFd(), (channellist[i] + "\n").c_str(), channellist[i].size() + 1, 0);
                send(user.getFd(), list.c_str(), list.size(), 0);
                list.clear();
            }
        }
    }
    return (0);
}