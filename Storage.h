#pragma once
#include <string>
#include <unordered_map>
#include <mutex>
#include <optional>

class Storage
{
    public:
    bool set(const std::string&,const std::string&);
    std::optional<std::string> get(const std::string&);
    bool del(const std::string&);

    private:
    std::unordered_map<std::string, std::string> data;
    std::mutex mutex;
};