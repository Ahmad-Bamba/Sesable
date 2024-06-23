#ifndef SESABLE_HEADER_LOGGER_HPP
#define SESABLE_HEADER_LOGGER_HPP

#include <boost/date_time/posix_time/posix_time.hpp>

#include <functional>
#include <iostream>
#include <mutex>
#include <ostream>
#include <string_view>
#include <sstream>

namespace Sesable {

enum class Severity : int {
    Trace    = -1,
    Debug    =  0,
    Info     =  1,
    Warning  =  2,
    Error    =  3,
    Critical =  4
};

constexpr std::string_view severity_str(Severity const severity) {
    switch(severity) {
    case Severity::Trace:
        return "Trace";
    case Severity::Debug:
        return "Debug";
    case Severity::Info:
        return "Info";
    case Severity::Warning:
        return "Warning";
    case Severity::Error:
        return "Error";
    case Severity::Critical:
        return "Critical";
    default:
        return "";
    }
}

struct LogMessage {
    Severity severity;
    std::string_view message_str;
};

// TODO: Actual logging beyond just printing to some file
class Logger : public std::ostream {
    class LoggerStrBuf : public std::stringbuf {
        std::ostream& m_stream;

        public:
        LoggerStrBuf(std::ostream& stream)
            : m_stream { stream }
        {}

        ~LoggerStrBuf() {
            if (pbase() != pptr()) {
                logOutToBuf();
            }
        }

        virtual int sync() {
            logOutToBuf();
            return 0;
        }

        void logOutToBuf() {
            auto time = boost::posix_time::microsec_clock::universal_time();
            m_stream 
                << '[' 
                << boost::posix_time::to_iso_extended_string(time)
                << "] "
                << str();
            str("");
            m_stream.flush();
        }
    };

public:
    Severity m_filter { 0 }; 
private:
    Severity m_severity;
    LoggerStrBuf m_buffer;
    std::mutex m_mutex;
public:
    Logger(std::ostream& stream, Severity sev = Severity::Debug) 
        : std::ostream(&m_buffer),
          m_buffer { stream },
          m_severity { sev }
    {}

    unsigned log(LogMessage const message);

    template<typename T>
    Logger& operator<<(T const& item) {
        if (m_severity != Severity::Critical
        and m_severity < m_filter ) {
            return *this;
        }

        auto const sev_sv = severity_str(m_severity);

        std::scoped_lock lock{ m_mutex };
        put('(');
        write(sev_sv.cbegin(), sev_sv.size()); //NOLINT
        write(") ", 2);
        std::ostream::operator<<(item);
        return *this;
    }

    Logger& operator<<(char const* char_buf) {
        if (m_severity != Severity::Critical
        and m_severity < m_filter ) {
            return *this;
        }

        if(char_buf == nullptr) {
            return *this;
        }

        std::string_view cb_sv { char_buf };

        std::scoped_lock lock{ m_mutex };
        write(cb_sv.cbegin(), cb_sv.size()); //NOLINT
        return *this;
    }

    Logger& operator<<(std::ostream& (*fp)(std::ostream&)) {
        std::scoped_lock lock{ m_mutex };
        fp(*this);
        return *this;
    }

    friend Logger& operator<<(Logger& logger, Severity const severity);
    friend Logger& operator<<(Logger& logger, LogMessage const message);
};

} // end of namespace Sesable

#endif
