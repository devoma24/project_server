#include "Storage.h"

bool Storage::set(const std::string& key, const std::string& value)
{
    std::lock_guard lock(mutex);
    data[key] = value;
    return true;
}

std::optional<std::string> Storage::get(const std::string& key)
{
    std::lock_guard lock(mutex);
    auto it = data.find(key);
    if(it == data.end())
    {
        return std::nullopt;
    }

    return it->second;
}

bool Storage::del(const std::string& key)
{
    std::lock_guard lock(mutex);
    return data.erase(key) > 0;
}