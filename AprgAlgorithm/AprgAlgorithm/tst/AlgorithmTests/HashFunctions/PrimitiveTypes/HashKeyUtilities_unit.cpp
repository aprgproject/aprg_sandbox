#include <Algorithm/HashFunctions/PrimitiveTypes/HashKeyUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

TEST(HashKeyUtilitiesTest, GetHashKeyForIntegerWorks) {
    EXPECT_EQ(18446744073586094827ULL, (getHashKeyForInteger<int, uint64_t>(-123456789)));
    EXPECT_EQ(18323287284586094827ULL, (getHashKeyForInteger<int64_t, uint64_t>(-123456789123456789)));
}

TEST(HashKeyUtilitiesTest, GetHashKeyForFloatingPointTypeWorks) {
    EXPECT_EQ(3298447916ULL, (getHashKeyForFloatingPointType<float, uint32_t>(-1234.56789)));
    EXPECT_EQ(13951429491210218357ULL, (getHashKeyForFloatingPointType<double, uint64_t>(-123456789.123456789)));
}

}  // namespace algorithm

}  // namespace alba
