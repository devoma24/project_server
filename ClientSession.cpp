#include "ClientSession.h"
#include <iostream>

#include "CommandParser.h"
#include "Server.h"

ClientSession::ClientSession(Socket client):
socket(std::move(client)), worker(&ClientSession::run, this) {}

ClientSession::~ClientSession()
{
    if(worker.joinable())
    {
        worker.join();
    }
    std::cout << "closed session" << std::endl;
}

void ClientSession::run()
{
    try
    {
        std::cout << "Client session started" << std::endl;

        while(true)
        {
            std::string input = readMessage(socket);
            Command cmd = CommandParser::parse(input);

            std::string response;
            switch(cmd.type)
            {
                case CommandType::SET:
                {
                    g_storage.set(cmd.key, cmd.value);
                    response = "OK";
                    break;
                }
                case CommandType::GET:
                {
                    auto answer = g_storage.get(cmd.key);
                    response = answer? *answer : "NOT_FOUND";
                    break;
                }
                case CommandType::DEL:
                {
                    response = g_storage.del(cmd.key)? "DELETED" : "NOT_FOUND";
                    break;
                }
                case CommandType::EXIT:
                {
                    sendMessage(socket, "BYE");
                    return;
                }
                default:
                {
                    response = "ERR invalid command";
                    break;
                }
            }
            sendMessage(socket, response);
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