#include "console_logger.h"
#include <iostream>

void ConsoleLogger::log(std::string_view msg) {
    std::cout << "[LOG] " << msg << "\n";
}