#pragma once

#include "loghole/loggers/base_logger.hpp"
#include "loghole/log_level.hpp"

class ConsoleLogger : public BaseLogger {
private:
    void m_log(const Log& log) override;
};