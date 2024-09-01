cmake_minimum_required(VERSION 3.22) 

project(sesable
    VERSION 0.1.0
    DESCRIPTION "Sesable - Web app for dead simple, encrypted, arbitary table storage."
    LANGUAGES CXX
)

option(SESABLE_LINT "Build with clang-tidy checks enabled" ON)
option(SESABLE_SANITIZE "Build with address and undefined behavior sanitizers" OFF)
option(SESABLE_TESTS "Build sesable backend unit tests" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24")
    cmake_policy(SET CMP0135 NEW)
endif()

if (SESABLE_LINT)
    find_program(CLANG_TIDY_EXE clang-tidy HINTS /usr/bin /usr/local/bin)
    if(NOT CLANG_TIDY_EXE OR NOT EXISTS ${PROJECT_SOURCE_DIR}/.clang-tidy)
        message(WARNING "Building without clang-tidy. Several quality control checks and guarantees are disabled!")
    endif()
endif()

include(GNUInstallDirs)

add_subdirectory(frontend)
add_subdirectory(backend)

