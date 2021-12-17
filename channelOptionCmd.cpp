#include "Server.hpp"

#define CHANNEL 1
#define USER 0

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
            if (!((it->second)->flags & (PRIVATE|SECRET) && !contains((it->second)->getUserList(), &user)))
            {
                list = it->first + " :";
                users = (it->second)->getUserList();
                for (size_t i = 0; i < users.size(); i++)
                {
                    if ((it->second)->isOperator(users[i]))
                        list += "@" + users[i]->getNick() + " ";
                    else
                        list += users[i]->getNick() + " ";
                }
                replyMEss(RPL_NAMREPLY, user, list);
                list = it->first;
                replyMEss(RPL_ENDOFNAMES, user, list);
            }
        }
    }
    else
    {
        std::vector<std::string> channellist = split(msg.midParams[0], ",");
        for (size_t i = 0; i < channellist.size(); i++)
        {
            if (*(channellist[i].begin()) == '#')
            {
                try {
                    Channel * current = channels.at(channellist[i]);
                    if (!(current->flags & (PRIVATE|SECRET) && !contains(current->getUserList(), &user)))
                    {
                        list = channellist[i] + " :";
                        users = current->getUserList();
                        for (size_t i = 0; i < users.size(); i++)
                        {
                            if (current->isOperator(users[i]))
                                list += "@" + users[i]->getNick() + " ";
                            else
                                list += users[i]->getNick() + " ";
                        }
                        replyMEss(RPL_NAMREPLY, user, list);
                        list = channellist[i];
                        replyMEss(RPL_ENDOFNAMES, user, list);
                    }
                }
                catch (std::exception & e) {
                    return (1);
                }
            }
        }
    }
    return (0);
}

int Server::topic( User & user )
{
    if (msg.midParams.size() < 1)
        errorMEss(ERR_NEEDMOREPARAMS, user);
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
                if (current->flags & TOPIC)
                    if (!current->isOperator(&user))
                        return(errorMEss(ERR_CHANOPRIVSNEEDED, user, msg.midParams[0]));
                std::string top;
                for (size_t i = 1; i < msg.midParams.size(); i++)
                    top += msg.midParams[i] + " ";
                top += msg.trailing;
                current->setTopic(top);
            }
        }
        else
            errorMEss(ERR_NOTONCHANNEL, user, msg.midParams[0]); 
    }
    return (0);
}

static int checkModeChar( std::string str, bool channel)
{
    if (channel) {
        if (str.find_first_not_of("+-opsitnmlbvk") != std::string::npos
        || str.size() != 2 || (str[0] != '-' && str[0] != '+'))
            return (1);
    }
    else {
        if (str.find_first_not_of("+-osiw") != std::string::npos
        || str.size() != 2 || (str[0] != '-' && str[0] != '+'))
            return (1);
    }
    return(0);
}

int Server::mode( User & user )
{
    if (msg.midParams.size() < 1)
        return(errorMEss(ERR_NEEDMOREPARAMS, user));
    if (*(msg.midParams[0].begin()) == '#') // channels mode
    {
        if (checkModeChar(msg.midParams[1], CHANNEL))
            return(errorMEss(ERR_UNKNOWNMODE, user, msg.midParams[1]));
        try {
            Channel * current = channels.at(msg.midParams[0]);
            if (!contains(user.getChannelList(), msg.midParams[0]))
                errorMEss(ERR_NOTONCHANNEL, user, msg.midParams[0]);
            else if (!current->isOperator(&user))
                errorMEss(ERR_CHANOPRIVSNEEDED, user, msg.midParams[0]);
            else
                setChannelMode(current, user);
        }
        catch (std::exception & e) {
            errorMEss(ERR_NOSUCHCHANNEL, user, msg.midParams[0]);
        }
    }  
    else // user mode
    {
        if (checkModeChar(msg.midParams[1], USER))
            return(errorMEss(ERR_UMODEUNKNOWNFLAG, user));
        else if (user.getNick() != msg.midParams[0])
            return(errorMEss(ERR_USERSDONTMATCH, user));
        else
            setUserMode(user);
    }
    return(0);
}

void    Server::setUserMode( User & user )
{
    char flag = msg.midParams[1][1];
    if (msg.midParams[1][0] == '-') {
        switch (flag) {
            case 'i': user.unsetFlags(INVISIBLE); break;
            case 'w': user.unsetFlags(WALLOPS); break;
            case 's': user.unsetFlags(SNOTICE); break;
            case 'o': user.unsetFlags(OPERATOR); break;
        }
    }
    else if (msg.midParams[1][0] == '+') {
        switch (flag) {
            case 'i': user.setFlags(INVISIBLE); break;
            case 'w': user.setFlags(WALLOPS); break;
            case 's': user.setFlags(SNOTICE); break;
            case 'o': break;
        }
    }
}

void    Server::setChannelMode(Channel * channel, User & user )
{
    char flag = msg.midParams[1][1];
    if (msg.midParams[1][0] == '-') {
        switch (flag) {
            case 'o':
                if (msg.midParams.size() < 3) {
                    errorMEss(461, user); break; }
                else if (contains(channel->getUserList(), &getUserByNick(msg.midParams[2]))) {
                    channel->deopUser(&getUserByNick(msg.midParams[2]));
                    getUserByNick(msg.midParams[2]).imNotOper(channel->getName());
                    break ; }
                else {
                    errorMEss(502, user); break; }
            case 'v':
                break;
            case 'b': 
                if (msg.midParams.size() < 3) {
                    errorMEss(461, user); break; }
                channel->deleteBanMasc(msg.midParams[2]);
                break;
            case 'k': channel->flags &= ~KEY; break;
            case 'l': channel->flags &= ~LIMITS; break;
            case 'p': channel->flags &= ~PRIVATE; break;
            case 's': channel->flags &= ~SECRET; break;
            case 'i': channel->flags &= ~INVITE; break;
            case 't': channel->flags &= ~TOPIC; break;
            case 'n': channel->flags &= ~NO_MESS; break;
            case 'm': channel->flags &= ~MODERATE; break;
        }
    }
    else if (msg.midParams[1][0] == '+') {
        switch (flag){
            case 'o':
                if (msg.midParams.size() < 3) {
                    errorMEss(461, user); break; }
                else if (contains(channel->getUserList(), &getUserByNick(msg.midParams[2]))) {
                    channel->opUser(&getUserByNick(msg.midParams[2]));
                    getUserByNick(msg.midParams[2]).imOper(channel->getName());
                    break ; }
                else {
                    errorMEss(502, user); break; }
            case 'v':
                break;
            case 'b': 
                if (msg.midParams.size() < 3) {
                    errorMEss(461, user); break; }
                channel->addBanMask(msg.midParams[2]);
                break;
            case 'k': channel->flags |= KEY;
                if (msg.midParams.size() < 3) {
                    errorMEss(461, user); break; }
                channel->setPass(msg.midParams[2]);
                break;
            case 'l': channel->flags |= LIMITS;
                if (msg.midParams.size() < 3) {
                    errorMEss(461, user); break; }
                channel->setUserLimit(stoi(msg.midParams[2]));
                break;
            case 'p': channel->flags |= PRIVATE; break;
            case 's': channel->flags |= SECRET; break;
            case 'i': channel->flags |= INVITE; break;
            case 't': channel->flags |= TOPIC; break;
            case 'n': channel->flags |= NO_MESS; break;
            case 'm': channel->flags |= MODERATE; break;
        } 
    }
}