#pragma once

#include "log_level.hpp"
#include "log.hpp"
#include <string_view>

class BaseLogger {
protected:
    LogLevel m_min_log_level = LogLevel::INFO;
    LogLevel m_max_log_level = LogLevel::FATAL;

    virtual void m_log(Log& log) = 0;

public:
    virtual ~BaseLogger() = default;

    void log(Log& log);
       
    void set_log_level(LogLevel min_level, LogLevel max_level = LogLevel::NONE);
};