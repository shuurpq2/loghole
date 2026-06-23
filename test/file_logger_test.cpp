#include "loghole/loghole.hpp"
#include <gtest/gtest.h>
#include <fstream>

class FileLoggerTestFixture : public ::testing::Test {
protected:
    std::string log_file_path;    
    FileLogger* file_logger;

    void SetUp() override {
        log_file_path = "log_file.log";
        file_logger = new FileLogger(log_file_path);
    }

    void TearDown() override {
        delete file_logger;
    }
};

TEST_F(FileLoggerTestFixture, Constructor_IntendedUse_SavesDataCorrectly) {
    EXPECT_EQ(file_logger->get_file_path(), log_file_path);
}

TEST_F(FileLoggerTestFixture, Log_IntendedUseLogsWithAllowedLevelAndNot_ShouldLogOnlyFirst) {
    std::ofstream log_file_w(log_file_path);
    log_file_w.close();

    file_logger->set_log_level(LogLevel::ERROR);

    Log allowed_log("Log with allowed level", LogLevel::ERROR);
    file_logger->log(allowed_log);

    Log not_allowed_log("Log with not allowed level", LogLevel::INFO);
    file_logger->log(not_allowed_log);

    std::ifstream log_file(log_file_path);

    ASSERT_TRUE(log_file.is_open());

    std::string line;
    std::getline(log_file, line);

    EXPECT_EQ(line, allowed_log.formatted());
}