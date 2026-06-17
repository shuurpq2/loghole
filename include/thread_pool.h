#ifndef LH_THREAD_POOL_H
#define LH_THREAD_POOL_H

#include "log.h"
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class ThreadPool {
private:
    int m_num_threads = 1;
    int m_stop_pool = 0;
    std::condition_variable m_pool_has_tasks;
    std::condition_variable m_pool_finished;
    std::queue<Log> m_log_queue;
    std::mutex m_queue_mutex;
    std::vector<std::thread*> m_threads;

    std::function<void(Log)> m_log_func;

public:
    ThreadPool(std::function<void(Log)>& log_func);

    void pool_init();

    void pool_free();

    void pool_add_log(Log& log);

    void pool_worker();

    void pool_wait();
};

#endif