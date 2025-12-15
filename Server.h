#pragma once
#include <atomic>
#include <vector>
#include <thread>
#include <memory>
#include "Socket.h"
#include "ClientSession.h"


class Server
{
    public:
    explicit Server(unsigned short);
    ~Server();

    public:
    void start();
    void stop();

    private:
    void acceptLoop(Socket&);

    Socket listener;
    std::vector<std::unique_ptr<ClientSession>> clients;

    std::thread threadAccept;

    //unsigned short m_port;
    std::atomic<bool> running{false};
};