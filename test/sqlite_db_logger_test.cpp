#include "loghole/loghole.hpp"
#include <gtest/gtest.h>

class SqliteDbLoggerTestFixture : public ::testing::Test{
    std::string db_file_path;
    std::string tablename;
    SqliteDBLogger* sqlite_db_logger;

    void SetUp() {
        db_file_path = "database.db";
        tablename = "logs";
        sqlite_db_logger = new SqliteDBLogger(db_file_path, tablename);
    }

    void TearDown() {

    }
};