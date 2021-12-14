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
        errorMEss(461, user); // ERR_NEEDMOREPARAMS
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
            errorMEss(442, user, msg.midParams[0]); // ERR_NOTONCHANNEL
    }
    return (0);
}

static int checkModeChar( std::string str )
{
    if (str.find_first_not_of("+-opsitnmlbvk") != std::string::npos
     || str.size() != 2 || (str[0] != '-' && str[0] != '+'))
        return (1);
    return(0);
}

int Server::mode( User & user )
{
    if (msg.midParams.size() < 1 && msg.trailing.empty())
        errorMEss(461, user); // ERR_NEEDMOREPARAMS
    else
    {
        if (*(msg.midParams[0].begin()) == '#') // channels mode
        {
            if (checkModeChar(msg.midParams[1]))
            {
                errorMEss(472, user, msg.midParams[1]); // ERR_UNKNOWNMODE
                return (1);
            }
            try {
                Channel * current = channels.at(msg.midParams[0]);
                if (!contains(user.getChannelList(), msg.midParams[0]))
                    errorMEss(442, user, msg.midParams[0]); // ERR_NOTONCHANNEL
                else if (!current->isOperator(&user))
                    errorMEss(482, user, msg.midParams[0]); // ERR_CHANOPRIVSNEEDED
                else
                    setChannelMode(current, user);
            }
            catch (std::exception & e) {
                errorMEss(403, user, msg.midParams[0]); // ERR_NOSUCHCHANNEL
            }
        }
        else // user mode
        {
            ;
        }
    }
    return(0);
}

void Server::setChannelMode(Channel * channel, User & user )
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