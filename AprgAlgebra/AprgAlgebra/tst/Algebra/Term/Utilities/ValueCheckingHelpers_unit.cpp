#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::algebra::Functions;

namespace alba
{

namespace algebra
{

TEST(ValueCheckingHelpersTest, IsValueSatisfyTheConditionWorksForTerm)
{
    Term termToTest(12345);

    EXPECT_TRUE(isValueSatisfyTheCondition(termToTest, [](AlbaNumber const& number){return AlbaNumber(12345) == number;}));
    EXPECT_FALSE(isValueSatisfyTheCondition(termToTest, [](AlbaNumber const& number){return AlbaNumber(98765) == number;}));
}

TEST(ValueCheckingHelpersTest, IsValueSatisfyTheConditionWorksForConstant)
{
    Constant constant(12345);

    EXPECT_TRUE(isValueSatisfyTheCondition(constant, [](AlbaNumber const& number){return AlbaNumber(12345) == number;}));
    EXPECT_FALSE(isValueSatisfyTheCondition(constant, [](AlbaNumber const& number){return AlbaNumber(98765) == number;}));
}

TEST(ValueCheckingHelpersTest, IsValueSatisfyTheConditionWorksForMonomial)
{
    Monomial monomial1(Monomial(1, {{"x", 12345}}));
    Monomial monomial2(Monomial(12345, {}));

    EXPECT_FALSE(isValueSatisfyTheCondition(monomial1, [](AlbaNumber const& number){return AlbaNumber(12345) == number;}));
    EXPECT_FALSE(isValueSatisfyTheCondition(monomial1, [](AlbaNumber const& number){return AlbaNumber(98765) == number;}));
    EXPECT_TRUE(isValueSatisfyTheCondition(monomial2, [](AlbaNumber const& number){return AlbaNumber(12345) == number;}));
    EXPECT_FALSE(isValueSatisfyTheCondition(monomial2, [](AlbaNumber const& number){return AlbaNumber(98765) == number;}));
}

TEST(ValueCheckingHelpersTest, IsValueSatisfyTheConditionWorksForPolynomial)
{
    Polynomial polynomial1{Monomial(1, {}), Monomial(1, {{"x", 12345}})};
    Polynomial polynomial2{Monomial(12345, {})};

    EXPECT_FALSE(isValueSatisfyTheCondition(polynomial1, [](AlbaNumber const& number){return AlbaNumber(12345) == number;}));
    EXPECT_FALSE(isValueSatisfyTheCondition(polynomial1, [](AlbaNumber const& number){return AlbaNumber(98765) == number;}));
    EXPECT_TRUE(isValueSatisfyTheCondition(polynomial2, [](AlbaNumber const& number){return AlbaNumber(12345) == number;}));
    EXPECT_FALSE(isValueSatisfyTheCondition(polynomial2, [](AlbaNumber const& number){return AlbaNumber(98765) == number;}));
}

TEST(ValueCheckingHelpersTest, IsValueSatisfyTheConditionWorksForExpression)
{
    Expression expression1(createExpressionIfPossible({"x", "+", 12345}));
    Expression expression2(createExpressionIfPossible({12345}));

    EXPECT_FALSE(isValueSatisfyTheCondition(expression1, [](AlbaNumber const& number){return AlbaNumber(12345) == number;}));
    EXPECT_FALSE(isValueSatisfyTheCondition(expression1, [](AlbaNumber const& number){return AlbaNumber(98765) == number;}));
    EXPECT_TRUE(isValueSatisfyTheCondition(expression2, [](AlbaNumber const& number){return AlbaNumber(12345) == number;}));
    EXPECT_FALSE(isValueSatisfyTheCondition(expression2, [](AlbaNumber const& number){return AlbaNumber(98765) == number;}));
}

TEST(ValueCheckingHelpersTest, DoAnyNumbersSatisfyTheConditionWorksForTerm)
{
    Term termToTest(12345);

    EXPECT_TRUE(doAnyNumbersSatisfyTheCondition(termToTest, [](AlbaNumber const& number){return AlbaNumber(12345) == number;}));
    EXPECT_FALSE(doAnyNumbersSatisfyTheCondition(termToTest, [](AlbaNumber const& number){return AlbaNumber(98765) == number;}));
}

TEST(ValueCheckingHelpersTest, DoAnyNumbersSatisfyTheConditionWorksForMonomial)
{
    Monomial monomial1(Monomial(1, {{"x", 12345}}));
    Monomial monomial2(Monomial(12345, {{"x", 1}}));

    EXPECT_TRUE(doAnyNumbersSatisfyTheCondition(monomial1, [](AlbaNumber const& number){return AlbaNumber(12345) == number;}));
    EXPECT_FALSE(doAnyNumbersSatisfyTheCondition(monomial1, [](AlbaNumber const& number){return AlbaNumber(98765) == number;}));
    EXPECT_TRUE(doAnyNumbersSatisfyTheCondition(monomial2, [](AlbaNumber const& number){return AlbaNumber(12345) == number;}));
    EXPECT_FALSE(doAnyNumbersSatisfyTheCondition(monomial2, [](AlbaNumber const& number){return AlbaNumber(98765) == number;}));
}

TEST(ValueCheckingHelpersTest, DoAnyNumbersSatisfyTheConditionWorksForPolynomial)
{
    Polynomial polynomial1{Monomial(1, {}), Monomial(1, {{"x", 12345}})};
    Polynomial polynomial2{Monomial(12345, {}), Monomial(1, {{"x", 1}})};

    EXPECT_TRUE(doAnyNumbersSatisfyTheCondition(polynomial1, [](AlbaNumber const& number){return AlbaNumber(12345) == number;}));
    EXPECT_FALSE(doAnyNumbersSatisfyTheCondition(polynomial1, [](AlbaNumber const& number){return AlbaNumber(98765) == number;}));
    EXPECT_TRUE(doAnyNumbersSatisfyTheCondition(polynomial2, [](AlbaNumber const& number){return AlbaNumber(12345) == number;}));
    EXPECT_FALSE(doAnyNumbersSatisfyTheCondition(polynomial2, [](AlbaNumber const& number){return AlbaNumber(98765) == number;}));
}

TEST(ValueCheckingHelpersTest, DoAnyNumbersSatisfyTheConditionWorksForExpression)
{
    Expression expression(createExpressionIfPossible({"x", "+", 12345}));

    EXPECT_TRUE(doAnyNumbersSatisfyTheCondition(expression, [](AlbaNumber const& number){return AlbaNumber(12345) == number;}));
    EXPECT_FALSE(doAnyNumbersSatisfyTheCondition(expression, [](AlbaNumber const& number){return AlbaNumber(98765) == number;}));
}

TEST(ValueCheckingHelpersTest, DoAnyNumbersSatisfyTheConditionWorksForFunction)
{
    Function absoluteValueFunction(Functions::abs(createExpressionIfPossible({"x", "+", 12345})));

    EXPECT_TRUE(doAnyNumbersSatisfyTheCondition(absoluteValueFunction, [](AlbaNumber const& number){return AlbaNumber(12345) == number;}));
    EXPECT_FALSE(doAnyNumbersSatisfyTheCondition(absoluteValueFunction, [](AlbaNumber const& number){return AlbaNumber(98765) == number;}));
}

TEST(ValueCheckingHelpersTest, WillHaveNoEffectOnAdditionOrSubtractionWorks)
{
    EXPECT_TRUE(willHaveNoEffectOnAdditionOrSubtraction(Term()));
    EXPECT_TRUE(willHaveNoEffectOnAdditionOrSubtraction(Term(0)));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(15)));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(Variable("x"))));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(Monomial(96, {{"x", 1}}))));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(Polynomial{Monomial(96, {{"x", 1}})})));
    EXPECT_FALSE(willHaveNoEffectOnAdditionOrSubtraction(Term(createExpressionIfPossible({254}))));
    EXPECT_TRUE(willHaveNoEffectOnAdditionOrSubtraction(Term(Expression())));
}

