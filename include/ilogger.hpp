#ifndef LH_ILOGGER_H
#define LH_ILOGGER_H

#include "log_level.hpp"
#include "log.hpp"
#include <string_view>

class ILogger {
protected:
    LogLevel m_min_log_level = LogLevel::INFO;
    LogLevel m_max_log_level = LogLevel::FATAL;

    virtual void m_log(Log& log) = 0;

public:
    virtual ~ILogger() = default;
    void log(Log& log) {if (log.get_level() >= m_min_log_level && log.get_level() <= m_max_log_level) return m_log(log);}
    void set_log_level(LogLevel min_level, LogLevel max_level = LogLevel::FATAL) {m_min_log_level = min_level; m_max_log_level = max_level;}
};

#endif