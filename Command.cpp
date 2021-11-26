#include "Command.hpp"

Command::Command(){
}

// //коструктор для Server
// Command::Command(Server &serv) : userData(serv.getUserData()) {
//     // setUserData(serv.getUserData());
// }

Command::~Command(){}

void Command::setUserData(std::vector<User*>&userData){
    this->userData = userData;
}
