#include "log.h"
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

Log::Log(std::string_view info, LogLevel level)
    :m_info(info), m_level(level)
{
    m_timestamp = get_timestamp();
}

std::string Log::formatted() {
    std::string res = m_timestamp + " [" + log_level_to_string(m_level) + "] " + m_info;

    return res;
}