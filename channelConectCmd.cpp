#include "Server.hpp"

int Server::join( User & user )
{
    if (msg.midParams.size() > 2 || msg.midParams.empty())
        errorMEss(0, user);
    std::vector<std::string> channellist = split(msg.midParams[0], ",");
    std::vector<std::string> channelpass;
    if (msg.midParams.size() == 2)
        channelpass = split(msg.midParams[1], ",");
    for (size_t i = 0; i < channellist.size(); i++)
    {
        if (*(channellist[i].begin()) == '#')
        {
            try
            {
                Channel * current = channels.at(channellist[i]);
                if (contains(user.getChannelList(), channellist[i]))
                {
                    if (i == 0 && user.getActiveChannel() != channellist[i])
                        user.setActiveChannel(channellist[i]);
                    std::cout << user.getNick() << " alreday on " << channellist[i] << "\n";
                }
                else
                {
                    current->addUser(&user);
                    user.addChannel(channellist[i]);
                    if (i == 0 && user.getActiveChannel() != channellist[i])
                        user.setActiveChannel(channellist[i]);
                    std::cout << user.getNick() << " connect to channel " << channellist[i] << "\n";
                }
            }
            catch (std::exception & e)
            {
                if (i < channelpass.size())
                    channels[channellist[i]] = new Channel(&user, channellist[i],  channelpass[i]);
                else
                    channels[channellist[i]] = new Channel(&user, channellist[i]);
                user.addChannel(channellist[i]);
                if (user.getActiveChannel() != channellist[i])
                    user.setActiveChannel(channellist[i]);
                std::cout << user.getNick() << " created new channel " << channellist[i] << "\n";
            }
        }
        else
            errorMEss(0, user); // ERR_NOSUCHCHANNEL
    }
    return (0);
}

int Server::part( User & user )
{
    if (msg.midParams.size() > 1 || msg.midParams.empty())
        errorMEss(0, user); // ERR_NEEDMOREPARAMS or too many
    std::vector<std::string> channellist = split(msg.midParams[0], ",");
    for (size_t i = 0; i < channellist.size(); i++)
    {
        if (*(channellist[i].begin()) == '#')
        {
            if (contains(user.getChannelList(), channellist[i]))
            {
                Channel * current = channels.at(channellist[i]);
                user.leaveChannel(channellist[i]);
                current->disconnectUser(user);
                std::cout << user.getNick() << " leave channel " << channellist[i] << "\n";
                if (current->getUserList().empty())
                {
                    channels.erase(channellist[i]);
                    delete current;
                }
            }
            else
                errorMEss(0, user); // ERR_NOTONCHANNEL
        }
        else
            errorMEss(0, user); // ERR_NOSUCHCHANNEL
    }
    return (0);
}