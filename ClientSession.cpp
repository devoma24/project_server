#include "ClientSession.h"
#include <iostream>

ClientSession::ClientSession(Socket client):
socket(std::move(client)), worker(&ClientSession::run, this) {}

ClientSession::~ClientSession()
{
    if(worker.joinable())
    {
        worker.join();
    }
}

void ClientSession::run()
{
    try
    {
        std::cout << "Client session started" << std::endl;

        while(true)
        {
            std::string data = readMessage(socket);

            std::cout << "Client says: " << data << std::endl;
            data = "Echo: " + data;
            sendMessage(socket, data);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Client error: " << e.what() << '\n';
    }   
}

std::string ClientSession::readMessage(Socket& s)
{
    //[4 bytes - lenght message][N bytes - yourself message]
    uint32_t size_net;
    s.recvAll(&size_net, sizeof(size_net));

    uint32_t size = ntohl(size_net);
    std::string data(size, '\0');

    s.recvAll(data.data(), size);

    return data;
}

void ClientSession::sendMessage(Socket& s, const std::string& msg)
{
    uint32_t size_net = htonl(static_cast<uint32_t>(msg.size()));
    s.sendAll(&size_net, sizeof(size_net));
    s.sendAll(msg.data(), msg.size());
}