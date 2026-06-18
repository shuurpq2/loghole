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
    Log(const std::string info, const LogLevel level);

    std::string formatted(const std::function<std::string(LogLevel)>& level_to_string_func = log_level_to_string) const;

    std::string get_info() const {return m_info;}

    LogLevel get_level() const {return m_level;}
};

#endif