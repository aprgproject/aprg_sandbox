#include <Algebra/Solution/SolutionUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(SolutionUtilitiesTest, GetInitialValueForNewtonMethodWorks)
{
    EXPECT_EQ(AlbaNumber(6.90775527898214), getInitialValueForNewtonMethod(Term(1000)));
    EXPECT_EQ(AlbaNumber(0), getInitialValueForNewtonMethod(Term("x")));
}


}

}
