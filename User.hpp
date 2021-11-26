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
        std::map<std::string, bool> oper;
        int                         _fd;
        bool                        registred;
        User( User const & _ot );
        User operator=( User const & _ot );
    
    public:
        std::string                 text;
        std::string                 tail;

        std::string const & getNick( void ) const;
        std::string const & getUser( void ) const;
        std::string const & getPass( void ) const;

        std::string const & getRealn( void ) const;
        std::string const & getHostn( void ) const;
        std::string const & getServern( void ) const;
        int const & getFd( void ) const;
        bool const & getRegistred( void ) const;

        void setNick( std::string const & nick );
        void setUser( std::string const & name );
        void setPass( std::string const & pass );

        void setRealn( std::string const & pass );
        void setHostn( std::string const & pass );
        void setServern( std::string const & pass );
        void setFd( int const & fd );
        void setRegistred( bool const & registred );

        User();
        ~User();
};

#endif