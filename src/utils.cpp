#include "loghole/utils.hpp"
#include <chrono>
#include <string>
#include <iomanip>
#include <iostream>

std::string LHUtils::get_timestamp() {
    auto now = std::chrono::system_clock::now();
    time_t time_t_now = std::chrono::system_clock::to_time_t(now);

    std:tm local_time;
    localtime_r(&time_t_now, &local_time);

    std::stringstream ss;
    ss << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");

    return ss.str();
}