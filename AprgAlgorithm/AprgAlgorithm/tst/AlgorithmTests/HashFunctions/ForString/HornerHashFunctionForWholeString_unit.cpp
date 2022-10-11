#include <Algorithm/HashFunctions/ForString/HornerHashFunctionForWholeString.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using HashValue = unsigned long long;
using HashFunctionForTest = HornerHashFunctionForWholeString<HashValue>;
constexpr HashValue RADIX=256U;
constexpr HashValue A_LARGE_PRIME=1229952067U;
}

TEST(HornerHashFunctionForWholeStringTest, Example1Works){
    HashFunctionForTest hashFunction(RADIX, A_LARGE_PRIME);

    EXPECT_EQ(23869869ULL, hashFunction.getHashCode("ALLEY"));
}

TEST(HornerHashFunctionForWholeStringTest, Example2Works)
{
    HashFunctionForTest hashFunction(RADIX, A_LARGE_PRIME);

    EXPECT_EQ(1068681688ULL, hashFunction.getHashCode("AACAA"));
}

TEST(HornerHashFunctionForWholeStringTest, Example3Works)
{
    HashFunctionForTest hashFunction(RADIX, A_LARGE_PRIME);

    EXPECT_EQ(1085070900ULL, hashFunction.getHashCode("AABRAACADABRAACAADABRA"));
}

}

}
