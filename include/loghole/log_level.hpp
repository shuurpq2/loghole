#pragma once

#include <string>

namespace lh {

enum class LogLevel {
    NONE = -1,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL,
    COUNT,
};

std::string log_level_to_string(LogLevel level);

std::string log_level_to_console_colored_string(LogLevel level);

bool is_log_level_valid(LogLevel level);

}