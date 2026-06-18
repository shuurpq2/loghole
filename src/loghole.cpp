#include "loghole.hpp"
#include <iostream>
#include <algorithm>

Loghole::Loghole(int num_threads)
    
{
    LH_DEBUG_PRINT("Constructing new Loghole instance with number of threads: " << num_threads);

    if (num_threads > 0) {
        m_thread_pool = new ThreadPool([this](std::string info, LogLevel level) {
            this->log(info, level);
        }, num_threads);

        m_thread_pool->pool_init();
    }
}

Loghole::~Loghole() {
    delete m_thread_pool;
}

int Loghole::get_logger_idx(std::shared_ptr<ILogger> logger_sptr) {
    int idx = -1;

    for (int i = 0; i < m_loggers.size(); i++) {
        if (m_loggers[i] == logger_sptr) {
            idx = i;
            break;
        }
    }

    return idx;
}

void Loghole::log(std::string info, LogLevel level) {
    LH_DEBUG_PRINT("New log with level \"" << log_level_to_console_colored_string(level) << "\": " << info);

    Log log(info, level);

    for (int i = 0; i < m_loggers.size(); i++) {
        m_loggers[i]->log(log);
    }
}

void Loghole::async_log(std::string info, LogLevel level) {
    if (m_thread_pool != nullptr) {
        m_thread_pool->pool_add_task(info, level);
    } else {
        std::cerr << "Can't async_log because number of threads < 1" << std::endl;
    }
}

void Loghole::async_logs_await() {
    if (m_thread_pool != nullptr) {
        m_thread_pool->pool_wait();
    } else {
        std::cerr << "Can't async_logs_await because number of threads < 1" << std::endl;
    }
}

void Loghole::attach(std::shared_ptr<ILogger> logger_sptr) {
    if (get_logger_idx(logger_sptr) == -1) {
        m_loggers.push_back(logger_sptr);

        LH_DEBUG_PRINT("Logger " << logger_sptr << " attached to " << this);

        return;
    }

    LH_DEBUG_PRINT("Logger " << logger_sptr << " is already attached to " << this);
}

void Loghole::detach(std::shared_ptr<ILogger> logger_sptr) {
    m_loggers.erase(std::remove(m_loggers.begin(), m_loggers.end(), logger_sptr), m_loggers.end());
    LH_DEBUG_PRINT("Logger " << logger_sptr << " detached from " << this);
}