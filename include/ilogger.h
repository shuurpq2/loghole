#ifndef ILOGGER_H
#define ILOGGER_H

#include <string_view>

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(std::string_view msg) = 0;
};

#endif