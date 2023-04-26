/*#include <benchmark/benchmark.h>

#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>

using namespace std;
namespace alba
{
// Format for asm: "assembly instructions : inputs : outputs : clobbers"

static void escape(void * sinkPointer) // to avoid optimizers deleting code
{
    asm volatile("" : : "g"(sinkPointer) : "memory");
}

static void clobber() // to avoid optimizers deleting code
{
    asm volatile("" : : : "memory"); // tells compiler that memory is changed
}

unsigned int arrayBasedImplementationForOneByte(uint8_t const value)
{
    constexpr std::array<uint8_t, 256> savedValues
    {0U, 1U, 1U, 2U, 1U, 2U, 2U, 3U, 1U, 2U, 2U, 3U, 2U, 3U, 3U, 4U, 1U, 2U, 2U, 3U, 2U, 3U, 3U, 4U, 2U, 3U, 3U, 4U, 3U,
4U, 4U, 5U, 1U, 2U, 2U, 3U, 2U, 3U, 3U, 4U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 3U, 4U, 4U,
5U, 4U, 5U, 5U, 6U, 1U, 2U, 2U, 3U, 2U, 3U, 3U, 4U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 3U,
4U, 4U, 5U, 4U, 5U, 5U, 6U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 3U, 4U, 4U, 5U, 4U, 5U, 5U,
6U, 4U, 5U, 5U, 6U, 5U, 6U, 6U, 7U, 1U, 2U, 2U, 3U, 2U, 3U, 3U, 4U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 2U, 3U, 3U, 4U, 3U,
4U, 4U, 5U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 3U, 4U, 4U,
5U, 4U, 5U, 5U, 6U, 4U, 5U, 5U, 6U, 5U, 6U, 6U, 7U, 2U, 3U, 3U, 4U, 3U, 4U, 4U, 5U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 3U,
4U, 4U, 5U, 4U, 5U, 5U, 6U, 4U, 5U, 5U, 6U, 5U, 6U, 6U, 7U, 3U, 4U, 4U, 5U, 4U, 5U, 5U, 6U, 4U, 5U, 5U, 6U, 5U, 6U, 6U,
7U, 4U, 5U, 5U, 6U, 5U, 6U, 6U, 7U, 5U, 6U, 6U, 7U, 6U, 7U, 7U, 8U}; return savedValues.at(value);
}

unsigned int arrayBasedImplementation(uint64_t const value)
{
    return arrayBasedImplementationForOneByte(static_cast<uint8_t>(value))
            + arrayBasedImplementationForOneByte(static_cast<uint8_t>(value >> 8))
            + arrayBasedImplementationForOneByte(static_cast<uint8_t>(value >> 16))
            + arrayBasedImplementationForOneByte(static_cast<uint8_t>(value >> 24))
            + arrayBasedImplementationForOneByte(static_cast<uint8_t>(value >> 32))
            + arrayBasedImplementationForOneByte(static_cast<uint8_t>(value >> 40))
            + arrayBasedImplementationForOneByte(static_cast<uint8_t>(value >> 48))
            + arrayBasedImplementationForOneByte(static_cast<uint8_t>(value >> 56));
}

unsigned int loopBasedImplementation(uint64_t const input)
{
    // Perform setup here

    unsigned int result(0);
    for(uint64_t value=input; value>0; value>>=1)
    {
        if((value&1) == 1)
        {
            ++result;
        }
    }
    return result;
}

static void BM_BaseRun(benchmark::State & state)
{
    // Perform setup here

    AlbaUniformNonDeterministicRandomizer<unsigned int> randomizer(0, numeric_limits<unsigned int>::max());
    unsigned int count{};
    while(state.KeepRunning())
    {
        // This code gets timed

        count = randomizer.getRandomValue();
        escape(&count);
    }
}
static void BM_ArrayBasedImplementation(benchmark::State & state)
{
    // Perform setup here

    AlbaUniformNonDeterministicRandomizer<uint64_t> randomizer(0, numeric_limits<uint64_t>::max());
    unsigned int count{};
    while(state.KeepRunning())
    {
        // This code gets timed

        count = arrayBasedImplementation(randomizer.getRandomValue());
        escape(&count);
    }
}
static void BM_LoopBasedImplementation(benchmark::State & state)
{
    // Perform setup here

    AlbaUniformNonDeterministicRandomizer<uint64_t> randomizer(0, numeric_limits<uint64_t>::max());
    unsigned int count{};
    while(state.KeepRunning())
    {
        // This code gets timed

        count = loopBasedImplementation(randomizer.getRandomValue());
        escape(&count);
    }
}
static void BM_BuiltinBasedImplementation(benchmark::State & state)
{
    // Perform setup here

    AlbaUniformNonDeterministicRandomizer<uint64_t> randomizer(0, numeric_limits<uint64_t>::max());
    unsigned int count{};
    while(state.KeepRunning())
    {
        // This code gets timed

        count = __builtin_popcount(randomizer.getRandomValue());
        escape(&count);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_BaseRun);
BENCHMARK(BM_ArrayBasedImplementation);BENCHMARK(BM_LoopBasedImplementation);
BENCHMARK(BM_BuiltinBasedImplementation);

// Run the benchmark
BENCHMARK_MAIN();

}*/
