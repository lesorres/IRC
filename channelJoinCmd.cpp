#include "Channel.hpp"
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
                channels.at(channellist[i]);
                if (contains(user.getChannelList(), channellist[i]))
                {
                    std::cout << user.getNick() << " alreday on " << channellist[i] << "\n";
                    if (i == 0 && user.getActiveChannel() != channellist[i])
                        user.setActiveChannel(channellist[i]);
                }
                else
                {
                    user.addChannel(channellist[i]);
                    std::cout << user.getNick() << " connect to channel " << channellist[i] << "\n";
                    if (i == 0 && user.getActiveChannel() != channellist[i])
                        user.setActiveChannel(channellist[i]);
                }
            }
            catch (std::exception & e)
            {
                if (channelpass.size() < i)
                    channels[channellist[i]] = new Channel(&user, channellist[i],  channelpass[i]);
                else
                    channels[channellist[i]] = new Channel(&user, channellist[i]);
                user.addChannel(channellist[i]);
                if (user.getActiveChannel() != channellist[i])
                    user.setActiveChannel(channellist[i]);
                std::cout << user.getNick() << " created new channel " << channellist[i] << "\n";
            }
        }
    }
    return (0);
}