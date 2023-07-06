#include <Algorithm/HashFunctions/PrimitiveTypes/IntegerHashFunction.hpp>

#include <gtest/gtest.h>

#include <cstdint>

using namespace std;

namespace alba {

namespace algorithm {

TEST(IntegerHashFunctionTest, GetHashWorks) {
    EXPECT_EQ(14ULL, (IntegerHashFunction<int, uint64_t, 100>::getHash(-123456789)));
}

}  // namespace algorithm

}  // namespace alba
