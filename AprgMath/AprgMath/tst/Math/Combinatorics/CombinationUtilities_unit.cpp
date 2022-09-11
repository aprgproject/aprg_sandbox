#include <Math/Combinatorics/CombinationUtilities.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba
{

namespace math
{

TEST(OtherUtilitiesTest, IsNumberOfCombinationsEqualToItsCounterpartWorks)
{
    EXPECT_FALSE(isNumberOfCombinationsEqualToItsCounterpart(2U, 4U)); // Wrong input so its false, it should be n>k
    EXPECT_TRUE(isNumberOfCombinationsEqualToItsCounterpart(4U, 2U));
    EXPECT_TRUE(isNumberOfCombinationsEqualToItsCounterpart(10U, 5U));
}
TEST(OtherUtilitiesTest, IsTheSumOfAllNumberOfCombinationsEqualTo2ToTheNWorks)
{
    EXPECT_TRUE(isTheSumOfAllNumberOfCombinationsEqualTo2ToTheN(4U));
    EXPECT_TRUE(isTheSumOfAllNumberOfCombinationsEqualTo2ToTheN(10U));
}

}

}
