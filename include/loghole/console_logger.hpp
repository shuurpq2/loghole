#pragma once

#include "loghole/base_logger.hpp"
#include "loghole/log_level.hpp"

class ConsoleLogger : public BaseLogger {
private:
    void m_log(Log& log) override;
};