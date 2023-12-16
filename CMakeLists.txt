cmake_minimum_required(VERSION 3.16)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


project(Practice
        VERSION 1.0
        LANGUAGES CXX)

find_package(benchmark REQUIRED)

file(GLOB ALL_SOURCES "*.cpp")
file(GLOB ALL_HEADERS "*.hpp")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.10.0.zip
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

set(GENERATED_HEADER "All.hpp")
file(WRITE ${GENERATED_HEADER})
foreach(HEADER ${ALL_HEADERS})
        file(RELATIVE_PATH REL_HEADER ${CMAKE_CURRENT_SOURCE_DIR} ${HEADER})
        if(NOT REL_HEADER STREQUAL ${GENERATED_HEADER})
                file(APPEND ${GENERATED_HEADER} "#include \"${HEADER}\"\n")
        endif()
endforeach()

add_executable(benchmark "Benchmark.cc" ${ALL_SOURCES})
target_link_libraries(benchmark benchmark::benchmark gtest)

add_executable(test "Test.cc" ${ALL_SOURCES})
target_link_libraries(test benchmark::benchmark gtest_main)
gtest_discover_tests(test)