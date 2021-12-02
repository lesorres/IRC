#ifndef Server_hpp
#define Server_hpp

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <poll.h>
#include <vector>
#include <iterator>
#include <stdexcept>
#include <fcntl.h>
#include <unistd.h>
#include "User.hpp"
#include "Utils.hpp"
#include "Channel.hpp"
#include <map>

#define BUF_SIZE 1024
std::vector<std::string> split(std::string str, std::string delimiter);

typedef struct s_msg
{
	std::string prefx;
	std::string cmd;
	std::vector <std::string> midParams;
	std::string trailing;
	int paramN;
}				t_msg;

class Server {
	private:
		std::vector<struct pollfd>	userFds;
		std::vector<User*>			userData;
		typedef int (Server:: * PType)( User &user );
    	std::map<std::string, PType>commands;

		int					srvFd;
		int					srvPort;
		std::string			srvPass;
		struct sockaddr_in	address;
		int					addrlen;

		void		initCommandMap();
		std::string checkMsgFormat( std::string cmdStr );
		std::string getRidOfCmdName( std::string cmdStr );

		Server( Server const & _ot );
		Server operator=( Server const & _ot ); 

	public:
		t_msg msg;

		Server( std::string const & _port, std::string const & _pass);
		~Server();

		void create();
		void connectUsers( void );
		void clientRequest( void );
		void disconnectClient( size_t const id );
		int  readRequest( size_t const id );
		void executeCommand( size_t const id );
		// std::vector<User*> &getUserData();

		// commands
    	void execute(std::string const &, User &);
		std::string parseMsg( std::string cmdStr );
    	int pass(User & );
    	int nick(User & );
    	int user(User & );
    	int oper(User & );
    	int quit(User & );
		int who( User & );
		int whois( User & );
		int whowas( User & );
		void cleanMsgStruct();

    	bool connection(User &);
    	void motd();
		void errorMEss(int err, User &user);

		// void passw( std::string const &str, User &user) { std::cout << str << " User: " << user.getNick();}

};

#endif