cmake_minimum_required(VERSION 3.18.0)
project(Gnocchi VERSION 0.1.0)

set(GENERATED_DIRECTORY ${CMAKE_BINARY_DIR}/build/generated)

file(MAKE_DIRECTORY ${GENERATED_DIRECTORY})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)


bison_target(parser
    ${SOURCE_DIR}/front/parser.y 
    ${GENERATED_DIRECTORY}/parser.cpp
    COMPILE_FLAGS "-Wcounterexamples"
)

flex_target(lexer 
    ${SOURCE_DIR}/front/scanner.l 
    ${GENERATED_DIRECTORY}/scanner.cpp
)

add_flex_bison_dependency(lexer parser)

include_directories(${SOURCE_DIR}/front)
include_directories(${SOURCE_DIR})
include_directories(${GENERATED_DIRECTORY})

add_executable(Gnocchi
    ${GENERATED_DIRECTORY}/parser.cpp
    ${GENERATED_DIRECTORY}/scanner.cpp
    ${SOURCE_DIR}/front/interpreter.cpp
    ${SOURCE_DIR}/main.cpp
)

set_target_properties(Gnocchi PROPERTIES 
    CXX_STANDARD 20
    OUTPUT_NAME gnocchi
)
