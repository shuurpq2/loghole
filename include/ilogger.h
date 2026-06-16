#ifndef ILOGGER_H
#define ILOGGER_H

#include <string_view>
#include "log_level.h"

class ILogger {
protected:
    LogLevel m_log_level = LogLevel::INFO;

public:
    virtual ~ILogger() = default;
    virtual void log(std::string_view info, LogLevel level) = 0;
    void set_log_level(LogLevel level) {m_log_level = level;}
};

#endif