#ifndef User_hpp
#define User_hpp

#include <iostream>
#include <queue>

class User {
    private:
        std::string username;
        std::string nickname;
        std::string password;
        bool        registred;


        User( User const & _ot );
        User operator=( User const & _ot );
    
    public:
        std::string text;
        std::string tail;

        std::string const & getNick( void ) const;
        std::string const & getUser( void ) const;
        std::string const & getPass( void ) const;

        void setNick( std::string const & nick );
        void setUser( std::string const & name );
        void setPass( std::string const & pass );

        User();
        ~User();
};

#endif