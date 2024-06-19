set(BACKEND_SRCS
    main.cpp
    logger.cpp
    table.cpp
    organization.cpp
)

add_executable(sesable_backend ${BACKEND_SRCS})
add_executable(sesable_backend_sanitized ${BACKEND_SRCS})

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
    PRIVATE ${DEBUG_INFO}
)

target_compile_options(sesable_backend_santizers
    PRIVATE ${OPTIMIZATION_LEVEL}
    PRIVATE "-ggdb3"
    PRIVATE "-fsanitize=address"
    PRIVATE "-fsanitize=undefined"
    PRIVATE "-fno-omit-frame-pointer"
)

