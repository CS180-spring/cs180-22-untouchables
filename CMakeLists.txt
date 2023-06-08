cmake_minimum_required(VERSION 3.0)
project(movieDB)

# Add the path to nlohmann JSON library
#set(NLOHMANN_JSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/nlohmann/json.hpp)

# Set the C++ language standard
set(CMAKE_CXX_STANDARD 17)

# Add your source files
set(SOURCES
    console.cpp
    filter.cpp
    database.cpp
)

# Add the executable
add_executable(movieDB ${SOURCES})

# Specify the include directories
#target_include_directories(movieDB PRIVATE ${NLOHMANN_JSON_INCLUDE_DIR})

# Add Google Test
add_subdirectory(googletest)

# Add the test source files
set(TEST_SOURCES
    database_test.cpp
    filter_test.cpp
)

# Add the test executable
add_executable(tests ${TEST_SOURCES})

# Specify the include directories for the tests
target_include_directories(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/googletest/include
)

# Link against Google Test
target_link_libraries(tests PRIVATE
    gtest
    gtest_main
)
