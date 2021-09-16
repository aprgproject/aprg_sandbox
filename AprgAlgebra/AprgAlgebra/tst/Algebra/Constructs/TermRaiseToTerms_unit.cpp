#include <Algebra/Constructs/TermRaiseToTerms.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{

TEST(TermRaiseToTermsTest, ConstructionWithNoArgumentWorks)
{
    TermRaiseToTerms termRaiseToTerms;

    EXPECT_TRUE(termRaiseToTerms.getBase().isEmpty());
    EXPECT_TRUE(termRaiseToTerms.getExponents().empty());
}

TEST(TermRaiseToTermsTest, ConstructionWithTermToExponentWorks)
{
    Term base("x");
    TermsWithDetails exponents{TermWithDetails(Term("y"), TermAssociationType::Positive)};
    TermRaiseToTerms termRaiseToTerms(base, exponents);

    EXPECT_EQ(base, termRaiseToTerms.getBase());
    EXPECT_EQ(exponents, termRaiseToTerms.getExponents());
}

TEST(TermRaiseToTermsTest, ConstructionWithTermsInRaiseToPowerExpressionWorks)
{
    TermsWithDetails termsInRaiseToPowerExpression;
    termsInRaiseToPowerExpression.emplace_back(Term("x"), TermAssociationType::Positive);
    termsInRaiseToPowerExpression.emplace_back(Term("y"), TermAssociationType::Positive);
    TermRaiseToTerms termRaiseToTerms(termsInRaiseToPowerExpression);

    TermsWithDetails expectedExponents{TermWithDetails(Term("y"), TermAssociationType::Positive)};
    EXPECT_EQ(Term("x"), termRaiseToTerms.getBase());
    EXPECT_EQ(expectedExponents, termRaiseToTerms.getExponents());
}

TEST(TermRaiseToTermsTest, MonomialToNumber)
{
    Term base(Monomial(1, {{"x", 2}}));
    TermsWithDetails exponents{TermWithDetails(Term(AlbaNumber::createFraction(1, 2)), TermAssociationType::Positive)};
    TermRaiseToTerms termRaiseToTerms(base, exponents);

    termRaiseToTerms.simplify();

    EXPECT_EQ(base, termRaiseToTerms.getBase());
    EXPECT_EQ(exponents, termRaiseToTerms.getExponents());
    EXPECT_EQ(Term("x"), termRaiseToTerms.getCombinedTerm());
}

}

}
