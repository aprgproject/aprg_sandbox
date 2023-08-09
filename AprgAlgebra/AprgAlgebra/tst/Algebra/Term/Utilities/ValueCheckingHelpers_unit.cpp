#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <gtest/gtest.h>

#include <cmath>

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

TEST(ValueCheckingHelpersTest, IsTheValueWorksWithTerm)
{
    Term term1;
    Term term2(Constant(0));
    Term term3(1);
    Term term4(Variable("length"));
    Term term5(Operator("+"));
    Term term6(Monomial(0, {}));
    Term term7(Monomial(1, {}));
    Term term8(Polynomial{});
    Term term9(Polynomial{Monomial(1, {})});
    Term term10(Expression{});
    Term term11(Function{});

    EXPECT_FALSE(isTheValue(term1, 0));
    EXPECT_FALSE(isTheValue(term1, 1));
    EXPECT_TRUE(isTheValue(term2, 0));
    EXPECT_FALSE(isTheValue(term2, 1));
    EXPECT_FALSE(isTheValue(term3, 0));
    EXPECT_TRUE(isTheValue(term3, 1));
    EXPECT_FALSE(isTheValue(term4, 0));
    EXPECT_FALSE(isTheValue(term4, 1));
    EXPECT_FALSE(isTheValue(term5, 0));
    EXPECT_FALSE(isTheValue(term5, 1));
    EXPECT_TRUE(isTheValue(term6, 0));
    EXPECT_FALSE(isTheValue(term6, 1));
    EXPECT_FALSE(isTheValue(term7, 0));
    EXPECT_TRUE(isTheValue(term7, 1));
    EXPECT_TRUE(isTheValue(term8, 0));
    EXPECT_FALSE(isTheValue(term8, 1));
    EXPECT_FALSE(isTheValue(term9, 0));
    EXPECT_TRUE(isTheValue(term9, 1));
    EXPECT_FALSE(isTheValue(term10, 0));
    EXPECT_FALSE(isTheValue(term10, 1));
    EXPECT_FALSE(isTheValue(term11, 0));
    EXPECT_FALSE(isTheValue(term11, 1));
}

TEST(ValueCheckingHelpersTest, IsTheValueWorksWithConstant)
{
    Constant constant1;
    Constant constant2(0);
    Constant constant3(1);
    Constant constant4(23);

    EXPECT_TRUE(isTheValue(constant1, 0));
    EXPECT_FALSE(isTheValue(constant1, 1));
    EXPECT_TRUE(isTheValue(constant2, 0));
    EXPECT_FALSE(isTheValue(constant2, 1));
    EXPECT_FALSE(isTheValue(constant3, 0));
    EXPECT_TRUE(isTheValue(constant3, 1));
    EXPECT_FALSE(isTheValue(constant4, 0));
    EXPECT_FALSE(isTheValue(constant4, 1));
    EXPECT_TRUE(isTheValue(constant4, 23));
}

TEST(ValueCheckingHelpersTest, IsTheValueWorksWithMonomial)
{
    Monomial monomial1;
    Monomial monomial2(1, {{"x", 6}, {"y", -1.25}});
    Monomial monomial3(0, {{"x", 6}, {"y", -1.25}});
    Monomial monomial4(1, {});
    Monomial monomial5(23, {});

    EXPECT_TRUE(isTheValue(monomial1, 0));
    EXPECT_FALSE(isTheValue(monomial1, 1));
    EXPECT_FALSE(isTheValue(monomial2, 0));
    EXPECT_FALSE(isTheValue(monomial2, 1));
    EXPECT_TRUE(isTheValue(monomial3, 0));
    EXPECT_FALSE(isTheValue(monomial3, 1));
    EXPECT_FALSE(isTheValue(monomial4, 0));
    EXPECT_TRUE(isTheValue(monomial4, 1));
    EXPECT_FALSE(isTheValue(monomial5, 0));
    EXPECT_FALSE(isTheValue(monomial5, 1));
    EXPECT_TRUE(isTheValue(monomial5, 23));
}

