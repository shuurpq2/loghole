#ifndef LH_LOG_LEVEL_H
#define LH_LOG_LEVEL_H

#include <string>

enum class LogLevel {
    NONE,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL
};

std::string log_level_to_string(LogLevel level);

std::string log_level_to_console_colored_string(LogLevel level);

#endif