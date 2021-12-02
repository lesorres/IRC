#include "Command.hpp"

// Server::Server()
// {
// 	msg.paramN = 0;
//     cmd_map.insert(make_pair("PASS", &Server::pass));
//     cmd_map.insert(make_pair("NICK", &Server::nick));
//     cmd_map.insert(make_pair("USER", &Server::user));
//     cmd_map.insert(make_pair("OPER", &Server::oper));
//     cmd_map.insert(make_pair("QUIT", &Server::quit));
//     // cmd_map.insert(make_pair("PRIVMSG", &Server::privmsg);
//     // cmd_map.insert(make_pair("AWAY", &Server::away);
//     // cmd_map.insert(make_pair("NOTICE", &Server::notice);
//     // cmd_map.insert(make_pair("WHO", &Server::who);
//     // cmd_map.insert(make_pair("WHOIS", &Server::whois);
//     // cmd_map.insert(make_pair("WHOWAS", &Server::whowas);
//     // cmd_map.insert(make_pair("MODE", &Server::mode);
//     // cmd_map.insert(make_pair("TOPIC", &Server::topic);
//     // cmd_map.insert(make_pair("JOIN", &Server::join);
//     // cmd_map.insert(make_pair("INVITE", &Server::invite);
//     // cmd_map.insert(make_pair("KICK", &Server::kick);
//     // cmd_map.insert(make_pair("PART", &Server::part);
//     // cmd_map.insert(make_pair("NAMES", &Server::names);
//     // cmd_map.insert(make_pair("LIST", &Server::list);
//     // cmd_map.insert(make_pair("WALLOPS", &Server::wallops);
//     // cmd_map.insert(make_pair("PING", &Server::ping);
//     // cmd_map.insert(make_pair("PONG", &Server::pong);
//     // cmd_map.insert(make_pair("ISON", &Server::ison);
//     // cmd_map.insert(make_pair("USERHOST", &Server::userhost);
//     // cmd_map.insert(make_pair("VERSION", &Server::version);
//     // cmd_map.insert(make_pair("INFO", &Server::info);
//     // cmd_map.insert(make_pair("ADMIN", &Server::admin);
//     // cmd_map.insert(make_pair("TIME", &Server::time);
//     // cmd_map.insert(make_pair("REHASH", &Server::rehash);
//     // cmd_map.insert(make_pair("RESTART", &Server::restart);
//     // cmd_map.insert(make_pair("KILL", &Server::kill);
// }

// //коструктор для Server
// Server::Server(Server &serv) : userData(serv.getUserData()) {
//     // setUserData(serv.getUserData());
// }

// std::vector<User *>Server::getUserData(){
//     return userData;
// }


// Server::~Server(){}

// void Server::setUserData(std::vector<User*>&userData){
//     this->userData = userData;
// }

// void Server::execute(std::string const &com, User &user, std::vector<User*> & userData){
//     try
//     {
//         (this->*(cmd_map.at(com)))( user, userData);
//         // user.messages.erase(user.messages.begin());
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
// }

// void Server::cleanMsgStruct()
// {
// 	msg.prefx.clear();
// 	msg.cmd.clear();
// 	msg.midParams.clear();
// 	msg.trailing.clear();
// 	msg.paramN = 0;
// }