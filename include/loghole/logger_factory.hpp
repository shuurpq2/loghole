#pragma once

#include "loghole/debug.hpp"
#include "loghole/loggers/base_logger.hpp"
#include <memory>

class LoggerFactory {
public:
    template<typename LoggerT, typename... Args>
    static std::shared_ptr<LoggerT> create_logger(Args&&... args) {
        auto new_logger = std::make_shared<LoggerT>(std::forward<Args>(args)...);

        LH_DEBUG_PRINT("Created logger " << new_logger << " with LoggerFactory");

        return new_logger;
    }
};