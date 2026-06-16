#include "log_level.h"

std::string log_level_to_string(LogLevel level) {
    switch(level) {
        case LogLevel::DEBUG: return "\033[34mDEBUG\033[0m";
        case LogLevel::INFO: return "\033[32mINFO\033[0m";
        case LogLevel::WARNING: return "\033[33mWARNING\33[0m";
        case LogLevel::ERROR: return "\033[31mERROR\033[0m";
        case LogLevel::FATAL: return "\033[1;31mFATAL\033[0m";
        default: return "UNKNOWN";
    }
}