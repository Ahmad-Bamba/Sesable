add_subdirectory(src)

# third_party dependency resolution
include(FetchContent)
find_package(Git REQUIRED)

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/root)

message(STATUS "Third-party build dependencies for backend.")

message(STATUS "Downloading asio...")
FetchContent_Declare(
    asio
    URL https://sourceforge.net/projects/asio/files/asio/1.30.2%20%28Stable%29/asio-1.30.2.tar.gz/download
    URL_MD5 c1643d3eddd45b210b760acc7ec25d59
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/asio
)
FetchContent_MakeAvailable(asio)
list(APPEND CMAKE_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/third_party/asio/include)

find_package(Boost CONFIG COMPONENTS date_time system)
if(NOT BOOST_DATE_TYPE_FOUND OR NOT BOOST_SYSTEM_FOUND)
    set(BOOST_INCLUDE_LIBRARIES data_time system)
    set(BOOST_ENABLE_CMAKE ON)
    message(STATUS "Downloading boost...")
    FetchContent_Declare(
        Boost
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG boost-1.64.0
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/boost
        OVERRIDE_FIND_PACKAGE
    )
    FetchContent_MakeAvailable(Boost)
endif()

# if (NOT EXISTS third_party/Crow/include/crow.h)
#         execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init ${CMAKE_CURRENT_SOURCE_DIR}/third_party/Crow)
# endif()

# add_subdirectory(third_party/Crow)

message(STATUS "Downloading Crow...")
FetchContent_Declare(
    Crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/Crow
    GIT_TAG v1.2.0
)

message(STATUS "Downloading tiny-aes-c...")
FetchContent_Declare(
    tiny-aes
    GIT_REPOSITORY https://github.com/kokke/tiny-AES-c.git
)

message(STATUS "Downloading liboauthcpp...")
FetchContent_Declare(
    oauthcpp
    GIT_REPOSITORY https://github.com/sirikata/liboauthcpp.git
    SOURCE_SUBDIR build
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/aes
)

FetchContent_MakeAvailable(Crow tiny-aes oauthcpp)