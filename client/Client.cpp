#include "../include/Socket.h"
#include <iostream>
#include <string>
#include <arpa/inet.h>

std::string readMessage(Socket& s)
{
    uint32_t size_net;
    s.recvAll(&size_net, sizeof(size_net));

    uint32_t size = ntohl(size_net);

    std::string data(size, '\0');
    s.recvAll(data.data(), size);

    return data;
}

void sendMessage(Socket& s, const std::string& msg)
{
    uint32_t size_net = htonl(static_cast<uint32_t>(msg.size()));
    s.sendAll(&size_net, sizeof(size_net));
    s.sendAll(msg.data(), msg.size());
}

int main()
{
    try
    {
        Socket socket;

        socket.connect("127.0.0.1", 8080);

        std::cout << "Connect server" << std::endl;
        std::string input;
        while(true)
        {
            std::getline(std::cin, input);
            if(input == "exit")
            {
                break;
            }

            sendMessage(socket, input);
            
            std::string responce = readMessage(socket);
            std::cout << "Server replied: " << responce << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}