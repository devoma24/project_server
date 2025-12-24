#pragma once
#include <mutex>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

enum class LogLevel
{
    Debug,
    Info,
    Warning,
    Error
};

class Logger
{
    public:
    static Logger& instance();

    void log(LogLevel level, const std::string& msg);

    private:
    Logger() = default;
    std::mutex mutex_;

    std::string levelToString(LogLevel level);
    std::string timestamp();
};