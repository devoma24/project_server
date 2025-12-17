#include "Server.h"
#include <iostream>
#include <thread>
#include "Socket.h"

Server::Server(unsigned short port, size_t threads) : pool_(threads)
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
    LOG_INFO("Server started");
    running = true;
    threadAccept = std::thread(&Server::acceptLoop, this);
}

void Server::stop()
{
    stopping_ = true;
    running = false;

    listener.close();

    if(threadAccept.joinable())
    {
        threadAccept.join();
    }

    pool_.shutdown();
}

void Server::acceptLoop()
{
    while(running)
    {
        try
        {
            LOG_INFO("Client connected");
            auto client = std::make_shared<Socket>(listener.accept());
            std::cout << "Client connetcted" << std::endl;
            pool_.submit([client, this]() {
                ClientSession session(std::move(*client), storage_, stopping_ );
                session.run();
            });
        }
        catch(const std::exception& e)
        {
            if(running)
            {
                LOG_ERROR("accept error: " + std::string(e.what()));
                std::cout << "Accept error" << std::endl;
            }
        }
        
    }
}