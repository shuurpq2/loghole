#pragma once

#include "loghole/loggers/base_logger.hpp"
#include "loghole/loggers/console_logger.hpp"
#include "loghole/loggers/file_logger.hpp"
#include "loghole/loggers/sqlite_db_logger.hpp"
#include "loghole/log_level.hpp"
#include "loghole/thread_pool.hpp"
#include "loghole/debug.hpp"
#include "loghole/log.hpp"
#include "loghole/logger_factory.hpp"
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