/*#include <Common/Math/Number/AlbaNumber.hpp>
#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>
#include <benchmark/benchmark.h>
using namespace std;

namespace alba {

static void BM_BaseRunForInteger(benchmark::State& state) {
    // Perform setup here
    AlbaUniformNonDeterministicRandomizer<int64_t> randomizer(
        numeric_limits<int64_t>::min(), numeric_limits<int64_t>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        benchmark::DoNotOptimize(randomizer.getRandomValue());
        benchmark::ClobberMemory();  // is it not needed?
    }
}
static void BM_BaseRunForDouble(benchmark::State& state) {
    // Perform setup here
    AlbaUniformNonDeterministicRandomizer<double> randomizer(
        numeric_limits<double>::min(), numeric_limits<double>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        benchmark::DoNotOptimize(randomizer.getRandomValue());
        benchmark::ClobberMemory();  // is it not needed?
    }
}
static void BM_BaseRunForTwoIntegers(benchmark::State& state) {
    // Perform setup here
    AlbaUniformNonDeterministicRandomizer<int32_t> randomizer(
        numeric_limits<int32_t>::min(), numeric_limits<int32_t>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        benchmark::DoNotOptimize(randomizer.getRandomValue());
        benchmark::DoNotOptimize(randomizer.getRandomValue());
        benchmark::ClobberMemory();  // is it not needed?
    }
}
static void BM_BaseRunForTwoFloats(benchmark::State& state) {
    // Perform setup here
    AlbaUniformNonDeterministicRandomizer<float> randomizer(numeric_limits<float>::min(), numeric_limits<float>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        benchmark::DoNotOptimize(randomizer.getRandomValue());
        benchmark::DoNotOptimize(randomizer.getRandomValue());
        benchmark::ClobberMemory();  // is it not needed?
    }
}
static void BM_AlbaNumberIntegerCreation(benchmark::State& state) {
    // Perform setup here
    AlbaUniformNonDeterministicRandomizer<int64_t> randomizer(
        numeric_limits<int64_t>::min(), numeric_limits<int64_t>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        AlbaNumber randomNumber(randomizer.getRandomValue());
        benchmark::DoNotOptimize(randomNumber);
        benchmark::ClobberMemory();  // is it not needed?
    }
}
static void BM_AlbaNumberDoubleCreation(benchmark::State& state) {
    // Perform setup here
    AlbaUniformNonDeterministicRandomizer<double> randomizer(
        numeric_limits<double>::min(), numeric_limits<double>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        AlbaNumber randomNumber(randomizer.getRandomValue());
        benchmark::DoNotOptimize(randomNumber);
        benchmark::ClobberMemory();  // is it not needed?
    }
}
static void BM_AlbaNumberFractionCreation(benchmark::State& state) {
    // Perform setup here
    AlbaUniformNonDeterministicRandomizer<int32_t> randomizer(
        numeric_limits<int32_t>::min(), numeric_limits<int32_t>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        AlbaNumber randomNumber(AlbaNumber::createFraction(
            randomizer.getRandomValue(), static_cast<uint32_t>(randomizer.getRandomValue())));
        benchmark::DoNotOptimize(randomNumber);
        benchmark::ClobberMemory();  // is it not needed?
    }
}
static void BM_AlbaNumberComplexNumberCreation(benchmark::State& state) {
    // Perform setup here
    AlbaUniformNonDeterministicRandomizer<float> randomizer(numeric_limits<float>::min(), numeric_limits<float>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        AlbaNumber randomNumber(
            AlbaNumber::createComplexNumber(randomizer.getRandomValue(), randomizer.getRandomValue()));
        benchmark::DoNotOptimize(randomNumber);
        benchmark::ClobberMemory();  // is it not needed?
    }
}
// Register the function as a benchmark
BENCHMARK(BM_BaseRunForInteger);
BENCHMARK(BM_BaseRunForDouble);BENCHMARK(BM_BaseRunForTwoIntegers);
BENCHMARK(BM_BaseRunForTwoFloats);
BENCHMARK(BM_AlbaNumberIntegerCreation);
BENCHMARK(BM_AlbaNumberDoubleCreation);
BENCHMARK(BM_AlbaNumberFractionCreation);
BENCHMARK(BM_AlbaNumberComplexNumberCreation);

// Run the benchmark
BENCHMARK_MAIN();

}  // namespace alba

*/