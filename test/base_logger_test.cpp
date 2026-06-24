#include "loghole/loghole.hpp"
#include <gtest/gtest.h>

class BaseLoggerTestFixture : public ::testing::Test {
protected:
    lh::BaseLogger* base_logger;

    void SetUp() {
        base_logger = new lh::ConsoleLogger();
    }

    void TearDown() {
        delete base_logger;
    }
};

TEST_F(BaseLoggerTestFixture, SetLogLevel_IntendedUseWithOneParam_AllowedLevelsShouldBeAllFromGiven) {
    lh::LogLevel min_log_level = lh::LogLevel::WARNING;
    std::vector<lh::LogLevel> expect_allowed_levels = {lh::LogLevel::WARNING, lh::LogLevel::ERROR, lh::LogLevel::FATAL};

    base_logger->set_log_level(min_log_level);

    EXPECT_EQ(base_logger->get_allowed_levels(), expect_allowed_levels);
}

TEST_F(BaseLoggerTestFixture, SetLogLevel_IntendedUseWithTwoParams_AllowedLevelsShouldBeFromMinToMax) {
    lh::LogLevel min_log_level = lh::LogLevel::INFO;
    lh::LogLevel max_log_level = lh::LogLevel::ERROR;
    std::vector<lh::LogLevel> expect_allowed_levels = {lh::LogLevel::INFO, lh::LogLevel::WARNING, lh::LogLevel::ERROR};

    base_logger->set_log_level(min_log_level, max_log_level);

    EXPECT_EQ(base_logger->get_allowed_levels(), expect_allowed_levels);
}

TEST_F(BaseLoggerTestFixture, SetLogLevel_UnintendedUseWithTwoParams_AllowedLevelsShouldBeFromMinToMax) {
    lh::LogLevel min_log_level = lh::LogLevel::ERROR;
    lh::LogLevel max_log_level = lh::LogLevel::INFO;
    std::vector<lh::LogLevel> expect_allowed_levels = {};

    base_logger->set_log_level(min_log_level, max_log_level);

    EXPECT_EQ(base_logger->get_allowed_levels(), expect_allowed_levels);
}

TEST_F(BaseLoggerTestFixture, SetLogLevel_IntendedUseWithThreeParams_AllowedLevelsShouldBeParams) {
    std::vector<lh::LogLevel> expect_allowed_levels = {lh::LogLevel::INFO, lh::LogLevel::ERROR, lh::LogLevel::DEBUG}; 

    base_logger->set_log_level(expect_allowed_levels[0], expect_allowed_levels[1], expect_allowed_levels[2]);

    EXPECT_EQ(base_logger->get_allowed_levels(), expect_allowed_levels);
}

TEST_F(BaseLoggerTestFixture, AddLogLevel_IntendedUse_AddNewAllowedLevel) {
    std::vector<lh::LogLevel> expect_allowed_levels = {lh::LogLevel::INFO, lh::LogLevel::ERROR};

    base_logger->set_log_level(expect_allowed_levels[0], expect_allowed_levels[0]);
    base_logger->add_log_level(expect_allowed_levels[1]);

    EXPECT_EQ(base_logger->get_allowed_levels(), expect_allowed_levels);
}