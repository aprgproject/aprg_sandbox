#include <Algorithm/HashFunctions/PrimitiveTypes/HashValueUtilities.hpp>
#include <Algorithm/HashFunctions/PrimitiveTypes/OpenAddressingProbing.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

TEST(OpenAddressingProbingTest, GetHashForLinearProbingWorks) {
    constexpr uint64_t numberOfSlots = 100;
    HashingFunction<uint64_t> originalHashFunction = [numberOfSlots](uint64_t const hashKey) {
        return getHashUsingDivisionMethod<uint64_t>(hashKey, numberOfSlots);
    };
    EXPECT_EQ(89ULL, (getHashForLinearProbing<uint64_t>(123456789, numberOfSlots, originalHashFunction, 0)));
    EXPECT_EQ(90ULL, (getHashForLinearProbing<uint64_t>(123456789, numberOfSlots, originalHashFunction, 1)));
    EXPECT_EQ(91ULL, (getHashForLinearProbing<uint64_t>(123456789, numberOfSlots, originalHashFunction, 2)));
    EXPECT_EQ(92ULL, (getHashForLinearProbing<uint64_t>(123456789, numberOfSlots, originalHashFunction, 3)));
    EXPECT_EQ(93ULL, (getHashForLinearProbing<uint64_t>(123456789, numberOfSlots, originalHashFunction, 4)));
}

TEST(OpenAddressingProbingTest, GetHashForQuadraticProbingWorks) {
    constexpr uint64_t numberOfSlots = 100;
    constexpr uint64_t coefficient1 = 3;
    constexpr uint64_t coefficient2 = 5;
    HashingFunction<uint64_t> originalHashFunction = [numberOfSlots](uint64_t const hashKey) {
        return getHashUsingDivisionMethod<uint64_t>(hashKey, numberOfSlots);
    };
    EXPECT_EQ(
        89ULL, (getHashForQuadraticProbing<uint64_t>(
                   123456789, numberOfSlots, originalHashFunction, 0, coefficient1, coefficient2)));
    EXPECT_EQ(
        97ULL, (getHashForQuadraticProbing<uint64_t>(
                   123456789, numberOfSlots, originalHashFunction, 1, coefficient1, coefficient2)));
    EXPECT_EQ(
        15ULL, (getHashForQuadraticProbing<uint64_t>(
                   123456789, numberOfSlots, originalHashFunction, 2, coefficient1, coefficient2)));
    EXPECT_EQ(
        43ULL, (getHashForQuadraticProbing<uint64_t>(
                   123456789, numberOfSlots, originalHashFunction, 3, coefficient1, coefficient2)));
    EXPECT_EQ(
        81ULL, (getHashForQuadraticProbing<uint64_t>(
                   123456789, numberOfSlots, originalHashFunction, 4, coefficient1, coefficient2)));
}

}  // namespace algorithm

}  // namespace alba
