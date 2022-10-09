#include <Algorithm/HashFunctions/ForString/HornerHashFunction.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using HashValue = unsigned long long;
using HashFunctionForTest = HornerHashFunction<HashValue>;
static constexpr HashValue RADIX=256U;
static constexpr HashValue A_LARGE_PRIME=1229952067U;
}

TEST(HornerHashFunctionTest, getHashCodeWorks)
{
    HashFunctionForTest hashFunction(RADIX, A_LARGE_PRIME);

    EXPECT_EQ(23869869ULL, hashFunction.getHashCode("ALLEY"));
}

TEST(HornerHashFunctionTest, getHashCodeWorksWithIndices)
{
    HashFunctionForTest hashFunction(RADIX, A_LARGE_PRIME);

    EXPECT_EQ(0ULL, hashFunction.getHashCode("ALLEY", 0U, 0U));
    EXPECT_EQ(65ULL, hashFunction.getHashCode("ALLEY", 0U, 1U));
    EXPECT_EQ(16716ULL, hashFunction.getHashCode("ALLEY", 0U, 2U));
    EXPECT_EQ(4279372ULL, hashFunction.getHashCode("ALLEY", 0U, 3U));
    EXPECT_EQ(1095519301ULL, hashFunction.getHashCode("ALLEY", 0U, 4U));
    EXPECT_EQ(23869869ULL, hashFunction.getHashCode("ALLEY", 0U, 5U));
    EXPECT_EQ(0ULL, hashFunction.getHashCode("ALLEY", 0U, 6U));

    EXPECT_EQ(0ULL, hashFunction.getHashCode("ALLEY", 3U, 0U));
    EXPECT_EQ(0ULL, hashFunction.getHashCode("ALLEY", 3U, 1U));
    EXPECT_EQ(0ULL, hashFunction.getHashCode("ALLEY", 3U, 2U));
    EXPECT_EQ(1173108616ULL, hashFunction.getHashCode("ALLEY", 3U, 3U));
    EXPECT_EQ(794814664ULL, hashFunction.getHashCode("ALLEY", 3U, 4U));
    EXPECT_EQ(953383207ULL, hashFunction.getHashCode("ALLEY", 3U, 5U));
    EXPECT_EQ(0ULL, hashFunction.getHashCode("ALLEY", 3U, 6U));
}

}

}
