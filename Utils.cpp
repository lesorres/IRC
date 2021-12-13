#include "Server.hpp"
#include <algorithm>

bool    contains(std::vector<std::string> vect, std::string str)
{
    if (find(vect.begin(), vect.end(), str) != vect.end())
        return (true);
    return (false);
}

void eraseString( std::vector<std::string> & vect, std::string name )
{
    std::vector<std::string>::iterator it = vect.begin();
    while (*it != name)
    {
        if (it == vect.end())
            return ;
        it++;
    }
    vect.erase(it);
}

void eraseUser( std::vector<User*> & vect, std::string name )
{
    std::vector<User*>::iterator it = vect.begin();
    while ((*it)->getNick() != name)
    {
        if (it == vect.end())
            return ;
        it++;
    }
    vect.erase(it);
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

bool isAlphaStr(std::string str)
{
	std::string::iterator beginIt;
	std::string::iterator endIt;

	beginIt = str.begin();
	endIt = str.end();

	for ( ; beginIt != endIt; ++beginIt)
	{
		if (!std::isalpha(*beginIt))
			return (1);
	}
	return(0);
}

bool isDigitStr(std::string str)
{
	std::string::iterator beginIt;
	std::string::iterator endIt;

	beginIt = str.begin();
	endIt = str.end();

	for ( ; beginIt != endIt; ++beginIt)
	{
		if (!std::isdigit(*beginIt))
			return (1);
	}
	return(0);
}