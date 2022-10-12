#include <Algorithm/HashFunctions/ForString/HornerHashFunctionForSubstrings.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using HashValue = unsigned long long;
using HashFunctionForTest = HornerHashFunctionForSubstrings<HashValue>;
constexpr HashValue RADIX=256U;
constexpr HashValue A_LARGE_PRIME=1229952067U;
}

TEST(HornerHashFunctionForSubstringsTest, Example1Works)
{
    HashFunctionForTest hashFunction(RADIX, A_LARGE_PRIME, "ALLEY");

    EXPECT_EQ(23869869ULL, hashFunction.getHashCodeOfWholeString());

    EXPECT_EQ(65ULL, hashFunction.getHashCodeOfSubstring(0U, 0U));
    EXPECT_EQ(16716ULL, hashFunction.getHashCodeOfSubstring(0U, 1U));
    EXPECT_EQ(4279372ULL, hashFunction.getHashCodeOfSubstring(0U, 2U));
    EXPECT_EQ(1095519301ULL, hashFunction.getHashCodeOfSubstring(0U, 3U));
    EXPECT_EQ(23869869ULL, hashFunction.getHashCodeOfSubstring(0U, 4U));
    EXPECT_EQ(0ULL, hashFunction.getHashCodeOfSubstring(0U, 5U));

    EXPECT_EQ(0ULL, hashFunction.getHashCodeOfSubstring(3U, 0U));
    EXPECT_EQ(0ULL, hashFunction.getHashCodeOfSubstring(3U, 1U));
    EXPECT_EQ(0ULL, hashFunction.getHashCodeOfSubstring(3U, 2U));
    EXPECT_EQ(69ULL, hashFunction.getHashCodeOfSubstring(3U, 3U));
    EXPECT_EQ(17753ULL, hashFunction.getHashCodeOfSubstring(3U, 4U));
    EXPECT_EQ(0ULL, hashFunction.getHashCodeOfSubstring(3U, 5U));
}

TEST(HornerHashFunctionForSubstringsTest, Example2Works)
{
    HashFunctionForTest hashFunction(RADIX, A_LARGE_PRIME, "AACAA");

    EXPECT_EQ(1068681688ULL, hashFunction.getHashCodeOfWholeString());

    EXPECT_EQ(65ULL, hashFunction.getHashCodeOfSubstring(0U, 0U));
    EXPECT_EQ(16705ULL, hashFunction.getHashCodeOfSubstring(0U, 1U));
    EXPECT_EQ(4276547ULL, hashFunction.getHashCodeOfSubstring(0U, 2U));
    EXPECT_EQ(1094796097ULL, hashFunction.getHashCodeOfSubstring(0U, 3U));
    EXPECT_EQ(1068681688ULL, hashFunction.getHashCodeOfSubstring(0U, 4U));
    EXPECT_EQ(0ULL, hashFunction.getHashCodeOfSubstring(0U, 5U));
}

TEST(HornerHashFunctionForSubstringsTest, Example3Works)
{
    HashFunctionForTest hashFunction(RADIX, A_LARGE_PRIME, "AABRAACADABRAACAADABRA");

    EXPECT_EQ(1085070900ULL, hashFunction.getHashCodeOfWholeString());
    EXPECT_EQ(1085070900ULL, hashFunction.getHashCodeOfSubstring(0U, 21U));

    // The results shoulbe same with AACAA example
    EXPECT_EQ(65ULL, hashFunction.getHashCodeOfSubstring(12U, 12U));
    EXPECT_EQ(16705ULL, hashFunction.getHashCodeOfSubstring(12U, 13U));
    EXPECT_EQ(4276547ULL, hashFunction.getHashCodeOfSubstring(12U, 14U));
    EXPECT_EQ(1094796097ULL, hashFunction.getHashCodeOfSubstring(12U, 15U));
    EXPECT_EQ(1068681688ULL, hashFunction.getHashCodeOfSubstring(12U, 16U));
}

}

}
