/*
#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>
#include <benchmark/benchmark.h>

using namespace std;

namespace alba {

uint64_t arrayBasedImplementationForOneByte(uint8_t const value) {
    constexpr std::array<uint8_t, 256> savedValues{
        0U, 1U, 1U, 2U, 1U, 2U, 2U, 3U, 1U, 2U, 2U, 3U, 2U, 3U, 3U, 4U, 1U, 2U, 2U, 3U, 2U, 3U, 3U, 4U, 2U, 3U,
        3U, 4U, 3U, 4U, 4U, 5U, 1U, 2U, 2U, 3U, 2U, 3U, 3U, 4U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 2U, 3U, 3U, 4U,
        3U, 4U, 4U, 5U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 1U, 2U, 2U, 3U, 2U, 3U, 3U, 4U, 2U, 3U, 3U, 4U, 3U, 4U,
        4U, 5U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U,
        3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 4U, 5U, 5U, 6U, 5U, 6U, 6U, 7U, 1U, 2U,
        2U, 3U, 2U, 3U, 3U, 4U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 3U, 4U, 4U, 5U,
        4U, 5U, 5U, 6U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 3U, 4U, 4U, 5U, 4U, 5U,
        5U, 6U, 4U, 5U, 5U, 6U, 5U, 6U, 6U, 7U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U,
        3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 4U, 5U, 5U, 6U, 5U, 6U, 6U, 7U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 4U, 5U,
        5U, 6U, 5U, 6U, 6U, 7U, 4U, 5U, 5U, 6U, 5U, 6U, 6U, 7U, 5U, 6U, 6U, 7U, 6U, 7U, 7U, 8U};
    return savedValues.at(value);
}

uint64_t arrayBasedImplementation(uint64_t const value) {
    return arrayBasedImplementationForOneByte(static_cast<uint8_t>(value)) +
           arrayBasedImplementationForOneByte(static_cast<uint8_t>(value >> 8)) +
           arrayBasedImplementationForOneByte(static_cast<uint8_t>(value >> 16)) +
           arrayBasedImplementationForOneByte(static_cast<uint8_t>(value >> 24)) +
           arrayBasedImplementationForOneByte(static_cast<uint8_t>(value >> 32)) +
           arrayBasedImplementationForOneByte(static_cast<uint8_t>(value >> 40)) +
           arrayBasedImplementationForOneByte(static_cast<uint8_t>(value >> 48)) +
           arrayBasedImplementationForOneByte(static_cast<uint8_t>(value >> 56));
}

uint64_t loopBasedImplementation(uint64_t const input) {
    // Perform setup here

    uint64_t result(0);
    for (uint64_t value = input; value > 0; value >>= 1) {
        if ((value & 1) == 1) {
            ++result;
        }
    }
    return result;
}

static void BM_BaseRun(benchmark::State& state) {
    // Perform setup here

    AlbaUniformNonDeterministicRandomizer<uint64_t> randomizer(0, numeric_limits<uint64_t>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        benchmark::DoNotOptimize(randomizer.getRandomValue());
        benchmark::ClobberMemory();  // is it not needed?
    }
}

static void BM_ArrayBasedImplementation(benchmark::State& state) {
    // Perform setup here

    AlbaUniformNonDeterministicRandomizer<uint64_t> randomizer(0, numeric_limits<uint64_t>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        benchmark::DoNotOptimize(arrayBasedImplementation(randomizer.getRandomValue()));
        benchmark::ClobberMemory();  // is it not needed?
    }
}

static void BM_LoopBasedImplementation(benchmark::State& state) {
    // Perform setup here

    AlbaUniformNonDeterministicRandomizer<uint64_t> randomizer(0, numeric_limits<uint64_t>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        benchmark::DoNotOptimize(loopBasedImplementation(randomizer.getRandomValue()));
        benchmark::ClobberMemory();  // is it not needed?
    }
}

static void BM_BuiltinBasedImplementation(benchmark::State& state) {
    // Perform setup here

    AlbaUniformNonDeterministicRandomizer<uint64_t> randomizer(0, numeric_limits<uint64_t>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        benchmark::DoNotOptimize(__builtin_popcount(randomizer.getRandomValue()));
        benchmark::ClobberMemory();  // is it not needed?
    }
}

// Register the function as a benchmark
BENCHMARK(BM_BaseRun);
BENCHMARK(BM_ArrayBasedImplementation);
BENCHMARK(BM_LoopBasedImplementation);
BENCHMARK(BM_BuiltinBasedImplementation);

// Run the benchmark
BENCHMARK_MAIN();

}  // namespace alba
*/
