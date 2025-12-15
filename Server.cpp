#include "Server.h"
#include <iostream>
#include <thread>
#include "Socket.h"

Server::Server(unsigned short port)
{
    listener.bind(port);
    listener.listen(10);
}

Server::~Server()
{
    stop();
}

void Server::start()
{
    running = true;
    threadAccept = std::thread(&Server::acceptLoop, this);
}

void Server::stop()
{
    running = false;

    if(threadAccept.joinable())
    {
        threadAccept.join();
    }

    clients.clear();
}

void Server::acceptLoop()
{
    while(running)
    {
        try
        {
            Socket client = listener.accept();
            std::cout << "Client connetcted" << std::endl;

            clients.push_back(std::make_unique<ClientSession>(std::move(client)));
        }
        catch(...)
        {
            if(running)
            {
                std::cout << "Accept error" << std::endl;
            }
        }
        
    }
}