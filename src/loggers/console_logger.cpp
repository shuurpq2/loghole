#include "loghole/loggers/console_logger.hpp"
#include <iostream>

namespace lh {

void ConsoleLogger::m_log(const Log& log) {
    std::cout << log.formatted(log_level_to_console_colored_string) << "\n";
}

}