cmake_minimum_required(VERSION 3.16)
project(LinAlg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program(CLANG_FORMAT_PATH NAMES clang-format-17 clang-format-16 clang-format-15 clang-format)

if(CLANG_FORMAT_PATH)
    message(STATUS "Found clang-format: ${CLANG_FORMAT_PATH}")

    file(GLOB_RECURSE ALL_SOURCE_FILES
        "${CMAKE_SOURCE_DIR}/include/*.hpp"
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/examples/*.cpp"
        "${CMAKE_SOURCE_DIR}/tests/*.cpp"
    )

    add_custom_target(format
        COMMAND ${CLANG_FORMAT_PATH} -i ${ALL_SOURCE_FILES}
        COMMENT "Formatting source files with clang-format..."
        VERBATIM
    )
else()
    message(WARNING "clang-format not found. Install it to use the 'format' target.")
endif()

add_subdirectory(tests)