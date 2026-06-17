#pragma once

#include "ilogger.hpp"
#include "log_level.hpp"
#include "thread_pool.hpp"
#include "debug.hpp"
#include "log.hpp"
#include "console_logger.hpp"
#include "file_logger.hpp"
#include <vector>
#include <memory>

class Loghole {
private:
    ThreadPool* m_thread_pool = nullptr;
    std::vector<std::shared_ptr<ILogger>> m_loggers;

    int get_logger_idx(std::shared_ptr<ILogger> logger_sptr);

public:
    Loghole(int num_threads = 0);

    ~Loghole();

    void log(std::string_view info, LogLevel level = LogLevel::INFO);

    void async_log(std::string_view info, LogLevel level = LogLevel::INFO);

    void async_logs_await();

    void attach(std::shared_ptr<ILogger> logger_sptr);

    void detach(std::shared_ptr<ILogger> logger_sptr);
};