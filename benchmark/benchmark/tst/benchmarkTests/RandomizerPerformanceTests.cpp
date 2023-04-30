/*#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>
#include <benchmark/benchmark.h>

using namespace std;

namespace alba {

static void BM_EntropySourceAsRandomDevice(benchmark::State& state) {
    // Perform setup here

    std::random_device entropySource;
    while (state.KeepRunning()) {
        // This code gets timed

        benchmark::DoNotOptimize(entropySource());
        benchmark::ClobberMemory();  // is it not needed?
    }
}

static void BM_EntropySourceBasedOnTime(benchmark::State& state) {
    // Perform setup here

    AlbaEntropySourceBasedOnTime entropySource;
    while (state.KeepRunning()) {
        // This code gets timed

        benchmark::DoNotOptimize(entropySource());
        benchmark::ClobberMemory();  // is it not needed?
    }
}

static void BM_EntropySourceAsCombinedSource(benchmark::State& state) {
    // Perform setup here

    AlbaCombinedEntropySource entropySource;
    while (state.KeepRunning()) {
        // This code gets timed

        benchmark::DoNotOptimize(entropySource());
        benchmark::ClobberMemory();  // is it not needed?
    }
}

static void BM_RandomEngineAsMersenneTwister32(benchmark::State& state) {
    // Perform setup here

    mt19937 randomEngine;
    while (state.KeepRunning()) {
        // This code gets timed

        benchmark::DoNotOptimize(randomEngine());
        benchmark::ClobberMemory();  // is it not needed?
    }
}

static void BM_RandomEngineAsMersenneTwister64(benchmark::State& state) {
    // Perform setup here

    mt19937_64 randomEngine;
    while (state.KeepRunning()) {
        // This code gets timed

        benchmark::DoNotOptimize(randomEngine());
        benchmark::ClobberMemory();  // is it not needed?
    }
}

static void BM_RandomDistributionAsUniform32BitInteger(benchmark::State& state) {
    // Perform setup here

    mt19937 randomEngine;
    uniform_int_distribution<uint32_t> randomDistribution;
    while (state.KeepRunning()) {
        // This code gets timed

        benchmark::DoNotOptimize(randomDistribution(randomEngine));
        benchmark::ClobberMemory();  // is it not needed?
    }
}

static void BM_RandomDistributionAsUniform32BitFloats(benchmark::State& state) {
    // Perform setup here

    mt19937 randomEngine;
    uniform_real_distribution<float> randomDistribution;
    while (state.KeepRunning()) {
        // This code gets timed

        benchmark::DoNotOptimize(randomDistribution(randomEngine));
        benchmark::ClobberMemory();  // is it not needed?
    }
}

// Register the function as a benchmark
BENCHMARK(BM_EntropySourceAsRandomDevice);
BENCHMARK(BM_EntropySourceBasedOnTime);
BENCHMARK(BM_EntropySourceAsCombinedSource);
BENCHMARK(BM_RandomEngineAsMersenneTwister32);
BENCHMARK(BM_RandomEngineAsMersenneTwister64);
BENCHMARK(BM_RandomDistributionAsUniform32BitInteger);
BENCHMARK(BM_RandomDistributionAsUniform32BitFloats);

// Run the benchmark
BENCHMARK_MAIN();

}  // namespace alba

*/
