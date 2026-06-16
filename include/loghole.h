#ifndef LOGHOLE_H
#define LOGHOLE_H

#include <vector>
#include <memory>
#include "ilogger.h"
#include "log_level.h"

class Loghole {
private:
    std::vector<std::shared_ptr<ILogger>> m_loggers;

    int get_logger_idx(std::shared_ptr<ILogger> logger);

public:
    void log(std::string_view info, LogLevel level = LogLevel::INFO);

    void attach(std::shared_ptr<ILogger> logger);

    void detach(std::shared_ptr<ILogger> logger);
};

#endif