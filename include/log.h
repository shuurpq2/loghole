#ifndef LH_LOG_H
#define LH_LOG_H

#include <string>
#include <log_level.h>
#include <chrono>

class Log {
private:
    std::string m_info;
    LogLevel m_level;
    std::string m_timestamp;

public:
    Log(std::string_view info, LogLevel level);

    std::string formatted();

    LogLevel get_level() {return m_level;}
};

#endif