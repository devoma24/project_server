#include "../include/Storage.h"

bool Storage::set(const std::string& key, const std::string& value)
{
    std::unique_lock lock(mutex_);
    data[key] = value;
    return true;
}

std::optional<std::string> Storage::get(const std::string& key)
{
    std::shared_lock lock(mutex_);
    auto it = data.find(key);
    if(it == data.end())
    {
        return std::nullopt;
    }

    return it->second;
}

bool Storage::del(const std::string& key)
{
    std::unique_lock lock(mutex_);
    return data.erase(key) > 0;
}