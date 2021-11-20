#ifndef User_hpp
#define User_hpp

#include <iostream>

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

        std::string const & getNick( void ) const;
        std::string const & getName( void ) const;

        void setNick( std::string const & nick );
        void setName( std::string const & name );

        User();
        ~User();
};

#endif