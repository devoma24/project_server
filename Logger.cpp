#include "Logger.h"

Logger& Logger::instance()
{
    static Logger inst;
    return inst;
}

void Logger::log(LogLevel level, const std::string& msg)
{
    std::lock_guard losk(mutex_);

    std::cout
    << "[" << timestamp() << "]"
    << "[" << levelToString(level) << "]"
    << "[tid" << std::this_thread::get_id() << "]"
    << msg << std::endl;
}

std::string Logger::levelToString(LogLevel level)
{
    switch(level)
    {
        case LogLevel::Debug: return "DEBUG";
        case LogLevel::Info: return "INFO";
        case LogLevel::Warning: return "WARN";
        case LogLevel::Error: return "ERROR";
    }
    return "UNKNOWN";
}

std::string Logger::timestamp()
{
    using namespace std::chrono;
    auto now = system_clock::now();
    auto t = system_clock::to_time_t(now);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%F %T", std::localtime(&t));
    return buf;
}