#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Integration/IntegrationForFiniteCalculus.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

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

    EXPECT_EQ(Term(Monomial(5, {{"x", 1}})), integrationForX.integrate(Term(5)));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForConstant)
{
    IntegrationForFiniteCalculus integrationForX("x");

    EXPECT_EQ(Term(Monomial(5, {{"x", 1}})), integrationForX.integrate(Constant(5)));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForVariable)
{
    IntegrationForFiniteCalculus integrationForX("x");

    Term expectedTerm(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    EXPECT_EQ(expectedTerm, integrationForX.integrate(Variable("x")));
    EXPECT_EQ(Term(Monomial(1, {{"x", 1}, {"y", 1}})), integrationForX.integrate(Variable("y")));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForMonomial)
{
    IntegrationForFiniteCalculus integrationForX("x");

    Term expectedTerm01(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    EXPECT_EQ(expectedTerm01, integrationForX.integrate(Monomial(1, {{"x", 1}})));
    Term expectedTerm02(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(1, 6), {{"x", 1}})});
    EXPECT_EQ(expectedTerm02, integrationForX.integrate(Monomial(1, {{"x", 2}})));
    Term expectedTerm03(Polynomial{Monomial(1, {{"x", 2}, {"y", 3}}), Monomial(-1, {{"x", 1}, {"y", 3}})});
    EXPECT_EQ(expectedTerm03, integrationForX.integrate(Monomial(2, {{"x", 1}, {"y", 3}})));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForPolynomial)
{
    IntegrationForFiniteCalculus integrationForX("x");
    Polynomial polynomial{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};

    Term expectedTerm(Polynomial
    {Monomial(7, {{"x", 4}}), Monomial(-16, {{"x", 3}}), Monomial(10, {{"x", 2}}), Monomial(7, {{"x", 1}})});
    EXPECT_EQ(expectedTerm, integrationForX.integrate(polynomial));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWorksForExpression)
{
    IntegrationForFiniteCalculus integrationForX("x");
    Term x("x");
    Expression expression01(createExpressionIfPossible({x}));
    Expression expression02(createExpressionIfPossible({Term(5), Term("^"), Term("x")}));
    Expression expression03(createExpressionIfPossible({Term(5), Term("^"), Term(Monomial(1, {{"x", 2}}))}));

    Term expectedTerm01(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    Term expectedTerm02(createExpressionIfPossible({Term(5), Term("^"), Term("x"), Term("/"), Term(4)}));
    EXPECT_EQ(expectedTerm01, integrationForX.integrate(expression01));
    EXPECT_EQ(expectedTerm02, integrationForX.integrate(expression02));
    Term termToVerify(integrationForX.integrate(expression03));
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

    Term expectedTerm(Polynomial{Monomial(1, {{"C", 1}}), Monomial(5, {{"x", 1}})});
    EXPECT_EQ(expectedTerm, integrationForX.integrateWithPlusC(Constant(5)));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateWithDefiniteValuesWorks)
{
    IntegrationForFiniteCalculus integrationForX("x");

    EXPECT_EQ(Term(9), integrationForX.integrateWithDefiniteValues(Term("x"), 4, 6));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateTermWorks)
{
    IntegrationForFiniteCalculus integrationForX("x");
    Polynomial polynomial{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};
    Expression expression(createExpressionIfPossible({Term(5), Term("^"), Term("x")}));

    Term x("x");
    Term expectedTerm01(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    Term expectedTerm02(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(1, 6), {{"x", 1}})});
    Term expectedTerm03(Polynomial
    {Monomial(7, {{"x", 4}}), Monomial(-16, {{"x", 3}}), Monomial(10, {{"x", 2}}), Monomial(7, {{"x", 1}})});
    Term expectedTerm04(createExpressionIfPossible({Term(5), Term("^"), Term("x"), Term("/"), Term(4)}));
    EXPECT_EQ(Term(Monomial(5, {{"x", 1}})), integrationForX.integrateTerm(Term(5)));
    EXPECT_EQ(expectedTerm01, integrationForX.integrateTerm(Term("x")));
    EXPECT_EQ(expectedTerm02, integrationForX.integrateTerm(Monomial(1, {{"x", 2}})));
    EXPECT_EQ(expectedTerm03, integrationForX.integrateTerm(Term(polynomial)));
    EXPECT_EQ(expectedTerm04, integrationForX.integrateTerm(Term(expression)));
    Term termToVerify(integrationForX.integrateTerm(Term(sin(x))));
    ASSERT_TRUE(termToVerify.isConstant());
    EXPECT_TRUE(termToVerify.getConstantValueConstReference().isNotANumber());
}

