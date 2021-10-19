#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(IntegrationTest, IntegrateWorksForTerm)
{
    Integration integrationForX("x");

    EXPECT_EQ(Term(Monomial(5, {{"x", 1}})), integrationForX.integrate(Term(5)));
}

TEST(IntegrationTest, IntegrateWorksForConstant)
{
    Integration integrationForX("x");

    EXPECT_EQ(Term(Monomial(5, {{"x", 1}})), integrationForX.integrate(Constant(5)));
}

TEST(IntegrationTest, IntegrateWorksForVariable)
{
    Integration integrationForX("x");

    EXPECT_EQ(Term(Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}})), integrationForX.integrate(Variable("x")));
    EXPECT_EQ(Term(Monomial(1, {{"x", 1}, {"y", 1}})), integrationForX.integrate(Variable("y")));
}

TEST(IntegrationTest, IntegrateWorksForMonomial)
{
    Integration integrationForX("x");

    EXPECT_EQ(Term(Monomial(1, {{"x", 2}, {"y", 3}})), integrationForX.integrate(Monomial(2, {{"x", 1}, {"y", 3}})));
    EXPECT_EQ(Term(Monomial(2, {{"x", 1}, {"y", 4}})), integrationForX.integrate(Monomial(2, {{"y", 4}})));
    EXPECT_EQ(Term(Monomial(3, {{"x", 1}, {"y", 4}, {"z", 5}})), integrationForX.integrate(Monomial(3, {{"y", 4}, {"z", 5}})));
}

TEST(IntegrationTest, IntegrateWorksForPolynomial)
{
    Integration integrationForX("x");
    Polynomial polynomial{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};

    Polynomial expectedPolynomial{Monomial(7, {{"x", 4}}), Monomial(-2, {{"x", 3}}), Monomial(8, {{"x", 1}})};
    Term expectedTerm(expectedPolynomial);
    EXPECT_EQ(expectedTerm, integrationForX.integrate(polynomial));
}

TEST(IntegrationTest, IntegrateWorksForExpression)
{
    Integration integrationForX("x");
    Term x("x");
    Expression expression01(createExpressionIfPossible({x}));
    Expression expression02(createExpressionIfPossible(
    {Term(Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}})),
     Term("*"),
     Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"x", -1}})})}));

    Term expectedTerm01(Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}));
    Term expectedTerm02(Polynomial
    {Monomial(AlbaNumber::createFraction(2, 5), {{"x", AlbaNumber::createFraction(5, 2)}}),
     Monomial(2, {{"x", AlbaNumber::createFraction(1, 2)}})});
    EXPECT_EQ(expectedTerm01, integrationForX.integrate(expression01));
    EXPECT_EQ(expectedTerm02, integrationForX.integrate(expression02));
}

TEST(IntegrationTest, IntegrateWorksForFunction)
{
    Integration integrationForX("x");

    Term x("x");
    Term expectedTerm(createExpressionIfPossible({Term(-1), Term("*"), cos(x)}));
    EXPECT_EQ(expectedTerm, integrationForX.integrate(sin(x)));
}

TEST(IntegrationTest, IntegrateWithPlusCWorks)
{
    Integration integrationForX("x");

    Term expectedTerm(Polynomial{Monomial(1, {{"C", 1}}), Monomial(5, {{"x", 1}})});
    EXPECT_EQ(expectedTerm, integrationForX.integrateWithPlusC(Constant(5)));
}

TEST(IntegrationTest, IntegrateWithDefiniteValuesWorks)
{
    Integration integrationForX("x");

    EXPECT_EQ(Term(10), integrationForX.integrateWithDefiniteValues(Term("x"), 4, 6));
}

TEST(IntegrationTest, IntegrateTermWorks)
{
    Integration integrationForX("x");    Polynomial polynomial{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};
    Expression expression(createExpressionIfPossible(
    {Term(Polynomial{Monomial(3, {{"x", 1}}), Monomial(4, {})}),
     Term("^"),     Term(AlbaNumber::createFraction(1, 2))}));

    Polynomial expectedPolynomial{Monomial(7, {{"x", 4}}), Monomial(-2, {{"x", 3}}), Monomial(8, {{"x", 1}})};
    Term expectedTerm(createExpressionIfPossible(
    {Term(2),
     Term("*"),
     Term(Polynomial{Monomial(3, {{"x", 1}}), Monomial(4, {})}),
     Term("^"),
     Term(AlbaNumber::createFraction(3, 2)),
     Term("/"),
     Term(9)}));
    EXPECT_EQ(Term(Monomial(5, {{"x", 1}})), integrationForX.integrateTerm(Term(5)));
    EXPECT_EQ(Term(Monomial(5, {{"x", 1}})), integrationForX.integrateTerm(Term(5)));
    EXPECT_EQ(Term(Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}})), integrationForX.integrateTerm(Term("x")));
    EXPECT_EQ(Term(Monomial(1, {{"x", 2}, {"y", 3}})), integrationForX.integrateTerm(Monomial(2, {{"x", 1}, {"y", 3}})));
    EXPECT_EQ(Term(expectedPolynomial), integrationForX.integrateTerm(Term(polynomial)));
    EXPECT_EQ(expectedTerm, integrationForX.integrateTerm(expression));
}

