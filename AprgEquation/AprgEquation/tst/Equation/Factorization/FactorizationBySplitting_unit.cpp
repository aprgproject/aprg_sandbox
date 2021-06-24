#include <Equation/Factorization/FactorizationBySplitting.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

namespace equation
{

namespace Factorization
{

TEST(FactorizationBySplittingTest, FactorizeBySplittingSmallerPolynomialsWorksWhenItCannotBeFactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};
    Polynomials polynomialsToVerify(factorizeBySplittingToSmallerPolynomials(polynomialToTest));

    ASSERT_EQ(1u, polynomialsToVerify.size());    Polynomial polynomialToExpect1(polynomialToTest);
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
}

TEST(FactorizationBySplittingTest, FactorizeBySplittingSmallerPolynomialsWorksWhenItCanBeFactored)
{
    Polynomial polynomialToTest{
        Monomial(1, {{"a", 1}, {"c", 1}, {"x", 2}}),                Monomial(1, {{"a", 1}, {"d", 1}, {"x", 1}}),
                Monomial(1, {{"b", 1}, {"c", 1}, {"x", 1}}),
                Monomial(1, {{"b", 1}, {"d", 1}})};
    Polynomials polynomialsToVerify(factorizeBySplittingToSmallerPolynomials(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(1, {{"b", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"c", 1}, {"x", 1}}), Monomial(1, {{"d", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationBySplittingTest, FactorizeBySplittingSmallerPolynomialsIfPossible_IsEmptyWhenItCannotBeRefactored)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 1}}), Monomial(13, {})};
    Polynomials polynomialsToVerify(factorizeIfPossibleBySplittingByFirstVariable(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationBySplittingTest, FactorizeBySplittingSmallerPolynomialsIfPossible_IsEmptyWhenPolynomialCannotBeSplitted)
{
    Polynomial polynomialToTest{Monomial(1, {{"x", 3}}), Monomial(13, {{"x", 7}})};
    Polynomials polynomialsToVerify(factorizeIfPossibleBySplittingByFirstVariable(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationBySplittingTest, FactorizeBySplittingSmallerPolynomialsIfPossible_IsEmptyWhenNoCommonFactorsCanBeFoundAfterSplit)
{
    Polynomial polynomialToTest{Monomial(1, {{"a", 3}}), Monomial(13, {{"b", 7}})};
    Polynomials polynomialsToVerify(factorizeIfPossibleBySplittingByFirstVariable(polynomialToTest));

    EXPECT_TRUE(polynomialsToVerify.empty());
}

TEST(FactorizationBySplittingTest, FactorizeBySplittingSmallerPolynomialsIfPossible_WorksOnAXPlusBTimesCXPlusD)
{
    Polynomial polynomialToTest{
        Monomial(1, {{"a", 1}, {"c", 1}, {"x", 2}}),                Monomial(1, {{"a", 1}, {"d", 1}, {"x", 1}}),
                Monomial(1, {{"b", 1}, {"c", 1}, {"x", 1}}),
                Monomial(1, {{"b", 1}, {"d", 1}})};
    Polynomials polynomialsToVerify(factorizeIfPossibleBySplittingByFirstVariable(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(1, {{"b", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"c", 1}, {"x", 1}}), Monomial(1, {{"d", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationBySplittingTest, FactorizeBySplittingSmallerPolynomialsIfPossible_WorksOnExample1)
{
    Polynomial polynomialToTest{
        Monomial(15, {{"a", 1}, {"b", 1}}),                Monomial(-20, {{"a", 1}}),
                Monomial(-21, {{"b", 1}}),
                Monomial(28, {})};
    Polynomials polynomialsToVerify(factorizeIfPossibleBySplittingByFirstVariable(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(5, {{"a", 1}}), Monomial(-7, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"b", 1}}), Monomial(-4, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationBySplittingTest, SplitPolynomialIntoSmallerPolynomialsWorks)
{
    Polynomial polynomialToTest{
        Monomial(1, {{"a", 1}, {"x", 1}}),                Monomial(1, {{"a", 1}, {"y", 1}}),
                Monomial(1, {{"b", 1}, {"x", 1}}),
                Monomial(1, {{"b", 1}, {"y", 1}})};
    Polynomials polynomialsToVerify(splitPolynomialsByFirstVariable(polynomialToTest));

    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(1, {{"a", 1}, {"x", 1}}), Monomial(1, {{"a", 1}, {"y", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"b", 1}, {"x", 1}}), Monomial(1, {{"b", 1}, {"y", 1}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationBySplittingTest, GetCommonFactorsInThesePolynomialsWorks)
{
    Polynomial polynomial1{Monomial(12, {{"x", 3}}), Monomial(24, {{"x", 2}}), Monomial(12, {{"x", 1}})};
    Polynomial polynomial2{Monomial(6, {{"x", 4}}), Monomial(-6, {{"x", 2}})};    Polynomial polynomial3{Monomial(4, {{"x", 4}}), Monomial(4, {{"x", 3}})};
    Polynomials polynomialsToTest{polynomial1, polynomial2, polynomial3};

    Polynomials polynomialsToVerify(getCommonFactorsInThesePolynomials(polynomialsToTest));
    ASSERT_EQ(2u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(2, {{"x", 1}})};
    Polynomial polynomialToExpect2{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
}

TEST(FactorizationBySplittingTest, RemoveCommonFactorsInPolynomialsWorks)
{
    Polynomial polynomial1{Monomial(12, {{"x", 3}}), Monomial(24, {{"x", 2}}), Monomial(12, {{"x", 1}})};
    Polynomial polynomial2{Monomial(6, {{"x", 4}}), Monomial(-6, {{"x", 2}})};    Polynomial polynomial3{Monomial(4, {{"x", 4}}), Monomial(4, {{"x", 3}})};
    Polynomial polynomial4{Monomial(2, {{"x", 1}})};
    Polynomial polynomial5{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomials polynomialsWithFactors{polynomial1, polynomial2, polynomial3};    Polynomials commonFactors{polynomial4, polynomial5};

    Polynomials polynomialsToVerify(getPolynomialsWithRemovedCommonFactors(polynomialsWithFactors, commonFactors));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(6, {{"x", 1}}), Monomial(6, {})};
    Polynomial polynomialToExpect2{Monomial(3, {{"x", 2}}), Monomial(-3, {{"x", 1}})};
    Polynomial polynomialToExpect3{Monomial(2, {{"x", 2}})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationBySplittingTest, CombinePolynomialsByAdditionAndEmplaceBackWorks)
{
    Polynomial polynomial1{Monomial(1, {{"x", 1}})};
    Polynomial polynomial2{Monomial(2, {{"x", 1}}), Monomial(3, {})};    Polynomial polynomial3{Monomial(4, {})};
    Polynomials polynomials{polynomial1, polynomial2, polynomial3};

    Polynomials polynomialsToVerify;    combinePolynomialsByAdditionAndThenEmplaceBack(polynomialsToVerify, polynomials);

    ASSERT_EQ(1u, polynomialsToVerify.size());
    Polynomial polynomialToExpect{Monomial(3, {{"x", 1}}), Monomial(7, {})};
    EXPECT_EQ(polynomialToExpect, polynomialsToVerify.at(0));
}

}

}

}
