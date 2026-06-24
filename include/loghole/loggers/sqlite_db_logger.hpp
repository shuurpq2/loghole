#pragma once

#include "loghole/loggers/base_sql_db_logger.hpp"
#include <sqlite3.h>

class SqliteDBLogger : public BaseSqlDBLogger {
private:
    std::string m_file_path;
    std::string m_tablename;
    sqlite3* m_db;

    void m_log(const Log& log) override;

    int m_create_table();

public:
    SqliteDBLogger(std::string file_path, std::string m_tablename = "logs");

    ~SqliteDBLogger();
};