TEST(IntegrationTest, IntegrateConstantWorks)
{
    Integration integrationForX("x");

    EXPECT_EQ(Monomial(5, {{"x", 1}}), integrationForX.integrateConstant(Constant(5)));
}

TEST(IntegrationTest, IntegrateVariableWorks)
{
    Integration integrationForX("x");

    EXPECT_EQ(Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}), integrationForX.integrateVariable(Variable("x")));
    EXPECT_EQ(Monomial(1, {{"x", 1}, {"y", 1}}), integrationForX.integrateVariable(Variable("y")));
}

TEST(IntegrationTest, IntegrateMonomialWorks)
{
    Integration integrationForX("x");

    EXPECT_EQ(Monomial(1, {{"x", 2}, {"y", 3}}), integrationForX.integrateMonomial(Monomial(2, {{"x", 1}, {"y", 3}})));
    EXPECT_EQ(Monomial(2, {{"x", 1}, {"y", 4}}), integrationForX.integrateMonomial(Monomial(2, {{"y", 4}})));
    EXPECT_EQ(Monomial(3, {{"x", 1}, {"y", 4}, {"z", 5}}), integrationForX.integrateMonomial(Monomial(3, {{"y", 4}, {"z", 5}})));
}

TEST(IntegrationTest, IntegratePolynomialWorks)
{
    Integration integrationForX("x");
    Polynomial polynomial1{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};
    Polynomial polynomial2{Monomial(5, {{"x", 4}}), Monomial(-8, {{"x", 3}}), Monomial(9, {{"x", 2}}), Monomial(-2, {{"x", 1}}), Monomial(7, {})};

    Polynomial expectedPolynomial1{Monomial(7, {{"x", 4}}), Monomial(-2, {{"x", 3}}), Monomial(8, {{"x", 1}})};
    Polynomial expectedPolynomial2{Monomial(1, {{"x", 5}}), Monomial(-2, {{"x", 4}}), Monomial(3, {{"x", 3}}), Monomial(-1, {{"x", 2}}), Monomial(7, {{"x", 1}})};
    EXPECT_EQ(expectedPolynomial1, integrationForX.integratePolynomial(polynomial1));
    EXPECT_EQ(expectedPolynomial2, integrationForX.integratePolynomial(polynomial2));
}

TEST(IntegrationTest, IntegrateExpressionWorks)
{
    Integration integrationForX("x");
    Term x("x");
    Expression expression01(createExpressionIfPossible({x}));
    Expression expression02(createExpressionIfPossible(
    {Term(Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}})),
     Term("*"),
     Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"x", -1}})})}));
    Expression expression03(createExpressionIfPossible(
    {Term(Polynomial{Monomial(5, {{"x", 2}}), Monomial(7, {})}),
     Term("/"),
     Term(Monomial(1, {{"x", AlbaNumber::createFraction(4, 3)}}))}));
    Expression expression04(createExpressionIfPossible(
    {Term(Polynomial{Monomial(3, {{"x", 1}}), Monomial(4, {})}),
     Term("^"),
     Term(AlbaNumber::createFraction(1, 2))}));
    Expression expression05(createExpressionIfPossible(
    {x, Term("*"), Term(cos(Term(Monomial(1, {{"x", 2}}))))}));

    Term expectedTerm01(Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}));
    Term expectedTerm02(Polynomial
    {Monomial(AlbaNumber::createFraction(2, 5), {{"x", AlbaNumber::createFraction(5, 2)}}),
     Monomial(2, {{"x", AlbaNumber::createFraction(1, 2)}})});
    Term expectedTerm03(Polynomial
    {Monomial(3, {{"x", AlbaNumber::createFraction(5, 3)}}),
     Monomial(-21, {{"x", AlbaNumber::createFraction(-1, 3)}})});
    Term expectedTerm04(createExpressionIfPossible(
    {Term(2),
     Term("*"),
     Term(Polynomial{Monomial(3, {{"x", 1}}), Monomial(4, {})}),
     Term("^"),
     Term(AlbaNumber::createFraction(3, 2)),
     Term("/"),
     Term(9)}));
    Term expectedTerm05(createExpressionIfPossible(
    {Term(sin(Term(Monomial(1, {{"x", 2}})))), Term("/"), Term(2)}));
    EXPECT_EQ(expectedTerm01, integrationForX.integrateExpression(expression01));
    EXPECT_EQ(expectedTerm02, integrationForX.integrateExpression(expression02));
    EXPECT_EQ(expectedTerm03, integrationForX.integrateExpression(expression03));
    EXPECT_EQ(expectedTerm04, integrationForX.integrateExpression(expression04));
    EXPECT_EQ(expectedTerm05, integrationForX.integrateExpression(expression05));
}