TEST(ValueCheckingHelpersTest, IsTheValueWorksWithPolynomial)
{
    Polynomial polynomial1;
    Polynomial polynomial2{Monomial(6, {})};
    Polynomial polynomial3{Monomial(6, {}), Monomial(-7, {{"x", 2}, {"y", 3}, {"z", 4}})};
    Polynomial polynomial4{Monomial(0, {{"x", 2}, {"y", 3}, {"z", 4}})};
    Polynomial polynomial5{Monomial(1, {{"x", 2}})};
    Polynomial polynomial6{Monomial(1, {})};

    EXPECT_TRUE(isTheValue(polynomial1, 0));
    EXPECT_FALSE(isTheValue(polynomial1, 1));
    EXPECT_FALSE(isTheValue(polynomial2, 0));
    EXPECT_FALSE(isTheValue(polynomial2, 1));
    EXPECT_TRUE(isTheValue(polynomial2, 6));
    EXPECT_FALSE(isTheValue(polynomial3, 0));
    EXPECT_FALSE(isTheValue(polynomial3, 1));
    EXPECT_FALSE(isTheValue(polynomial3, 6));
    EXPECT_FALSE(isTheValue(polynomial4, 0));
    EXPECT_FALSE(isTheValue(polynomial4, 1));
    EXPECT_FALSE(isTheValue(polynomial5, 0));
    EXPECT_FALSE(isTheValue(polynomial5, 1));
    EXPECT_FALSE(isTheValue(polynomial6, 0));
    EXPECT_TRUE(isTheValue(polynomial6, 1));
}

TEST(ValueCheckingHelpersTest, IsTheValueWorksWithExpression)
{
    EXPECT_FALSE(isTheValue(createExpressionIfPossible({Term(NAN)}), 67));
    EXPECT_TRUE(isTheValue(createExpressionIfPossible({Term(67)}), 67));
    EXPECT_FALSE(isTheValue(createExpressionIfPossible({Term(67), Term("+"), Term("x")}), 67));
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
    EXPECT_FALSE(isNotANumber(createExpressionIfPossible({Term(67), Term("+"), Term("x")})));
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

TEST(ValueCheckingHelpersTest, IsAFiniteConstantWorksForFunction)
{
    EXPECT_FALSE(isAFiniteConstant(Term("x")));
    EXPECT_TRUE(isAFiniteConstant(Term(1)));
    EXPECT_FALSE(isAFiniteConstant(Term(NAN)));
}

TEST(ValueCheckingHelpersTest, IsNegativeTermWorks)
{
    EXPECT_TRUE(isNegativeTerm(Term(-1)));
    EXPECT_FALSE(isNegativeTerm(Term(1)));
    EXPECT_FALSE(isNegativeTerm(Term("x")));
    EXPECT_TRUE(isNegativeTerm(Term(Monomial(-1, {{"x", 1}}))));
    EXPECT_FALSE(isNegativeTerm(Term(Monomial(1, {{"x", 1}}))));
    EXPECT_TRUE(isNegativeTerm(Term(Polynomial{Monomial(-1, {{"x", 3}}), Monomial(4, {}), })));
    EXPECT_FALSE(isNegativeTerm(Term(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-4, {}), })));
    EXPECT_TRUE(isNegativeTerm(Term(createExpressionIfPossible({Term(-5), Term("+"), Term("x")}))));
    EXPECT_FALSE(isNegativeTerm(Term(createExpressionIfPossible({Term(5), Term("+"), Term("x")}))));
    EXPECT_TRUE(isNegativeTerm(Term(createExpressionIfPossible({Term(-5), Term("*"), Term("x")}))));
    EXPECT_FALSE(isNegativeTerm(Term(createExpressionIfPossible({Term(-5), Term("*"), Term(-3)}))));
    EXPECT_TRUE(isNegativeTerm(Term(createExpressionIfPossible({Term(-5), Term("^"), Term("x")}))));
    EXPECT_FALSE(isNegativeTerm(Term(createExpressionIfPossible({Term(5), Term("^"), Term("x")}))));
    EXPECT_FALSE(isNegativeTerm(Term(Functions::abs(Term(-5)))));
}

}

}
