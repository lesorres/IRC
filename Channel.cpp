#include "Channel.hpp"

Channel::~Channel() {}

Channel::Channel(User * creater, std::string cnlname, std::string pass)
{
    name = cnlname;
    password = pass;
    users.push_back(creater);
    operators.push_back(creater);
} 