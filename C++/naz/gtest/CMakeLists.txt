cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(/usr/include/gtest)
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(run_tests naztest.cpp)
target_link_libraries(run_tests /usr/lib/libgtest_main.a /usr/lib/libgtest.a -lpthread)
