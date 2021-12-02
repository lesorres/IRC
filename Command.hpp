#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <map>
#include <vector>
#include <sys/socket.h>
#include <iostream>
#include "User.hpp"

// #include "Server.hpp"

// class Server;

typedef struct s_msg
{
	std::string prefx;
	std::string cmd;
	std::vector <std::string> midParams;
	std::string trailing;
	int paramN;
}				t_msg;

class Command {
private:
    typedef int (Command:: * PType)( User &user, std::vector<User*>& userData);
    std::map<std::string, PType>cmd_map;
	std::string checkMsgFormat( std::string cmdStr );
	std::string getRidOfCmdName( std::string cmdStr );

public:
	t_msg msg;
    void execute(std::string const &, User &, std::vector<User*>& userData);
	std::string parseMsg( std::string cmdStr );
    int pass(User &, std::vector<User*>& userData );
    int nick(User &, std::vector<User*>& userData );
    int user(User &, std::vector<User*>& userData );
    int oper(User &, std::vector<User*>& userData );
    int quit(User &, std::vector<User*>& userData );

	int who( User &, std::vector<User*>& userData );
	int whois( User &, std::vector<User*>& userData );
	int whowas( User &, std::vector<User*>& userData );
	void cleanMsgStruct();

	void join(const User * user, std::string _name, std::string _pass = "");

    bool connection(User &);
    void motd();
    Command();
    ~Command();
};

#endif