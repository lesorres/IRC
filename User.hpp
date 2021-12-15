#ifndef User_hpp
#define User_hpp

#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <queue>
#include <map>

#define REGISTRED   0b00000001
#define OPERATOR    0b00000010
#define AWAY        0b00000100

class User {
    private:
        std::string                 username;
        std::string                 nickname;
        std::string                 password;

        std::string                 ipv4;
        std::string                 realname;
        std::string                 hostname;
        std::string                 servername;
        std::string                 quitMess;
        std::vector<std::string>    channels;
        std::vector<std::string>    opchannels;
        std::string                 activeChannel;

        struct sockaddr_in          sockaddr;
        int                         fd;
        int                         srvFd;
        int                         registred;
        char                        userFlags;
        bool                        breakconnect;

        User();
        User &operator=( User const & src );
    
    public:
        User( User const & src );
        std::vector<std::string>    messages;

        std::string const & getNick( void ) const;
        std::string const & getUser( void ) const;
        std::string const & getPass( void ) const;
        std::string const & getIp( void ) const;
        struct sockaddr_in & getSockAddr( void );

        std::string const & getReal( void ) const;
        std::string const & getHost( void ) const;
        std::string const & getServer( void ) const;
        std::string const & getQuitMess( void ) const;
        int const & getFd( void ) const;
        int const & getRegistred( void ) const;
        bool const & getBreakconnect( void ) const;
        char const & getUserFlags( void ) const;	

        void setNick( std::string const & nick );
        void setUser( std::string const & name );
        void setPass( std::string const & pass );

        void setReal( std::string const & relaname );
        void setHost( std::string const & host );
        void setServer( std::string const & server );
        void setQuitMess( std::string const & mess );
        void setRegistred( int const & registred );
        void setUserFlags( char const & flags );

        void checkConnection( std::string const & mess );
        bool empty();

        // channels
        void addChannel( std::string & name );
        void imOper( std::string const & channelname );
        void imNotOper( std::string const & channelname );
        void leaveChannel( std::string & name );
        void setActiveChannel( std::string &name );
        std::string getActiveChannel( void ) const;
        std::vector<std::string> getChannelList( void ) const;
		std::vector<std::string> getOpChannelList( void ) const;

        User(int serverSocket, int mySocket, struct sockaddr_in address);
        ~User();
};

#endif