TEST(IntegrationForFiniteCalculusTest, IntegrateConstantWorks)
{
    IntegrationForFiniteCalculus integrationForX("x");

    EXPECT_EQ(Monomial(5, {{"x", 1}}), integrationForX.integrateConstant(Constant(5)));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateVariableWorks)
{
    IntegrationForFiniteCalculus integrationForX("x");

    Polynomial expectedPolynomial01
    {Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})};
    EXPECT_EQ(expectedPolynomial01, integrationForX.integrateVariable(Variable("x")));
    Polynomial expectedPolynomial02{Monomial(1, {{"x", 1}, {"y", 1}})};
    EXPECT_EQ(expectedPolynomial02, integrationForX.integrateVariable(Variable("y")));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateMonomialWorks)
{
    IntegrationForFiniteCalculus integrationForX("x");

    Term expectedTerm01(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    EXPECT_EQ(expectedTerm01, integrationForX.integrateMonomial(Monomial(1, {{"x", 1}})));
    Term expectedTerm02(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 3), {{"x", 3}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(1, 6), {{"x", 1}})});
    EXPECT_EQ(expectedTerm02, integrationForX.integrateMonomial(Monomial(1, {{"x", 2}})));
    Term expectedTerm03(Polynomial{Monomial(1, {{"x", 2}, {"y", 3}}), Monomial(-1, {{"x", 1}, {"y", 3}})});
    EXPECT_EQ(expectedTerm03, integrationForX.integrateMonomial(Monomial(2, {{"x", 1}, {"y", 3}})));
}

TEST(IntegrationForFiniteCalculusTest, IntegratePolynomialWorks)
{
    IntegrationForFiniteCalculus integrationForX("x");
    Polynomial polynomial{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};

    Polynomial expectedPolynomial
    {Monomial(7, {{"x", 4}}), Monomial(-16, {{"x", 3}}), Monomial(10, {{"x", 2}}), Monomial(7, {{"x", 1}})};
    Term expectedTerm(expectedPolynomial);
    EXPECT_EQ(expectedTerm, integrationForX.integratePolynomial(polynomial));
}

TEST(IntegrationForFiniteCalculusTest, IntegrateExpressionWorks)
{
    IntegrationForFiniteCalculus integrationForX("x");
    Term x("x");
    Expression expression01(createExpressionIfPossible({x}));
    Expression expression02(createExpressionIfPossible({Term(5), Term("^"), Term("x")}));
    Expression expression03(createExpressionIfPossible({Term(5), Term("^"), Term(Monomial(1, {{"x", 2}}))}));

    Term expectedTerm01(Polynomial
    {Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}),
     Monomial(AlbaNumber::createFraction(-1, 2), {{"x", 1}})});
    Term expectedTerm02(createExpressionIfPossible({Term(5), Term("^"), Term("x"), Term("/"), Term(4)}));
    EXPECT_EQ(expectedTerm01, integrationForX.integrateExpression(expression01));
    EXPECT_EQ(expectedTerm02, integrationForX.integrateExpression(expression02));
    Term termToVerify(integrationForX.integrateExpression(expression03));
    ASSERT_TRUE(termToVerify.isConstant());
    EXPECT_TRUE(termToVerify.getConstantValueConstReference().isNotANumber());
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
