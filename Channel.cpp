#include "Channel.hpp"

Channel::~Channel() {}
Channel::Channel(User * creater, std::string _name, std::string _pass = "")
{
    name = _name;
    password = _pass;
    users.push_back(creater);
    operators.push_back(creater);
}