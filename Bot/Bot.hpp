#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "../Server.hpp"
#include "../Utils.hpp"

class Bot {
private:
	std::string cmds;
	typedef int ( Bot:: *Type )( );
    std::map<std::string, Type>	cmd;
public:
	Bot();
	void run();
	void execute();

	void showInfo();

	int command();
	int help();
	int pass();
	int nick();
	int user();
	int oper();
	int quit();
	int join();
	int part();
	int mode();
	int topic();
	int names();
	int list();
	int invite();
	int kick();
	int version();
	int time();
	int admin();
	int info();
	int privmsg();
	int notice();
	int who();
	int whois();
	int whowas();
	int kill();
	int ping();
	int pong();
	int away();
	int rehash();
	int restart();
	int userhost();
	int ison();
	~Bot();
};

#endif