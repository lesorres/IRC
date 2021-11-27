#include "Command.hpp"

Command::Command(){
}

// //коструктор для Server
// Command::Command(Server &serv) : userData(serv.getUserData()) {
//     // setUserData(serv.getUserData());
// }

std::vector<User *>Command::getUserData(){
    return userData;
}

Command::~Command(){}

void Command::setUserData(std::vector<User*>&userData){
    this->userData = userData;
}