TEST(ValueCheckingHelpersTest, WillHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPowerWorks)
{
    EXPECT_TRUE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term()));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(0)));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(15)));
    EXPECT_TRUE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(1)));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Variable("x"))));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Monomial(96, {{"x", 1}}))));
    EXPECT_TRUE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Monomial(1, {}))));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Polynomial{Monomial(96, {{"x", 1}})})));
    EXPECT_FALSE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(createExpressionIfPossible({254}))));
    EXPECT_TRUE(willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term(Expression())));
}

TEST(ValueCheckingHelpersTest, IsTheValueWorksWithTerm)
{
    Term term1;
    Term term2(0);
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
    EXPECT_FALSE(isTheValue(createExpressionIfPossible({NAN}), 67));
    EXPECT_TRUE(isTheValue(createExpressionIfPossible({67}), 67));
    EXPECT_FALSE(isTheValue(createExpressionIfPossible({67, "+", "x"}), 67));
}

TEST(ValueCheckingHelpersTest, IsNotANumberWorksForTerm)
{
    EXPECT_TRUE(isNotANumber(Term(NAN)));
    EXPECT_FALSE(isNotANumber(Term("x")));
    EXPECT_TRUE(isNotANumber(Term(Monomial(NAN, {}))));
    EXPECT_TRUE(isNotANumber(Term(Polynomial{Monomial(NAN, {})})));
    EXPECT_TRUE(isNotANumber(Term(createExpressionIfPossible({NAN}))));
    EXPECT_FALSE(isNotANumber(Term(createExpressionIfPossible({5.12, "+", NAN}))));
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
    EXPECT_TRUE(isNotANumber(createExpressionIfPossible({NAN})));
    EXPECT_FALSE(isNotANumber(createExpressionIfPossible({67})));
    EXPECT_FALSE(isNotANumber(createExpressionIfPossible({67, "+", "x"})));
}

