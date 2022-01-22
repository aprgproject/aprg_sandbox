#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Integration/IntegrationForFiniteCalculus.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForTerm)
{
    IntegrationForFiniteCalculus integrationForX("x");
    Term termToTest(5);

    EXPECT_EQ(Term(Monomial(5, {{"x", 1}})), integrationForX.integrate(termToTest));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForConstant)
{
    IntegrationForFiniteCalculus integrationForX("x");

    EXPECT_EQ(Term(Monomial(5, {{"x", 1}})), integrationForX.integrate(Constant(5)));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForVariable)
{
    IntegrationForFiniteCalculus integrationForX("x");

    Term termToVerify1(integrationForX.integrate(Variable("x")));
    Term termToVerify2( integrationForX.integrate(Variable("y")));

    Term termToExpect1(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    Term termToExpect2(Monomial(1, {{"x", 1}, {"y", 1}}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForMonomial)
{
    IntegrationForFiniteCalculus integrationForX("x");

    Term termToVerify1(integrationForX.integrate(Monomial(1, {{"x", 1}})));
    Term termToVerify2(integrationForX.integrate(Monomial(1, {{"x", 2}})));
    Term termToVerify3(integrationForX.integrate(Monomial(2, {{"x", 1}, {"y", 3}})));

    Term termToExpect1(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    Term termToExpect2(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(1, 6), {{"x", 1}})});
    Term termToExpect3(Polynomial{Monomial(1, {{"x", 2}, {"y", 3}}), Monomial(-1, {{"x", 1}, {"y", 3}})});
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForPolynomial)
{
    IntegrationForFiniteCalculus integrationForX("x");
    Polynomial polynomial{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};

    Term termToVerify(integrationForX.integrate(polynomial));

    Term termToExpect(Polynomial
    {Monomial(7, {{"x", 4}}), Monomial(-16, {{"x", 3}}), Monomial(10, {{"x", 2}}), Monomial(7, {{"x", 1}})});
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForExpression)
{
    IntegrationForFiniteCalculus integrationForX("x");
    Term x("x");
    Expression expression1(createExpressionIfPossible({x}));
    Expression expression2(createExpressionIfPossible({5, "^", x}));
    Expression expression3(createExpressionIfPossible({5, "^", Monomial(1, {{"x", 2}})}));

    Term termToVerify(integrationForX.integrate(expression3));

    Term termToExpect1(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    Term termToExpect2(createExpressionIfPossible({5, "^", x, "/", 4}));
    EXPECT_EQ(termToExpect1, integrationForX.integrate(expression1));
    EXPECT_EQ(termToExpect2, integrationForX.integrate(expression2));
    ASSERT_TRUE(termToVerify.isConstant());
    EXPECT_TRUE(termToVerify.getConstantValueConstReference().isNotANumber());
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForFunction)
{
    IntegrationForFiniteCalculus integrationForX("x");
    Term x("x");

    Term termToVerify(integrationForX.integrate(sin(x)));

    ASSERT_TRUE(termToVerify.isConstant());
    EXPECT_TRUE(termToVerify.getConstantValueConstReference().isNotANumber());
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWithPlusCWorks)
{
    IntegrationForFiniteCalculus integrationForX("x");

    Term termToVerify(integrationForX.integrateWithPlusC(Constant(5)));

    Term termToExpect(Polynomial{Monomial(1, {{C, 1}}), Monomial(5, {{"x", 1}})});
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationForFiniteCalculusTest, IntegrateAtDefiniteValuesWorks)
{
    IntegrationForFiniteCalculus integrationForX("x");
    Term x("x");

    EXPECT_EQ(Term(9), integrationForX.integrateAtDefiniteValues(x, 4, 6));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateTermWorks)
{
    IntegrationForFiniteCalculus integrationForX("x");
    Term x("x");
    Polynomial polynomial{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};
    Expression expression(createExpressionIfPossible({5, "^", x}));

    Term termToVerify1(integrationForX.integrateTerm(5));
    Term termToVerify2(integrationForX.integrateTerm(x));
    Term termToVerify3(integrationForX.integrateTerm(Monomial(1, {{"x", 2}})));
    Term termToVerify4(integrationForX.integrateTerm(polynomial));
    Term termToVerify5(integrationForX.integrateTerm(expression));
    Term termToVerify6(integrationForX.integrateTerm(sin(x)));

    Term termToExpect1(Monomial(5, {{"x", 1}}));
    Term termToExpect2(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    Term termToExpect3(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(1, 6), {{"x", 1}})});
    Term termToExpect4(Polynomial
    {Monomial(7, {{"x", 4}}), Monomial(-16, {{"x", 3}}), Monomial(10, {{"x", 2}}), Monomial(7, {{"x", 1}})});
    Term termToExpect5(createExpressionIfPossible({5, "^", x, "/", 4}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    ASSERT_TRUE(termToVerify6.isConstant());
    EXPECT_TRUE(termToVerify6.getConstantValueConstReference().isNotANumber());
}

TEST(IntegrationForFiniteCalculusTest, IntegrateConstantWorks)
{
    IntegrationForFiniteCalculus integrationForX("x");

    EXPECT_EQ(Monomial(5, {{"x", 1}}), integrationForX.integrateConstant(Constant(5)));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateVariableWorks)
{
    IntegrationForFiniteCalculus integrationForX("x");

    Polynomial polynomialToVerify1(integrationForX.integrateVariable(Variable("x")));
    Polynomial polynomialToVerify2(integrationForX.integrateVariable(Variable("y")));

    Polynomial expectedPolynomial01
    {Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})};
    Polynomial expectedPolynomial02{Monomial(1, {{"x", 1}, {"y", 1}})};
    EXPECT_EQ(expectedPolynomial01, polynomialToVerify1);
    EXPECT_EQ(expectedPolynomial02, polynomialToVerify2);
}

TEST(IntegrationForFiniteCalculusTest, IntegrateMonomialWorks)
{
    IntegrationForFiniteCalculus integrationForX("x");
    Term x("x");

    Term termToVerify1(integrationForX.integrateMonomial(Monomial(1, {{"x", 1}})));
    Term termToVerify2(integrationForX.integrateMonomial(Monomial(1, {{"x", 2}})));
    Term termToVerify3(integrationForX.integrateMonomial(Monomial(2, {{"x", 1}, {"y", 3}})));
    Term termToVerify4(integrationForX.integrateMonomial(Monomial(1, {{"x", -3}})));
    Term termToVerify5(integrationForX.integrateMonomial(Monomial(5, {{"x", -1}, {"y", 4}})));

    Term termToExpect1(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    Term termToExpect2(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(1, 6), {{"x", 1}})});
    Term termToExpect3(Polynomial{Monomial(1, {{"x", 2}, {"y", 3}}), Monomial(-1, {{"x", 1}, {"y", 3}})});
    Term termToExpect5(createExpressionIfPossible({Monomial(5, {{"y", 4}}), "*", harmonicNumber(x)}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    ASSERT_TRUE(termToVerify4.isConstant());
    EXPECT_TRUE(termToVerify4.getConstantValueConstReference().isNotANumber());
    EXPECT_EQ(termToExpect5, termToVerify5);
}

TEST(IntegrationForFiniteCalculusTest, IntegratePolynomialWorks)
{
    IntegrationForFiniteCalculus integrationForX("x");
    Polynomial polynomial1{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};

    Term termToVerify(integrationForX.integratePolynomial(polynomial1));

    Polynomial expectedPolynomial
    {Monomial(7, {{"x", 4}}), Monomial(-16, {{"x", 3}}), Monomial(10, {{"x", 2}}), Monomial(7, {{"x", 1}})};
    Term termToExpect(expectedPolynomial);
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationForFiniteCalculusTest, IntegrateExpressionWorks)
{
    IntegrationForFiniteCalculus integrationForX("x");
    Term x("x");
    Expression expression1(createExpressionIfPossible({x}));
    Expression expression2(createExpressionIfPossible({5, "^", x}));
    Expression expression3(createExpressionIfPossible({5, "^", Monomial(1, {{"x", 2}})}));

    Term termToVerify1(integrationForX.integrateExpression(expression1));
    Term termToVerify2(integrationForX.integrateExpression(expression2));
    Term termToVerify3(integrationForX.integrateExpression(expression3));

    Term termToExpect1(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    Term termToExpect2(createExpressionIfPossible({5, "^", x, "/", 4}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    ASSERT_TRUE(termToVerify3.isConstant());
    EXPECT_TRUE(termToVerify3.getConstantValueConstReference().isNotANumber());
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksWithTermRaiseToTerm)
{
    IntegrationForFiniteCalculus integrationForX("x");
    Term n("n");
    Term x("x");
    Term termToTest1(createExpressionIfPossible({n, "^", n}));
    Term termToTest2(createExpressionIfPossible({n, "^", x}));
    Term termToTest3(createExpressionIfPossible({x, "^", n}));
    Term termToTest4(createExpressionIfPossible({x, "^", x}));

    Term termToVerify1(integrationForX.integrate(termToTest1));
    Term termToVerify2(integrationForX.integrate(termToTest2));
    Term termToVerify3(integrationForX.integrate(termToTest3));
    Term termToVerify4(integrationForX.integrate(termToTest4));

    Term nMinusOne(Polynomial{Monomial(1, {{"n", 1}}), Monomial(-1, {})});
    Term termToExpect1(createExpressionIfPossible({n, "^", n, "*", x}));
    Term termToExpect2(createExpressionIfPossible({n, "^", x, "/", nMinusOne}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_TRUE(isNotANumber(termToVerify3));
    EXPECT_TRUE(isNotANumber(termToVerify4));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateFunctionWorks)
{
    IntegrationForFiniteCalculus integrationForX("x");

    Term x("x");
    Term termToVerify(integrationForX.integrateFunction(sin(x)));
    ASSERT_TRUE(termToVerify.isConstant());
    EXPECT_TRUE(termToVerify.getConstantValueConstReference().isNotANumber());
}

}

}
