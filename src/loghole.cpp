#include "loghole.h"
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

void Loghole::log(std::string_view msg) {
    for (int i = 0; i < m_loggers.size(); i++) {
        m_loggers[i]->log(msg);
    }
}

void Loghole::attach(std::shared_ptr<ILogger> logger) {
    if (get_logger_idx(logger) == -1) {
        m_loggers.push_back(logger);
    }
}

void Loghole::detach(std::shared_ptr<ILogger> logger) {
    m_loggers.erase(std::remove(m_loggers.begin(), m_loggers.end(), logger), m_loggers.end());
}