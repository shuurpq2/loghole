#include "loghole/log_level.hpp"
#include <colorhead/colorhead.hpp>

namespace lh {

std::string log_level_to_string(LogLevel level) {
    switch(level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::FATAL: return "FATAL";
        case LogLevel::NONE: return "NONE";
        default: return "UNKNOWN";
    }
}

std::string log_level_to_console_colored_string(LogLevel level) {
    switch(level) {
        case LogLevel::DEBUG: return clrhd::transform_text(log_level_to_string(level), clrhd::BLUE_16);
        case LogLevel::INFO: return clrhd::transform_text(log_level_to_string(level), clrhd::GREEN_16);
        case LogLevel::WARNING: return clrhd::transform_text(log_level_to_string(level), clrhd::YELLOW_16);
        case LogLevel::ERROR: return clrhd::transform_text(log_level_to_string(level), clrhd::RED_16);
        case LogLevel::FATAL: return clrhd::transform_text(log_level_to_string(level), clrhd::RED_16, clrhd::BOLD);
        default: return log_level_to_string(level);
    }
}

bool is_log_level_valid(LogLevel level) {
    return level != LogLevel::NONE && level != LogLevel::COUNT;
}

}