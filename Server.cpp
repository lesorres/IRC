#include "Server.hpp"

void Server::create( void )
{
    struct protoent	*pe;

    pe = getprotobyname("tcp");
    if ((srvFd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(srvPort);
    if (bind(srvFd, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(srvFd, 5) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    fcntl(srvFd, F_SETFL, O_NONBLOCK);
    /* 
    / F_SETFL устанавливет флаг O_NONBLOCK для подаваемого дескриптора 
    / O_NONBLOCK устанавливает  режим  неблокирования, 
    / что позволяет при ошибке вернуть чтение другим запросам 
    */
}

void Server::run( void )
{
    while(true)
    {
        connectUsers();
        clientRequest();
    }
}

void Server::connectUsers( void )
{
    int new_client_fd;

    if ((new_client_fd = accept(srvFd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) > 0) 
    {
        struct pollfd nw;

        nw.fd = new_client_fd;
        nw.events = POLLIN;
        nw.revents = 0;
        userData.push_back(new User(srvFd));
        userFds.push_back(nw);
        userData[userData.size() - 1]->setFd(new_client_fd);
        std::cout << "New client on " << new_client_fd << " socket." << "\n";
    }
}

void Server::disconnectClient( size_t const id )
{
    if (userData[id]->getNick().empty())
        std::cout << "Socket " << userFds[id].fd << " gone away.\n";
    else
        std::cout << userData[id]->getNick() << " gone away.\n";
    close(userFds[id].fd);
    userFds.erase(userFds.begin() + id);
    userData.erase(userData.begin() + id);
}

void Server::clientRequest( void )
{
    int ret = poll(userFds.data(), userFds.size(), 0);
    if (ret != 0)
    {
        for (size_t id = 0; id < userFds.size(); id++)
        {
            if (userFds[id].revents & POLLIN)
            {
                if (readRequest(id) <= 0)
                    disconnectClient(id);
                else if (!userData[id]->getBreakconnect())
                    executeCommand(id);
                userFds[id].revents = 0;
            }
        }
    }
}

int  Server::readRequest( size_t const id )
{
    char buf[BUF_SIZE + 1];
    int bytesRead = 0;
    int rd;
    std::string text;
    if (userData[id]->messages.size() > 0)
		text = userData[id]->messages.front();
    while ((rd = recv(userFds[id].fd, buf, BUF_SIZE, 0)) > 0)
    {
        buf[rd] = 0;
        bytesRead += rd;
        text += buf;
        if (text.find("\n") != std::string::npos)
            break;
    }
    while (text.find("\r") != std::string::npos)      // Удаляем символ возврата карретки
        text.erase(text.find("\r"), 1);               // из комбинации CRLF
    userData[id]->checkConnection(text);
    userData[id]->messages = split(text, "\n");
    return (bytesRead);
}

void Server::execute(std::string const &com, User &user){
    try
    {
        (this->*(commands.at(com)))( user );
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Server::executeCommand( size_t const id )
{
    parseMsg(userData[id]->messages[0]);
    // cmd.msg.cmd = userData[id]->messages[0].substr(0, 4);
    // userData[id]->messages[0].erase(0, 5);
    // CHECK REGISTER //
    // if (userData[id]->getRegistred() != 3 && msg.cmd != "PASS" && msg.cmd != "NICK" &&\
    //     msg.cmd != "USER" && msg.cmd != "QUIT")
    //     send(userFds[id].fd, "You not registred\n", 19, 0);
    // else
    // {
    //     send(userFds[id].fd, "MOTD\n", 5, 0);
    // }
    
    //////


    //
    // if ((msg.cmd != "USER" && msg.cmd != "PASS" && msg.cmd != "NICK") && userData[id]->getRegistred() != 3 ) {
    //      cleanMsgStruct();
	// 	    errorMEss(451, *userData[id]);
    //      return ;
    // }


    execute(msg.cmd, *userData[id]); // <---- Command HERE
	
	cleanMsgStruct();

    //////
    if (userData[id]->getNick().empty())
        std::cout << "< socket " << userFds[id].fd << " >: " << userData[id]->messages[0] << "\n";
    else
        std::cout << "< " << userData[id]->getNick() << " >: " << userData[id]->messages[0] << "\n";
    userData[id]->messages.erase(userData[id]->messages.begin());
    if (!userData[id]->messages.empty())
        executeCommand(id);
}

void Server::initCommandMap( void )
{
    commands.insert(std::make_pair("PASS", &Server::pass));
    commands.insert(std::make_pair("NICK", &Server::nick));
    commands.insert(std::make_pair("USER", &Server::user));
    commands.insert(std::make_pair("OPER", &Server::oper));
    commands.insert(std::make_pair("QUIT", &Server::quit));
    // commands.insert(make_pair("PRIVMSG", &Server::privmsg));
    // commands.insert(make_pair("AWAY", &Server::away));
    // commands.insert(make_pair("NOTICE", &Server::notice));
    commands.insert(std::make_pair("WHO", &Server::who));
    commands.insert(std::make_pair("JOIN", &Server::join));
    // commands.insert(make_pair("WHOIS", &Server::whois));
    // commands.insert(make_pair("WHOWAS", &Server::whowas));
    // commands.insert(make_pair("MODE", &Server::mode));
    // commands.insert(make_pair("TOPIC", &Server::topic));
    // commands.insert(make_pair("INVITE", &Server::invite));
    // commands.insert(make_pair("KICK", &Server::kick));
    // commands.insert(make_pair("PART", &Server::part));
    // commands.insert(make_pair("NAMES", &Server::names));
    // commands.insert(make_pair("LIST", &Server::list));
    // commands.insert(make_pair("WALLOPS", &Server::wallops));
    // commands.insert(make_pair("PING", &Server::ping));
    // commands.insert(make_pair("PONG", &Server::pong));
    // commands.insert(make_pair("ISON", &Server::ison));
    // commands.insert(make_pair("USERHOST", &Server::userhost));
    // commands.insert(make_pair("VERSION", &Server::version));
    // commands.insert(make_pair("INFO", &Server::info));
    // commands.insert(make_pair("ADMIN", &Server::admin));
    // commands.insert(make_pair("TIME", &Server::time));
    // commands.insert(make_pair("REHASH", &Server::rehash));
    // commands.insert(make_pair("RESTART", &Server::restart));
    // commands.insert(make_pair("KILL", &Server::kill));
}

Server::Server( std::string const & _port, std::string const & _pass)
{
	msg.paramN = 0;
    initCommandMap();
	serverName = "IRC16.11";

    // (this->*(command.at("PASS")))("DATA", *bob);
    try
    {
        if (_port.find_first_not_of("0123456789") != std::string::npos)
            throw std::invalid_argument("Port must contain only numbers");
        srvPort = atoi(_port.c_str());
        if (srvPort < 1000 || srvPort > 65555) // надо взять правельный рендж портов...
            throw std::invalid_argument("Port out of range");
    }
    catch ( std::exception & e)
    {
        std::cerr << e.what() << "\n";
        exit(EXIT_FAILURE);
    }
    srvPass = _pass;
    addrlen = sizeof(address);
    std::cout << "Done!\n";
}

Server::~Server()
{
    std::cout << "Destroyed.\n";
}
