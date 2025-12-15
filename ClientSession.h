#pragma once
#include "Socket.h"
#include <thread>
#include <atomic>

class ClientSession
{
    public:
    explicit ClientSession(Socket);
    ~ClientSession();

    ClientSession(const ClientSession&) = delete;
    ClientSession& operator= (const ClientSession&) = delete;

    private:
    void run();

    Socket socket;
    std::thread worker;
    std::atomic<bool> running{true};
};