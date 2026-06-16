#include "console_logger.h"
#include <iostream>

void ConsoleLogger::log(Log& log) {
    if (log.get_level() >= m_log_level) {
        std::cout << log.formatted() << "\n";
    }

}