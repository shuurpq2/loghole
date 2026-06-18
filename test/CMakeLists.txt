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

add_executable(a.out
    ../src/console_logger.cpp
    ../src/file_logger.cpp
    ../src/log_level.cpp
    ../src/log.cpp
    ../src/loghole.cpp
    ../src/thread_pool.cpp
    log_test.cpp
)

target_include_directories(a.out PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_link_libraries(a.out PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(a.out)