#include "loghole/loghole.hpp"
#include <gtest/gtest.h>

TEST(LoggerFactoryTestSuite, CreateLogger_IntendedUse_ReturningCorrectLogger) {
    auto console_logger_sptr = lh::LoggerFactory::create_logger<lh::ConsoleLogger>();

    std::string log_file_path = "log_file.log";
    auto file_logger_sptr = lh::LoggerFactory::create_logger<lh::FileLogger>(log_file_path);

    EXPECT_EQ(file_logger_sptr->get_file_path(), log_file_path);
}