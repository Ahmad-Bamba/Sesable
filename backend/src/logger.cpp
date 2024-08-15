#include "logger.hpp"

namespace Sesable {

unsigned Logger::log(LogMessage const message) {
    if (message.severity != Severity::Critical
    and message.severity < m_filter) {
        return 0u;
    }

    auto const sev_sv = severity_str(m_severity);

    auto last_pos = tellp();
    {
        std::scoped_lock lock{ m_mutex };
        put('(');
        write(sev_sv.cbegin(), static_cast<std::streamsize>(sev_sv.size()));
        write(") ", 2);
        write(
            message.message_str.cbegin(),
            static_cast<std::streamsize>(message.message_str.size()
            ));
    }
    auto current_pos = tellp();

    unsigned ret = current_pos - last_pos;

    return ret;
}

Logger& Logger::operator<<(char const* char_buf) {
    if (m_severity != Severity::Critical
    and m_severity < m_filter ) {
        return *this;
    }

    if(char_buf == nullptr) {
        return *this;
    }

    std::string_view cb_sv { char_buf };

    std::scoped_lock lock{ m_mutex };
    write(cb_sv.cbegin(), static_cast<std::streamsize>(cb_sv.size()));
    return *this;
}

Logger& Logger::operator<<(char const ch) {
    std::scoped_lock lock { m_mutex };
    put(ch);
    return *this;
}

Logger& Logger::operator<<(std::ostream& (*fp)(std::ostream&)) {
    std::scoped_lock lock{ m_mutex };
    fp(*this);
    return *this;
}

Logger& operator<<(Logger& logger, Severity const severity) {
    logger.m_severity = severity;

    auto const sev_sv = severity_str(severity);

    std::scoped_lock lock{ logger.m_mutex };
    logger.put('(');
    logger.write(sev_sv.cbegin(), static_cast<std::streamsize>(sev_sv.size()));
    logger.write(") ", 2);
    return logger;
}

Logger& operator<<(Logger& logger, LogMessage const message) {
    logger.log(message);
    return logger;
}

void Logger::filter(Severity filter) {
    std::scoped_lock lock { m_mutex };
    m_filter = filter;
}

Severity Logger::getCurrentFilter() const {
    std::scoped_lock lock { m_mutex };
    return m_filter;
}

} // end of namespace Sesable