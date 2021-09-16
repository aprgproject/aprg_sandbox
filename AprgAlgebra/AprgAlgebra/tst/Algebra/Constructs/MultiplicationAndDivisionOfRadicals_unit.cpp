#include <Algebra/Constructs/MultiplicationAndDivisionOfRadicals.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningConstantAndRadicalPolynomialInMultiplicationWorks)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    TermsWithDetails termsWithDetails
    {{Term(2), TermAssociationType::Positive},
        {squareRootOfXPlusOneTerm, TermAssociationType::Positive}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term subTerm(Polynomial{Monomial(4, {{"x", 1}}), Monomial(4, {})});
    Term termToExpect(createExpressionIfPossible({Term(subTerm), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningConstantAndRadicalPolynomialInDivisionWorks)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    TermsWithDetails termsWithDetails
    {{Term(2), TermAssociationType::Positive},
        {squareRootOfXPlusOneTerm, TermAssociationType::Negative}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term subTerm(createExpressionIfPossible({Term(4), Term("/"), xPlusOneTerm}));
    Term termToExpect(createExpressionIfPossible({Term(subTerm), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningMonomialAndRadicalPolynomialInMultiplicationWorks)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    TermsWithDetails termsWithDetails
    {{Term("x"), TermAssociationType::Positive},
        {squareRootOfXPlusOneTerm, TermAssociationType::Positive}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term insideSquareRootTerm(Polynomial{Monomial(1, {{"x", 3}}), Monomial(1, {{"x", 2}})});
    Term termToExpect(createExpressionIfPossible({insideSquareRootTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningMonomialAndRadicalPolynomialInDivisionWorks)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    TermsWithDetails termsWithDetails
    {{Term("x"), TermAssociationType::Positive},
        {squareRootOfXPlusOneTerm, TermAssociationType::Negative}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term subTerm(createExpressionIfPossible({Term(Monomial(1, {{"x", 2}})), Term("/"), xPlusOneTerm}));
    Term termToExpect(createExpressionIfPossible({Term(subTerm), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningRadicalPolynomialsInMultiplicationWorks)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    TermsWithDetails termsWithDetails
    {{squareRootOfXPlusOneTerm, TermAssociationType::Positive},
        {squareRootOfXPlusOneTerm, TermAssociationType::Positive}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term insideSquareRootTerm(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Term termToExpect(createExpressionIfPossible({insideSquareRootTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningRadicalPolynomialsInDivisionWorks)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term xPlusOneSquaredExpandedTerm(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneSquaredTerm(createExpressionIfPossible({xPlusOneSquaredExpandedTerm, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    TermsWithDetails termsWithDetails
    {{squareRootOfXPlusOneSquaredTerm, TermAssociationType::Positive},
        {squareRootOfXPlusOneTerm, TermAssociationType::Negative}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term subTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term termToExpect(createExpressionIfPossible({Term(subTerm), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningMonomialWithCubeRootAndRadicalSquaredCubeRootWorks)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term xPlusOneRadicalTerm(createExpressionIfPossible({xPlusOneTerm, Term("^"), Term(AlbaNumber::createFraction(2, 3))}));
    TermsWithDetails termsWithDetails
    {{Term(Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}})), TermAssociationType::Positive},
        {xPlusOneRadicalTerm, TermAssociationType::Positive}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term subTerm(Polynomial{Monomial(1, {{"x", 3}}), Monomial(2, {{"x", 2}}), Monomial(1, {{"x", 1}})});
    Term termToExpect(createExpressionIfPossible({Term(subTerm), Term("^"), Term(AlbaNumber::createFraction(1, 3))}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}


}

}
