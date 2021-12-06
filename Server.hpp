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
#include <fstream>
#include <string>
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

class Server {
	private:
		std::string serverName;
		std::vector<struct pollfd>	userFds;
		std::vector<User*>			userData;
		typedef int (Server:: * PType)( User &user );
    	std::map<std::string, PType>	commands;
		std::map<std::string, Channel *> channels;
		t_msg 						msg;

		int					srvFd;
		int					srvPort;
		std::string			srvPass;
		struct sockaddr_in	address;
		int					addrlen;

		void 		connectUsers( void );
		void 		clientRequest( void );
		void 		disconnectClient( size_t const id );
		int  		readRequest( size_t const id );
		void 		executeCommand( size_t const id );

		// parser
		int			parseMsg(size_t id);
		int			checkMsgFormat( std::string cmdStr , size_t id);
		void		cleanMsgStruct();
		void		processWildcard();
		void		printStuct();

		// commands
		void		initCommandMap( void );
    	void		execute(std::string const &, User &);
    	int			pass(User & user );
    	int			nick(User & user );
    	int			user(User & user );
    	int			oper(User & user );
    	int			quit(User & user );
		int			who( User & user );
		int			whois( User & user );
		int			whowas( User & user );
		int			join( User & user );
		int			part( User & user );
		int			list( User & user );
		

		bool		notRegistr(User &);
    	bool		connection(User &);
    	void		motd(User &);
		void		errorMEss(int err, User &user);
		void		replyMEss(int reply, User &user, const std::string &str = "");
		void		showMEss( User const & user, Channel const * channel );

		Server( Server const & _ot );
		Server operator=( Server const & _ot ); 

	public:

		Server( std::string const & _port, std::string const & _pass);
		~Server();

		void create( void );
		void run( void );

		

		// void passw( std::string const &str, User &user) { std::cout << str << " User: " << user.getNick();}

};

#endif