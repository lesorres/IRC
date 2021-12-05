#include "Server.hpp"

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
    if (res.empty())
        res.push_back(str);
    return (res);
}

bool isAlphaStr(std::string str)
{
	std::string::iterator beginIt;
	std::string::iterator endIt;

	beginIt = str.begin();
	endIt = str.end();

	// for ( ; beginIt != endIt; ++beginIt)
	// {
	// 	if ()
	// }
	return(0);
}