TEST(ValueCheckingHelpersTest, IsPositiveOrNegativeInfinityWorksForTerm)
{
    EXPECT_TRUE(isPositiveOrNegativeInfinity(Term(INFINITY)));
    EXPECT_FALSE(isPositiveOrNegativeInfinity(Term("x")));
    EXPECT_TRUE(isPositiveOrNegativeInfinity(Term(Monomial(-INFINITY, {}))));
    EXPECT_TRUE(isPositiveOrNegativeInfinity(Term(Polynomial{Monomial(INFINITY, {})})));
    EXPECT_TRUE(isPositiveOrNegativeInfinity(Term(createExpressionIfPossible({-INFINITY}))));
    EXPECT_FALSE(isPositiveOrNegativeInfinity(Term(createExpressionIfPossible({5.12, "+", INFINITY}))));
}

TEST(ValueCheckingHelpersTest, IsPositiveOrNegativeInfinityWorksForConstant)
{
    EXPECT_TRUE(isPositiveOrNegativeInfinity(Constant(INFINITY)));
    EXPECT_FALSE(isPositiveOrNegativeInfinity(Constant(15)));
}

TEST(ValueCheckingHelpersTest, IsPositiveOrNegativeInfinityWorksForMonomial)
{
    EXPECT_TRUE(isPositiveOrNegativeInfinity(Monomial(INFINITY, {})));
    EXPECT_FALSE(isPositiveOrNegativeInfinity(Monomial(-NAN, {{"x", 1}})));
    EXPECT_FALSE(isPositiveOrNegativeInfinity(Monomial(15, {})));
    EXPECT_FALSE(isPositiveOrNegativeInfinity(Monomial(15, {{"x", INFINITY}})));
}

TEST(ValueCheckingHelpersTest, IsPositiveOrNegativeInfinityWorksForPolynomial)
{
    EXPECT_TRUE(isPositiveOrNegativeInfinity(Polynomial{Monomial(INFINITY, {})}));
    EXPECT_FALSE(isPositiveOrNegativeInfinity(Polynomial{Monomial(-INFINITY, {}), Monomial(5, {{"x", 1}})}));
    EXPECT_FALSE(isPositiveOrNegativeInfinity(Polynomial{Monomial(15, {})}));
}

TEST(ValueCheckingHelpersTest, IsPositiveOrNegativeInfinityWorksForExpression)
{
    EXPECT_TRUE(isPositiveOrNegativeInfinity(createExpressionIfPossible({INFINITY})));
    EXPECT_FALSE(isPositiveOrNegativeInfinity(createExpressionIfPossible({67})));
    EXPECT_FALSE(isPositiveOrNegativeInfinity(createExpressionIfPossible({67, "+", "x"})));
}

