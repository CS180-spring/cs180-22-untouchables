include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)

add_library(console console.cpp)

target_include_directories(console PUBLIC include)

target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(console_test console_test.cpp)

target_link_libraries(console_test
 PRIVATE
  GTest::GTest
  console)

add_test(console_gtests console_test)