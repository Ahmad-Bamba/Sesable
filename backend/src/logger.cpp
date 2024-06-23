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
        //NOLINTBEGIN(cppcoreguidelines-narrowing-conversions)
        write(sev_sv.cbegin(), sev_sv.size());
        write(") ", 2);
        write(message.message_str.cbegin(), message.message_str.size());
        //NOLINTEND(cppcoreguidelines-narrowing-conversions)
    }
    auto current_pos = tellp();

    unsigned ret = current_pos - last_pos;

    return ret;
}

Logger& operator<<(Logger& logger, Severity const severity) {
    logger.m_severity = severity;

    auto const sev_sv = severity_str(severity);
    std::scoped_lock lock{ logger.m_mutex };
    //NOLINTBEGIN(cppcoreguidelines-narrowing-conversions)
    logger.put('(');
    logger.write(sev_sv.cbegin(), sev_sv.size());
    logger.write(") ", 2);
    //NOLINTEND(cppcoreguidelines-narrowing-conversions)
    return logger;
}

Logger& operator<<(Logger& logger, LogMessage const message) {
    logger.log(message);
    return logger;
}

} // end of namespace Sesable