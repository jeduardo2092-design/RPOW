#include <benchmark/benchmark.h>
#include <string>
#include <vector>
#include <cstring>

// External C function wrapper for SHA1
extern "C" {
    void sha1_hash_wrapper(const unsigned char* data, unsigned int len, unsigned char* digest);
}

// Benchmark SHA1 with small input (64 bytes)
static void BM_SHA1_Small(benchmark::State& state) {
    std::vector<unsigned char> input(64, 'a');
    unsigned char digest[20];
    
    for (auto _ : state) {
        sha1_hash_wrapper(input.data(), input.size(), digest);
        benchmark::DoNotOptimize(digest);
        benchmark::ClobberMemory();
    }
    
    state.SetBytesProcessed(state.iterations() * input.size());
}
BENCHMARK(BM_SHA1_Small);

// Benchmark SHA1 with medium input (1 KB)
static void BM_SHA1_Medium(benchmark::State& state) {
    std::vector<unsigned char> input(1024, 'a');
    unsigned char digest[20];
    
    for (auto _ : state) {
        sha1_hash_wrapper(input.data(), input.size(), digest);
        benchmark::DoNotOptimize(digest);
        benchmark::ClobberMemory();
    }
    
    state.SetBytesProcessed(state.iterations() * input.size());
}
BENCHMARK(BM_SHA1_Medium);

// Benchmark SHA1 with large input (64 KB)
static void BM_SHA1_Large(benchmark::State& state) {
    std::vector<unsigned char> input(65536, 'a');
    unsigned char digest[20];
    
    for (auto _ : state) {
        sha1_hash_wrapper(input.data(), input.size(), digest);
        benchmark::DoNotOptimize(digest);
        benchmark::ClobberMemory();
    }
    
    state.SetBytesProcessed(state.iterations() * input.size());
}
BENCHMARK(BM_SHA1_Large);

// Benchmark SHA1 with very large input (1 MB)
static void BM_SHA1_VeryLarge(benchmark::State& state) {
    std::vector<unsigned char> input(1048576, 'a');
    unsigned char digest[20];
    
    for (auto _ : state) {
        sha1_hash_wrapper(input.data(), input.size(), digest);
        benchmark::DoNotOptimize(digest);
        benchmark::ClobberMemory();
    }
    
    state.SetBytesProcessed(state.iterations() * input.size());
}
BENCHMARK(BM_SHA1_VeryLarge);

// Benchmark SHA1 with varying input sizes
static void BM_SHA1_Range(benchmark::State& state) {
    size_t size = state.range(0);
    std::vector<unsigned char> input(size, 'a');
    unsigned char digest[20];
    
    for (auto _ : state) {
        sha1_hash_wrapper(input.data(), input.size(), digest);
        benchmark::DoNotOptimize(digest);
        benchmark::ClobberMemory();
    }
    
    state.SetBytesProcessed(state.iterations() * size);
}
BENCHMARK(BM_SHA1_Range)->Range(8, 8<<10);

BENCHMARK_MAIN();
