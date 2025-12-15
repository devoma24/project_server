#pragma once
#include "Socket.h"
#include <thread>

class ClientSession
{
    public:
    explicit ClientSession(Socket);
    ~ClientSession();

    ClientSession(const ClientSession&) = delete;
    ClientSession& operator= (const ClientSession&) = delete;

    private:

    std::string readMessage(Socket&);
    void sendMessage(Socket&, const std::string&);

    void run();

    Socket socket;
    std::thread worker;
};