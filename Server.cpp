#include "Server.hpp"

void Server::create()
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
    address.sin_port = htons(port);
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

void Server::connectUsers( void )
{
    int new_client_fd;

    if ((new_client_fd = accept(srvFd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) > 0) 
    {
        struct pollfd nw;

        nw.fd = new_client_fd;
        nw.events = POLLIN;
        nw.revents = 0;
        userData.push_back(new User);
        userFds.push_back(nw);
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
                else
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
    while ((rd = recv(userFds[id].fd, buf, BUF_SIZE, 0)) > 0)
    {
        buf[rd] = 0;
        bytesRead += rd;
        userData[id]->text += buf;
        userData[id]->setFd(userFds[id].fd);
        if (userData[id]->text.find("\n") != std::string::npos)
            break;
    }
    while (userData[id]->text.find("\r") != std::string::npos)      // Удаляем символ возврата карретки
        userData[id]->text.erase(userData[id]->text.find("\r"), 1); // отправляемый старыми клиентами на MacOS
    return (bytesRead);
}

void Server::executeCommand( size_t const id )
{
    userData[id]->tail.clear();
    if (userData[id]->text.find("\n") != userData[id]->text.size() - 1)
    {
        userData[id]->tail = userData[id]->text.substr(userData[id]->text.find("\n") + 1);
        userData[id]->text.erase(userData[id]->text.find("\n") + 1);
    }
    for (size_t j = 0; j < userFds.size(); j++)
    {
        if (userData[id]->text.substr(0, 4) == "PASS")
        {
            std::string tmp = userData[id]->text.substr(5);
            tmp.pop_back();
            userData[id]->setPass(tmp);
        }
        else if (userData[id]->text.substr(0, 4) == "NICK")
        {
            std::string tmp = userData[id]->text.substr(5);
            tmp.pop_back();
            userData[id]->setNick(tmp);
        }
        else if (userData[id]->text.substr(0, 4) == "USER")
        {
            std::string tmp = userData[id]->text.substr(5);
            tmp.pop_back();
            userData[id]->setUser(tmp);
        }
        else if (userFds[id].fd != userFds[j].fd)
        {
            std::string tmp = userData[id]->getNick();
            tmp += ": ";
            send(userFds[j].fd, &tmp, tmp.size() + 1, 0);
            send(userFds[j].fd, userData[id]->text.c_str(), userData[id]->text.size(), 0);
        }
    }
    if (userData[id]->getNick().empty())
        std::cout << "< socket " << userFds[id].fd << " >: " << userData[id]->text;
    else
        std::cout << "< " << userData[id]->getNick() << " >: " << userData[id]->text;
    userData[id]->text.clear();
    if (!userData[id]->tail.empty())
    {
        userData[id]->text = userData[id]->tail;
        executeCommand(id);
    }
}

Server::Server( std::string const & _port, std::string const & _pass)
{
    cmd_map.insert(make_pair("PASS", &Command::pass);
    cmd_map.insert(make_pair("NICK", &Command::nick);
    cmd_map.insert(make_pair("USER", &Command::user);
    // cmd_map.insert(make_pair("OPER", &Command::oper);
    // cmd_map.insert(make_pair("QUIT", &Command::quit);
    // cmd_map.insert(make_pair("PRIVMSG", &Command::privmsg);
    // cmd_map.insert(make_pair("AWAY", &Command::away);
    // cmd_map.insert(make_pair("NOTICE", &Command::notice);
    // cmd_map.insert(make_pair("WHO", &Command::who);
    // cmd_map.insert(make_pair("WHOIS", &Command::whois);
    // cmd_map.insert(make_pair("WHOWAS", &Command::whowas);
    // cmd_map.insert(make_pair("MODE", &Command::mode);
    // cmd_map.insert(make_pair("TOPIC", &Command::topic);
    // cmd_map.insert(make_pair("JOIN", &Command::join);
    // cmd_map.insert(make_pair("INVITE", &Command::invite);
    // cmd_map.insert(make_pair("KICK", &Command::kick);
    // cmd_map.insert(make_pair("PART", &Command::part);
    // cmd_map.insert(make_pair("NAMES", &Command::names);
    // cmd_map.insert(make_pair("LIST", &Command::list);
    // cmd_map.insert(make_pair("WALLOPS", &Command::wallops);
    // cmd_map.insert(make_pair("PING", &Command::ping);
    // cmd_map.insert(make_pair("PONG", &Command::pong);
    // cmd_map.insert(make_pair("ISON", &Command::ison);
    // cmd_map.insert(make_pair("USERHOST", &Command::userhost);
    // cmd_map.insert(make_pair("VERSION", &Command::version);
    // cmd_map.insert(make_pair("INFO", &Command::info);
    // cmd_map.insert(make_pair("ADMIN", &Command::admin);
    // cmd_map.insert(make_pair("TIME", &Command::time);
    // cmd_map.insert(make_pair("REHASH", &Command::rehash);
    // cmd_map.insert(make_pair("RESTART", &Command::restart);
    // cmd_map.insert(make_pair("KILL", &Command::kill);
    
    // cmd.setUserData(getUserData());
    try
    {
        port = atoi(_port.c_str());
        if (port < 1000 || port > 65555 || _port.find_first_not_of("0123456789") != std::string::npos) // надо взять правельный рендж портов...
            throw std::invalid_argument("Port out of range");
    }
    catch ( std::exception & e)
    {
        std::cerr << e.what() << "\n";
        exit(EXIT_FAILURE);
    }
    pass = _pass;
    addrlen = sizeof(address);
    std::cout << "Done!\n";
}

Server::~Server()
{
    std::cout << "Destroyed.\n";
}

std::vector<User*> &Server::getUserData(){
    return userData;
}