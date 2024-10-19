find_program(NPM_EXE npm)
if (NOT NPM_EXE)
    message(FATAL_ERROR "Could not find npm. I cannot build the frontend without it.")
endif ()
find_program(NODE_EXE node)
if (NOT NODE_EXE)
    vmessage(FATAL_ERROR "Could not find node. I cannot build the frontend without it.")
endif ()
execute_process(COMMAND "${NODE_EXE}" --version
                  OUTPUT_VARIABLE NODE_VERSION_STR
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
message(STATUS "Output node version = ${NODE_VERSION_STR}")
string(REGEX MATCH "[0-9]+\.[0-9]+\.[0-9]+" NODE_VERSION ${NODE_VERSION_STR})
if (NOT (NODE_VERSION AND (NODE_VERSION VERSION_GREATER_EQUAL "18")))
    message(FATAL_ERROR "I need a version of nodejs greater than 18. I found \"v${NODE_VERSION}\"")
endif ()

set(FRONTEND_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/npm_build)
file(MAKE_DIRECTORY ${FRONTEND_BUILD_DIR})

configure_file(.env.in ${CMAKE_CURRENT_SOURCE_DIR}/.env NEWLINE_STYLE UNIX)

add_custom_target(
    sesable_frontend
    ALL
    COMMAND ${NPM_EXE} run build
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

find_program(NPX_EXE npx)
if (SESABLE_LINT AND NPX_EXE)
    add_custom_target(lint_frontend COMMAND ${NPX_EXE} eslint src/components/** src/lib/** --fix WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    add_dependencies(sesable_frontend lint_frontend)
endif ()
