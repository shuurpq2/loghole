#include "console_logger.hpp"
#include <iostream>

void ConsoleLogger::log(Log& log) {
    std::cout << log.formatted(log_level_to_console_colored_string) << "\n";
}