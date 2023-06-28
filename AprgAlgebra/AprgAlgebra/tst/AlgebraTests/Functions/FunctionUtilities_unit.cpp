#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Functions/FunctionUtilities.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algebra {

namespace Functions {

TEST(FunctionUtilitiesTest, IsFunctionContinuousWorks) {
    Function unknownFunction("functionToTest", Term("x"), [](AlbaNumber const& number) { return number; });

    EXPECT_FALSE(isFunctionContinuous(unknownFunction));
    EXPECT_TRUE(isFunctionContinuous(abs("x")));
}

TEST(FunctionUtilitiesTest, EvaluateAndGetInputOutputPairWorks) {
    AlbaNumbers inputNumbers{-2, -1, 0, 1, 2};

    AlbaNumberPairs inputAndOutputPairs(
        evaluateAndGetInputOutputPair(inputNumbers, "x", abs(createExpressionIfPossible({"x"}))));

    ASSERT_EQ(5U, inputAndOutputPairs.size());
    EXPECT_EQ(AlbaNumber(-2), inputAndOutputPairs[0].first);
    EXPECT_EQ(AlbaNumber(2), inputAndOutputPairs[0].second);
    EXPECT_EQ(AlbaNumber(-1), inputAndOutputPairs[1].first);
    EXPECT_EQ(AlbaNumber(1), inputAndOutputPairs[1].second);
    EXPECT_EQ(AlbaNumber(0), inputAndOutputPairs[2].first);
    EXPECT_EQ(AlbaNumber(0), inputAndOutputPairs[2].second);
    EXPECT_EQ(AlbaNumber(1), inputAndOutputPairs[3].first);
    EXPECT_EQ(AlbaNumber(1), inputAndOutputPairs[3].second);
    EXPECT_EQ(AlbaNumber(2), inputAndOutputPairs[4].first);
    EXPECT_EQ(AlbaNumber(2), inputAndOutputPairs[4].second);
}

}  // namespace Functions

}  // namespace algebra

}  // namespace alba
