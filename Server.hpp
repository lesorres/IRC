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
#include "User.hpp"

#define BUF_SIZE 20

class Server {
    private:
        std::vector<struct pollfd> userFds;
        std::vector<User*> userData;
        int srvFd;
        int port;
        std::string pass;
        int addrlen;
        struct sockaddr_in address;

        Server( Server const & _ot );
        Server operator=( Server const & _ot );

    public:

        void create();
        void connectUsers( void );
        void clientRequest( void );
        void disconnectClient( size_t const id );
        int  readRequest( size_t const id );
        void executeCommand( size_t const id );
        
        Server( const char * _port, const char * _pass );
        ~Server();

};

#endif