#include <Common/Math/Number/AlbaNumber.hpp>
#include <Common/Randomizer/AlbaUniformFloatingPointRandomizer.hpp>
#include <Common/Randomizer/AlbaUniformIntegerRandomizer.hpp>
#include <benchmark/benchmark.h>

using namespace std;

namespace alba {

// Format for asm: "assembly instructions : inputs : outputs : clobbers"

static void escape(void* sinkPointer)  // to avoid optimizers deleting code
{
    asm volatile("" : : "g"(sinkPointer) : "memory");
}

static void clobber()  // to avoid optimizers deleting code
{
    asm volatile("" : : : "memory");  // tells compiler that memory is changed
}

static void BM_BaseRunForInteger(benchmark::State& state) {
    // Perform setup here

    AlbaUniformIntegerRandomizer<int64_t> randomizer(numeric_limits<int64_t>::min(), numeric_limits<int64_t>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        auto randomValue = randomizer.getRandomInteger();
        escape(&randomValue);
    }
}

static void BM_BaseRunForDouble(benchmark::State& state) {
    // Perform setup here

    AlbaUniformFloatingPointRandomizer<double> randomizer(numeric_limits<double>::min(), numeric_limits<double>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        auto randomValue(randomizer.getRandomFloatingPointValue());
        escape(&randomValue);
    }
}

static void BM_BaseRunForTwoIntegers(benchmark::State& state) {
    // Perform setup here

    AlbaUniformIntegerRandomizer<int32_t> randomizer(numeric_limits<int32_t>::min(), numeric_limits<int32_t>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        auto randomValue1 = randomizer.getRandomInteger();
        auto randomValue2 = randomizer.getRandomInteger();
        escape(&randomValue1);
        escape(&randomValue2);
    }
}

static void BM_BaseRunForTwoFloats(benchmark::State& state) {
    // Perform setup here

    AlbaUniformFloatingPointRandomizer<float> randomizer(numeric_limits<float>::min(), numeric_limits<float>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        auto randomValue1(randomizer.getRandomFloatingPointValue());
        auto randomValue2(randomizer.getRandomFloatingPointValue());
        escape(&randomValue1);
        escape(&randomValue2);
    }
}

static void BM_AlbaNumberIntegerCreation(benchmark::State& state) {
    // Perform setup here

    AlbaUniformIntegerRandomizer<int64_t> randomizer(numeric_limits<int64_t>::min(), numeric_limits<int64_t>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        AlbaNumber randomNumber(randomizer.getRandomInteger());
        escape(&randomNumber);
    }
}

static void BM_AlbaNumberDoubleCreation(benchmark::State& state) {
    // Perform setup here

    AlbaUniformFloatingPointRandomizer<double> randomizer(numeric_limits<double>::min(), numeric_limits<double>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        AlbaNumber randomNumber(randomizer.getRandomFloatingPointValue());
        escape(&randomNumber);
    }
}

static void BM_AlbaNumberFractionCreation(benchmark::State& state) {
    // Perform setup here

    AlbaUniformIntegerRandomizer<int32_t> randomizer(numeric_limits<int32_t>::min(), numeric_limits<int32_t>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        AlbaNumber randomNumber(AlbaNumber::createFraction(
            randomizer.getRandomInteger(), static_cast<uint32_t>(randomizer.getRandomInteger())));
        escape(&randomNumber);
    }
}

static void BM_AlbaNumberComplexNumberCreation(benchmark::State& state) {
    // Perform setup here

    AlbaUniformFloatingPointRandomizer<float> randomizer(numeric_limits<float>::min(), numeric_limits<float>::max());
    while (state.KeepRunning()) {
        // This code gets timed

        AlbaNumber randomNumber(AlbaNumber::createComplexNumber(
            randomizer.getRandomFloatingPointValue(), randomizer.getRandomFloatingPointValue()));
        escape(&randomNumber);
    }
}

// Register the function as a benchmark
BENCHMARK(BM_BaseRunForInteger);
BENCHMARK(BM_BaseRunForDouble);
BENCHMARK(BM_BaseRunForTwoIntegers);
BENCHMARK(BM_BaseRunForTwoFloats);
BENCHMARK(BM_AlbaNumberIntegerCreation);
BENCHMARK(BM_AlbaNumberDoubleCreation);
BENCHMARK(BM_AlbaNumberFractionCreation);
BENCHMARK(BM_AlbaNumberComplexNumberCreation);

// Run the benchmark
BENCHMARK_MAIN();

}  // namespace alba
