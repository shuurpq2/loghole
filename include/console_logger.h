#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include "ilogger.h"
#include "log_level.h"

class ConsoleLogger : public ILogger {
public:
    void log(std::string_view info, LogLevel level) override;
};

#endif