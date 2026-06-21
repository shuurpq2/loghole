#include "loghole.hpp"
#include <gtest/gtest.h>

TEST(LogTestSuite, Constructor_SavesDataCorrectly) {
    std::string log_info = "SOME FATAL ERROR INFO";
    LogLevel log_level = LogLevel::FATAL;

    Log log(log_info, log_level);

    EXPECT_EQ(log.get_info(), log_info);
    EXPECT_EQ(log.get_level(), log_level);
}