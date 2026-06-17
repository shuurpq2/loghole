#include "thread_pool.h"
#include "debug.h"

ThreadPool::ThreadPool(const std::function<void(std::string_view, LogLevel)>& log_func, int num_threads)
    : m_log_func(log_func), m_num_threads(num_threads)
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

void ThreadPool::pool_add_task(std::string_view info, LogLevel level) {
    Task new_task = {.info=std::string(info), .level=level};

    std::unique_lock<std::mutex> queue_lock(m_queue_mutex);
    m_task_queue.push(new_task);
    m_tasks_remaining++;
    queue_lock.unlock();

    m_pool_has_tasks.notify_one();
}

void ThreadPool::pool_worker() {
    while (1) {
        std::unique_lock<std::mutex> queue_lock(m_queue_mutex);

        while (m_task_queue.empty() && m_stop_pool == 0) {
            m_pool_has_tasks.wait(queue_lock);
        }

        if (m_stop_pool) {
            queue_lock.unlock();
            break;
        }

        Task task = m_task_queue.front();
        m_task_queue.pop();

        queue_lock.unlock();

        m_log_func(task.info, task.level);

        queue_lock.lock();
        
        m_tasks_remaining--;
        if (m_tasks_remaining ==0) {
            m_pool_finished.notify_all();
        }

        queue_lock.unlock();
    }
}

void ThreadPool::pool_wait() {
    std::unique_lock<std::mutex> queue_lock(m_queue_mutex);
    
    while (m_tasks_remaining > 0) {
        m_pool_finished.wait(queue_lock);
    }

    queue_lock.unlock();
}

