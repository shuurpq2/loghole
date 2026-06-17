#include "thread_pool.hpp"
#include "debug.hpp"

ThreadPool::ThreadPool(const std::function<void(std::string_view, LogLevel)>& log_func, int num_threads)
    : m_log_func(log_func), m_num_threads(num_threads)
{
    
}

ThreadPool::~ThreadPool() {
    pool_free();
}

void ThreadPool::pool_init() {
    LH_DEBUG_PRINT("Initializing new thread pool");

    std::unique_lock<std::mutex> queue_lock(m_queue_mutex);

    for (int i = 0; i < m_num_threads; i++) {        
        m_threads.emplace_back(&ThreadPool::pool_worker, this);

        LH_DEBUG_PRINT("New thread with id \"" << m_threads[i].get_id() << "\" created");
    }
}

void ThreadPool::pool_free() {
    LH_DEBUG_PRINT("Clearing thread pool " << this);

    pool_wait();

    std::unique_lock<std::mutex> queue_lock(m_queue_mutex);
    m_stop_pool = 1;
    queue_lock.unlock();
    m_pool_has_tasks.notify_all();

    for (int i = 0; i < m_num_threads; i++) {
        LH_DEBUG_PRINT("Deleting thread with id \"" << m_threads[i].get_id() << "\"");

        m_threads[i].join();
    }
}

void ThreadPool::pool_add_task(std::string_view info, LogLevel level) {
    LH_DEBUG_PRINT("New pool task with level \"" << log_level_to_console_colored_string(level) << "\": " << info << "\"");

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

        if (m_stop_pool == 1) {
            queue_lock.unlock();
            break;
        }

        Task task = m_task_queue.front();
        m_task_queue.pop();
    
        m_log_func(task.info, task.level);
        
        m_tasks_remaining--;
        if (m_tasks_remaining ==0) {
            m_pool_finished.notify_all();
        }

        queue_lock.unlock();
    }
}

void ThreadPool::pool_wait() {
    LH_DEBUG_PRINT("Awaiting pool");

    std::unique_lock<std::mutex> queue_lock(m_queue_mutex);
    
    while (m_tasks_remaining > 0) {
        m_pool_finished.wait(queue_lock);
    }

    queue_lock.unlock();
}

