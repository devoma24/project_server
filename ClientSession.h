#pragma once
#include "Socket.h"
#include "Storage.h"
#include <thread>

class ClientSession
{
    public:
    explicit ClientSession(Socket, Storage&);
    ~ClientSession();

    ClientSession(const ClientSession&) = delete;
    ClientSession& operator= (const ClientSession&) = delete;

    public:
    void run();

    private:

    std::string readMessage(Socket&);
    void sendMessage(Socket&, const std::string&);

    Socket socket;
    std::thread worker;

    Storage& storage_;
};