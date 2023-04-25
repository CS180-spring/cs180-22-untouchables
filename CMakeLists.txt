cmake_minimum_required(VERSION 3.0.0)
project(untouchables)

add_subdirectory(googletest)

include_directories(googletest/include)

include(CTest)
enable_testing()

add_executable(main console.cpp)
add_executable(tests test.cpp)

target_link_libraries(tests PRIVATE gtest)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
