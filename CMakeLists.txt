cmake_minimum_required(VERSION 3.14)
project(rpow_benchmarks CXX C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build the RPOW server library
add_library(rpow_server STATIC
    server/sha1.c
    server/sha.h
)

target_include_directories(rpow_server PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/server
    ${CMAKE_CURRENT_SOURCE_DIR}/common
)

# Fetch CodSpeed-compatible Google Benchmark
include(FetchContent)

FetchContent_Declare(
    google_benchmark
    GIT_REPOSITORY https://github.com/CodSpeedHQ/codspeed-cpp.git
    GIT_TAG main
    GIT_SHALLOW TRUE
)

# Instrument hooks for CodSpeed
FetchContent_Declare(
    instrument_hooks_repo
    GIT_REPOSITORY https://github.com/CodSpeedHQ/codspeed-instrument-hooks.git
    GIT_TAG main
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(google_benchmark instrument_hooks_repo)

# Build benchmarks
add_executable(sha1_benchmark
    benchmarks/sha1_bench.cpp
    benchmarks/sha1_wrapper.c
)

target_link_libraries(sha1_benchmark
    PRIVATE
    rpow_server
    benchmark::benchmark
)

target_include_directories(sha1_benchmark PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/server
    ${CMAKE_CURRENT_SOURCE_DIR}/common
)

# Enable testing
enable_testing()
add_test(NAME sha1_benchmark COMMAND sha1_benchmark)
