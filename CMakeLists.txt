cmake_minimum_required(VERSION 3.28)
project(loghole VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(loghole STATIC
        src/console_logger.cpp
        src/file_logger.cpp
        src/log_level.cpp
        src/log.cpp
        src/loghole.cpp
        src/thread_pool.cpp
        src/base_logger.cpp
        src/sql_db_logger.cpp
)

target_compile_definitions(loghole PRIVATE $<$<CONFIG:Debug>:LH_DEBUG>)

target_include_directories(loghole PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)