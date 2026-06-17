#ifndef LH_FILE_LOGGER_H
#define LH_FILE_LOGGER_H

#include "ilogger.hpp"
#include <string>

class FileLogger : public ILogger {
private:
    std::string m_file_path;

public:
    FileLogger(std::string file_path);

    void log(Log& log) override;
};

#endif