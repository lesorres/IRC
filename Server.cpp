#include "Server.hpp"
#include <fcntl.h>
#include <unistd.h>

void Server::create( const char * _port, const char * _pass )
{
    struct protoent	*pe;

    this->setPort(atoi(_port));
    pass = _pass;
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



///  Говнокод ... 
User * Server::newUser(struct pollfd nw)
{
    // send message to new connected user //
    send(nw.fd, "SERVER PASSWORD: ", 18, 0);
    // try get data from user //
    int ret = poll(&nw, 1, 20000);
    if (ret == -1)
    {
        perror("poll");
        exit(EXIT_FAILURE);
    }
    else if (ret == 0)
    {
        send(nw.fd, "timeout\n", 9, 0);
        close(nw.fd);
        return NULL;
    }
    else
    {
        // get message from user //
        if (nw.revents & POLLIN)
        {
            //std::string *buf = new std::string[100];
            std::string buf[100];
            int r = recv(nw.fd, buf, 100, 0);
            if (r <= 0)
            {
                printf("client #%d gone away\n", nw.fd);
                close(nw.fd);
                return NULL;
            }
            else
            {
                std::string tmp = (char *)buf;
                tmp.pop_back();

                if (tmp != pass)
                {
                    send(nw.fd, "incorrect password\n", 20, 0);
                    close(nw.fd);
                    return NULL;
                }
                return (new User);
            }
        }
    }
    return NULL;
}

void Server::setUser(User * user, struct pollfd nw)
{
    // send message to new connected user //
    send(nw.fd, "USERNAME: ", 11, 0);
    // try get data from user //
    int ret = poll(&nw, 1, 20000);
    if (ret == -1)
    {
        perror("poll");
        exit(EXIT_FAILURE);
    }
    else if (ret == 0)
    {
        send(nw.fd, "timeout\n", 9, 0);
        close(nw.fd);
        return ;
    }
    else
    {
        // get message from user //
        if (nw.revents & POLLIN)
        {
            //std::string *buf = new std::string[100];
            std::string buf[100];
            int r = recv(nw.fd, buf, 100, 0);
            if (r <= 0)
            {
                printf("client #%d gone away\n", nw.fd);
                close(nw.fd);
                return ;
            }
            else
            {
                std::string tmp = (char *)buf;
                tmp.pop_back();
                user->setName(tmp);
            }
        }
    }
}
// Конец говнокода


void Server::connectUsers( void )
{
    int new_client_fd;

    if ((new_client_fd = accept(srvFd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) > 0)
    // {
    //     perror("accept");
    //     exit(EXIT_FAILURE);
    // }
    {
        struct pollfd nw;
        nw.fd = new_client_fd;
        nw.events = POLLIN;

        User * new_client = this->newUser(nw);
        if (!new_client)
            return ;
        this->setUser(new_client, nw);
        // add new client to server //
        userData.push_back(new_client);
        userFds.push_back(nw);
        std::cout << "new client: " << userData[userData.size() - 1]->getName() << " fd=" << new_client_fd << "\n";
        send(nw.fd, "me: ", 5, 0);
    }
}

void Server::clientRequest( void )
{
    
    int ret = poll(userFds.data(), userFds.size(), 0);
    if (ret != 0)
    {
        for (size_t i = 0; i < userFds.size(); i++)
        {
            if (userFds[i].revents & POLLIN)
            {
                std::string buf[100];
                int bytesRead = recv(userFds[i].fd, buf, 100, 0);
                if (bytesRead <= 0)
                {
                    std::cout << userData[i]->getName() << " gone away.\n";
                    close(userFds[i].fd);
                    userFds.erase(userFds.begin() + i);
                    userData.erase(userData.begin() + i);
                }
                else
                {
                    for (size_t j = 0; j < userFds.size(); j++)
                        if (userFds[i].fd != userFds[j].fd)
                        {
                            std::string tmp = userData[i]->getName();
                            tmp += ": ";
                            send(userFds[j].fd, &tmp, tmp.size() + 1, 0);
                            send(userFds[j].fd, buf, bytesRead, 0);
                        }
                    send(userFds[i].fd, "me: ", 5, 0);
                    std::cout << "< " << userData[i]->getName() << " say >: " << (char *)buf;
                }
            }
            userFds[i].revents = 0;
        }
    }
}

int const & Server::getPort( void ) const { return (port); }
void Server::setPort( int _port ) { port = _port; }

Server::Server()
{
    addrlen = sizeof(address);
    std::cout << "Done!\n";
}

Server::~Server()
{
    std::cout << "Destroyed.\n";
}