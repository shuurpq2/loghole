#ifndef LH_CONSOLE_LOGGER_H
#define LH_CONSOLE_LOGGER_H

#include "ilogger.hpp"
#include "log_level.hpp"

class ConsoleLogger : public ILogger {
private:
    void m_log(Log& log) override;
};

#endif