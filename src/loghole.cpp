#include "loghole.h"

void Loghole::log(std::string_view msg) {
    for (int i = 0; i < m_loggers.size(); i++) {
        m_loggers[i]->log(msg);
    }
}


void Loghole::attach(std::shared_ptr<ILogger> logger) {
    m_loggers.push_back(logger);
}
