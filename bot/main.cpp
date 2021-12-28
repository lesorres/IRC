#include "Bot.hpp"

int     main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " host port pass\n";
        return (1);
    }

    Bot bot(argv[1], argv[2], argv[3]);

    bot.create();
    bot.run();

    return (0);    
}