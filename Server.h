#pragma once
#include <atomic>
#include <vector>
#include <thread>
#include <memory>
#include "Socket.h"
#include "ClientSession.h"

#include "ThreadPool.h"

#include "Storage.h"
extern Storage g_storage;

class Server
{
    public:
    explicit Server(unsigned short, size_t);
    ~Server();

    public:
    void start();
    void stop();

    private:
    void acceptLoop();

    Socket listener;

    std::thread threadAccept;

    ThreadPool pool_;
    //unsigned short m_port;
    std::atomic<bool> running{false};
};