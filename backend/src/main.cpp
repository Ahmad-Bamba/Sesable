/*
    Sesable -- fast, lightweight, organization-based encrypted notes.
    Copyright (C) 2024  Ahmad Bamba

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License;
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "logger.hpp"

// We have no control over outside code, so it shouldn't be subject to some
// lints
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#include "crow.h"
#pragma GCC diagnostic pop


#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace {
    std::string_view constexpr license_message = R"(
Sesable  Copyright (C) 2024  Ahmad Bamba
NOTICE This program comes with ABSOLUTELY NO WARRANTY;
This is free software, and you are welcome to redistribute it
under certain conditions;
)";

    int constexpr default_port = 8080;
} // end of anonymous namespace

int main(int argc, char const* argv[]) {
    using namespace Sesable;

    std::ios::sync_with_stdio(false);
    std::cout << license_message;

    std::vector<std::string> const args { argv, argv + argc };

    // TODO: build actual application.

    return 0;
}

