#include "loghole/loghole.hpp"
#include <gtest/gtest.h>

class ThreadPoolTestFixture : public ::testing::Test {
protected:
    ThreadPool* thread_pool;
    int num_threads;

    void mock_log_func(std::string info, LogLevel level) {
        return;
    }

    void SetUp() override {
        num_threads = 1;
        thread_pool = new ThreadPool([this](std::string info, LogLevel level) {this->mock_log_func(info, level);}, num_threads);
    }

    void TearDown() override {
        delete thread_pool;
        std::vector<int> v;
        v.push_back(10);
    }
};
