#ifndef LH_FILE_LOGGER_H
#define LH_FILE_LOGGER_H

#include "ilogger.hpp"
#include <string>

class FileLogger : public ILogger {
private:
    std::string m_file_path;

    void m_log(Log& log) override;

public:
    FileLogger(const std::string& file_path);

    void set_file_path(const std::string& file_path) {m_file_path = file_path;}

    std::string get_file_path() const {return m_file_path;}
};

#endif