#include <Algorithm/HashFunctions/String/HornerHashFunctionForWholeString.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using HashValue = uint64_t;
using HashFunctionForTest = HornerHashFunctionForWholeString<HashValue>;
constexpr HashValue RADIX = 256;
constexpr HashValue A_LARGE_PRIME = 1229952067;
}  // namespace

TEST(HornerHashFunctionForWholeStringTest, Example1Works) {
    HashFunctionForTest hashFunction(RADIX, A_LARGE_PRIME);

    EXPECT_EQ(23869869ULL, hashFunction.getHashCode("ALLEY"));
}

TEST(HornerHashFunctionForWholeStringTest, Example2Works) {
    HashFunctionForTest hashFunction(RADIX, A_LARGE_PRIME);

    EXPECT_EQ(1068681688ULL, hashFunction.getHashCode("AACAA"));
}

TEST(HornerHashFunctionForWholeStringTest, Example3Works) {
    HashFunctionForTest hashFunction(RADIX, A_LARGE_PRIME);

    EXPECT_EQ(1085070900ULL, hashFunction.getHashCode("AABRAACADABRAACAADABRA"));
}

}  // namespace algorithm

}  // namespace alba
