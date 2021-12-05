#include "Channel.hpp"
#include "Server.hpp"

int Server::join( User & user )
{
    if (msg.midParams.size() > 2)
        errorMEss(0, user);
    try
    {
        channels.at(msg.midParams[0]);
        std::cout << "connect to channel\n";
    }
    catch (std::exception & e)
    {
        if (msg.midParams.size() == 2)
            channels[msg.midParams[0]] = new Channel(&user, msg.midParams[0], msg.midParams[1]);
        else
            channels[msg.midParams[0]] = new Channel(&user, msg.midParams[0]);
        std::cout << "created new channel\n";
    }
    return (0);
}