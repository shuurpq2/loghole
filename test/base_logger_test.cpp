#include "loghole.hpp"
#include <gtest/gtest.h>

class BaseLoggerTestFixture : public ::testing::Test {
protected:
    BaseLogger* base_logger;

    void SetUp() {
        base_logger = new ConsoleLogger();
    }

    void TearDown() {
        delete base_logger;
    }
};

TEST_F(BaseLoggerTestFixture, SetLogLevel_WithOneParam_AllowedLevelsShouldBeAllFromGiven) {
    LogLevel min_log_level = LogLevel::WARNING;
    std::vector<LogLevel> expect_allowed_levels = {LogLevel::WARNING, LogLevel::ERROR, LogLevel::FATAL};

    base_logger->set_log_level(min_log_level);

    EXPECT_EQ(base_logger->get_allowed_levels(), expect_allowed_levels);
}

TEST_F(BaseLoggerTestFixture, SetLogLevel_WithTwoParams_AllowedLevelsShouldBeFromMinToMax) {
    LogLevel min_log_level = LogLevel::INFO;
    LogLevel max_log_level = LogLevel::ERROR;
    std::vector<LogLevel> expect_allowed_levels = {LogLevel::INFO, LogLevel::WARNING, LogLevel::ERROR};

    base_logger->set_log_level(min_log_level, max_log_level);

    EXPECT_EQ(base_logger->get_allowed_levels(), expect_allowed_levels);
}

TEST_F(BaseLoggerTestFixture, SetLogLevel_WithThreeParams_AllowedLevelsShouldBeParams) {
    LogLevel param1 = LogLevel::INFO;
    LogLevel param2 = LogLevel::ERROR;
    LogLevel param3 = LogLevel::DEBUG;
    std::vector<LogLevel> expect_allowed_levels = {param1, param2, param3}; 

    base_logger->set_log_level(param1, param2, param3);
    EXPECT_EQ(base_logger->get_allowed_levels(), expect_allowed_levels);
}