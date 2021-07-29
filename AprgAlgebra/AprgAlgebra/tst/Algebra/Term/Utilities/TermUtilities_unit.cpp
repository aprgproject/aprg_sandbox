#include <Algebra/Term/Utilities/TermUtilities.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{

TEST(TermUtilitiesTest, GetRootsWorksAndRootsIsEmptyWhenConstantIsGiven)
{
    AlbaNumbers roots(getRoots(Polynomial{Monomial(-16, {})}));

    EXPECT_TRUE(roots.empty());
}

TEST(TermUtilitiesTest, GetRootsWorksAndRootsIsEmptyWhenMultipleVariablesAreGiven)
{
    AlbaNumbers roots(getRoots(Polynomial{Monomial(1, {{"x", 4}}), Monomial(1, {{"y", 3}}), Monomial(-16, {})}));

    EXPECT_TRUE(roots.empty());
}

TEST(TermUtilitiesTest, GetRootsWorksAndFactorizesAPolynomial)
{
    AlbaNumbers roots(getRoots(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-16, {})}));

    ASSERT_EQ(2u, roots.size());
    EXPECT_EQ(AlbaNumber(-4), roots.at(0));
    EXPECT_EQ(AlbaNumber(4), roots.at(1));
}

TEST(TermUtilitiesTest, GetRootsWorksAndRootIsZeroWhenExponentIsPositive)
{
    AlbaNumbers roots(getRoots(Polynomial{Monomial(1, {{"x", AlbaNumber(4)/3}})}));

    ASSERT_EQ(1u, roots.size());
    EXPECT_EQ(AlbaNumber(0), roots.at(0));
}

TEST(TermUtilitiesTest, GetRootsWorksAndZeroIsNotIncludedWhenExponentIsNegative)
{
    AlbaNumbers roots(getRoots(Polynomial{Monomial(1, {{"x", AlbaNumber(-4)/3}})}));

    EXPECT_TRUE(roots.empty());
}

TEST(TermUtilitiesTest, GetRootsWorksAndWhenPolynomialIsNotSorted)
{
    AlbaNumbers roots(getRoots(Polynomial{Monomial(-16, {}), Monomial(1, {{"x", 1}})}));

    ASSERT_EQ(1u, roots.size());
    EXPECT_EQ(AlbaNumber(16), roots.at(0));
}

TEST(TermUtilitiesTest, GetRootsWorksAndRootIsCorrectlyCalculatedWhenExponentIsNotAnInteger)
{
    AlbaNumbers roots(getRoots(Polynomial{Monomial(1, {{"x", AlbaNumber(4)/3}}), Monomial(-16, {})}));

    ASSERT_EQ(1u, roots.size());
    EXPECT_EQ(AlbaNumber(8), roots.at(0));
}

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
