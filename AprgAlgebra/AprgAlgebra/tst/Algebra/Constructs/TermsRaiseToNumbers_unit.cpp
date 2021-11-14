#include <Algebra/Constructs/TermsRaiseToNumbers.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(TermsRaiseToNumbersTest, ConstructionWorks)
{
    TermsRaiseToNumbers termsRaiseToNumbers1;
    TermsRaiseToNumbers termsRaiseToNumbers2({{Term("x"), 1}, {Term("y"), -2}, {Term("z"), 3}});

    EXPECT_TRUE(termsRaiseToNumbers1.getBaseToExponentMap().empty());
    TermsRaiseToNumbers::BaseToExponentMap const& mapToVerify(termsRaiseToNumbers2.getBaseToExponentMap());
    ASSERT_EQ(3U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term("x"), itToVerify->first);    EXPECT_EQ(AlbaNumber(1), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("y"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(-2), itToVerify->second);    itToVerify++;
    EXPECT_EQ(Term("z"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(3), itToVerify->second);
}

TEST(TermsRaiseToNumbersTest, GetBaseToExponentMapWorks)
{
    TermsRaiseToNumbers termsRaiseToNumbers({{Term("x"), 1}, {Term("y"), -2}, {Term("z"), 3}});

    TermsRaiseToNumbers::BaseToExponentMap const& mapToVerify(termsRaiseToNumbers.getBaseToExponentMap());

    ASSERT_EQ(3U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();    EXPECT_EQ(Term("x"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(1), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("y"), itToVerify->first);    EXPECT_EQ(AlbaNumber(-2), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("z"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(3), itToVerify->second);
}

TEST(TermsRaiseToNumbersTest, GetExponentOfBaseWorks)
{
    TermsRaiseToNumbers termsRaiseToNumbers({{Term("x"), 1}, {Term("y"), -2}, {Term("z"), 3}});

    EXPECT_EQ(AlbaNumber(1), termsRaiseToNumbers.getExponentOfBase(Term("x")));
    EXPECT_EQ(AlbaNumber(-2), termsRaiseToNumbers.getExponentOfBase(Term("y")));
    EXPECT_EQ(AlbaNumber(3), termsRaiseToNumbers.getExponentOfBase(Term("z")));
    EXPECT_EQ(AlbaNumber(0), termsRaiseToNumbers.getExponentOfBase(Term("NotFound")));
}

TEST(TermsRaiseToNumbersTest, GetTermsInMultiplicationOperationWorks)
{
    TermsRaiseToNumbers termsRaiseToNumbers({{Term("x"), 1}, {Term("y"), -2}, {Term("z"), 3}});

    Terms const termsToVerify(termsRaiseToNumbers.getTermsInMultiplicationOperation());

    Term expectedTerm1("x");
    Term expectedTerm2(Monomial(1, {{"y", -2}}));
    Term expectedTerm3(Monomial(1, {{"z", 3}}));
    ASSERT_EQ(3U, termsToVerify.size());
    EXPECT_EQ(expectedTerm1, termsToVerify.at(0));
    EXPECT_EQ(expectedTerm2, termsToVerify.at(1));
    EXPECT_EQ(expectedTerm3, termsToVerify.at(2));
}

TEST(TermsRaiseToNumbersTest, GetTermWithDetailsInMultiplicationAndDivisionOperationWorks)
{
    TermsRaiseToNumbers termsRaiseToNumbers({{Term("x"), 1}, {Term("y"), -2}, {Term("z"), 3}});

    TermsWithDetails const termsToVerify(termsRaiseToNumbers.getTermWithDetailsInMultiplicationAndDivisionOperation());

    Term expectedTerm1("x");
    TermWithDetails expectedTermWithDetails1({expectedTerm1, TermAssociationType::Positive});
    Term expectedTerm2(Monomial(1, {{"y", 2}}));
    TermWithDetails expectedTermWithDetails2({expectedTerm2, TermAssociationType::Negative});
    Term expectedTerm3(Monomial(1, {{"z", 3}}));
    TermWithDetails expectedTermWithDetails3({expectedTerm3, TermAssociationType::Positive});
    ASSERT_EQ(3U, termsToVerify.size());
    EXPECT_EQ(expectedTermWithDetails1, termsToVerify.at(0));
    EXPECT_EQ(expectedTermWithDetails2, termsToVerify.at(1));
    EXPECT_EQ(expectedTermWithDetails3, termsToVerify.at(2));
}

TEST(TermsRaiseToNumbersTest, AddExponentsWorks)
{
    TermsRaiseToNumbers termsRaiseToNumbersToAdd({{Term("x"), 1}, {Term("y"), -2}, {Term("z"), 3}});
    TermsRaiseToNumbers termsRaiseToNumbers({{Term("x"), 4}, {Term("y"), -5}, {Term("z"), 6}});

    termsRaiseToNumbers.addExponents(termsRaiseToNumbersToAdd);

    TermsRaiseToNumbers::BaseToExponentMap const mapToVerify(termsRaiseToNumbers.getBaseToExponentMap());
    ASSERT_EQ(3U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term("x"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(5), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("y"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(-7), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("z"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(9), itToVerify->second);
}

TEST(TermsRaiseToNumbersTest, SubtractExponentsWorks)
{
    TermsRaiseToNumbers termsRaiseToNumbers({{Term("x"), 4}, {Term("y"), -5}, {Term("z"), 6}});
    TermsRaiseToNumbers termsRaiseToNumbersToSubtract({{Term("x"), 1}, {Term("y"), -2}, {Term("z"), 3}});

    termsRaiseToNumbers.subtractExponents(termsRaiseToNumbersToSubtract);

    TermsRaiseToNumbers::BaseToExponentMap const mapToVerify(termsRaiseToNumbers.getBaseToExponentMap());
    ASSERT_EQ(3U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term("x"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(3), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("y"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(-3), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("z"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(3), itToVerify->second);
}

TEST(TermsRaiseToNumbersTest, MultiplyNumberToExponentsWorks)
{
    TermsRaiseToNumbers termsRaiseToNumbers({{Term("x"), 4}, {Term("y"), -5}, {Term("z"), 6}});

    termsRaiseToNumbers.multiplyToExponents(5);

    TermsRaiseToNumbers::BaseToExponentMap const mapToVerify(termsRaiseToNumbers.getBaseToExponentMap());
    ASSERT_EQ(3U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term("x"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(20), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("y"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(-25), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("z"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(30), itToVerify->second);
}

TEST(TermsRaiseToNumbersTest, PutTermWorksOnMonomial)
{
    TermsRaiseToNumbers termsRaiseToNumbers({{Term("x"), 1}, {Term("y"), -2}, {Term("z"), 3}});
    Term termWithPositive(Monomial(5, {{"x", 6}}));
    Term termWithNegative(Monomial(7, {{"y", 8}}));
    Term termWithHaveNoEffect(Monomial(1, {{"z", 0}}));

    termsRaiseToNumbers.putTerm(termWithPositive, TermAssociationType::Positive);
    termsRaiseToNumbers.putTerm(termWithNegative, TermAssociationType::Negative);
    termsRaiseToNumbers.putTerm(termWithHaveNoEffect, TermAssociationType::Positive);

    TermsRaiseToNumbers::BaseToExponentMap const mapToVerify(termsRaiseToNumbers.getBaseToExponentMap());
    ASSERT_EQ(5U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term(5), itToVerify->first);
    EXPECT_EQ(AlbaNumber(1), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term(7), itToVerify->first);
    EXPECT_EQ(AlbaNumber(-1), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("x"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(7), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("y"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(-10), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("z"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(3), itToVerify->second);
}

TEST(TermsRaiseToNumbersTest, PutTermWorksOnOtherTermTypes)
{
    Term x("x");
    TermsRaiseToNumbers termsRaiseToNumbers({{Term(cos(x)), 1}, {Term(sin(x)), -2}, {Term(tan(x)), 3}});
    Term termWithPositive(createExpressionIfPossible({Term(cos(x)), Term("^"), Term(6)}));
    Term termWithNegative(createExpressionIfPossible({Term(sin(x)), Term("^"), Term(8)}));

    termsRaiseToNumbers.putTerm(termWithPositive, TermAssociationType::Positive);
    termsRaiseToNumbers.putTerm(termWithNegative, TermAssociationType::Negative);

    TermsRaiseToNumbers::BaseToExponentMap const mapToVerify(termsRaiseToNumbers.getBaseToExponentMap());
    ASSERT_EQ(3U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term(cos(x)), itToVerify->first);
    EXPECT_EQ(AlbaNumber(7), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term(sin(x)), itToVerify->first);
    EXPECT_EQ(AlbaNumber(-10), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term(tan(x)), itToVerify->first);
    EXPECT_EQ(AlbaNumber(3), itToVerify->second);
}

TEST(TermsRaiseToNumbersTest, PutTermsWorks)
{
    TermsRaiseToNumbers termsRaiseToNumbers({{Term("x"), 1}, {Term("y"), -2}, {Term("z"), 3}});

    termsRaiseToNumbers.putTerms(
    {Term(Monomial(1, {{"x", 5}})), Term(Monomial(1, {{"y", 6}})), Term(Monomial(1, {{"z", 7}}))}, TermAssociationType::Positive);

    TermsRaiseToNumbers::BaseToExponentMap const mapToVerify(termsRaiseToNumbers.getBaseToExponentMap());
    ASSERT_EQ(3U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term("x"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(6), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("y"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(4), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("z"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(10), itToVerify->second);
}

TEST(TermsRaiseToNumbersTest, SetBaseAndExponentWorks)
{
    TermsRaiseToNumbers termsRaiseToNumbers;

    termsRaiseToNumbers.setBaseAndExponent(Term("x"), 9);

    TermsRaiseToNumbers::BaseToExponentMap const mapToVerify(termsRaiseToNumbers.getBaseToExponentMap());
    ASSERT_EQ(1U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term("x"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(9), itToVerify->second);
}

TEST(TermsRaiseToNumbersTest, RemoveItemWithBaseWorks)
{
    TermsRaiseToNumbers termsRaiseToNumbers({{Term("x"), 1}, {Term("y"), -2}, {Term("z"), 3}});

    termsRaiseToNumbers.removeItemWithBase(Term("x"));

    TermsRaiseToNumbers::BaseToExponentMap const mapToVerify(termsRaiseToNumbers.getBaseToExponentMap());
    ASSERT_EQ(2U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term("y"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(-2), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("z"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(3), itToVerify->second);
}

TEST(TermsRaiseToNumbersTest, SimplifyWorks)
{
    TermsRaiseToNumbers termsRaiseToNumbers({{Term("x"), 1}, {Term("y"), 0}, {Term("z"), 0}});

    termsRaiseToNumbers.simplify();

    TermsRaiseToNumbers::BaseToExponentMap const mapToVerify(termsRaiseToNumbers.getBaseToExponentMap());
    ASSERT_EQ(1U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term("x"), itToVerify->first);
    EXPECT_EQ(AlbaNumber(1), itToVerify->second);
}

}

}
