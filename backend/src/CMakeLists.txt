set(BACKEND_SRCS
    main.cpp
    logger.cpp
)

set(BACKEND_LINK_LIBS
    # Crow::Crow
    Boost::date_time
    Boost::system
    JsonCpp::JsonCpp
    Drogon::Drogon
)
if (SESABLE_SANITIZE)
    list(APPEND BACKEND_LINK_LIBS 
        "-fsanitize=address"
        "-fsanitize=undefined"
    )
endif()

add_executable(sesable_backend ${BACKEND_SRCS})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(OPTIMIZATION_LEVEL "-O0")
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(OPTIMIZATION_LEVEL "-Os")
else()
    set(OPTIMIZATION_LEVEL "-O2")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR "RelWithDebInfo")
    set(DEBUG_INFO "-ggdb3")
else()
    set(DEBUG_INFO "-g0")
endif()

target_compile_options(sesable_backend
    PRIVATE ${OPTIMIZATION_LEVEL}
    PRIVATE "-Wall"
    PRIVATE "-Wextra"
    PRIVATE "-Weffc++"
    PRIVATE "-Werror"
    PRIVATE "-pedantic"
)

if (NOT SESABLE_SANITIZE)
    target_compile_options(sesable_backend
        PRIVATE ${DEBUG_INFO}
    )
else()
    target_compile_options(sesable_backend
        PRIVATE "-ggdb3"
        PRIVATE "-fsanitize=address"
        PRIVATE "-fsanitize=undefined"
        PRIVATE "-fno-omit-frame-pointer"
    )
endif()

target_link_libraries(sesable_backend
    PRIVATE ${BACKEND_LINK_LIBS}
)

target_include_directories(sesable_backend
    PRIVATE ${Boost_INCLUDE_DIRS}
)

if (SESABLE_LINT AND CLANG_TIDY_EXE)
    set_target_properties(sesable_backend 
        PROPERTIES 
        CXX_CLANG_TIDY "${CLANG_TIDY_EXE};--config-file=${PROJECT_SOURCE_DIR}/.clang-tidy"
    )
endif()