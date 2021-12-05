#ifndef User_hpp
#define User_hpp

#include <iostream>
#include <queue>
#include <map>

class User {
    private:
        std::string                 username;
        std::string                 nickname;
        std::string                 password;

        std::string                 realname;
        std::string                 hostname;
        std::string                 servername;
        std::vector<std::string>    channels;
        std::string                 currentChannel;
        std::map<std::string, bool> oper;

        int                         fd;
        int                         srvFd;
        int                         registred;
        bool                        breakconnect;

        User();
        User( User const & _ot );
        User operator=( User const & _ot );
    
    public:
        std::vector<std::string>    messages;

        std::string const & getNick( void ) const;
        std::string const & getUser( void ) const;
        std::string const & getPass( void ) const;

        std::string const & getRealn( void ) const;
        std::string const & getHostn( void ) const;
        std::string const & getServern( void ) const;
        int const & getFd( void ) const;
        int const & getRegistred( void ) const;
        bool const & getBreakconnect( void ) const;

        void setNick( std::string const & nick );
        void setUser( std::string const & name );
        void setPass( std::string const & pass );

        void setRealn( std::string const & pass );
        void setHostn( std::string const & pass );
        void setServern( std::string const & pass );
        void setFd( int const & fd );
        void setRegistred( int const & registred );

        void checkConnection( std::string const & mess );

        // channels
        void addChannel( std::string & name );
        void leaveChannel( std::string & name );
        void setActiveChannel( std::string &name );
        std::string getActiveChannel( void ) const;
        std::vector<std::string> getChannelList( void ) const;

        User(int serverSocket);
        ~User();
};

#endif