#include "loghole/log_level.hpp"

namespace lh {

std::string log_level_to_string(LogLevel level) {
    switch(level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::FATAL: return "FATAL";
        default: return "UNKNOWN";
    }
}

std::string log_level_to_console_colored_string(LogLevel level) {
    switch(level) {
        case LogLevel::DEBUG: return "\033[34m" + log_level_to_string(level) + "\033[0m";
        case LogLevel::INFO: return "\033[32m" + log_level_to_string(level) + "\033[0m";
        case LogLevel::WARNING: return "\033[33m" + log_level_to_string(level) + "\033[0m";
        case LogLevel::ERROR: return "\033[31m" + log_level_to_string(level) + "\033[0m";
        case LogLevel::FATAL: return "\033[1;31m" + log_level_to_string(level) + "\033[0m";
        default: return log_level_to_string(level);
    }
}

bool is_log_level_valid(LogLevel level) {
    return level != LogLevel::NONE && level != LogLevel::COUNT;
}

}