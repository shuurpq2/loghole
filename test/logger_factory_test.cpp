#include "loghole.hpp"
#include <gtest/gtest.h>

TEST(LoggerFactoryTestSuite, CreateLogger_ReturningCorrectLogger) {
    auto console_logger_sptr = LoggerFactory::create_logger<ConsoleLogger>();

    std::string log_file_path = "log_file.log";
    auto file_logger_sptr = LoggerFactory::create_logger<FileLogger>(log_file_path);

    EXPECT_EQ(file_logger_sptr->get_file_path(), log_file_path);
}