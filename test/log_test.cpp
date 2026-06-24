#include "loghole/loghole.hpp"
#include <gtest/gtest.h>

TEST(LogTestSuite, Constructor_IntendedUse_SavesDataCorrectly) {
    std::string log_info = "SOME FATAL ERROR INFO";
    lh::LogLevel log_level = lh::LogLevel::FATAL;

    lh::Log log(log_info, log_level);

    EXPECT_EQ(log.get_info(), log_info);
    EXPECT_EQ(log.get_level(), log_level);
}