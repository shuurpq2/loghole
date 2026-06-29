cmake_minimum_required(VERSION 3.28)
project(loghole VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "/home/savethebees/my_libs")

find_package(SQLite3 REQUIRED)

find_package(colorhead REQUIRED)

add_library(loghole STATIC
        src/loggers/console_logger.cpp
        src/loggers/file_logger.cpp
        src/loggers/base_logger.cpp
        src/loggers/sqlite_db_logger.cpp
        src/log_level.cpp
        src/log.cpp
        src/loghole.cpp
        src/thread_pool.cpp
        src/utils.cpp
)

target_link_libraries(loghole PUBLIC SQLite::SQLite3 clrhd::colorhead)

target_compile_definitions(loghole PRIVATE $<$<CONFIG:Debug>:LH_DEBUG>)
set_target_properties(loghole PROPERTIES DEBUG_POSTFIX d)


target_include_directories(loghole PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

include(CMakePackageConfigHelpers)

install(TARGETS loghole
        EXPORT logholeTargets
        ARCHIVE DESTINATION lib
)

install(EXPORT logholeTargets
        FILE logholeTargets.cmake
        NAMESPACE lh::
        DESTINATION lib/cmake/loghole
)

install(DIRECTORY include/ DESTINATION include)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/logholeConfig.cmake" "
include(CMakeFindDependencyMacro)
find_dependency(SQLite3 REQUIRED)
include(\"\${CMAKE_CURRENT_LIST_DIR}/logholeTargets.cmake\")
")


file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/logholeConfig.cmake" [[
include(CMakeFindDependencyMacro)

find_dependency(colorhead REQUIRED)
find_dependency(SQLite3 REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/logholeTargets.cmake")
]])

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/logholeConfig.cmake" 
    DESTINATION lib/cmake/loghole
)


install(FILES "${CMAKE_CURRENT_BINARY_DIR}/logholeConfig.cmake" DESTINATION lib/cmake/loghole)