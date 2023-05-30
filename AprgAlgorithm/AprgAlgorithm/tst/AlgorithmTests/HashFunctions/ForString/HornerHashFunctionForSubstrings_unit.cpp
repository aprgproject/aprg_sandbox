#include <Algorithm/HashFunctions/ForString/HornerHashFunctionForSubstrings.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using HashValue = uint64_t;
using HashFunctionForTest = HornerHashFunctionForSubstrings<HashValue>;
constexpr HashValue RADIX = 256;
constexpr HashValue A_LARGE_PRIME = 1229952067;
}  // namespace

TEST(HornerHashFunctionForSubstringsTest, Example1Works) {
    HashFunctionForTest hashFunction(RADIX, A_LARGE_PRIME, "ALLEY");

    EXPECT_EQ(23869869ULL, hashFunction.getHashCodeOfWholeString());

    EXPECT_EQ(65ULL, hashFunction.getHashCodeOfSubstring(0, 0));
    EXPECT_EQ(16716ULL, hashFunction.getHashCodeOfSubstring(0, 1));
    EXPECT_EQ(4279372ULL, hashFunction.getHashCodeOfSubstring(0, 2));
    EXPECT_EQ(1095519301ULL, hashFunction.getHashCodeOfSubstring(0, 3));
    EXPECT_EQ(23869869ULL, hashFunction.getHashCodeOfSubstring(0, 4));
    EXPECT_EQ(0ULL, hashFunction.getHashCodeOfSubstring(0, 5));

    EXPECT_EQ(0ULL, hashFunction.getHashCodeOfSubstring(3, 0));
    EXPECT_EQ(0ULL, hashFunction.getHashCodeOfSubstring(3, 1));
    EXPECT_EQ(0ULL, hashFunction.getHashCodeOfSubstring(3, 2));
    EXPECT_EQ(69ULL, hashFunction.getHashCodeOfSubstring(3, 3));
    EXPECT_EQ(17753ULL, hashFunction.getHashCodeOfSubstring(3, 4));
    EXPECT_EQ(0ULL, hashFunction.getHashCodeOfSubstring(3, 5));
}

TEST(HornerHashFunctionForSubstringsTest, Example2Works) {
    HashFunctionForTest hashFunction(RADIX, A_LARGE_PRIME, "AACAA");

    EXPECT_EQ(1068681688ULL, hashFunction.getHashCodeOfWholeString());

    EXPECT_EQ(65ULL, hashFunction.getHashCodeOfSubstring(0, 0));
    EXPECT_EQ(16705ULL, hashFunction.getHashCodeOfSubstring(0, 1));
    EXPECT_EQ(4276547ULL, hashFunction.getHashCodeOfSubstring(0, 2));
    EXPECT_EQ(1094796097ULL, hashFunction.getHashCodeOfSubstring(0, 3));
    EXPECT_EQ(1068681688ULL, hashFunction.getHashCodeOfSubstring(0, 4));
    EXPECT_EQ(0ULL, hashFunction.getHashCodeOfSubstring(0, 5));
}

TEST(HornerHashFunctionForSubstringsTest, Example3Works) {
    HashFunctionForTest hashFunction(RADIX, A_LARGE_PRIME, "AABRAACADABRAACAADABRA");

    EXPECT_EQ(1085070900ULL, hashFunction.getHashCodeOfWholeString());
    EXPECT_EQ(1085070900ULL, hashFunction.getHashCodeOfSubstring(0, 21));

    // The results shoulbe same with AACAA example
    EXPECT_EQ(65ULL, hashFunction.getHashCodeOfSubstring(12, 12));
    EXPECT_EQ(16705ULL, hashFunction.getHashCodeOfSubstring(12, 13));
    EXPECT_EQ(4276547ULL, hashFunction.getHashCodeOfSubstring(12, 14));
    EXPECT_EQ(1094796097ULL, hashFunction.getHashCodeOfSubstring(12, 15));
    EXPECT_EQ(1068681688ULL, hashFunction.getHashCodeOfSubstring(12, 16));
}

}  // namespace algorithm

}  // namespace alba
