#ifndef LH_THREAD_POOL_H
#define LH_THREAD_POOL_H

#include "log.hpp"
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

typedef struct Task {
    std::string info;
    LogLevel level;
} Task;

class ThreadPool {
private:
    int m_num_threads;
    int m_stop_pool = 0;
    std::condition_variable m_pool_has_tasks;
    std::condition_variable m_pool_finished;
    std::queue<Task> m_task_queue;
    int m_tasks_remaining = 0;
    std::mutex m_queue_mutex;
    std::vector<std::thread> m_threads;
    std::function<void(std::string, LogLevel)> m_log_func;

public:
    ThreadPool(const std::function<void(std::string, LogLevel)>& log_func, int num_threads = 1);

    ~ThreadPool();

    void pool_init();

    void pool_free();

    void pool_add_task(std::string info, LogLevel level);

    void pool_worker();

    void pool_wait();
};

#endif