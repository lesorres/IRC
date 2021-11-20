#include "Server.hpp"
#include <fcntl.h>
#include <unistd.h>

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
    std::cout << userData[id]->getName() << " gone away.\n";
    close(userFds[id].fd);
    userFds.erase(userFds.begin() + id);
    userData.erase(userData.begin() + id);
}

int  Server::readRequest( size_t const id )
{
    char buf[BUF_SIZE + 1];
    int bytesRead = 0;
    userData[id]->text.clear();
    while ((bytesRead += recv(userFds[id].fd, buf, BUF_SIZE, 0)) > 0)
    {
        buf[BUF_SIZE] = 0;
        userData[id]->text += buf;
        if (userData[id]->text.find("\n") != std::string::npos)
            break;
    }
    return (bytesRead);
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
            }
            userFds[id].revents = 0;
        }
    }
}

void Server::executeCommand( size_t const id )
{
    for (size_t j = 0; j < userFds.size(); j++)
        if (userFds[id].fd != userFds[j].fd)
        {
            // std::string tmp = userData[id]->getName();
            // tmp += ": ";
            // send(userFds[j].fd, &tmp, tmp.size() + 1, 0);
            send(userFds[j].fd, userData[id]->text.c_str(), userData[id]->text.size(), 0);
        }
    std::cout << "< socket " << userFds[id].fd << " say >: " << userData[id]->text;
}

Server::Server( const char * _port, const char * _pass )
{
    try
    {
        port = atoi(_port);
        if (port < 1000 || port > 65555) // надо взять правельный рендж портов...
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
