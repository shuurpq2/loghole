#pragma once

#include "loghole/log_level.hpp"
#include "loghole/log.hpp"
#include "loghole/debug.hpp"
#include <string_view>

class BaseLogger {
protected:
    std::vector<LogLevel> m_allowed_levels = {LogLevel::INFO, LogLevel::WARNING, LogLevel::ERROR, LogLevel::FATAL};

    virtual void m_log(Log& log) = 0;

    bool m_is_level_allowed(LogLevel level);

public:
    virtual ~BaseLogger() = default;

    void log(Log& log);
    void log(std::string info, LogLevel level);

    void set_log_level(LogLevel min_level);
    void set_log_level(LogLevel min_level, LogLevel max_level);
    template<typename... Levels>
    void set_log_level(Levels... allowed_levels) {
        m_allowed_levels.clear();

        ([&](LogLevel level) {
            if (level != LogLevel::NONE && level != LogLevel::COUNT) {
                m_allowed_levels.push_back(level);                
            }
        } (allowed_levels), ...);

        LH_DEBUG_PRINT("New allowed log levels set for logger " << this);
    }

    std::vector<LogLevel> get_allowed_levels() const {return m_allowed_levels;}
};