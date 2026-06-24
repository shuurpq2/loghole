#include "loghole/utils.hpp"
#include <chrono>
#include <string>
#include <iomanip>
#include <iostream>

namespace lh {

std::string Utils::get_timestamp() {
    auto now = std::chrono::system_clock::now();
    time_t time_t_now = std::chrono::system_clock::to_time_t(now);

    std:tm local_time;
    localtime_r(&time_t_now, &local_time);

    std::stringstream ss;
    ss << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");

    return ss.str();
}

std::string Utils::red(std::string str) {
    return "\033[31m" + std::move(str) + "\033[0m";
}


}