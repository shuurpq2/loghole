#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include "ilogger.h"

class ConsoleLogger : public ILogger {
public:
    void log(std::string_view msg) override;
};

#endif