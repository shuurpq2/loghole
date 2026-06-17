#include "thread_pool.h"
#include "debug.h"

ThreadPool::ThreadPool(std::function<void(Log)>& log_func)
    : m_log_func(log_func)
{
    
}

void ThreadPool::pool_init() {
    std::unique_lock<std::mutex> queue_lock(m_queue_mutex);

    for (int i = 0; i < m_num_threads; i++) {
        std::thread new_thread(&ThreadPool::pool_worker, this);
        m_threads.push_back(&new_thread);
        new_thread.detach();
    }
}

void ThreadPool::pool_free() {
    pool_wait();

    std::unique_lock<std::mutex> queue_lock(m_queue_mutex);
    m_stop_pool = 1;
    queue_lock.unlock();
    m_pool_has_tasks.notify_all();

    for (int i = 0; i < m_num_threads; i++) {
        m_threads[i]->join();
    }
}

void ThreadPool::pool_add_log(Log& log) {
    m_log_queue.push(log);
}

void ThreadPool::pool_worker() {
    while (1) {
        std::unique_lock<std::mutex> queue_lock(m_queue_mutex);

        while (m_log_queue.empty() && m_stop_pool == 0) {
            m_pool_has_tasks.wait(queue_lock);
        }

        if (m_stop_pool) {
            queue_lock.unlock();
            break;
        }

        Log log = m_log_queue.front();
        m_log_queue.pop();

        queue_lock.unlock();

        m_log_func(log);
    }
}

void ThreadPool::pool_wait() {
    std::unique_lock<std::mutex> queue_lock(m_queue_mutex);

    while (m_log_queue.size() > 0) {
        m_pool_finished.wait(queue_lock);
    }

    queue_lock.unlock();
}

