#ifndef LOGHOLE_H
#define LOGHOLE_H

#include <vector>
#include <memory>
#include "ilogger.hpp"
#include "log_level.hpp"
#include "thread_pool.hpp"

class Loghole {
private:
    ThreadPool* m_thread_pool = nullptr;
    std::vector<std::shared_ptr<ILogger>> m_loggers;

    int get_logger_idx(std::shared_ptr<ILogger> logger);

public:
    Loghole(int num_threads = 0);

    ~Loghole();

    void log(std::string_view info, LogLevel level = LogLevel::INFO);

    void async_log(std::string_view info, LogLevel level = LogLevel::INFO);

    void async_logs_await();

    void attach(std::shared_ptr<ILogger> logger);

    void detach(std::shared_ptr<ILogger> logger);
};

#endif