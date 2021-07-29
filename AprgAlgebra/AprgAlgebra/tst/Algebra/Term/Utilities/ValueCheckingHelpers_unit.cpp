#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algebra
{

TEST(ValueCheckingHelpersTest, WillHaveNoEffectOnAdditionOrSubtractionWorks)
{
    EXPECT_TRUE(willHaveNoEffectOnAdditionOrSubtraction(Term()));
    EXPECT_TRUE(willHaveNoEffectOnAdditionOrSubtraction(Term(Constant(0))));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(15)));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(Variable("x"))));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(Monomial(96, {{"x", 1}}))));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(Polynomial{Monomial(96, {{"x", 1}})})));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(createExpressionIfPossible({Term(254)}))));
    EXPECT_TRUE(willHaveNoEffectOnAdditionOrSubtraction(Term(Expression())));
}

TEST(ValueCheckingHelpersTest, WillHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPowerWorks)
{
    EXPECT_TRUE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term()));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Constant(0))));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(15)));
    EXPECT_TRUE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(1)));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Variable("x"))));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Monomial(96, {{"x", 1}}))));
    EXPECT_TRUE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Monomial(1, {}))));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Polynomial{Monomial(96, {{"x", 1}})})));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(createExpressionIfPossible({Term(254)}))));
    EXPECT_TRUE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Expression())));
}

TEST(ValueCheckingHelpersTest, IsNotANumberWorksForTerm)
{
    EXPECT_TRUE(isNotANumber(Term(NAN)));
    EXPECT_FALSE(isNotANumber(Term("x")));
    EXPECT_TRUE(isNotANumber(Term(Monomial(NAN, {}))));
    EXPECT_TRUE(isNotANumber(Term(Polynomial{Monomial(NAN, {})})));
    EXPECT_TRUE(isNotANumber(Term(createExpressionIfPossible({Term(NAN)}))));
    EXPECT_FALSE(isNotANumber(Term(createExpressionIfPossible({Term(5.12), Term("+"), Term(NAN)}))));
}

TEST(ValueCheckingHelpersTest, IsNotANumberWorksForConstant)
{
    EXPECT_TRUE(isNotANumber(Constant(NAN)));
    EXPECT_FALSE(isNotANumber(Constant(15)));
}

TEST(ValueCheckingHelpersTest, IsNotANumberWorksForMonomial)
{
    EXPECT_TRUE(isNotANumber(Monomial(NAN, {})));
    EXPECT_FALSE(isNotANumber(Monomial(NAN, {{"x", 1}})));
    EXPECT_FALSE(isNotANumber(Monomial(15, {})));
    EXPECT_FALSE(isNotANumber(Monomial(15, {{"x", NAN}})));
}

TEST(ValueCheckingHelpersTest, IsNotANumberWorksForPolynomial)
{
    EXPECT_TRUE(isNotANumber(Polynomial{Monomial(NAN, {})}));
    EXPECT_FALSE(isNotANumber(Polynomial{Monomial(NAN, {}), Monomial(5, {{"x", 1}})}));
    EXPECT_FALSE(isNotANumber(Polynomial{Monomial(15, {})}));
}

TEST(ValueCheckingHelpersTest, IsNotANumberWorksForExpression)
{
    EXPECT_TRUE(isNotANumber(createExpressionIfPossible({Term(NAN)})));
    EXPECT_FALSE(isNotANumber(createExpressionIfPossible({Term(67)})));
}

TEST(ValueCheckingHelpersTest, HasNotANumberWorksForTerm)
{
    EXPECT_TRUE(hasNotANumber(Term(NAN)));
    EXPECT_FALSE(hasNotANumber(Term("x")));
    EXPECT_TRUE(hasNotANumber(Term(Monomial(NAN, {}))));
    EXPECT_TRUE(hasNotANumber(Term(Polynomial{Monomial(NAN, {})})));
    EXPECT_TRUE(hasNotANumber(Term(createExpressionIfPossible({Term(NAN)}))));
    EXPECT_TRUE(hasNotANumber(Term(createExpressionIfPossible({Term(5.12), Term("+"), Term(NAN)}))));
}

TEST(ValueCheckingHelpersTest, HasNotANumberWorksForMonomial)
{
    EXPECT_TRUE(hasNotANumber(Monomial(NAN, {})));
    EXPECT_TRUE(hasNotANumber(Monomial(NAN, {{"x", 1}})));
    EXPECT_FALSE(hasNotANumber(Monomial(15, {})));
    EXPECT_TRUE(hasNotANumber(Monomial(15, {{"x", NAN}})));
}

TEST(ValueCheckingHelpersTest, HasNotANumberWorksForPolynomial)
{
    EXPECT_TRUE(hasNotANumber(Polynomial{Monomial(NAN, {})}));
    EXPECT_TRUE(hasNotANumber(Polynomial{Monomial(NAN, {}), Monomial(5, {{"x", 1}})}));
    EXPECT_FALSE(hasNotANumber(Polynomial{Monomial(15, {})}));
}

TEST(ValueCheckingHelpersTest, HasNotANumberWorksForExpression)
{
    EXPECT_TRUE(isNotANumber(createExpressionIfPossible({Term(NAN)})));
    EXPECT_TRUE(hasNotANumber(createExpressionIfPossible({Term(5.12), Term("+"), Term(NAN)})));
}

TEST(ValueCheckingHelpersTest, HasNotANumberWorksForFunction)
{
    Function absoluteValueFunction(Functions::abs(createExpressionIfPossible({Term(5.12), Term("+"), Term(NAN)})));
    EXPECT_TRUE(hasNotANumber(absoluteValueFunction));
}

}

}
