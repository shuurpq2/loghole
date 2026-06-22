#include "log.hpp"
#include <iomanip>
#include <iostream>

std::string get_timestamp() {
    auto now = std::chrono::system_clock::now();
    time_t time_t_now = std::chrono::system_clock::to_time_t(now);

    std:tm local_time;
    localtime_r(&time_t_now, &local_time);

    std::stringstream ss;
    ss << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");

    return ss.str();
}

Log::Log(const std::string info, const LogLevel level)
    :m_info(info), m_level(level)
{
    if (!is_log_level_valid(level)) {
        std::cerr << "Error: invalid log level" << std::endl;
        exit(1);
    }
    
    m_timestamp = get_timestamp();
}

std::string Log::formatted(const std::function<std::string(LogLevel)>& level_to_string_func) const {
    std::string res = m_timestamp + " [" + level_to_string_func(m_level) + "] " + m_info;

    return res;
}