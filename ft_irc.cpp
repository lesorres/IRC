#include "Server.hpp"

int     main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " port pass\n";
        return (1);
    }

    Server server;

    server.create(argv[1], "qwerty");

    while(true)
    {
        server.connectUsers();
        server.clientRequest();
    }

    return (0);
}