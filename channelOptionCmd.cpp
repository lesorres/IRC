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
            list = it->first + " :";
            users = (it->second)->getUserList();
            for (size_t i = 0; i < users.size(); i++)
                list += users[i]->getNick() + " ";
            replyMEss(353, user, list);
            list = it->first;
            replyMEss(366, user, list);
        }
    }
    else
    {
        std::vector<std::string> channellist = split(msg.midParams[0], ",");
        for (size_t i = 0; i < channellist.size(); i++)
        {
            if (*(channellist[i].begin()) == '#')
            {
                list = channellist[i] + " :";
                users = channels[channellist[i]]->getUserList();
                for (size_t i = 0; i < users.size(); i++)
                    list += users[i]->getNick() + " ";
                replyMEss(353, user, list);
                list = channellist[i];
                replyMEss(366, user, list);
            }
        }
    }
    return (0);
}

int Server::topic( User & user )
{
    if (msg.midParams.size() < 1)
        errorMEss(461, user);
    else
    {
        if (contains(user.getChannelList(), msg.midParams[0]))
        {
            Channel * current = channels.at(msg.midParams[0]);
            if (msg.midParams.size() == 1 && msg.trailing.empty())
            {
                if (current->getTopic().empty())
                    replyMEss(331, user, msg.midParams[0]);
                else
                    replyMEss(332, user, msg.midParams[0] + " :" + current->getTopic());
            }
            else
            {
                std::string top;
                for (size_t i = 1; i < msg.midParams.size(); i++)
                    top += msg.midParams[i] + " ";
                top += msg.trailing;
                current->setTopic(top);
            }
        }
        else
            errorMEss(442, user, msg.midParams[0]);
    }
    return (0);
}