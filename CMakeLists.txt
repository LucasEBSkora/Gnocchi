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

set(GNOCCHI_COMPILER_INCLUDES
    ${SOURCE_DIR}/front
    ${SOURCE_DIR}
    ${GENERATED_DIRECTORY}
)

if(WIN32)
    set(GNOCCHI_COMPILER_INCLUDES ${GNOCCHI_COMPILER_INCLUDES}
        ${SOURCE_DIR}/front/windows
    )
endif()


file(GLOB GNOCCHI_COMPILER_SOURCES
    ${SOURCE_DIR}/front/*.cpp
)

add_library(CompilerSources STATIC 
    ${GENERATED_DIRECTORY}/scanner.cpp
    ${GENERATED_DIRECTORY}/parser.cpp
    ${GNOCCHI_COMPILER_SOURCES}
        src/front/scanner_utils.cpp
)
target_include_directories(CompilerSources PUBLIC ${GNOCCHI_COMPILER_INCLUDES})
set_target_properties(CompilerSources PROPERTIES
    CXX_STANDARD 20
)

add_executable(Gnocchi ${SOURCE_DIR}/main.cpp)

target_link_libraries(Gnocchi CompilerSources)

set(CMAKE_BUILD_TYPE Debug)

set_target_properties(Gnocchi PROPERTIES 
    CXX_STANDARD 20
    OUTPUT_NAME gnocchi
)

enable_testing()
add_subdirectory(unittests)