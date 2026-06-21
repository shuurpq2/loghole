#include "base_logger.hpp"

void BaseLogger::log(Log& log) {
    if (log.get_level() >= m_min_log_level && log.get_level() <= m_max_log_level) {
        return m_log(log);
    }
}

void BaseLogger::set_log_level(LogLevel min_level, LogLevel max_level) {
    if (min_level != LogLevel::NONE) {
        m_min_log_level = min_level;
    }

    if (max_level != LogLevel::NONE) {
        m_max_log_level = max_level;
    }
}