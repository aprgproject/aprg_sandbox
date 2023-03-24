#include <benchmark/benchmark.h>

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Debug/AlbaDebug.hpp>
#include <Common/Randomizer/AlbaUniformIntegerRandomizer.hpp>

using namespace std;

namespace alba
{

// Format for asm: "assembly instructions : inputs : outputs : clobbers"

static void escape(void * sinkPointer) // to avoid deleting code done by optimizers
{
    asm volatile("" : : "g"(sinkPointer) : "memory");
}

static void clobber() // to avoid deleting code done by optimizers
{
    asm volatile("" : : : "memory"); // tells compiler that memory is changed
}

static void BM_BaseRun(benchmark::State & state)
{
    // Perform setup here

    AlbaUniformIntegerRandomizer<uint64_t> randomizer(0, numeric_limits<uint64_t>::max());
    while(state.KeepRunning())
    {
        // This code gets timed

        randomizer.getRandomInteger();
        clobber();
    }
}

static void BM_ArrayBasedImplementation(benchmark::State & state)
{
    // Perform setup here

    AlbaUniformIntegerRandomizer<uint64_t> randomizer(0, numeric_limits<uint64_t>::max());
    while(state.KeepRunning())
    {
        // This code gets timed

        AlbaBitValueUtilities<uint64_t>::getNumberOfOnes(randomizer.getRandomInteger());
        clobber();
    }
}

static void BM_LoopBasedImplementation(benchmark::State & state)
{
    // Perform setup here

    AlbaUniformIntegerRandomizer<uint64_t> randomizer(0, numeric_limits<uint64_t>::max());
    while(state.KeepRunning())
    {
        // This code gets timed

        AlbaBitValueUtilities<uint64_t>::getNumberOfOnesOtherImplementation(randomizer.getRandomInteger());
        clobber();
    }
}

static void BM_BuiltinBasedImplementation(benchmark::State & state)
{
    // Perform setup here

    AlbaUniformIntegerRandomizer<uint64_t> randomizer(0, numeric_limits<uint64_t>::max());
    while(state.KeepRunning())
    {
        // This code gets timed

        __builtin_popcount(randomizer.getRandomInteger());
        clobber();
    }
}

// Register the function as a benchmark
BENCHMARK(BM_BaseRun);
BENCHMARK(BM_ArrayBasedImplementation);
BENCHMARK(BM_LoopBasedImplementation);
BENCHMARK(BM_BuiltinBasedImplementation);

// Run the benchmark
BENCHMARK_MAIN();

// 2021-10-03T01:23:55-00:00
// Running N:\Branches\APRG_GIT\aprg\benchmark\build-benchmark-Desktop_Qt_6_1_3_MinGW_64_bit-Debug\benchmark.exe
// Run on (8 X 4200 MHz CPU s)
// CPU Caches:
//   L1 Data 32 KiB (x4)
//   L1 Instruction 32 KiB (x4)
//   L2 Unified 256 KiB (x4)
//   L3 Unified 8192 KiB (x1)
// ------------------------------------------------------------------------
// Benchmark                              Time             CPU   Iterations
// ------------------------------------------------------------------------
// BM_BaseRun                          9.69 ns         9.84 ns     74666667
// BM_ArrayBasedImplementation         9.93 ns         9.77 ns     64000000
// BM_LoopBasedImplementation          30.0 ns         29.8 ns     23578947
// BM_BuiltinBasedImplementation       9.69 ns         9.63 ns     74666667

}
