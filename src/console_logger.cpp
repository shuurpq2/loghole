#include "console_logger.h"
#include <iostream>

void ConsoleLogger::log(std::string_view info, LogLevel level) {
    if (level >= m_log_level) {
        std::cout << "[" << log_level_to_string(level) << "] " << info << "\n";
    }

}