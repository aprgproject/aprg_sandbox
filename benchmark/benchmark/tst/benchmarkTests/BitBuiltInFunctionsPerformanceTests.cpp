/*#include <benchmark/benchmark.h>

#include <Common/Bit/Common/AlbaBitUtilitiesBuiltIn.hpp>
#include <Common/Randomizer/AlbaUniformIntegerRandomizer.hpp>

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

#define BENCHMARK_BASE_RUN(DataType) \
static void BM_BaseRun_##DataType(benchmark::State & state) \
{ \
    AlbaUniformIntegerRandomizer<DataType> randomizer(0, numeric_limits<DataType>::max()); \
    DataType count{};  \
    while(state.KeepRunning())  \
    { \
        count = randomizer.getRandomInteger(); \
        escape(&count); \
    } \
} \
BENCHMARK(BM_BaseRun_##DataType)

BENCHMARK_BASE_RUN(uint8_t);
BENCHMARK_BASE_RUN(uint16_t);
BENCHMARK_BASE_RUN(uint32_t);
BENCHMARK_BASE_RUN(uint64_t);


#define BENCHMARK_FUNCTION(DataType, function, name) \
static void BM_##name(benchmark::State & state) \
{ \
    AlbaUniformIntegerRandomizer<DataType> randomizer(0, numeric_limits<DataType>::max()); \
    unsigned int count{}; \
    while(state.KeepRunning()) \
    { \
        count = function(randomizer.getRandomInteger()); \
        escape(&count); \
    } \
} \
BENCHMARK(BM_##name)

BENCHMARK_FUNCTION(uint8_t, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::isEvenParity,
U8_WithoutBuiltin_isEvenParity); BENCHMARK_FUNCTION(uint16_t,
BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::isEvenParity, U16_WithoutBuiltin_isEvenParity);
BENCHMARK_FUNCTION(uint32_t, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::isEvenParity,
U32_WithoutBuiltin_isEvenParity); BENCHMARK_FUNCTION(uint64_t,
BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::isEvenParity, U64_WithoutBuiltin_isEvenParity);
BENCHMARK_FUNCTION(uint8_t, BitUtilitiesBuiltIn::BitUtilitiesWithBuiltIn::isEvenParity, U8_WithBuiltin_isEvenParity);
BENCHMARK_FUNCTION(uint16_t, BitUtilitiesBuiltIn::BitUtilitiesWithBuiltIn::isEvenParity, U16_WithBuiltin_isEvenParity);
BENCHMARK_FUNCTION(uint32_t, BitUtilitiesBuiltIn::BitUtilitiesWithBuiltIn::isEvenParity, U32_WithBuiltin_isEvenParity);
BENCHMARK_FUNCTION(uint64_t, BitUtilitiesBuiltIn::BitUtilitiesWithBuiltIn::isEvenParity, U64_WithBuiltin_isEvenParity);
BENCHMARK_FUNCTION(uint8_t, BitUtilitiesBuiltIn::isEvenParity, U8_Default_isEvenParity);
BENCHMARK_FUNCTION(uint16_t, BitUtilitiesBuiltIn::isEvenParity, U16_Default_isEvenParity);
BENCHMARK_FUNCTION(uint32_t, BitUtilitiesBuiltIn::isEvenParity, U32_Default_isEvenParity);
BENCHMARK_FUNCTION(uint64_t, BitUtilitiesBuiltIn::isEvenParity, U64_Default_isEvenParity);

BENCHMARK_FUNCTION(uint8_t, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfOnes,
U8_WithoutBuiltin_getNumberOfOnes); BENCHMARK_FUNCTION(uint16_t,
BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfOnes, U16_WithoutBuiltin_getNumberOfOnes);
BENCHMARK_FUNCTION(uint32_t, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfOnes,
U32_WithoutBuiltin_getNumberOfOnes); BENCHMARK_FUNCTION(uint64_t,
BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfOnes, U64_WithoutBuiltin_getNumberOfOnes);
BENCHMARK_FUNCTION(uint8_t, BitUtilitiesBuiltIn::BitUtilitiesWithBuiltIn::getNumberOfOnes,
U8_WithBuiltin_getNumberOfOnes); BENCHMARK_FUNCTION(uint16_t,
BitUtilitiesBuiltIn::BitUtilitiesWithBuiltIn::getNumberOfOnes, U16_WithBuiltin_getNumberOfOnes);
BENCHMARK_FUNCTION(uint32_t, BitUtilitiesBuiltIn::BitUtilitiesWithBuiltIn::getNumberOfOnes,
U32_WithBuiltin_getNumberOfOnes); BENCHMARK_FUNCTION(uint64_t,
BitUtilitiesBuiltIn::BitUtilitiesWithBuiltIn::getNumberOfOnes, U64_WithBuiltin_getNumberOfOnes);
BENCHMARK_FUNCTION(uint8_t, BitUtilitiesBuiltIn::getNumberOfOnes, U8_Default_getNumberOfOnes);
BENCHMARK_FUNCTION(uint16_t, BitUtilitiesBuiltIn::getNumberOfOnes, U16_Default_getNumberOfOnes);
BENCHMARK_FUNCTION(uint32_t, BitUtilitiesBuiltIn::getNumberOfOnes, U32_Default_getNumberOfOnes);
BENCHMARK_FUNCTION(uint64_t, BitUtilitiesBuiltIn::getNumberOfOnes, U64_Default_getNumberOfOnes);

BENCHMARK_FUNCTION(uint8_t, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb,
U8_WithoutBuiltin_getNumberOfConsecutiveZerosFromMsb); BENCHMARK_FUNCTION(uint16_t,
BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb,
U16_WithoutBuiltin_getNumberOfConsecutiveZerosFromMsb); BENCHMARK_FUNCTION(uint32_t,
BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb,
U32_WithoutBuiltin_getNumberOfConsecutiveZerosFromMsb); BENCHMARK_FUNCTION(uint64_t,
BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb,
U64_WithoutBuiltin_getNumberOfConsecutiveZerosFromMsb); BENCHMARK_FUNCTION(uint8_t,
BitUtilitiesBuiltIn::BitUtilitiesWithBuiltIn::getNumberOfConsecutiveZerosFromMsb,
U8_WithBuiltin_getNumberOfConsecutiveZerosFromMsb); BENCHMARK_FUNCTION(uint16_t,
BitUtilitiesBuiltIn::BitUtilitiesWithBuiltIn::getNumberOfConsecutiveZerosFromMsb,
U16_WithBuiltin_getNumberOfConsecutiveZerosFromMsb); BENCHMARK_FUNCTION(uint32_t,
BitUtilitiesBuiltIn::BitUtilitiesWithBuiltIn::getNumberOfConsecutiveZerosFromMsb,
U32_WithBuiltin_getNumberOfConsecutiveZerosFromMsb); BENCHMARK_FUNCTION(uint64_t,
BitUtilitiesBuiltIn::BitUtilitiesWithBuiltIn::getNumberOfConsecutiveZerosFromMsb,
U64_WithBuiltin_getNumberOfConsecutiveZerosFromMsb); BENCHMARK_FUNCTION(uint8_t,
BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb, U8_Default_getNumberOfConsecutiveZerosFromMsb);
BENCHMARK_FUNCTION(uint16_t, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb,
U16_Default_getNumberOfConsecutiveZerosFromMsb); BENCHMARK_FUNCTION(uint32_t,
BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb, U32_Default_getNumberOfConsecutiveZerosFromMsb);
BENCHMARK_FUNCTION(uint64_t, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb,
U64_Default_getNumberOfConsecutiveZerosFromMsb);

BENCHMARK_FUNCTION(uint8_t, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb,
U8_WithoutBuiltin_getNumberOfConsecutiveZerosFromLsb); BENCHMARK_FUNCTION(uint16_t,
BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb,
U16_WithoutBuiltin_getNumberOfConsecutiveZerosFromLsb); BENCHMARK_FUNCTION(uint32_t,
BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb,
U32_WithoutBuiltin_getNumberOfConsecutiveZerosFromLsb); BENCHMARK_FUNCTION(uint64_t,
BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb,
U64_WithoutBuiltin_getNumberOfConsecutiveZerosFromLsb); BENCHMARK_FUNCTION(uint8_t,
BitUtilitiesBuiltIn::BitUtilitiesWithBuiltIn::getNumberOfConsecutiveZerosFromLsb,
U8_WithBuiltin_getNumberOfConsecutiveZerosFromLsb); BENCHMARK_FUNCTION(uint16_t,
BitUtilitiesBuiltIn::BitUtilitiesWithBuiltIn::getNumberOfConsecutiveZerosFromLsb,
U16_WithBuiltin_getNumberOfConsecutiveZerosFromLsb); BENCHMARK_FUNCTION(uint32_t,
BitUtilitiesBuiltIn::BitUtilitiesWithBuiltIn::getNumberOfConsecutiveZerosFromLsb,
U32_WithBuiltin_getNumberOfConsecutiveZerosFromLsb); BENCHMARK_FUNCTION(uint64_t,
BitUtilitiesBuiltIn::BitUtilitiesWithBuiltIn::getNumberOfConsecutiveZerosFromLsb,
U64_WithBuiltin_getNumberOfConsecutiveZerosFromLsb); BENCHMARK_FUNCTION(uint8_t,
BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb, U8_Default_getNumberOfConsecutiveZerosFromLsb);
BENCHMARK_FUNCTION(uint16_t, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb,
U16_Default_getNumberOfConsecutiveZerosFromLsb); BENCHMARK_FUNCTION(uint32_t,
BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb, U32_Default_getNumberOfConsecutiveZerosFromLsb);
BENCHMARK_FUNCTION(uint64_t, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb,
U64_Default_getNumberOfConsecutiveZerosFromLsb);

// Register the function as a benchmark

// Run the benchmark
BENCHMARK_MAIN();

}*/
