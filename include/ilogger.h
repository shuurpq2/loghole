#ifndef LH_ILOGGER_H
#define LH_ILOGGER_H

#include "log_level.h"
#include "log.h"
#include <string_view>

class ILogger {
protected:
    LogLevel m_min_log_level = LogLevel::INFO;
    LogLevel m_max_log_level = LogLevel::FATAL;

public:
    virtual ~ILogger() = default;
    virtual void log(Log& log) = 0;
    void prep_to_log(Log& log) {if (log.get_level() >= m_min_log_level && log.get_level() <= m_max_log_level) this->log(log);}
    void set_log_level(LogLevel min_level, LogLevel max_level = LogLevel::FATAL) {m_min_log_level = min_level; m_max_log_level = max_level;}
};

#endif