cmake_minimum_required(VERSION 3.10)

project(QueueUnitTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Source files
set(SOURCES
    queue.cpp
)

# Mock and Test files
set(MOCK_SOURCES
   
)

set(TEST_SOURCES
    queue_test.cpp
)

# Create executable for tests
add_executable(QueueTests ${SOURCES} ${TEST_SOURCES} ${MOCK_SOURCES})

# Link libraries
target_link_libraries(QueueTests
    gtest
    gmock
    gtest_main
    pthread
)

# Enable tests
enable_testing()

include(GoogleTest)
gtest_discover_tests(QueueTests)