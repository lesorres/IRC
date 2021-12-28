#ifndef Utils_hpp
#define Utils_hpp

#include <iostream>
#include <vector>
#include <cctype>
#include <sstream>

#define RESET "\e[0m"
#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define BLUE "\e[34m"
#define PURPLE "\e[35m"
#define CYAN "\e[36m"
#define GRAY "\e[37m"

std::string	itos( int const & num );
std::vector<std::string> split(std::string str, std::string delimiter);
bool isDigit(std::string const & str);

#endif