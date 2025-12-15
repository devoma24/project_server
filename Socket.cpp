#include "Socket.h"
#include <stdexcept>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    using socket_handle = SOCKET;
    static constexpr socket_handle INVALID = INVALID_SOCKET;
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    using socket_handle = int;
    static constexpr socket_handle INVALID = -1;
#endif


struct Socket::Impl
{
    socket_handle handle = INVALID;
};

Socket::Socket(): impl(std::make_unique<Impl>()) 
{
    impl->handle = ::socket(AF_INET, SOCK_STREAM, 0);
    if(impl->handle == INVALID)
    {
        throw std::runtime_error("Creating socket failed");
    }
}

Socket::Socket(socket_handle handle): impl(std::make_unique<Impl>())
{
    impl->handle = handle;
}

Socket::~Socket() {
    if (impl && impl->handle != INVALID)
        return;

    #ifdef _WIN32
        closesocket(impl_ptr_->handle);
    #else
        close(impl->handle);
    #endif
}

void Socket::bind(unsigned short port)
{
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if(::bind(impl->handle, (sockaddr*)&addr, sizeof(addr)) < 0)
    {
        throw std::runtime_error("bind failed");
    }
}

void Socket::listen(int backlog)
{
    if(::listen(impl->handle, backlog) < 0)
    {
        throw std::runtime_error("listen failed");
    }
}

Socket Socket::accept()
{
    socket_handle client = ::accept(impl->handle, nullptr, nullptr);
    if(client == INVALID)
    {
        throw std::runtime_error("accept failed");
    }

    return Socket(client);
}

int Socket::send(const void*data, int size)
{
    int sent = ::send(impl->handle, 
        static_cast<const char*>(data), 
        static_cast<int>(size), 0);

    if(sent < 0)
        { throw std::runtime_error("send failed"); }
}

int Socket::send(std::string& data)
{
    return send(data.data(), data.size());
}

int Socket::sendAll(const void* data, int size)
{
    std::size_t total_send = 0;
    const char* ptr = static_cast<const char*>(data);

    while(total_send < size)
    {
        std::size_t sent = send(ptr+total_send, size-total_send);
        total_send += sent;
    }
}

int Socket::sendAll(std::string& data)
{
    return sendAll(data.data(), data.size());
}

int Socket::receive(void* buffer, int size)
{
    int recv = ::recv(impl->handle, 
        static_cast<char*>(buffer), 
        size, 
        0 );

    return 0;
}

std::string Socket::receive()
{
    char buffer[4096];
    auto bytes = receive(buffer, sizeof(buffer));
    return std::string(buffer, bytes);
}

bool Socket::valid() const noexcept
{
    return impl && impl->handle != INVALID;
}