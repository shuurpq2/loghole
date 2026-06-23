#include "loghole/loghole.hpp"
#include <gtest/gtest.h>

class SqliteDBLoggerTestFixture : public ::testing::Test{
protected:
    std::string db_file_path;
    std::string tablename;
    SqliteDBLogger* sqlite_db_logger;
    sqlite3* db;

    void SetUp() {
        db_file_path = "database.db";
        tablename = "logs";
        sqlite_db_logger = new SqliteDBLogger(db_file_path, tablename);

        ASSERT_EQ(sqlite3_open(db_file_path.c_str(), &db), SQLITE_OK);
        ASSERT_EQ(sqlite3_exec(db, std::string("DROP TABLE IF EXISTS " + tablename).c_str(), nullptr, nullptr, nullptr), SQLITE_OK);
    }

    void TearDown() {
        sqlite3_close(db);
    }
};

TEST_F(SqliteDBLoggerTestFixture, Log_IntendedUse_AddLogToDB) {
    std::string log_info = "Log in database";
    LogLevel log_level = LogLevel::INFO;
    sqlite_db_logger->log(log_info, log_level);

    char** result;
    int rows, columns;

    std::string sql = "SELECT * FROM " + tablename;

    ASSERT_EQ(sqlite3_get_table(db, sql.c_str(), &result, &rows, &columns, nullptr), SQLITE_OK);
    EXPECT_EQ(std::stoi(result[columns]), 1);
    EXPECT_EQ(result[columns + 3], log_info);
}