#pragma once

#include <memory>
#include <ilogger.hpp>

class LoggerFactory {
public:
    template<typename LoggerT, typename... Args>
    static std::shared_ptr<LoggerT> create_logger(Args&&... args) {
        return std::make_shared<LoggerT>(std::forward<Args>(args)...);
    }
};