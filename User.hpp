#ifndef User_hpp
#define User_hpp

#include <iostream>

class User {
    private:
        std::string _username;
        std::string _nickname;
        std::string _password;

        User( User const & _ot );
        User operator=( User const & _ot );
    public:

        std::string const & getNick( void ) const;
        std::string const & getName( void ) const;

        void setNick( std::string const & nick );
        void setName( std::string const & name );

        User();
        ~User();
};

#endif