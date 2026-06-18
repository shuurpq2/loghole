#include "console_logger.hpp"
#include <iostream>

void ConsoleLogger::m_log(Log& log) {
    std::cout << log.formatted(log_level_to_console_colored_string) << "\n";
}