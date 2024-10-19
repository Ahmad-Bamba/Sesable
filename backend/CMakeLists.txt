# third_party dependency resolution
include(FetchContent)
find_package(Git REQUIRED)

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/root)

message(STATUS "Third-party build dependencies for backend.")

message(STATUS "Downloading liboauthcpp...")
option(LIBOAUTHCPP_BUILD_TESTS OFF)
option(LIBOAUTHCPP_BUILD_DEMOS OFF)
FetchContent_Declare(
    oauthcpp
    GIT_REPOSITORY https://github.com/sirikata/liboauthcpp.git
    SOURCE_SUBDIR build
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/oauthcpp
)

FetchContent_MakeAvailable(oauthcpp)

find_package(boost_date_time CONFIG REQUIRED)
find_package(boost_system CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(Drogon CONFIG REQUIRED)
find_package(unofficial-tiny-aes-c CONFIG REQUIRED)

# Build backend
add_subdirectory(src)
