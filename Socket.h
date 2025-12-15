#pragma once
#include <string>
#include <cstdint>
#include <memory>

#ifdef _WIN32
using socket_handle = unsigned long long;
#else
using socket_handle = int;
#endif

class Socket
{
    public:
    Socket();
    ~Socket();

    public:
    Socket(Socket&&) noexcept;
    Socket& operator = (Socket&&) noexcept;

    Socket(const Socket&) = delete;
    Socket& operator =(const Socket&) = delete;

    public:
    void bind(unsigned short port);
    void listen(int);
    Socket accept();

    int send(const void*, int);
    int send(std::string&);

    int sendAll(const void*, int);
    int sendAll(std::string&);

    int receive(void*, int);
    std::string receive();

    void recvAll(void*, std::size_t);

    bool valid() const noexcept;

    void connect(std::string, unsigned short);

    private:
    struct Impl;
    std::unique_ptr<Impl> impl;

    explicit Socket(socket_handle handle);
};