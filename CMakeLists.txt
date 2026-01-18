cmake_minimum_required(VERSION 3.20)
project(RPOW VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Enable release mode with debug symbols to display useful profiling data
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Server library - using wrapper that includes string.h
add_library(rpow_server STATIC
    benchmarks/sha1_wrapper.c
)

target_include_directories(rpow_server PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/server
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${OPENSSL_INCLUDE_DIR}
)

target_link_libraries(rpow_server PUBLIC
    OpenSSL::Crypto
)

# Benchmarks
option(BUILD_BENCHMARKS "Build benchmarks" ON)

if(BUILD_BENCHMARKS)
    include(FetchContent)
    
    set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)
    
    # Fetch CodSpeed's google_benchmark
    FetchContent_Declare(
        google_benchmark
        GIT_REPOSITORY https://github.com/CodSpeedHQ/codspeed-cpp.git
        SOURCE_SUBDIR google_benchmark
        GIT_TAG main
    )
    
    FetchContent_MakeAvailable(google_benchmark)
    
    # Benchmark executable
    add_executable(rpow_benchmarks
        benchmarks/sha1_bench.cpp
    )
    
    target_link_libraries(rpow_benchmarks PRIVATE
        rpow_server
        benchmark::benchmark
    )
    
    target_include_directories(rpow_benchmarks PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/server
        ${CMAKE_CURRENT_SOURCE_DIR}/common
    )
endif()
