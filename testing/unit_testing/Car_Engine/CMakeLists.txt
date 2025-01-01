cmake_minimum_required(VERSION 3.10)

project(CarUnitTest)

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
    car.cpp
    v8_engine.cpp
)

# Mock and Test files
set(MOCK_SOURCES
    engine_mock.cpp
)

set(TEST_SOURCES
    car_test.cpp
)

# Create executable for tests
add_executable(CarTests ${SOURCES} ${TEST_SOURCES} ${MOCK_SOURCES})

# Link libraries
target_link_libraries(CarTests
    gtest
    gmock
    gtest_main
    pthread
)

# Enable tests
enable_testing()

include(GoogleTest)
gtest_discover_tests(CarTests)