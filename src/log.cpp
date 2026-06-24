#include "loghole/log.hpp"
#include "loghole/utils.hpp"
#include <iostream>

namespace lh {

Log::Log(const std::string info, const LogLevel level)
    :m_info(info), m_level(level)
{
    if (!is_log_level_valid(level)) {
        std::cerr << "Error: invalid log level" << std::endl;
        exit(1);
    }

    m_timestamp = Utils::get_timestamp();
}

std::string Log::formatted(const std::function<std::string(LogLevel)>& level_to_string_func) const {
    std::string res = m_timestamp + " [" + level_to_string_func(m_level) + "] " + m_info;

    return res;
}

}