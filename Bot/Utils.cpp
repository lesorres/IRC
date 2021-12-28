#include "Utils.hpp"

bool isDigit(std::string const & str)
{
	if (str.find_first_not_of("0123456789") != std::string::npos)
		return (false);
	return(true);
}

std::string	itos( int const & num )
{
	std::stringstream ss;
	ss << num;
	return(ss.str());
}

std::vector<std::string> split(std::string str, std::string delimiter)
{
    size_t pos = 0;
    std::string token;
    std::vector<std::string> res;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        res.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    if (!str.empty())
        res.push_back(str);
    return (res);
}