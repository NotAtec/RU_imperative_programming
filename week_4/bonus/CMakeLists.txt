cmake_minimum_required(VERSION 3.10)

project(Assignment4_bonus)

set(CMAKE_CXX_STANDARD 17)

# Grab googletest dependency if needed
include(FetchContent)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/main_test.cpp)
    FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        e2239ee6043f73722e7aa812a459f54a28552929 # release-1.11.0
    )
    FetchContent_MakeAvailable(googletest)
endif()

# Build regular `main` executable
add_executable(${PROJECT_NAME} main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic-errors)

# Copy over all the files in the `files` folder if it exists
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/files/)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/files/ $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

# Check if unit tests exist and need to be compiled
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/main_test.cpp)
    # Build `main_test` executable that runs the tests
    # Define `TESTING` to prevent `main` function being generated
    add_executable(${PROJECT_NAME}_test main_test.cpp)
    target_compile_definitions(${PROJECT_NAME}_test PUBLIC TESTING)
    set_target_properties(${PROJECT_NAME}_test PROPERTIES OUTPUT_NAME "main_test")
    target_link_libraries(${PROJECT_NAME}_test gtest_main)

    # Let googletest enumerate the available tests for CTest
    enable_testing()
    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}_test)
endif()

