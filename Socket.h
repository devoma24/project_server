#pragma once
#include <string>
#include <cstdint>
#include <memory>

class Socket
{
    public:
    Socket();
    ~Socket();

    public:
    Socket(Socket&&) noexcept = default;
    Socket& operator = (Socket&&) noexcept = default;

    Socket(const Socket&) = delete;
    Socket& operator =(const Socket&) = delete;

    public:
    void bind(unsigned short port);
    void listen(int);
    Socket accept();

    int send(const void*, int);
    int send(std::string&);

    int receive(void*, int);
    std::string receive();

    int sendAll(const void*, int);
    int sendAll(std::string&);

    bool valid() const noexcept;

    private:
    struct Impl;
    std::unique_ptr<Impl> impl;

    explicit Socket(socket_handle handle);
};