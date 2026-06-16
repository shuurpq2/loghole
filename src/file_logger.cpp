#include "file_logger.h"
#include "debug.h"
#include <iostream>
#include <fstream>

FileLogger::FileLogger(std::string file_path)
    :m_file_path(file_path)
{

}

void FileLogger::log(Log& log) {
    LH_DEBUG_PRINT("Opening file \"" + m_file_path + "\" to log");

    std::ofstream file(m_file_path, std::ios::app);
    if (file.is_open()) {
        file << log.formatted() << "\n";
        file.close();
    } else {
        std::cerr << "Error while opening file {}\n", m_file_path;
    }
}