#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Functions/FunctionUtilities.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Functions
{

TEST(FunctionUtilitiesTest, EvaluateAndGetInputOutputPairWorks)
{
    AlbaNumbers inputNumbers{-2,-1,0,1,2};

    AlbaNumberPairs inputAndOutputPairs(
                evaluateAndGetInputOutputPair(
                    inputNumbers,
                    "x",
                    Functions::abs(createExpressionIfPossible({Term("x")}))));

    ASSERT_EQ(5u, inputAndOutputPairs.size());
    EXPECT_EQ(AlbaNumber(-2), inputAndOutputPairs.at(0).first);
    EXPECT_EQ(AlbaNumber(2), inputAndOutputPairs.at(0).second);
    EXPECT_EQ(AlbaNumber(-1), inputAndOutputPairs.at(1).first);
    EXPECT_EQ(AlbaNumber(1), inputAndOutputPairs.at(1).second);
    EXPECT_EQ(AlbaNumber(0), inputAndOutputPairs.at(2).first);
    EXPECT_EQ(AlbaNumber(0), inputAndOutputPairs.at(2).second);
    EXPECT_EQ(AlbaNumber(1), inputAndOutputPairs.at(3).first);
    EXPECT_EQ(AlbaNumber(1), inputAndOutputPairs.at(3).second);
    EXPECT_EQ(AlbaNumber(2), inputAndOutputPairs.at(4).first);
    EXPECT_EQ(AlbaNumber(2), inputAndOutputPairs.at(4).second);
}

}

}

}
