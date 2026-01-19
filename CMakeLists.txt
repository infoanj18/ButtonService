cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(ButtonService
    VERSION 1.0.0
    LANGUAGES CXX
)

# Platform Specific Config

# QNX
if("${CMAKE_SYSTEM_NAME}" STREQUAL "QNX")
    add_compile_definitions(
        "FORD_BUTTON_SERVICE_USE_SLOG2_LOGGING"
    )
    set(BUTTON_SERVICE_QNX_LIBRARIES
        slog2
    )
endif()

# Global Config

# Use plain -std=c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_program(CCACHE_FOUND "ccache")
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif()

add_compile_options(
    "-Werror"
    "-Wall"
    "-Wpedantic"
    "-Wextra"
    "-fexceptions"
    "-g"
)

set(BUTTON_SERVICE_LIBRARIES
    ${BUTTON_SERVICE_QNX_LIBRARIES}
)

# Build Artifacts and Source

file(GLOB_RECURSE BUTTON_SERVICE_SOURCES "${PROJECT_SOURCE_DIR}/impl/src/*.cpp" )
set(BUTTON_SERVICE_HEADERS "${PROJECT_SOURCE_DIR}/impl/inc" )

add_subdirectory(impl)
