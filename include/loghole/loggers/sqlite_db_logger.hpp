#pragma once

#include "loghole/loggers/base_sql_db_logger.hpp"
#include <sqlite3.h>

class SqliteDBLogger : public BaseSqlDBLogger {
private:
    std::string m_file_path;
    sqlite3* m_db;

    void m_log(Log& log) override;

public:
    SqliteDBLogger(std::string file_path);

    ~SqliteDBLogger();
};