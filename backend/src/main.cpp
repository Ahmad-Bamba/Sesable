#include "logger.hpp"

#include "crow.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
    int constexpr default_port = 8080;
} // end of anonymous namespace

int main(int argc, char const* argv[]) {
    using namespace Sesable;

    std::vector<std::string> const args { argv, argv + argc };

    Logger log { std::cout };
    log.m_filter = Severity::Trace;

    [[maybe_unused]] int port = default_port;
    if (argc >= 2) {
        try {
            port = std::stoi(args[1]);
        } catch(std::exception const& e) {
            log << Severity::Error;
            log 
                << "Invalid port number. The web server will now exit."
                << std::endl;
            return 1;
        }
    }
    log.log({Severity::Info, "What is going on here?\n"});
    log << Severity::Info << "Hello, world!" << std::endl;
    log << Severity::Trace << "End of program\n"
        << "Port number was: " << port << '\n';
    log.flush();

    return 0;
}

