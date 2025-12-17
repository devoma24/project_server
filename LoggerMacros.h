#pragma once
#include "Logger.h"

#define LOG_DEBUG(msg) Logger::instance().log(LogLevel::Debug, msg)
#define LOG_INFO(msg)  Logger::instance().log(LogLevel::Info, msg)
#define LOG_WARN(msg)  Logger::instance().log(LogLevel::Warning, msg)
#define LOG_ERROR(msg) Logger::instance().log(LogLevel::Error, msg)