#include "loghole/loggers/file_logger.hpp"
#include "loghole/debug.hpp"
#include <iostream>
#include <fstream>

FileLogger::FileLogger(const std::string& file_path)
    :m_file_path(file_path)
{

}

void FileLogger::m_log(Log& log) {
    std::ofstream file(m_file_path, std::ios::app);
    if (file.is_open()) {
        file << log.formatted() << "\n";
        file.close();

        LH_DEBUG_PRINT("New log added to file \"" << m_file_path << "\" with level \"" << log_level_to_console_colored_string(log.get_level()) << "\": \"" << log.get_info() << "\"");
    } else {
        std::cerr << "Error while opening file \"" + m_file_path + "\"" << std::endl;
    }
}