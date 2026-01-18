#include <benchmark/benchmark.h>
#include "sha.h"
#include <cstring>
#include <vector>

// Benchmark SHA1 with different input sizes
static void BM_SHA1_Small(benchmark::State& state) {
    const char* data = "Hello, World!";
    size_t len = strlen(data);
    SHA_CTX ctx;
    sha1_byte digest[SHA1_DIGEST_LENGTH];
    
    for (auto _ : state) {
        SHA1_Init(&ctx);
        SHA1_Update(&ctx, (sha1_byte*)data, len);
        SHA1_Final(digest, &ctx);
        benchmark::DoNotOptimize(digest);
        benchmark::ClobberMemory();
    }
    
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(len));
}
BENCHMARK(BM_SHA1_Small);

static void BM_SHA1_Medium(benchmark::State& state) {
    // Create a 1KB buffer
    std::vector<char> data(1024, 'A');
    SHA_CTX ctx;
    sha1_byte digest[SHA1_DIGEST_LENGTH];
    
    for (auto _ : state) {
        SHA1_Init(&ctx);
        SHA1_Update(&ctx, (sha1_byte*)data.data(), data.size());
        SHA1_Final(digest, &ctx);
        benchmark::DoNotOptimize(digest);
        benchmark::ClobberMemory();
    }
    
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(data.size()));
}
BENCHMARK(BM_SHA1_Medium);

static void BM_SHA1_Large(benchmark::State& state) {
    // Create a 64KB buffer
    std::vector<char> data(64 * 1024, 'B');
    SHA_CTX ctx;
    sha1_byte digest[SHA1_DIGEST_LENGTH];
    
    for (auto _ : state) {
        SHA1_Init(&ctx);
        SHA1_Update(&ctx, (sha1_byte*)data.data(), data.size());
        SHA1_Final(digest, &ctx);
        benchmark::DoNotOptimize(digest);
        benchmark::ClobberMemory();
    }
    
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(data.size()));
}
BENCHMARK(BM_SHA1_Large);

// Benchmark with varying input sizes
static void BM_SHA1_VariableSize(benchmark::State& state) {
    size_t size = state.range(0);
    std::vector<char> data(size, 'X');
    SHA_CTX ctx;
    sha1_byte digest[SHA1_DIGEST_LENGTH];
    
    for (auto _ : state) {
        SHA1_Init(&ctx);
        SHA1_Update(&ctx, (sha1_byte*)data.data(), data.size());
        SHA1_Final(digest, &ctx);
        benchmark::DoNotOptimize(digest);
        benchmark::ClobberMemory();
    }
    
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(size));
}
BENCHMARK(BM_SHA1_VariableSize)->Range(64, 8<<10);

// Benchmark just the Init operation
static void BM_SHA1_Init(benchmark::State& state) {
    SHA_CTX ctx;
    
    for (auto _ : state) {
        SHA1_Init(&ctx);
        benchmark::DoNotOptimize(&ctx);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_SHA1_Init);

// Benchmark incremental updates
static void BM_SHA1_IncrementalUpdates(benchmark::State& state) {
    std::vector<char> chunk(64, 'M');  // 64 byte chunks
    SHA_CTX ctx;
    sha1_byte digest[SHA1_DIGEST_LENGTH];
    
    for (auto _ : state) {
        SHA1_Init(&ctx);
        // Simulate multiple small updates
        for (int i = 0; i < 16; i++) {
            SHA1_Update(&ctx, (sha1_byte*)chunk.data(), chunk.size());
        }
        SHA1_Final(digest, &ctx);
        benchmark::DoNotOptimize(digest);
        benchmark::ClobberMemory();
    }
    
    state.SetBytesProcessed(int64_t(state.iterations()) * 64 * 16);
}
BENCHMARK(BM_SHA1_IncrementalUpdates);

BENCHMARK_MAIN();
