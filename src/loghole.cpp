#include "loghole.h"
#include "debug.h"
#include "log.h"
#include <iostream>
#include <algorithm>

int Loghole::get_logger_idx(std::shared_ptr<ILogger> logger) {
    int idx = -1;

    for (int i = 0; i < m_loggers.size(); i++) {
        if (m_loggers[i] == logger) {
            idx = i;
            break;
        }
    }

    return idx;
}

void Loghole::log(std::string_view info, LogLevel level) {
    LH_DEBUG_PRINT("New log with level \"" << log_level_to_string(level) << "\": " << info);

    Log log(info, level);

    for (int i = 0; i < m_loggers.size(); i++) {
        m_loggers[i]->prep_to_log(log);
    }
}

void Loghole::attach(std::shared_ptr<ILogger> logger) {
    if (get_logger_idx(logger) == -1) {
        m_loggers.push_back(logger);

        LH_DEBUG_PRINT(logger << " attached to " << this);

        return;
    }

    LH_DEBUG_PRINT(logger << " is already attached to " << this);
}

void Loghole::detach(std::shared_ptr<ILogger> logger) {
    m_loggers.erase(std::remove(m_loggers.begin(), m_loggers.end(), logger), m_loggers.end());
    LH_DEBUG_PRINT("Successfully detached " << logger << " from " << this);
}