TEST(IntegrationTest, IntegrateWorksUsingChainRuleUsingExample1)
{
    Integration integrationForX("x");
    Term numerator(Monomial(4, {{"x", 2}}));
    Term denominatorPolynomial(Polynomial{Monomial(1, {}), Monomial(-8, {{"x", 3}})});
    Term denominator(createExpressionIfPossible({denominatorPolynomial, Term("^"), Term(4)}));
    Term termToTest(createExpressionIfPossible({numerator, Term("/"), denominator}));

    Term expectedTerm(createExpressionIfPossible(
    {Term(-1), Term("/"), Term(18),
     Term("/"), Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(-1, {})}), Term("^"), Term(3),
     Term("/"), Term(Polynomial{Monomial(4, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})}),  Term("^"), Term(3)}));
    EXPECT_EQ(expectedTerm, integrationForX.integrate(termToTest));
}

TEST(IntegrationTest, IntegrateWorksUsingSubstitutionUsingExample1)
{
    Integration integrationForX("x");
    Term squareRootTerm(createExpressionIfPossible(
    {Term(Polynomial{Monomial(1, {}), Monomial(1, {{"x", 1}})}), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term termToTest(createExpressionIfPossible({Term(Monomial(1, {{"x", 2}})), Term("*"), squareRootTerm}));

    Term xPlusOne(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term firstPart(createExpressionIfPossible({Term(2), Term("*"), xPlusOne, Term("^"), Term(AlbaNumber::createFraction(7, 2)), Term("/"), Term(7)}));
    Term secondPart(createExpressionIfPossible({Term(4), Term("*"), xPlusOne, Term("^"), Term(AlbaNumber::createFraction(5, 2)), Term("/"), Term(5)}));
    Term thirdPart(createExpressionIfPossible({Term(2), Term("*"), xPlusOne, Term("^"), Term(AlbaNumber::createFraction(3, 2)), Term("/"), Term(3)}));
    Term expectedTerm(createExpressionIfPossible({firstPart, Term("-"), secondPart, Term("+"), thirdPart}));
    EXPECT_EQ(expectedTerm, integrationForX.integrate(termToTest));
}

TEST(IntegrationTest, IntegrateWorksUsingSubstitutionUsingExample2)
{
    Integration integrationForX("x");
    Term squareRootOfX(Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}));
    Term termToTest(createExpressionIfPossible({Term(sin(squareRootOfX)), Term("/"), squareRootOfX}));

    Term expectedTerm(createExpressionIfPossible({Term(-2), Term("*"), Term(cos(squareRootOfX))}));
    EXPECT_EQ(expectedTerm, integrationForX.integrate(termToTest));
}

TEST(IntegrationTest, IntegrateWorksUsingSubstitutionUsingExample3)
{
    Integration integrationForX("x");
    Term x("x");
    Term termToTest(createExpressionIfPossible({Term(tan(x)), Term("*"), Term(sec(x)), Term("^"), Term(2)}));

    Term expectedTerm(createExpressionIfPossible({Term(sec(x)), Term("^"), Term(2), Term("/"), Term(2)}));
    EXPECT_EQ(expectedTerm, integrationForX.integrate(termToTest));
}

TEST(IntegrationTest, IntegrateFunctionWorks)
{
    Integration integrationForX("x");

    Term x("x");
    Term expectedTerm01(createExpressionIfPossible({Term(-1), Term("*"), cos(x)}));
    Term expectedTerm02(createExpressionIfPossible({Term(-1), Term("*"), cos(Monomial(5, {{"x", 1}})), Term("/"), Term(5)}));
    EXPECT_EQ(expectedTerm01, integrationForX.integrateFunction(sin(x)));
    EXPECT_EQ(expectedTerm02, integrationForX.integrateFunction(sin(Term(Monomial(5, {{"x", 1}})))));
}

TEST(IntegrationTest, IntegrateWorksForTrigonometricFunctions)
{
    Integration integrationForX("x");
    Term x("x");
    Term term01(sin(x));
    Term term02(cos(x));
    Term term03(createExpressionIfPossible({sec(x), Term("^"), Term(2)}));
    Term term04(createExpressionIfPossible({csc(x), Term("^"), Term(2)}));
    Term term05(createExpressionIfPossible({sec(x), Term("*"), tan(x)}));
    Term term06(createExpressionIfPossible({csc(x), Term("*"), cot(x)}));

    Term expectedTerm01(createExpressionIfPossible({Term(-1), Term("*"), cos(x)}));
    Term expectedTerm02(sin(x));
    Term expectedTerm03(tan(x));
    Term expectedTerm04(createExpressionIfPossible({Term(-1), Term("*"), cot(x)}));
    EXPECT_EQ(expectedTerm01, integrationForX.integrate(term01));
    EXPECT_EQ(expectedTerm02, integrationForX.integrate(term02));
    EXPECT_EQ(expectedTerm03, integrationForX.integrate(term03));
    EXPECT_EQ(expectedTerm04, integrationForX.integrate(term04));
}

}

}
