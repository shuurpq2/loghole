cmake_minimum_required(VERSION 3.28)

project(loghole_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

list(APPEND CMAKE_PREFIX_PATH "/home/savethebees/my_libs")

find_package(loghole REQUIRED)

add_executable(a.out
    log_test.cpp
    logger_factory_test.cpp
    file_logger_test.cpp
    thread_pool_test.cpp
    base_logger_test.cpp
    sqlite_db_logger_test.cpp
)

target_include_directories(a.out PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(a.out PRIVATE gtest_main loghole::loghole)

include(GoogleTest)
gtest_discover_tests(a.out)