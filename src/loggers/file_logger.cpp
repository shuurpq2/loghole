#include "loghole/loggers/file_logger.hpp"
#include "loghole/debug.hpp"
#include <iostream>
#include <fstream>

FileLogger::FileLogger(const std::string& file_path)
    :m_file_path(file_path)
{

}

void FileLogger::m_log(Log& log) {
    LH_DEBUG_PRINT("Opening file \"" + m_file_path + "\" to log");

    std::ofstream file(m_file_path, std::ios::app);
    if (file.is_open()) {
        file << log.formatted() << "\n";
        file.close();
    } else {
        std::cerr << "Error while opening file \"" + m_file_path + "\"" << std::endl;
    }
}