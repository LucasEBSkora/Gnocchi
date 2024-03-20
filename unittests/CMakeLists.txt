cmake_minimum_required(VERSION 3.14)

project(GnocchiCompilerUnitTests)

################################
# GTest
################################
include(FetchContent)
FetchContent_Declare(googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG main
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
	FetchContent_Populate(googletest)
	FetchContent_MakeAvailable(googletest)
	add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

include(CTest)

################################
# Unit Tests
################################

file(GLOB_RECURSE UNIT_TESTS_SOURCES
	"*.cpp"	
)

set(CMAKE_BUILD_TYPE Debug)

foreach(testfile ${UNIT_TESTS_SOURCES})

	get_filename_component(SUITE_NAME ${testfile} NAME_WE)

	add_executable(${SUITE_NAME} 
		${testfile}
	)

	target_link_libraries(${SUITE_NAME} gtest_main ModularNOPGraph CompilerSources)

	set_target_properties(${SUITE_NAME} PROPERTIES
		CXX_STANDARD 20
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	)

	add_test(NAME "${SUITE_NAME}" COMMAND ${SUITE_NAME})

endforeach(testfile)