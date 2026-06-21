#pragma once

#include "base_logger.hpp"
#include "log_level.hpp"
#include "thread_pool.hpp"
#include "debug.hpp"
#include "log.hpp"
#include "console_logger.hpp"
#include "file_logger.hpp"
#include "logger_factory.hpp"
#include <vector>
#include <memory>

class Loghole {
private:
    ThreadPool* m_thread_pool = nullptr;
    std::vector<std::shared_ptr<BaseLogger>> m_loggers;

    int get_logger_idx(std::shared_ptr<BaseLogger> logger_sptr);

public:
    Loghole(int num_threads = 0);

    ~Loghole();

    void log(std::string info, LogLevel level = LogLevel::INFO);

    void async_log(std::string info, LogLevel level = LogLevel::INFO);

    void async_logs_await();

    void attach(std::shared_ptr<BaseLogger> logger_sptr);

    void detach(std::shared_ptr<BaseLogger> logger_sptr);
};