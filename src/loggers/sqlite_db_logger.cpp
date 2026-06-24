#include "loghole/loggers/sqlite_db_logger.hpp"

SqliteDBLogger::SqliteDBLogger(std::string file_path, std::string tablename) 
    : m_file_path(file_path), m_tablename(tablename)
{
    if (sqlite3_open(m_file_path.c_str(), &m_db) != SQLITE_OK) {
        std::cerr << "Error: sqlite connection error";
    }
}

SqliteDBLogger::~SqliteDBLogger() {
    sqlite3_close(m_db);
}

void SqliteDBLogger::m_log(const Log& log) {
    if (m_create_table() != SQLITE_OK) {
        std::cerr << "Error: sqlite table creation error" << std::endl;
    }

    const char* log_insertion_sql = "INSERT INTO logs (timestamp, level, info) VALUES (?, ?, ?);";
    sqlite3_stmt* log_insertion_stmt = nullptr;

    if (sqlite3_prepare_v2(m_db, log_insertion_sql, -1, &log_insertion_stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error: sqlite preparing error" << std::endl;
    }

    sqlite3_bind_text(log_insertion_stmt, 1, log.get_timestamp().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(log_insertion_stmt, 2, log_level_to_string(log.get_level()).c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(log_insertion_stmt, 3, log.get_info().c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(log_insertion_stmt) != SQLITE_DONE) {
        std::cerr << "Error: sqlite insertion error" << std::endl;
    }

    sqlite3_finalize(log_insertion_stmt);

    LH_DEBUG_PRINT("New log added to db \"" << m_file_path << "\" with level \"" << log_level_to_console_colored_string(log.get_level()) << "\": \"" << log.get_info() << "\"");
}

int SqliteDBLogger::m_create_table() {
    std::string table_creation_sql = "CREATE TABLE IF NOT EXISTS " + m_tablename + " (id INTEGER PRIMARY KEY AUTOINCREMENT, timestamp TEXT, level TEXT, info TEXT);";

    return sqlite3_exec(m_db, table_creation_sql.c_str(), nullptr, nullptr, nullptr);
}