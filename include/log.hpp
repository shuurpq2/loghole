#ifndef LH_LOG_H
#define LH_LOG_H

#include <functional>
#include <string>
#include <chrono>
#include "log_level.hpp"

class Log {
private:
    std::string m_info;
    LogLevel m_level;
    std::string m_timestamp;

public:
    Log(std::string_view info, LogLevel level);

    std::string formatted(const std::function<std::string(LogLevel)>& level_to_string_func = log_level_to_string);

    LogLevel get_level() {return m_level;}
};

#endif