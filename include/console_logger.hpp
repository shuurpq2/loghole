#ifndef LH_CONSOLE_LOGGER_H
#define LH_CONSOLE_LOGGER_H

#include "base_logger.hpp"
#include "log_level.hpp"

class ConsoleLogger : public BaseLogger {
private:
    void m_log(Log& log) override;
};

#endif