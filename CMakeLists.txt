cmake_minimum_required(VERSION 3.10)

project(Je-Log)

# Directories
set(JELOG_LIBRARY_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Je-Log")
set(JELOG_TESTS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Tests")
set(JELOG_SAMPLES_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Samples")


# Set C++ Standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(JeLog INTERFACE)


target_include_directories(JeLog INTERFACE include "${JELOG_LIBRARY_DIRECTORY}/")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/JeLog")


# Build Sample Project
if (${CMAKE_CXX_COMPILER} MATCHES ".*em[+][+]")
    set(EMSCRIPTEN TRUE)
else()
    set(EMSCRIPTEN FALSE)
endif()

# Build Sample Project
if (${CMAKE_CXX_COMPILER} MATCHES ".*em[+][+]")
    set(EMSCRIPTEN TRUE)
else()
    set(EMSCRIPTEN FALSE)
endif()


file(GLOB SOURCES
    src/logger.cpp
    src/utils/file_utils.cpp
)

add_library( ${SOURCES})

file(GLOB TEST_SOURCES
    tests/test_logger.cpp
    tests/test_file_utils.cpp
)

add_executable(logging-library-tests ${TEST_SOURCES})
target_link_libraries(logging-library-tests logging-library)