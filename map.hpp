#include <iostream>
#include <map>
#include "Command.hpp"

typedef void (Command:: * PType)(std::string &str, User &user);

std::map<std::string, PType> cmd_map;

// в коструктор сервера:

cmd_map.insert(make_pair(num_1, num_2));
cmd_map.insert(make_pair("PASS", &Command::pass);
cmd_map.insert(make_pair("NICK", &Command::nick);
cmd_map.insert(make_pair("USER", &Command::user);
cmd_map.insert(make_pair("OPER", &Command::oper);
cmd_map.insert(make_pair("QUIT", &Command::quit);
cmd_map.insert(make_pair("PRIVMSG", &Command::privmsg);
cmd_map.insert(make_pair("AWAY", &Command::away);
cmd_map.insert(make_pair("NOTICE", &Command::notice);
cmd_map.insert(make_pair("WHO", &Command::who);
cmd_map.insert(make_pair("WHOIS", &Command::whois);
cmd_map.insert(make_pair("WHOWAS", &Command::whowas);
cmd_map.insert(make_pair("MODE", &Command::mode);
cmd_map.insert(make_pair("TOPIC", &Command::topic);
cmd_map.insert(make_pair("JOIN", &Command::join);
cmd_map.insert(make_pair("INVITE", &Command::invite);
cmd_map.insert(make_pair("KICK", &Command::kick);
cmd_map.insert(make_pair("PART", &Command::part);
cmd_map.insert(make_pair("NAMES", &Command::names);
cmd_map.insert(make_pair("LIST", &Command::list);
cmd_map.insert(make_pair("WALLOPS", &Command::wallops);
cmd_map.insert(make_pair("PING", &Command::ping);
cmd_map.insert(make_pair("PONG", &Command::pong);
cmd_map.insert(make_pair("ISON", &Command::ison);
cmd_map.insert(make_pair("USERHOST", &Command::userhost);
cmd_map.insert(make_pair("VERSION", &Command::version);
cmd_map.insert(make_pair("INFO", &Command::info);
cmd_map.insert(make_pair("ADMIN", &Command::admin);
cmd_map.insert(make_pair("TIME", &Command::time);
cmd_map.insert(make_pair("REHASH", &Command::rehash);
cmd_map.insert(make_pair("RESTART", &Command::restart);
cmd_map.insert(make_pair("KILL", &Command::kill);