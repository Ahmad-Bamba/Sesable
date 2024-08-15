#include "logger.hpp"

// We have no control over outside code, so it shouldn't be subject to lints
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#include "crow.h"
#pragma GCC diagnostic pop


#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
    int constexpr default_port = 8080;
} // end of anonymous namespace

int main(int argc, char const* argv[]) {
    using namespace Sesable;

    std::ios::sync_with_stdio(false);

    std::vector<std::string> const args { argv, argv + argc };

    Logger log { std::cout };
    log.filter(Severity::Trace);

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

