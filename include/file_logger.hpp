#ifndef LH_FILE_LOGGER_H
#define LH_FILE_LOGGER_H

#include "ilogger.hpp"
#include <string>

class FileLogger : public ILogger {
private:
    std::string m_file_path;

public:
    FileLogger(std::string file_path = "");

    void m_log(Log& log) override;

    void set_file_path(std::string file_path);
};

#endif