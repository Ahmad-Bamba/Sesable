cmake_minimum_required(VERSION 3.22) 

project(sesable
    VERSION 0.1.0
    DESCRIPTION "Sesable - Web app for dead simple, encrypted, arbitary table storage."
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_program(CLANG_TIDY_EXE clang-tidy HINTS /usr/bin /usr/local/bin)
if(NOT CLANG_TIDY_EXE OR NOT EXISTS ${PROJECT_SOURCE_DIR}/.clang-tidy)
    message(WARNING "Building without clang-tidy. Several quality control checks and guarantees are disabled!")
else()
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE} --config-file=${PROJECT_SOURCE_DIR}/.clang-tidy")
endif()

include(GNUInstallDirs)

add_subdirectory(frontend)
add_subdirectory(backend)

