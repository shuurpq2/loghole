#ifndef ILOGGER_H
#define ILOGGER_H

#include "log_level.h"
#include "log.h"
#include <string_view>

class ILogger {
protected:
    LogLevel m_log_level = LogLevel::INFO;

public:
    virtual ~ILogger() = default;
    virtual void log(Log& log) = 0;
    void set_log_level(LogLevel level) {m_log_level = level;}
};

#endif