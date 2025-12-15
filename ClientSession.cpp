#include "ClientSession.h"
#include <iostream>

ClientSession::ClientSession(Socket client):
socket(std::move(client)), worker(&ClientSession::run, this) {}

ClientSession::~ClientSession()
{
    running = false;
    if(worker.joinable())
    {
        worker.join();
    }
}

void ClientSession::run()
{
    try
    {
        std::cout << "Start work witch client" << std::endl;
        std::string data {};
        while(running)
        {
            data = socket.receive();
            if(data.empty())
            {
                break;
            }

            std::cout << "Client says: " << data << std::endl;

            data = "Echo: " + data;
            socket.sendAll(data);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Client error: " << e.what() << '\n';
    }
    
}