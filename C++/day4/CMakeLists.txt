cmake_minimum_required(VERSION 2.8.11)

#Turn on C++11 Support
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
set(files
    var1.h
    var1.cpp
    )

# Locate GTest
find_package(GTest REQUIRED)
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(run_tests var1test.cpp)
target_link_libraries(run_tests GTest::Main)