TEST(ValueCheckingHelpersTest, IsANegativeTermWorks)
{
    Term x("x");
    EXPECT_TRUE(isANegativeTerm(-1));
    EXPECT_FALSE(isANegativeTerm(1));
    EXPECT_FALSE(isANegativeTerm(x));
    EXPECT_TRUE(isANegativeTerm(Monomial(-1, {{"x", 1}})));
    EXPECT_FALSE(isANegativeTerm(Monomial(1, {{"x", 1}})));
    EXPECT_TRUE(isANegativeTerm(Polynomial{Monomial(-1, {{"x", 3}}), Monomial(4, {}), }));
    EXPECT_FALSE(isANegativeTerm(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-4, {}), }));
    EXPECT_TRUE(isANegativeTerm(createExpressionIfPossible({-5, "+", x})));
    EXPECT_FALSE(isANegativeTerm(createExpressionIfPossible({5, "+", x})));
    EXPECT_FALSE(isANegativeTerm(Functions::abs(-5)));
}

TEST(ValueCheckingHelpersTest, IsANegativeConstantWorks)
{
    EXPECT_TRUE(isANegativeConstant(Constant(-1)));
    EXPECT_FALSE(isANegativeConstant(Constant(1)));
}

TEST(ValueCheckingHelpersTest, IsANegativeMonomialWorks)
{
    EXPECT_TRUE(isANegativeMonomial(Monomial(-1, {{"x", 1}})));
    EXPECT_FALSE(isANegativeMonomial(Monomial(1, {{"x", 1}})));
}

TEST(ValueCheckingHelpersTest, IsANegativePolynomialWorks)
{
    EXPECT_TRUE(isANegativePolynomial(Polynomial{Monomial(-1, {{"x", 3}}), Monomial(4, {}), }));
    EXPECT_FALSE(isANegativePolynomial(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-4, {}), }));
}

TEST(ValueCheckingHelpersTest, IsANegativeExpressionWorks)
{
    Term x("x");
    EXPECT_TRUE(isANegativeExpression(createExpressionIfPossible({-5, "+", x})));
    EXPECT_FALSE(isANegativeExpression(createExpressionIfPossible({5, "+", x})));
    EXPECT_TRUE(isANegativeExpression(createExpressionIfPossible({-5, "*", x})));
    EXPECT_FALSE(isANegativeExpression(createExpressionIfPossible({-5, "*", -3})));
    EXPECT_FALSE(isANegativeExpression(createExpressionIfPossible({-5, "^", x})));
    EXPECT_FALSE(isANegativeExpression(createExpressionIfPossible({5, "^", x})));
}

TEST(ValueCheckingHelpersTest, IsIntegerConstantWorks)
{
    EXPECT_FALSE(isIntegerConstant("x"));
    EXPECT_TRUE(isIntegerConstant(1));
    EXPECT_TRUE(isIntegerConstant(-1));
    EXPECT_FALSE(isIntegerConstant(NAN));
}

TEST(ValueCheckingHelpersTest, IsPositiveIntegerConstantWorks)
{
    EXPECT_FALSE(isPositiveIntegerConstant("x"));
    EXPECT_TRUE(isPositiveIntegerConstant(1));
    EXPECT_FALSE(isPositiveIntegerConstant(-1));
    EXPECT_FALSE(isPositiveIntegerConstant(NAN));
}

TEST(ValueCheckingHelpersTest, IsAFiniteConstantWorks)
{
    EXPECT_FALSE(isARealFiniteConstant("x"));
    EXPECT_TRUE(isARealFiniteConstant(1));
    EXPECT_FALSE(isARealFiniteConstant(NAN));
}

TEST(ValueCheckingHelpersTest, HasNotANumberWorksForTerm)
{
    EXPECT_TRUE(hasNotANumber(Term(NAN)));
    EXPECT_FALSE(hasNotANumber(Term("x")));
    EXPECT_TRUE(hasNotANumber(Term(Monomial(NAN, {}))));
    EXPECT_TRUE(hasNotANumber(Term(Polynomial{Monomial(NAN, {})})));
    EXPECT_TRUE(hasNotANumber(Term(createExpressionIfPossible({NAN}))));
    EXPECT_TRUE(hasNotANumber(Term(createExpressionIfPossible({5.12, "+", NAN}))));
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
    EXPECT_TRUE(hasNotANumber(createExpressionIfPossible({NAN})));
    EXPECT_TRUE(hasNotANumber(createExpressionIfPossible({5.12, "+", NAN})));
}

