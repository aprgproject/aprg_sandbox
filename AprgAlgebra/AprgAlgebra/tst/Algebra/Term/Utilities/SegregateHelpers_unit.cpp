#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/SegregateHelpers.hpp>

#include <gtest/gtest.h>

using TermWithDetails=alba::algebra::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::algebra::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace algebra
{

TEST(SegregateHelpersTest, SegregateMonomialsAndNonMonomialsWorks)
{
    Terms monomialTerms;
    Terms nonMonomialTerms;
    Term termExpression(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));

    segregateMonomialsAndNonMonomials({Term(234), termExpression}, monomialTerms, nonMonomialTerms);

    ASSERT_EQ(1u, monomialTerms.size());
    EXPECT_EQ(Term(234), monomialTerms.at(0));
    ASSERT_EQ(1u, nonMonomialTerms.size());
    EXPECT_EQ(termExpression, nonMonomialTerms.at(0));
}

TEST(SegregateHelpersTest, SegregatePolynomialAndNonPolynomialsWorks)
{
    Terms polynomialTerms;
    Terms nonPolynomialTerms;
    Term termExpression(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));

    segregatePolynomialAndNonPolynomials({Term(234), termExpression}, polynomialTerms, nonPolynomialTerms);

    ASSERT_EQ(1u, polynomialTerms.size());
    EXPECT_EQ(Term(234), polynomialTerms.at(0));
    ASSERT_EQ(1u, nonPolynomialTerms.size());
    EXPECT_EQ(termExpression, nonPolynomialTerms.at(0));
}

TEST(SegregateHelpersTest, SegregateNonExpressionsAndExpressionsWorks)
{
    TermsWithAssociation termsWithAssociation;
    TermsWithDetails termsWithNonExpressions;
    TermsWithDetails termsWithExpressions;
    Term termExpression(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    termsWithAssociation.putTermWithNegativeAssociation(Term(753));
    termsWithAssociation.putTermWithPositiveAssociation(termExpression);

    segregateNonExpressionsAndExpressions(termsWithAssociation.getTermsWithDetails(), termsWithNonExpressions, termsWithExpressions);

    ASSERT_EQ(1u, termsWithNonExpressions.size());
    TermWithDetails const& termWithDetails1(termsWithNonExpressions.at(0));
    EXPECT_EQ(Term(753), getTermConstReferenceFromSharedPointer(termWithDetails1.baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termWithDetails1.association);
    ASSERT_EQ(1u, termsWithExpressions.size());
    TermWithDetails const& termWithDetails2(termsWithExpressions.at(0));
    EXPECT_EQ(termExpression, getTermConstReferenceFromSharedPointer(termWithDetails2.baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termWithDetails2.association);
}

TEST(SegregateHelpersTest, SegregateTermsWithPositiveAndNegativeAssociationsWorks)
{
    TermsWithAssociation termsWithAssociation;
    TermsWithDetails termsInPositive;
    TermsWithDetails termsInNegative;
    termsWithAssociation.putTermWithNegativeAssociation(Term(753));
    termsWithAssociation.putTermWithPositiveAssociation(Term(159));

    segregateTermsWithPositiveAndNegativeAssociations(termsWithAssociation.getTermsWithDetails(), termsInPositive, termsInNegative);

    ASSERT_EQ(1u, termsInPositive.size());
    TermWithDetails const& termWithDetails1(termsInPositive.at(0));
    EXPECT_EQ(Term(159), getTermConstReferenceFromSharedPointer(termWithDetails1.baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Positive, termWithDetails1.association);
    ASSERT_EQ(1u, termsInNegative.size());
    TermWithDetails const& termWithDetails2(termsInNegative.at(0));
    EXPECT_EQ(Term(753), getTermConstReferenceFromSharedPointer(termWithDetails2.baseTermSharedPointer));
    EXPECT_EQ(TermAssociationType::Negative, termWithDetails2.association);
}

}

}
