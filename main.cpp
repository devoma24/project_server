#include "Server.h"
#include <iostream>

int main()
{
    try
    {
        Server server(8080);
        server.start();

        std::cout << "Press Enter to stop server...\n";
        std::cin.get();

        server.stop();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}