TEST(ValueCheckingHelpersTest, HasNotANumberWorksForFunction)
{
    Function absoluteValueFunction(Functions::abs(createExpressionIfPossible({5.12, "+", NAN})));
    EXPECT_TRUE(hasNotANumber(absoluteValueFunction));
}

TEST(ValueCheckingHelpersTest, HasNonFiniteNumbersForTerm)
{
    EXPECT_TRUE(hasNonRealFiniteNumbers(Term(NAN)));
    EXPECT_FALSE(hasNonRealFiniteNumbers(Term("x")));
    EXPECT_TRUE(hasNonRealFiniteNumbers(Term(Monomial(NAN, {}))));
    EXPECT_TRUE(hasNonRealFiniteNumbers(Term(Polynomial{Monomial(NAN, {})})));
    EXPECT_TRUE(hasNonRealFiniteNumbers(Term(createExpressionIfPossible({NAN}))));
    EXPECT_TRUE(hasNonRealFiniteNumbers(Term(createExpressionIfPossible({5.12, "+", NAN}))));
}

TEST(ValueCheckingHelpersTest, HasNonFiniteNumbersForMonomial)
{
    EXPECT_TRUE(hasNonRealFiniteNumbers(Monomial(NAN, {})));
    EXPECT_TRUE(hasNonRealFiniteNumbers(Monomial(NAN, {{"x", 1}})));
    EXPECT_FALSE(hasNonRealFiniteNumbers(Monomial(15, {})));
    EXPECT_TRUE(hasNonRealFiniteNumbers(Monomial(15, {{"x", NAN}})));
}

TEST(ValueCheckingHelpersTest, HasNonFiniteNumbersForPolynomial)
{
    EXPECT_TRUE(hasNonRealFiniteNumbers(Polynomial{Monomial(NAN, {})}));
    EXPECT_TRUE(hasNonRealFiniteNumbers(Polynomial{Monomial(NAN, {}), Monomial(5, {{"x", 1}})}));
    EXPECT_FALSE(hasNonRealFiniteNumbers(Polynomial{Monomial(15, {})}));
}

TEST(ValueCheckingHelpersTest, HasNonFiniteNumbersForExpression)
{
    EXPECT_TRUE(hasNonRealFiniteNumbers(createExpressionIfPossible({NAN})));
    EXPECT_TRUE(hasNonRealFiniteNumbers(createExpressionIfPossible({5.12, "+", NAN})));
}

TEST(ValueCheckingHelpersTest, HasNonFiniteNumbersForFunction)
{
    Function absoluteValueFunction(Functions::abs(createExpressionIfPossible({5.12, "+", NAN})));
    EXPECT_TRUE(hasNonRealFiniteNumbers(absoluteValueFunction));
}

TEST(ValueCheckingHelpersTest, HasZeroWorks)
{
    EXPECT_FALSE(hasZero({1, 2, 3}));
    EXPECT_TRUE(hasZero({1, 0, 3}));
}

TEST(ValueCheckingHelpersTest, HasNegativeExponentsWithVariableWorks)
{
    Polynomial polynomial{Monomial(1, {{"a", 1}, {"b", 2}, {"c", 3}}), Monomial(1, {{"x", -4}, {"y", -5}, {"z", -6}})};

    EXPECT_FALSE(hasNegativeExponentsWithVariable(polynomial, "a"));
    EXPECT_FALSE(hasNegativeExponentsWithVariable(polynomial, "b"));
    EXPECT_FALSE(hasNegativeExponentsWithVariable(polynomial, "c"));
    EXPECT_TRUE(hasNegativeExponentsWithVariable(polynomial, "x"));
    EXPECT_TRUE(hasNegativeExponentsWithVariable(polynomial, "y"));
    EXPECT_TRUE(hasNegativeExponentsWithVariable(polynomial, "z"));
}

}

}
