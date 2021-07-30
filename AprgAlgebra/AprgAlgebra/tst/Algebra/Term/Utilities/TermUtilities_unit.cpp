#include <Algebra/Term/Utilities/TermUtilities.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{

TEST(TermUtilitiesTest, EvaluateAndGetInputOutputPairWorks)
{
    AlbaNumbers inputNumbers{-2,-1,0,1,2};

    AlbaNumberPairs inputAndOutputPairs(
                evaluateAndGetInputOutputPair(
                    inputNumbers,
                    "x",
                    Term(Monomial(-2, {{"x", 3}}))
                    ));

    ASSERT_EQ(5u, inputAndOutputPairs.size());
    EXPECT_EQ(AlbaNumber(-2), inputAndOutputPairs.at(0).first);
    EXPECT_EQ(AlbaNumber(16), inputAndOutputPairs.at(0).second);
    EXPECT_EQ(AlbaNumber(-1), inputAndOutputPairs.at(1).first);
    EXPECT_EQ(AlbaNumber(2), inputAndOutputPairs.at(1).second);
    EXPECT_EQ(AlbaNumber(0), inputAndOutputPairs.at(2).first);
    EXPECT_EQ(AlbaNumber(0), inputAndOutputPairs.at(2).second);
    EXPECT_EQ(AlbaNumber(1), inputAndOutputPairs.at(3).first);
    EXPECT_EQ(AlbaNumber(-2), inputAndOutputPairs.at(3).second);
    EXPECT_EQ(AlbaNumber(2), inputAndOutputPairs.at(4).first);
    EXPECT_EQ(AlbaNumber(-16), inputAndOutputPairs.at(4).second);
}

}

}
