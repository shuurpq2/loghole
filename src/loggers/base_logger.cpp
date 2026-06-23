#include "loghole/loggers/base_logger.hpp"

bool BaseLogger::m_is_level_allowed(LogLevel level) {
    for (LogLevel l : m_allowed_levels) {
        if (l == level) return true;
    }

    return false;
}

void BaseLogger::log(Log& log) {
    if (m_is_level_allowed(log.get_level())) {
        m_log(log);
    }
}

void BaseLogger::log(std::string info, LogLevel level)  {
    Log log(std::move(info), level);
    this->log(log);
}

void BaseLogger::set_log_level(LogLevel min_level) {
    if (!is_log_level_valid(min_level)) {
        std::cerr << "Error: invalid log level" << std::endl;
        exit(1);
    }

    m_allowed_levels.clear();
    
    for (int i = static_cast<int>(min_level); i < static_cast<int>(LogLevel::COUNT); i++) {
        m_allowed_levels.push_back(static_cast<LogLevel>(i));
    }

    LH_DEBUG_PRINT("New min log level set for logger " << this << ": \"" << log_level_to_console_colored_string(min_level) << "\"");
}

void BaseLogger::set_log_level(LogLevel min_level, LogLevel max_level) {
    if (!(is_log_level_valid(min_level) && is_log_level_valid(max_level))) {
        std::cerr << "Error: invalid log level" << std::endl;
        exit(1);
    }

    m_allowed_levels.clear();

    for (int i = static_cast<int>(min_level); i <= static_cast<int>(max_level); i++) {
        m_allowed_levels.push_back(static_cast<LogLevel>(i));
    }

    LH_DEBUG_PRINT("New allowed log levels set for logger " << this << ": from \"" << log_level_to_console_colored_string(min_level) << "\" to \"" << log_level_to_console_colored_string(max_level) << "\"");
}

void BaseLogger::add_log_level(LogLevel level) {
    if (is_log_level_valid(level) && !m_is_level_allowed(level)) {
        m_allowed_levels.push_back(level);

        LH_DEBUG_PRINT("New allowed log level added for logger " << this << ": \"" << log_level_to_console_colored_string(level) << "\"");
    }
}