#ifndef Server_hpp
#define Server_hpp

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <poll.h>
#include <vector>
#include <iterator>
#include "User.hpp"

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

        int const & getPort( void ) const;
        void setPort( int _port );

        void create( const char * port, const char * pass );
        void connectUsers( void );
        void clientRequest( void );

        User * newUser(struct pollfd nw);
        void setUser(User * user, struct pollfd nw);
        
        Server();
        ~Server();

};

#endif