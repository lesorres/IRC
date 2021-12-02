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
// #include "Command.hpp"
#include <map>

#define BUF_SIZE 1024

typedef struct s_msg
{
	std::string prefx;
	std::string cmd;
	std::vector <std::string> midParams;
	std::string trailing;
	int paramN;
}				t_msg;

std::vector<std::string> split(std::string str, std::string delimiter);

class Server {
	private:
		// Command						cmd;
		std::vector<struct pollfd>	userFds;
		std::vector<User*>			userData;
		typedef int (Server:: * PType)( User &user);
    	std::map<std::string, PType>commands;
		std::string checkMsgFormat( std::string cmdStr );
		std::string getRidOfCmdName( std::string cmdStr );

		int					srvFd;
		int					port;
		std::string			pass;
		struct sockaddr_in	address;
		int					addrlen;

		Server( Server const & _ot );
		Server operator=( Server const & _ot ); 

	public:
		void create();
		void connectUsers( void );
		void clientRequest( void );
		void disconnectClient( size_t const id );
		int  readRequest( size_t const id );
		void executeCommand( size_t const id );
		// std::vector<User*> &getUserData();
		
		Server( std::string const & _port, std::string const & _pass);
		~Server();

		//commands
		t_msg msg;
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

		void passw( std::string const &str, User &user) { std::cout << str << " User: " << user.getNick();}

};

#endif