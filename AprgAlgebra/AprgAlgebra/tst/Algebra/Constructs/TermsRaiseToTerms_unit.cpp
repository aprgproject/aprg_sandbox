#include <Algebra/Constructs/TermsRaiseToTerms.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(TermsRaiseToTermsTest, ConstructionWorks)
{
    TermsRaiseToTerms termsRaiseToTerms1;
    TermsRaiseToTerms termsRaiseToTerms2({{Term("x"), Term(1)}, {Term("y"), Term(-2)}, {Term("z"), Term(3)}});

    EXPECT_TRUE(termsRaiseToTerms1.getBaseToExponentMap().empty());
    TermsRaiseToTerms::BaseToExponentMap const& mapToVerify(termsRaiseToTerms2.getBaseToExponentMap());
    ASSERT_EQ(3U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term("x"), itToVerify->first);    EXPECT_EQ(Term(1), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("y"), itToVerify->first);
    EXPECT_EQ(Term(-2), itToVerify->second);    itToVerify++;
    EXPECT_EQ(Term("z"), itToVerify->first);
    EXPECT_EQ(Term(3), itToVerify->second);
}

TEST(TermsRaiseToTermsTest, GetBaseToExponentMapWorks)
{
    TermsRaiseToTerms termsRaiseToTerms({{Term("x"), Term(1)}, {Term("y"), Term(-2)}, {Term("z"), Term(3)}});

    TermsRaiseToTerms::BaseToExponentMap const& mapToVerify(termsRaiseToTerms.getBaseToExponentMap());

    ASSERT_EQ(3U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();    EXPECT_EQ(Term("x"), itToVerify->first);
    EXPECT_EQ(Term(1), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("y"), itToVerify->first);    EXPECT_EQ(Term(-2), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("z"), itToVerify->first);
    EXPECT_EQ(Term(3), itToVerify->second);
}

TEST(TermsRaiseToTermsTest, GetExponentOfBaseWorks)
{
    TermsRaiseToTerms termsRaiseToTerms({{Term("x"), Term(1)}, {Term("y"), Term(-2)}, {Term("z"), Term(3)}});

    EXPECT_EQ(Term(1), termsRaiseToTerms.getExponentOfBase(Term("x")));
    EXPECT_EQ(Term(-2), termsRaiseToTerms.getExponentOfBase(Term("y")));
    EXPECT_EQ(Term(3), termsRaiseToTerms.getExponentOfBase(Term("z")));
    EXPECT_EQ(Term(), termsRaiseToTerms.getExponentOfBase(Term("NotFound")));
}

TEST(TermsRaiseToTermsTest, GetTermsInMultiplicationOperationWorks)
{
    TermsRaiseToTerms termsRaiseToTerms({{Term("x"), Term(1)}, {Term("y"), Term(-2)}, {Term("z"), Term(3)}});

    Terms const termsToVerify(termsRaiseToTerms.getTermsInMultiplicationOperation());

    Term expectedTerm1("x");
    Term expectedTerm2(Monomial(1, {{"y", -2}}));
    Term expectedTerm3(Monomial(1, {{"z", 3}}));
    ASSERT_EQ(3U, termsToVerify.size());
    EXPECT_EQ(expectedTerm1, termsToVerify.at(0));
    EXPECT_EQ(expectedTerm2, termsToVerify.at(1));
    EXPECT_EQ(expectedTerm3, termsToVerify.at(2));
}

TEST(TermsRaiseToTermsTest, GetTermWithDetailsInMultiplicationAndDivisionOperationWorks)
{
    TermsRaiseToTerms termsRaiseToTerms({{Term("x"), Term(1)}, {Term("y"), Term(-2)}, {Term("z"), Term(3)}});

    TermsWithDetails const termsToVerify(termsRaiseToTerms.getTermWithDetailsInMultiplicationAndDivisionOperation());

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

TEST(TermsRaiseToTermsTest, AddExponentsWorks)
{
    TermsRaiseToTerms termsRaiseToTermsToAdd({{Term("x"), Term(1)}, {Term("y"), Term(-2)}, {Term("z"), Term(3)}});
    TermsRaiseToTerms termsRaiseToTerms({{Term("x"), Term(4)}, {Term("y"), Term(-5)}, {Term("z"), Term(6)}});

    termsRaiseToTerms.addExponents(termsRaiseToTermsToAdd);

    TermsRaiseToTerms::BaseToExponentMap const mapToVerify(termsRaiseToTerms.getBaseToExponentMap());
    ASSERT_EQ(3U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term("x"), itToVerify->first);
    EXPECT_EQ(Term(5), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("y"), itToVerify->first);
    EXPECT_EQ(Term(-7), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("z"), itToVerify->first);
    EXPECT_EQ(Term(9), itToVerify->second);
}

TEST(TermsRaiseToTermsTest, SubtractExponentsWorks)
{
    TermsRaiseToTerms termsRaiseToTerms({{Term("x"), Term(4)}, {Term("y"), Term(-5)}, {Term("z"), Term(6)}});
    TermsRaiseToTerms termsRaiseToTermsToSubtract({{Term("x"), Term(1)}, {Term("y"), Term(-2)}, {Term("z"), Term(3)}});

    termsRaiseToTerms.subtractExponents(termsRaiseToTermsToSubtract);

    TermsRaiseToTerms::BaseToExponentMap const mapToVerify(termsRaiseToTerms.getBaseToExponentMap());
    ASSERT_EQ(3U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term("x"), itToVerify->first);
    EXPECT_EQ(Term(3), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("y"), itToVerify->first);
    EXPECT_EQ(Term(-3), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("z"), itToVerify->first);
    EXPECT_EQ(Term(3), itToVerify->second);
}

TEST(TermsRaiseToTermsTest, MultiplyNumberToExponentsWorks)
{
    TermsRaiseToTerms termsRaiseToTerms({{Term("x"), Term(4)}, {Term("y"), Term(-5)}, {Term("z"), Term(6)}});

    termsRaiseToTerms.multiplyToExponents(Term(5));

    TermsRaiseToTerms::BaseToExponentMap const mapToVerify(termsRaiseToTerms.getBaseToExponentMap());
    ASSERT_EQ(3U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term("x"), itToVerify->first);
    EXPECT_EQ(Term(20), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("y"), itToVerify->first);
    EXPECT_EQ(Term(-25), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("z"), itToVerify->first);
    EXPECT_EQ(Term(30), itToVerify->second);
}

TEST(TermsRaiseToTermsTest, PutTermWorksOnMonomial)
{
    TermsRaiseToTerms termsRaiseToTerms({{Term("x"), Term(1)}, {Term("y"), Term(-2)}, {Term("z"), Term(3)}});
    Term termWithPositive(Monomial(5, {{"x", 6}}));
    Term termWithNegative(Monomial(7, {{"y", 8}}));
    Term termWithHaveNoEffect(Monomial(1, {{"z", 0}}));

    termsRaiseToTerms.putTerm(termWithPositive, TermAssociationType::Positive);
    termsRaiseToTerms.putTerm(termWithNegative, TermAssociationType::Negative);
    termsRaiseToTerms.putTerm(termWithHaveNoEffect, TermAssociationType::Positive);

    TermsRaiseToTerms::BaseToExponentMap const mapToVerify(termsRaiseToTerms.getBaseToExponentMap());
    ASSERT_EQ(5U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term(5), itToVerify->first);
    EXPECT_EQ(Term(1), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term(7), itToVerify->first);
    EXPECT_EQ(Term(-1), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("x"), itToVerify->first);
    EXPECT_EQ(Term(7), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("y"), itToVerify->first);
    EXPECT_EQ(Term(-10), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("z"), itToVerify->first);
    EXPECT_EQ(Term(3), itToVerify->second);
}

TEST(TermsRaiseToTermsTest, PutTermWorksOnOtherTermTypes)
{
    Term x("x");
    TermsRaiseToTerms termsRaiseToTerms({{Term(cos(x)), Term(1)}, {Term(sin(x)), Term(-2)}, {Term(tan(x)), Term(3)}});
    Term termWithPositive(createExpressionIfPossible({Term(cos(x)), Term("^"), Term(6)}));
    Term termWithNegative(createExpressionIfPossible({Term(sin(x)), Term("^"), Term(8)}));

    termsRaiseToTerms.putTerm(termWithPositive, TermAssociationType::Positive);
    termsRaiseToTerms.putTerm(termWithNegative, TermAssociationType::Negative);

    TermsRaiseToTerms::BaseToExponentMap const mapToVerify(termsRaiseToTerms.getBaseToExponentMap());
    ASSERT_EQ(3U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term(cos(x)), itToVerify->first);
    EXPECT_EQ(Term(7), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term(sin(x)), itToVerify->first);
    EXPECT_EQ(Term(-10), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term(tan(x)), itToVerify->first);
    EXPECT_EQ(Term(3), itToVerify->second);
}

TEST(TermsRaiseToTermsTest, PutTermsWorks)
{
    TermsRaiseToTerms termsRaiseToTerms({{Term("x"), Term(1)}, {Term("y"), Term(-2)}, {Term("z"), Term(3)}});

    termsRaiseToTerms.putTerms(
    {Term(Monomial(1, {{"x", 5}})), Term(Monomial(1, {{"y", 6}})), Term(Monomial(1, {{"z", 7}}))}, TermAssociationType::Positive);

    TermsRaiseToTerms::BaseToExponentMap const mapToVerify(termsRaiseToTerms.getBaseToExponentMap());
    ASSERT_EQ(3U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term("x"), itToVerify->first);
    EXPECT_EQ(Term(6), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("y"), itToVerify->first);
    EXPECT_EQ(Term(4), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("z"), itToVerify->first);
    EXPECT_EQ(Term(10), itToVerify->second);
}

TEST(TermsRaiseToTermsTest, SetBaseAndExponentWorks)
{
    TermsRaiseToTerms termsRaiseToTerms;

    termsRaiseToTerms.setBaseAndExponent(Term("x"), Term(9));

    TermsRaiseToTerms::BaseToExponentMap const mapToVerify(termsRaiseToTerms.getBaseToExponentMap());
    ASSERT_EQ(1U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term("x"), itToVerify->first);
    EXPECT_EQ(Term(9), itToVerify->second);
}

TEST(TermsRaiseToTermsTest, RemoveItemWithBaseWorks)
{
    TermsRaiseToTerms termsRaiseToTerms({{Term("x"), Term(1)}, {Term("y"), Term(-2)}, {Term("z"), Term(3)}});

    termsRaiseToTerms.removeItemWithBase(Term("x"));

    TermsRaiseToTerms::BaseToExponentMap const mapToVerify(termsRaiseToTerms.getBaseToExponentMap());
    ASSERT_EQ(2U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term("y"), itToVerify->first);
    EXPECT_EQ(Term(-2), itToVerify->second);
    itToVerify++;
    EXPECT_EQ(Term("z"), itToVerify->first);
    EXPECT_EQ(Term(3), itToVerify->second);
}

TEST(TermsRaiseToTermsTest, SimplifyWorks)
{
    TermsRaiseToTerms termsRaiseToTerms({{Term("x"), Term(1)}, {Term("y"), Term(Constant(0))}, {Term("z"), Term(Constant(0))}});

    termsRaiseToTerms.simplify();

    TermsRaiseToTerms::BaseToExponentMap const mapToVerify(termsRaiseToTerms.getBaseToExponentMap());
    ASSERT_EQ(1U, mapToVerify.size());
    auto itToVerify = mapToVerify.cbegin();
    EXPECT_EQ(Term("x"), itToVerify->first);
    EXPECT_EQ(Term(1), itToVerify->second);
}

}

}
