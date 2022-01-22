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
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    TermsWithDetails termsWithDetails{{Term(2), TermAssociationType::Positive}, {squareRootOfXPlusOneTerm, TermAssociationType::Positive}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term subTerm(Polynomial{Monomial(4, {{"x", 1}}), Monomial(4, {})});
    Term termToExpect(createExpressionIfPossible({subTerm, "^", AlbaNumber::createFraction(1, 2)}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningNegativeConstantAndRadicalPolynomialInMultiplicationWorks)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    TermsWithDetails termsWithDetails
    {{Term(-2), TermAssociationType::Positive}, {squareRootOfXPlusOneTerm, TermAssociationType::Positive}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term termToExpect(createExpressionIfPossible({-2, "*", squareRootOfXPlusOneTerm}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningConstantAndRadicalPolynomialInDivisionWorks)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    TermsWithDetails termsWithDetails{{Term(2), TermAssociationType::Positive}, {squareRootOfXPlusOneTerm, TermAssociationType::Negative}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term subTerm(createExpressionIfPossible({4, "/", xPlusOneTerm}));
    Term termToExpect(createExpressionIfPossible({subTerm, "^", AlbaNumber::createFraction(1, 2)}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningMonomialAndRadicalPolynomialInMultiplicationWorks)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    TermsWithDetails termsWithDetails{{Term("x"), TermAssociationType::Positive}, {squareRootOfXPlusOneTerm, TermAssociationType::Positive}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term insideSquareRootTerm(Polynomial{Monomial(1, {{"x", 3}}), Monomial(1, {{"x", 2}})});
    Term termToExpect(createExpressionIfPossible({insideSquareRootTerm, "^", AlbaNumber::createFraction(1, 2)}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningMonomialAndRadicalPolynomialInDivisionWorks)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    TermsWithDetails termsWithDetails{{Term("x"), TermAssociationType::Positive}, {squareRootOfXPlusOneTerm, TermAssociationType::Negative}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term subTerm(createExpressionIfPossible({Monomial(1, {{"x", 2}}), "/", xPlusOneTerm}));
    Term termToExpect(createExpressionIfPossible({subTerm, "^", AlbaNumber::createFraction(1, 2)}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningRadicalPolynomialsInMultiplicationWorks)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    TermsWithDetails termsWithDetails
    {{squareRootOfXPlusOneTerm, TermAssociationType::Positive},
        {squareRootOfXPlusOneTerm, TermAssociationType::Positive}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term insideSquareRootTerm(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Term termToExpect(createExpressionIfPossible({insideSquareRootTerm, "^", AlbaNumber::createFraction(1, 2)}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningRadicalPolynomialsInDivisionWorks)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneTerm(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(1, 2)}));
    Term xPlusOneSquaredExpandedTerm(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Term squareRootOfXPlusOneSquaredTerm(createExpressionIfPossible({xPlusOneSquaredExpandedTerm, "^", AlbaNumber::createFraction(1, 2)}));
    TermsWithDetails termsWithDetails
    {{squareRootOfXPlusOneSquaredTerm, TermAssociationType::Positive},
        {squareRootOfXPlusOneTerm, TermAssociationType::Negative}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term subTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term termToExpect(createExpressionIfPossible({subTerm, "^", AlbaNumber::createFraction(1, 2)}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningMonomialWithCubeRootAndRadicalSquaredCubeRootWorks)
{
    Term xPlusOneTerm(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term xPlusOneRadicalTerm(createExpressionIfPossible({xPlusOneTerm, "^", AlbaNumber::createFraction(2, 3)}));
    TermsWithDetails termsWithDetails
    {{Term(Monomial(1, {{"x", AlbaNumber::createFraction(1, 3)}})), TermAssociationType::Positive},
        {xPlusOneRadicalTerm, TermAssociationType::Positive}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term subTerm(Polynomial{Monomial(1, {{"x", 3}}), Monomial(2, {{"x", 2}}), Monomial(1, {{"x", 1}})});
    Term termToExpect(createExpressionIfPossible({subTerm, "^", AlbaNumber::createFraction(1, 3)}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}

TEST(MultiplicationAndDivisionOfRadicalsTest, CombiningVariableAndMonomialWorks)
{
    TermsWithDetails termsWithDetails
    {{Term("x"), TermAssociationType::Positive},
        {Term(Monomial(1, {{"x", AlbaNumber::createFraction(3, 2)}})), TermAssociationType::Positive}};
    MultiplicationAndDivisionOfRadicals radicalConstruct(termsWithDetails);

    radicalConstruct.simplify();

    Term termToExpect(Monomial(1, {{"x", AlbaNumber::createFraction(5, 2)}}));
    EXPECT_EQ(termToExpect, radicalConstruct.getCombinedTerm());
}


}

}
