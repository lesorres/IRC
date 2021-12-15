#include "User.hpp"
#include "Utils.hpp"

User::User(int serverSocket, int mySocket, struct sockaddr_in address)
{
    username = "";
    nickname = "";
    password = "";
    realname = "";
    hostname = "";
    quitMess = "";
    servername = "";
    activeChannel = "";
    userFlags = 0;
    registred = 0;
    breakconnect = false;
    srvFd = serverSocket;
    fd = mySocket;
    sockaddr = address;
    char ip[INET_ADDRSTRLEN];
    inet_ntop( AF_INET, &sockaddr.sin_addr, ip, INET_ADDRSTRLEN );
    ipv4 = ip;
    std::cout << "ip=" << ipv4 << "\n";
}

User::User( User const & src )
{
	*this = src;
}

User &User::operator=( User const & src )
{
	if (this == &src)
		return(*this);
	username = src.username;
	nickname = src.nickname;
	password = src.password;
	realname = src.realname;
	hostname = src.hostname;
	servername = src.servername;
	quitMess = src.quitMess;
	channels = src.channels;
	activeChannel = src.activeChannel;
	fd = src.fd;
	srvFd = src.srvFd;
	registred = src.registred;
	breakconnect = src.breakconnect;
	messages = src.messages;
	return(*this);
}

User::~User() {}

std::string const & User::getNick( void ) const { return(nickname); }
std::string const & User::getUser( void ) const { return(username); }
std::string const & User::getPass( void ) const { return(password); }
std::string const & User::getIp( void ) const { return(ipv4); }

std::string const & User::getReal( void ) const { return(realname); }
std::string const & User::getHost( void ) const { return(hostname); }
std::string const & User::getServer( void ) const { return(servername); }
std::string const & User::getQuitMess( void ) const { return(quitMess); }
int const & User::getFd( void ) const { return(fd); }
int const & User::getRegistred( void ) const { return(registred); }
bool const & User::getBreakconnect( void ) const { return(breakconnect); }
char const & User::getUserFlags( void ) const { return userFlags; }
struct sockaddr_in & User::getSockAddr( void ) { return(sockaddr); }

void User::setNick( std::string const & nick ) { nickname = nick; }
void User::setUser( std::string const & name ) { username = name; }
void User::setPass( std::string const & pass ) { password = pass; }

void User::setReal( std::string const & real ) { realname = real; }
void User::setHost( std::string const & host ) { hostname = host; }
void User::setServer( std::string const & server ) { servername = server; }
void User::setQuitMess( std::string const & mess ) { quitMess = mess; }
void User::setRegistred( int const & status ) { registred = status; }
void User::setUserFlags( char const & flag ) { userFlags = flag; }

void User::imOper( std::string const & name ) { opchannels.push_back(name); }
void User::imNotOper( std::string const & name ) { eraseString(opchannels, name); }
void User::addChannel(std::string & name) { channels.push_back(name); }
std::vector<std::string> User::getChannelList( void ) const { return (channels); }
std::vector<std::string> User::getOpChannelList( void ) const { return (opchannels); }
void User::setActiveChannel( std::string &name ) { activeChannel = name; }
std::string User::getActiveChannel( void ) const { return(activeChannel); }
void User::leaveChannel(std::string & name)
{
    if (name == activeChannel)
        activeChannel = "";
    eraseString(channels, name);
}

void User::checkConnection( std::string const & mess )
{
    if (mess.find_last_of("\n") != mess.size() - 1)
        breakconnect = true;
    else if (breakconnect)
        breakconnect = false;
}

bool User::empty()
{
    int i;
    i = username.empty() \
    + nickname.empty() \
    + password.empty() \
    + realname.empty() \
    + hostname.empty() \
    + servername.empty() \
    + channels.empty() \
    + activeChannel.empty();
    if (i == 8)
        return (1);
    return (0);
}
