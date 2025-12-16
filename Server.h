#pragma once
#include <atomic>
#include <vector>
#include <thread>
#include <memory>
#include "Socket.h"
#include "ClientSession.h"

#include "Storage.h"
extern Storage g_storage;

class Server
{
    public:
    explicit Server(unsigned short);
    ~Server();

    public:
    void start();
    void stop();

    private:
    void acceptLoop();

    Socket listener;
    std::vector<std::unique_ptr<ClientSession>> clients;

    std::thread threadAccept;

    //unsigned short m_port;
    std::atomic<bool> running{false};
};