#ifndef LH_LOG_LEVEL_H
#define LH_LOG_LEVEL_H

#include <string>

enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3,
    FATAL = 4
};

std::string log_level_to_string(LogLevel level);

#endif