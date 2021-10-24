#include <Algebra/Integration/Integration.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Simplification/SimplificationOfExpression.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Algebra/Utilities/KnownNames.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace alba::algebra::Simplification;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(IntegrationTest, IntegrateWorksForTerm)
{
    Integration integrationForX("x");
    Polynomial polynomial{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};
    Expression expression(createExpressionIfPossible(
    {Term(Polynomial{Monomial(3, {{"x", 1}}), Monomial(4, {})}),
     Term("^"),
     Term(AlbaNumber::createFraction(1, 2))}));

    Term termToVerify1(integrationForX.integrate(Term(5)));
    Term termToVerify2(integrationForX.integrate(Term(5)));
    Term termToVerify3(integrationForX.integrate(Term("x")));
    Term termToVerify4(integrationForX.integrate(Monomial(2, {{"x", 1}, {"y", 3}})));
    Term termToVerify5(integrationForX.integrate(Term(polynomial)));
    Term termToVerify6(integrationForX.integrate(expression));

    Term termToExpect1(Monomial(5, {{"x", 1}}));
    Term termToExpect2(Monomial(5, {{"x", 1}}));
    Term termToExpect3(Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}));
    Term termToExpect4(Monomial(1, {{"x", 2}, {"y", 3}}));
    Term termToExpect5(Polynomial{Monomial(7, {{"x", 4}}), Monomial(-2, {{"x", 3}}), Monomial(8, {{"x", 1}})});
    Term termToExpect6(createExpressionIfPossible(
    {Term(2),
     Term("*"),
     Term(Polynomial{Monomial(3, {{"x", 1}}), Monomial(4, {})}),
     Term("^"),
     Term(AlbaNumber::createFraction(3, 2)),
     Term("/"),
     Term(9)}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
}

TEST(IntegrationTest, IntegrateWorksForConstant)
{
    Integration integrationForX("x");

    EXPECT_EQ(Term(Monomial(5, {{"x", 1}})), integrationForX.integrate(Constant(5)));
}

TEST(IntegrationTest, IntegrateWorksForVariable)
{
    Integration integrationForX("x");

    Term termToVerify1(integrationForX.integrate(Variable("x")));
    Term termToVerify2(integrationForX.integrate(Variable("y")));

    Term termToExpect1(Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}));
    Term termToExpect2(Monomial(1, {{"x", 1}, {"y", 1}}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
}

TEST(IntegrationTest, IntegrateWorksForMonomial)
{
    Integration integrationForX("x");

    Term termToVerify1(integrationForX.integrate(Monomial(2, {{"x", 1}, {"y", 3}})));
    Term termToVerify2(integrationForX.integrate(Monomial(2, {{"y", 4}})));
    Term termToVerify3(integrationForX.integrate(Monomial(3, {{"y", 4}, {"z", 5}})));
    Term termToVerify4(integrationForX.integrate(Monomial(3, {{"x", -1}, {"z", 5}})));

    Term termToExpect1(Monomial(1, {{"x", 2}, {"y", 3}}));
    Term termToExpect2(Monomial(2, {{"x", 1}, {"y", 4}}));
    Term termToExpect3(Monomial(3, {{"x", 1}, {"y", 4}, {"z", 5}}));
    Term termToExpect4(createExpressionIfPossible(
    {Term(Monomial(3, {{"z", 5}})),
     Term("*"),
     Term(ln(Term(abs(Term("x")))))}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
}

TEST(IntegrationTest, IntegrateWorksForPolynomial)
{
    Integration integrationForX("x");
    Polynomial polynomial{Monomial(-2, {{"x", 1}}), Monomial(7, {}), Monomial(1, {{"x", -1}})};

    Term termToVerify(integrationForX.integratePolynomial(polynomial));

    Term termToExpect(createExpressionIfPossible(
    {Term(Polynomial{Monomial(-1, {{"x", 2}}), Monomial(7, {{"x", 1}})}),
     Term("+"),
     Term(ln(Term(abs(Term("x")))))}));
    EXPECT_EQ(termToExpect, termToVerify);
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

    Term termToVerify1(integrationForX.integrate(expression01));
    Term termToVerify2(integrationForX.integrate(expression02));

    Term termToExpect1(Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}));
    Term termToExpect2(Polynomial
    {Monomial(AlbaNumber::createFraction(2, 5), {{"x", AlbaNumber::createFraction(5, 2)}}),
     Monomial(2, {{"x", AlbaNumber::createFraction(1, 2)}})});
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
}

TEST(IntegrationTest, IntegrateWorksForFunction)
{
    Integration integrationForX("x");
    Term x("x");

    Term termToVerify(integrationForX.integrate(sin(x)));

    Term termToExpect(createExpressionIfPossible({Term(-1), Term("*"), cos(x)}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationTest, IntegrateWithPlusCWorks)
{
    Integration integrationForX("x");

    Term termToVerify(integrationForX.integrateWithPlusC(Constant(5)));

    Term termToExpect(Polynomial{Monomial(1, {{C, 1}}), Monomial(5, {{"x", 1}})});
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationTest, IntegrateWithDefiniteValuesWorks)
{
    Integration integrationForX("x");

    EXPECT_EQ(Term(10), integrationForX.integrateWithDefiniteValues(Term("x"), 4, 6));
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

    Term termToVerify1(integrationForX.integrateMonomial(Monomial(2, {{"x", 1}, {"y", 3}})));
    Term termToVerify2(integrationForX.integrateMonomial(Monomial(2, {{"y", 4}})));
    Term termToVerify3(integrationForX.integrateMonomial(Monomial(3, {{"y", 4}, {"z", 5}})));
    Term termToVerify4(integrationForX.integrateMonomial(Monomial(3, {{"x", -1}, {"z", 5}})));

    Term termToExpect1(Monomial(1, {{"x", 2}, {"y", 3}}));
    Term termToExpect2(Monomial(2, {{"x", 1}, {"y", 4}}));
    Term termToExpect3(Monomial(3, {{"x", 1}, {"y", 4}, {"z", 5}}));
    Term termToExpect4(createExpressionIfPossible(
    {Term(Monomial(3, {{"z", 5}})),
     Term("*"),
     Term(ln(Term(abs(Term("x")))))}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
}

TEST(IntegrationTest, IntegratePolynomialWorks)
{
    Integration integrationForX("x");
    Polynomial polynomial1{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};
    Polynomial polynomial2{Monomial(5, {{"x", 4}}), Monomial(-8, {{"x", 3}}), Monomial(9, {{"x", 2}}), Monomial(-2, {{"x", 1}}), Monomial(7, {})};
    Polynomial polynomial3{Monomial(-2, {{"x", 1}}), Monomial(7, {}), Monomial(1, {{"x", -1}})};

    Term termToVerify1(integrationForX.integratePolynomial(polynomial1));
    Term termToVerify2(integrationForX.integratePolynomial(polynomial2));
    Term termToVerify3(integrationForX.integratePolynomial(polynomial3));

    Term termToExpect1(Polynomial
    {Monomial(7, {{"x", 4}}),
     Monomial(-2, {{"x", 3}}),
     Monomial(8, {{"x", 1}})});
    Term termToExpect2(Polynomial
    {Monomial(1, {{"x", 5}}),
     Monomial(-2, {{"x", 4}}),
     Monomial(3, {{"x", 3}}),
     Monomial(-1, {{"x", 2}}),
     Monomial(7, {{"x", 1}})});
    Term termToExpect3(createExpressionIfPossible(
    {Term(Polynomial{Monomial(-1, {{"x", 2}}), Monomial(7, {{"x", 1}})}),
     Term("+"),
     Term(ln(Term(abs(Term("x")))))}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(IntegrationTest, IntegrateExpressionWorks)
{
    Integration integrationForX("x");
    Term x("x");
    Term twoX(Monomial(2, {{"x", 1}}));
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
    Expression expression06(createExpressionIfPossible({twoX, Term("^"), Term(4)}));
    Expression expression07(createExpressionIfPossible({Term(4), Term("^"), twoX}));
    Expression expression08(createExpressionIfPossible({twoX, Term("^"), twoX}));

    Term termToVerify1(integrationForX.integrateExpression(expression01));
    Term termToVerify2(integrationForX.integrateExpression(expression02));
    Term termToVerify3(integrationForX.integrateExpression(expression03));
    Term termToVerify4(integrationForX.integrateExpression(expression04));
    Term termToVerify5(integrationForX.integrateExpression(expression05));
    Term termToVerify6(integrationForX.integrateExpression(expression06));
    Term termToVerify7(integrationForX.integrateExpression(expression07));
    Term termToVerify8(integrationForX.integrateExpression(expression08));

    Term termToExpect1(Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}));
    Term termToExpect2(Polynomial
    {Monomial(AlbaNumber::createFraction(2, 5), {{"x", AlbaNumber::createFraction(5, 2)}}),
     Monomial(2, {{"x", AlbaNumber::createFraction(1, 2)}})});
    Term termToExpect3(Polynomial
    {Monomial(3, {{"x", AlbaNumber::createFraction(5, 3)}}),
     Monomial(-21, {{"x", AlbaNumber::createFraction(-1, 3)}})});
    Term termToExpect4(createExpressionIfPossible(
    {Term(2), Term("*"), Term(Polynomial{Monomial(3, {{"x", 1}}), Monomial(4, {})}), Term("^"), Term(AlbaNumber::createFraction(3, 2)), Term("/"), Term(9)}));
    Term termToExpect5(createExpressionIfPossible(
    {Term(sin(Term(Monomial(1, {{"x", 2}})))), Term("/"), Term(2)}));
    Term termToExpect6(Monomial(AlbaNumber::createFraction(16, 5), {{"x", 5}}));
    Term termToExpect7(createExpressionIfPossible(
    {Term(4), Term("^"), Term("x"), Term("^"), Term(2), Term("/"), Term(2.772588722239781)}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
    EXPECT_EQ(termToExpect7, termToVerify7);
    EXPECT_TRUE(isNotANumber(termToVerify8));
}

TEST(IntegrationTest, IntegrateFunctionWorksWithDifferentFunctions)
{
    Integration integrationForX("x");
    Term x("x");

    Term termToVerify1(integrationForX.integrateFunction(abs(x)));
    Term termToVerify2(integrationForX.integrateFunction(sin(x)));
    Term termToVerify3(integrationForX.integrateFunction(cos(x)));
    Term termToVerify4(integrationForX.integrateFunction(tan(x)));
    Term termToVerify5(integrationForX.integrateFunction(csc(x)));
    Term termToVerify6(integrationForX.integrateFunction(sec(x)));
    Term termToVerify7(integrationForX.integrateFunction(cot(x)));

    Term termToExpect1(createExpressionIfPossible({Term(-1), Term("*"), cos(x)}));
    Term termToExpect2(sin(x));
    Term termToExpect3(ln(Term(abs(Term(sec(x))))));
    Term termToExpect4(ln(Term(abs(Term(csc(x))-Term(cot(x))))));
    Term termToExpect5(ln(Term(abs(Term(sec(x))+Term(tan(x))))));
    Term termToExpect7(ln(Term(abs(Term(sin(x))))));
    EXPECT_TRUE(isNotANumber(termToVerify1));
    EXPECT_EQ(termToExpect1, termToVerify2);
    EXPECT_EQ(termToExpect2, termToVerify3);
    EXPECT_EQ(termToExpect3, termToVerify4);
    EXPECT_EQ(termToExpect4, termToVerify5);
    EXPECT_EQ(termToExpect5, termToVerify6);
    EXPECT_EQ(termToExpect7, termToVerify7);
}

TEST(IntegrationTest, IntegrateFunctionWorksWithChainRule)
{
    Integration integrationForX("x");

    Term x("x");
    Term termToExpect1(createExpressionIfPossible({Term(-1), Term("*"), cos(Monomial(5, {{"x", 1}})), Term("/"), Term(5)}));
    EXPECT_EQ(termToExpect1, integrationForX.integrateFunction(sin(Term(Monomial(5, {{"x", 1}})))));
}

TEST(IntegrationTest, IntegrateWorksForCombinationOfRecognizedTrigonometicFunctions)
{
    Integration integrationForX("x");
    Term x("x");
    Term term1(sin(x));
    Term term2(cos(x));
    Term term3(createExpressionIfPossible({sec(x), Term("^"), Term(2)}));
    Term term4(createExpressionIfPossible({csc(x), Term("^"), Term(2)}));
    Term term5(createExpressionIfPossible({sec(x), Term("*"), tan(x)}));
    Term term6(createExpressionIfPossible({csc(x), Term("*"), cot(x)}));

    Term termToVerify1(integrationForX.integrate(term1));
    Term termToVerify2(integrationForX.integrate(term2));
    Term termToVerify3(integrationForX.integrate(term3));
    Term termToVerify4(integrationForX.integrate(term4));
    Term termToVerify5(integrationForX.integrate(term5));
    Term termToVerify6(integrationForX.integrate(term6));

    Term termToExpect1(createExpressionIfPossible({Term(-1), Term("*"), cos(x)}));
    Term termToExpect2(sin(x));
    Term termToExpect3(tan(x));
    Term termToExpect4(createExpressionIfPossible({Term(-1), Term("*"), cot(x)}));
    Term termToExpect5(sec(x));
    Term termToExpect6(createExpressionIfPossible({Term(-1), Term("*"), csc(x)}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
}

TEST(IntegrationTest, IntegrateWorksForCombinationOfRecognizedHyperbolicFunctions)
{
    Integration integrationForX("x");
    Term x("x");
    Term term1(sinh(x));
    Term term2(cosh(x));
    Term term3(createExpressionIfPossible({sech(x), Term("^"), Term(2)}));
    Term term4(createExpressionIfPossible({csch(x), Term("^"), Term(2)}));
    Term term5(createExpressionIfPossible({sech(x), Term("*"), tanh(x)}));
    Term term6(createExpressionIfPossible({csch(x), Term("*"), coth(x)}));

    Term termToVerify1(integrationForX.integrate(term1));
    Term termToVerify2(integrationForX.integrate(term2));
    Term termToVerify3(integrationForX.integrate(term3));
    Term termToVerify4(integrationForX.integrate(term4));
    Term termToVerify5(integrationForX.integrate(term5));
    Term termToVerify6(integrationForX.integrate(term6));

    Term termToExpect1(cosh(x));
    Term termToExpect2(sinh(x));
    Term termToExpect3(tanh(x));
    Term termToExpect4(createExpressionIfPossible({Term(-1), Term("*"), coth(x)}));
    Term termToExpect5(createExpressionIfPossible({Term(-1), Term("*"), sech(x)}));
    Term termToExpect6(createExpressionIfPossible({Term(-1), Term("*"), csch(x)}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
}

TEST(IntegrationTest, IntegrateWorksUsingChainRuleInReverseUsingExample1)
{
    Integration integrationForX("x");
    Term numerator(Monomial(4, {{"x", 2}}));
    Term denominatorPolynomial(Polynomial{Monomial(1, {}), Monomial(-8, {{"x", 3}})});
    Term denominator(createExpressionIfPossible({denominatorPolynomial, Term("^"), Term(4)}));
    Term termToTest(createExpressionIfPossible({numerator, Term("/"), denominator}));

    Term termToVerify(integrationForX.integrate(termToTest));

    Term termToExpect(createExpressionIfPossible(
    {Term(-1), Term("/"), Term(18),
     Term("/"), Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(-1, {})}), Term("^"), Term(3),
     Term("/"), Term(Polynomial{Monomial(4, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})}),  Term("^"), Term(3)}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationTest, IntegrateWorksUsingChainRuleInReverseUsingExample2)
{
    Integration integrationForX("x");
    Term squareRootOfX(Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}));
    Term termToTest(createExpressionIfPossible({Term(sin(squareRootOfX)), Term("/"), squareRootOfX}));

    Term termToVerify(integrationForX.integrate(termToTest));

    Term termToExpect(createExpressionIfPossible({Term(-2), Term("*"), Term(cos(squareRootOfX))}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationTest, IntegrateWorksUsingChainRuleInReverseUsingExample3)
{
    Integration integrationForX("x");
    Term partOne(Monomial(2, {{"x", 2}}));
    Term partTwo(Polynomial{Monomial(1, {{"x", 3}}), Monomial(1, {})});
    Term partThree(createExpressionIfPossible({partTwo, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term termToTest(createExpressionIfPossible({partThree, Term("*"), partOne}));

    Term termToVerify(integrationForX.integrate(termToTest));

    Term partOneOfExpectedTerm(createExpressionIfPossible({partTwo, Term("^"), Term(AlbaNumber::createFraction(3, 2))}));
    Term termToExpect(createExpressionIfPossible({Term(4), Term("*"), Term(partOneOfExpectedTerm), Term("/"), Term(9)}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationTest, IntegrateWorksUsingChainRuleInReverseUsingExample4)
{
    Integration integrationForX("x");
    Term x("x");
    Term termToTest(createExpressionIfPossible({Term(sin(x)), Term("^"), Term(3), Term("*"), Term(cos(x))}));

    Term termToVerify(integrationForX.integrate(termToTest));

    Term termToExpect(createExpressionIfPossible({Term(sin(x)), Term("^"), Term(4), Term("/"), Term(4)}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationTest, IntegrateWorksUsingChainRuleInReverseUsingExample5)
{
    Integration integrationForX("x");
    Term x("x");
    Term termToTest(createExpressionIfPossible({Term(3), Term("^"), Term(sin(x)), Term("*"), Term(cos(x))}));

    Term termToVerify(integrationForX.integrate(termToTest));

    Term termToExpect(createExpressionIfPossible({Term(0.9102392266268373), Term("*"), Term(3), Term("^"), Term(sin(x))}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationTest, IntegrateWorksUsingPartialFractionsUsingExample1)
{
    Integration integrationForX("x");
    Term numerator(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-1, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 5}}), Monomial(-6, {{"x", 4}}), Monomial(12, {{"x", 3}}), Monomial(-8, {{"x", 2}})});
    Term termToTest(createExpressionIfPossible({numerator, Term("/"), denominator}));

    Term termToVerify(integrationForX.integrate(termToTest));

    string stringToExpect("((-1/8)[x^-1]+(3*ln(abs(x))/16)-(3*ln(abs((1[x] + -2)))/16)-(5/4/(1[x] + -2))-(7/8/((1[x] + -2)^2)))");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksUsingPartialFractionsUsingExample2)
{
    Integration integrationForX("x");
    Term numerator(1);
    Term denominator(Polynomial{Monomial(2, {{"x", 3}}), Monomial(1, {{"x", 1}})});
    Term termToTest(createExpressionIfPossible({numerator, Term("/"), denominator}));

    Term termToVerify(integrationForX.integrate(termToTest));

    string stringToExpect("(ln(abs(x))-(ln(abs((2[x^2] + 1)))/2))");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksUsingSubstitutionUsingExample1)
{
    Integration integrationForX("x");
    Term squareRootTerm(createExpressionIfPossible(
    {Term(Polynomial{Monomial(1, {}), Monomial(1, {{"x", 1}})}), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term termToTest(createExpressionIfPossible({Term(Monomial(1, {{"x", 2}})), Term("*"), squareRootTerm}));

    Term termToVerify(integrationForX.integrate(termToTest));

    Term xPlusOne(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term firstPart(createExpressionIfPossible({Term(2), Term("*"), xPlusOne, Term("^"), Term(AlbaNumber::createFraction(7, 2)), Term("/"), Term(7)}));
    Term secondPart(createExpressionIfPossible({Term(4), Term("*"), xPlusOne, Term("^"), Term(AlbaNumber::createFraction(5, 2)), Term("/"), Term(5)}));
    Term thirdPart(createExpressionIfPossible({Term(2), Term("*"), xPlusOne, Term("^"), Term(AlbaNumber::createFraction(3, 2)), Term("/"), Term(3)}));
    Term termToExpect(createExpressionIfPossible({firstPart, Term("-"), secondPart, Term("+"), thirdPart}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationTest, IntegrateWorksUsingSubstitutionWhichResultsToNaturalLogarithmAsExample1)
{
    Integration integrationForX("x");
    Term numerator(Monomial(1, {{"x", 2}}));
    Term denominator(Polynomial{Monomial(1, {{"x", 3}}), Monomial(1, {})});
    Term termToTest(createExpressionIfPossible({numerator, Term("/"), denominator}));

    Term termToVerify(integrationForX.integrate(termToTest));

    Term expectedPolynomialTerm(Polynomial{Monomial(1, {{"x", 3}}), Monomial(1, {})});
    Term expectedLogarithm(ln(Term(abs(expectedPolynomialTerm))));
    Term termToExpect(createExpressionIfPossible({expectedLogarithm, Term("/"), Term(3)}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationTest, IntegrateWorksUsingSubstitutionWhichResultsToNaturalLogarithmAsExample2)
{
    Integration integrationForX("x");
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term termToTest(createExpressionIfPossible({numerator, Term("/"), denominator}));

    Term termToVerify(integrationForX.integrate(termToTest));

    Term expectedPolynomialTerm1(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term expectedLogarithm(ln(Term(abs(expectedPolynomialTerm1))));
    Term termToExpectPart1(Polynomial{Monomial(AlbaNumber::createFraction(1, 2), {{"x", 2}}), Monomial(-1, {{"x", 1}})});
    Term termToExpectPart2(createExpressionIfPossible({Term(3), Term("*"), expectedLogarithm}));
    Term termToExpect(createExpressionIfPossible({termToExpectPart1, Term("+"), termToExpectPart2}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationTest, IntegrateWorksUsingSubstitutionWhichResultsToNaturalLogarithmAsExample3)
{
    Integration integrationForX("x");
    Term numerator(ln(Term("x")));
    Term denominator("x");
    Term termToTest(createExpressionIfPossible({numerator, Term("/"), denominator}));

    Term termToVerify(integrationForX.integrate(termToTest));

    Term expectedLogarithm(ln(Term("x")));
    Term termToExpect(createExpressionIfPossible({expectedLogarithm, Term("^"), Term(2), Term("/"), Term(2)}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationTest, IntegrateWorksUsingTrigonometricSubstitutionUsingTanSubstitution)
{
    Integration integrationForX("x");
    Term termToTest(createExpressionIfPossible(
    {Term(Polynomial{Monomial(9, {}), Monomial(1, {{"x", 2}})}), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));

    Term termToVerify(integrationForX.integrate(termToTest));

    string stringToExpect("(9*(ln(abs(((1/3)[x]+(((1[x^2] + 9)^(1/2))/3))))+(x*((1[x^2] + 9)^(1/2))/9))/2)");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksUsingTrigonometricSubstitutionUsingSinSubstitution)
{
    Integration integrationForX("x");
    Term numerator(createExpressionIfPossible(
    {Term(Polynomial{Monomial(9, {}), Monomial(-1, {{"x", 2}})}), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term denominator(Monomial(1, {{"x", 2}}));
    Term termToTest(createExpressionIfPossible({numerator, Term("/"), denominator}));

    Term termToVerify(integrationForX.integrate(termToTest));

    string stringToExpect("((-1*arcsin((1/3)[x]))-(((-1[x^2] + 9)^(1/2))/x))");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksUsingTrigonometricSubstitutionUsingSecSubstitution)
{
    Integration integrationForX("x");
    Term denominator(createExpressionIfPossible(
    {Term(Polynomial{Monomial(-25, {}), Monomial(1, {{"x", 2}})}), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term termToTest(createExpressionIfPossible({Term(1), Term("/"), denominator}));

    Term termToVerify(integrationForX.integrate(termToTest));

    string stringToExpect("ln(abs(((1/5)[x]+(((1[x^2] + -25)^(1/2))/5))))");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksUsingIntegrationByPartsUsingExamples1)
{
    Integration integrationForX("x");
    Term x("x");
    Term termToTest(createExpressionIfPossible({Term(x), Term("*"), Term(ln(x))}));

    Term termToVerify(integrationForX.integrate(termToTest));

    Term expectedMonomialTerm1(Monomial(AlbaNumber::createFraction(-1, 4), {{"x", 2}}));
    Term expectedMonomialTerm2(Monomial(1, {{"x", 2}}));
    Term termToExpect(createExpressionIfPossible(
    {expectedMonomialTerm1, Term("+"), expectedMonomialTerm2, Term("*"), Term(ln(x)), Term("/"), Term(2)}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(IntegrationTest, IntegrateWorksUsingIntegrationByPartsUsingExamples2)
{
    Integration integrationForX("x");
    Term x("x");
    Term xSquared(Monomial(1, {{"x", 2}}));
    Term eToTheX(createExpressionIfPossible({getEAsTerm(), Term("^"), x}));
    Term termToTest(createExpressionIfPossible({xSquared, Term("*"), eToTheX}));

    Term termToVerify(integrationForX.integrate(termToTest));

    string stringToExpect("((1[x^2]*((e)^x))-(2[x]*((e)^x))+(2*((e)^x)))");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksUsingIntegrationByPartsUsingExamples3)
{
    Integration integrationForX("x");
    Term x("x");
    Term termToTest(arctan(x));

    Term termToVerify(integrationForX.integrate(termToTest));

    string stringToExpect("((x*arctan(x))-(ln(abs((1[x^2] + 1)))/2))");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksUsingIntegrationByPartsUsingExamples4)
{
    Integration integrationForX("x");
    Term x("x");
    Term eToTheX(createExpressionIfPossible({getEAsTerm(), Term("^"), x}));
    Term termToTest(createExpressionIfPossible({Term(eToTheX), Term("*"), Term(sin(x))}));

    Term simplifiedResult(integrationForX.integrate(termToTest));
    EXPECT_EQ("((((e)^x)*sin(x))-(((e)^x)*cos(x))-(((((e)^x)*sin(x))-(((e)^x)*cos(x)))/2))",
              simplifiedResult.getDisplayableString());

    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
                    SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldSimplifyToACommonDenominator = true;

        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        simplifiedResult.simplify();
    }
    EXPECT_EQ("(((((e)^x)*sin(x))-(((e)^x)*cos(x)))/2)", simplifiedResult.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksUsingIntegrationByPartsUsingExamples5)
{
    Integration integrationForX("x");
    Term x("x");
    Term termToTest(createExpressionIfPossible({Term(sin(Term(ln(x))))}));

    Term simplifiedResult(integrationForX.integrate(termToTest));
    EXPECT_EQ("((x*sin(ln(x)))-(x*cos(ln(x)))-(((x*sin(ln(x)))-(x*cos(ln(x))))/2))",
              simplifiedResult.getDisplayableString());
    {
        SimplificationOfExpression::ConfigurationDetails configurationDetails(
                    SimplificationOfExpression::Configuration::getInstance().getConfigurationDetails());
        configurationDetails.shouldSimplifyToACommonDenominator = true;

        SimplificationOfExpression::ScopeObject scopeObject;
        scopeObject.setInThisScopeThisConfiguration(configurationDetails);

        simplifiedResult.simplify();
    }
    EXPECT_EQ("(((x*sin(ln(x)))-(x*cos(ln(x))))/2)", simplifiedResult.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksSinRaiseToAConstant)
{
    Integration integrationForX("x");
    Term x("x");
    Term termToTest1(createExpressionIfPossible({Term(17), Term("*"), Term(sin(x)), Term("^"), Term(5)}));
    Term termToTest2(createExpressionIfPossible({Term(19), Term("*"), Term(sin(x)), Term("^"), Term(6)}));

    Term termToVerify1(integrationForX.integrate(termToTest1));
    Term termToVerify2(integrationForX.integrate(termToTest2));

    string stringToExpect1("((-17*cos(x))-(17*(cos(x)^5)/5)+(34*(cos(x)^3)/3))");
    string stringToExpect2("((95/16)[x]-(19*sin(2[x])/4)+(57*sin(4[x])/64)+(19*(sin(2[x])^3)/48))");
    EXPECT_EQ(stringToExpect1, termToVerify1.getDisplayableString());
    EXPECT_EQ(stringToExpect2, termToVerify2.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksCosRaiseToAConstant)
{
    Integration integrationForX("x");
    Term x("x");
    Term termToTest1(createExpressionIfPossible({Term(17), Term("*"), Term(cos(x)), Term("^"), Term(5)}));
    Term termToTest2(createExpressionIfPossible({Term(19), Term("*"), Term(cos(x)), Term("^"), Term(6)}));

    Term termToVerify1(integrationForX.integrate(termToTest1));
    Term termToVerify2(integrationForX.integrate(termToTest2));

    string stringToExpect1("((17*sin(x))+(17*(sin(x)^5)/5)-(34*(sin(x)^3)/3))");
    string stringToExpect2("((95/16)[x]+(19*sin(2[x])/4)+(57*sin(4[x])/64)-(19*(sin(2[x])^3)/48))");
    EXPECT_EQ(stringToExpect1, termToVerify1.getDisplayableString());
    EXPECT_EQ(stringToExpect2, termToVerify2.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksTanRaiseToAConstant)
{
    Integration integrationForX("x");
    Term x("x");
    Term termToTest1(createExpressionIfPossible({Term(17), Term("*"), Term(tan(x)), Term("^"), Term(3)}));
    Term termToTest2(createExpressionIfPossible({Term(19), Term("*"), Term(tan(x)), Term("^"), Term(6)}));

    Term termToVerify1(integrationForX.integrate(termToTest1));
    Term termToVerify2(integrationForX.integrate(termToTest2));

    string stringToExpect1("((-17*ln(abs(sec(x))))+(17*(sec(x)^2)/2))");
    string stringToExpect2("(-19[x]+(19*tan(x))+(19*(tan(x)^5)/5)-(19*(tan(x)^3)/3))");
    EXPECT_EQ(stringToExpect1, termToVerify1.getDisplayableString());
    EXPECT_EQ(stringToExpect2, termToVerify2.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksCscRaiseToAConstant)
{
    Integration integrationForX("x");
    Term x("x");
    Term termToTest1(createExpressionIfPossible({Term(17), Term("*"), Term(csc(x)), Term("^"), Term(3)}));
    Term termToTest2(createExpressionIfPossible({Term(19), Term("*"), Term(csc(x)), Term("^"), Term(6)}));

    Term termToVerify1(integrationForX.integrate(termToTest1));
    Term termToVerify2(integrationForX.integrate(termToTest2));

    string stringToExpect1("(17*(ln(abs((csc(x)-cot(x))))-(cot(x)*csc(x)))/2)");
    string stringToExpect2("((-19*cot(x))-(19*(cot(x)^5)/5)-(38*(cot(x)^3)/3))");
    EXPECT_EQ(stringToExpect1, termToVerify1.getDisplayableString());
    EXPECT_EQ(stringToExpect2, termToVerify2.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksSecRaiseToAConstant)
{
    Integration integrationForX("x");
    Term x("x");
    Term termToTest1(createExpressionIfPossible({Term(17), Term("*"), Term(sec(x)), Term("^"), Term(3)}));
    Term termToTest2(createExpressionIfPossible({Term(19), Term("*"), Term(sec(x)), Term("^"), Term(6)}));

    Term termToVerify1(integrationForX.integrate(termToTest1));
    Term termToVerify2(integrationForX.integrate(termToTest2));

    string stringToExpect1("(17*(ln(abs((sec(x)+tan(x))))+(sec(x)*tan(x)))/2)");
    string stringToExpect2("((19*tan(x))+(19*(tan(x)^5)/5)+(38*(tan(x)^3)/3))");
    EXPECT_EQ(stringToExpect1, termToVerify1.getDisplayableString());
    EXPECT_EQ(stringToExpect2, termToVerify2.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksCotRaiseToAConstant)
{
    Integration integrationForX("x");
    Term x("x");
    Term termToTest1(createExpressionIfPossible({Term(17), Term("*"), Term(cot(x)), Term("^"), Term(3)}));
    Term termToTest2(createExpressionIfPossible({Term(19), Term("*"), Term(cot(x)), Term("^"), Term(6)}));

    Term termToVerify1(integrationForX.integrate(termToTest1));
    Term termToVerify2(integrationForX.integrate(termToTest2));

    string stringToExpect1("((-17*ln(abs(sin(x))))-(17*(csc(x)^2)/2))");
    string stringToExpect2("(-19[x]-(19*cot(x))-(19*(cot(x)^5)/5)+(19*(cot(x)^3)/3))");
    EXPECT_EQ(stringToExpect1, termToVerify1.getDisplayableString());
    EXPECT_EQ(stringToExpect2, termToVerify2.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksOnCombinationOfSinAndCos)
{
    Integration integrationForX("x");
    Term x("x");
    Term termToTest1(createExpressionIfPossible({Term(11), Term("*"), Term(sin(x)), Term("*"), Term(cos(x))}));
    Term termToTest2(createExpressionIfPossible({Term(13), Term("*"), Term(sin(x)), Term("^"), Term(3), Term("*"), Term(cos(x)), Term("^"), Term(4)}));
    Term termToTest3(createExpressionIfPossible({Term(17), Term("*"), Term(sin(x)), Term("^"), Term(4), Term("*"), Term(cos(x)), Term("^"), Term(4)}));
    Term termToTest4(createExpressionIfPossible({Term(19), Term("*"), Term(sin(x)), Term("^"), Term(4), Term("*"), Term(cos(x)), Term("^"), Term(4)}));

    Term termToVerify1(integrationForX.integrate(termToTest1));
    Term termToVerify2(integrationForX.integrate(termToTest2));
    Term termToVerify3(integrationForX.integrate(termToTest3));
    Term termToVerify4(integrationForX.integrate(termToTest4));

    string stringToExpect1("(-11*(cos(x)^2)/2)");
    string stringToExpect2("((13*(cos(x)^7)/7)-(13*(cos(x)^5)/5))");
    string stringToExpect3("((51/128)[x]-(17*sin(4[x])/64)+(17*sin(4[x])/128)+(17*sin(8[x])/1024))");
    string stringToExpect4("((57/128)[x]-(19*sin(4[x])/64)+(19*sin(4[x])/128)+(19*sin(8[x])/1024))");
    EXPECT_EQ(stringToExpect1, termToVerify1.getDisplayableString());
    EXPECT_EQ(stringToExpect2, termToVerify2.getDisplayableString());
    EXPECT_EQ(stringToExpect3, termToVerify3.getDisplayableString());
    EXPECT_EQ(stringToExpect4, termToVerify4.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksOnCombinationOfCscAndCot)
{
    Integration integrationForX("x");
    Term x("x");
    Term termToTest1(createExpressionIfPossible({Term(11), Term("*"), Term(csc(x)), Term("*"), Term(cot(x))}));
    Term termToTest2(createExpressionIfPossible({Term(13), Term("*"), Term(csc(x)), Term("^"), Term(3), Term("*"), Term(cot(x)), Term("^"), Term(5)}));
    Term termToTest3(createExpressionIfPossible({Term(17), Term("*"), Term(csc(x)), Term("^"), Term(4), Term("*"), Term(cot(x)), Term("^"), Term(4)}));
    //Term termToTest4(createExpressionIfPossible({Term(19), Term("*"), Term(csc(x)), Term("^"), Term(3), Term("*"), Term(cot(x)), Term("^"), Term(4)}));

    Term termToVerify1(integrationForX.integrate(termToTest1));
    Term termToVerify2(integrationForX.integrate(termToTest2));
    Term termToVerify3(integrationForX.integrate(termToTest3));
    //Term termToVerify4(integrationForX.integrate(termToTest4));

    string stringToExpect1("(-11*csc(x))");
    string stringToExpect2("((-13*(csc(x)^7)/7)+(26*(csc(x)^5)/5)-(13*(csc(x)^3)/3))");
    string stringToExpect3("((-17*(cot(x)^7)/7)-(17*(cot(x)^5)/5))");
    //string stringToExpect4("nan");
    EXPECT_EQ(stringToExpect1, termToVerify1.getDisplayableString());
    EXPECT_EQ(stringToExpect2, termToVerify2.getDisplayableString());
    EXPECT_EQ(stringToExpect3, termToVerify3.getDisplayableString());
    //EXPECT_EQ(stringToExpect4, termToVerify4.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksOnCombinationOfSecAndTan)
{
    Integration integrationForX("x");
    Term x("x");
    Term termToTest1(createExpressionIfPossible({Term(11), Term("*"), Term(sec(x)), Term("*"), Term(tan(x))}));
    Term termToTest2(createExpressionIfPossible({Term(13), Term("*"), Term(sec(x)), Term("^"), Term(3), Term("*"), Term(tan(x)), Term("^"), Term(5)}));
    Term termToTest3(createExpressionIfPossible({Term(17), Term("*"), Term(sec(x)), Term("^"), Term(4), Term("*"), Term(tan(x)), Term("^"), Term(4)}));
    //Term termToTest4(createExpressionIfPossible({Term(19), Term("*"), Term(sec(x)), Term("^"), Term(3), Term("*"), Term(tan(x)), Term("^"), Term(4)}));

    Term termToVerify1(integrationForX.integrate(termToTest1));
    Term termToVerify2(integrationForX.integrate(termToTest2));
    Term termToVerify3(integrationForX.integrate(termToTest3));
    //Term termToVerify4(integrationForX.integrate(termToTest4));

    string stringToExpect1("(11*sec(x))");
    string stringToExpect2("((13*(sec(x)^7)/7)-(26*(sec(x)^5)/5)+(13*(sec(x)^3)/3))");
    string stringToExpect3("((17*(tan(x)^7)/7)+(17*(tan(x)^5)/5))");
    //string stringToExpect4("nan");
    EXPECT_EQ(stringToExpect1, termToVerify1.getDisplayableString());
    EXPECT_EQ(stringToExpect2, termToVerify2.getDisplayableString());
    EXPECT_EQ(stringToExpect3, termToVerify3.getDisplayableString());
    //EXPECT_EQ(stringToExpect4, termToVerify4.getDisplayableString());
}

TEST(IntegrationTest, IntegrateWorksWithSimplificationToACommonDenominator)
{
    Integration integrationForX("x");
    Term termWithNegativeExponents(Polynomial{Monomial(1, {}), Monomial(AlbaNumber::createFraction(4, 9), {{"x", AlbaNumber::createFraction(-2, 3)}})});
    Term termToTest(createExpressionIfPossible(
    {termWithNegativeExponents, Term("^"), Term(AlbaNumber::createFraction(1, 2))}));

    Term termToVerify(integrationForX.integrate(termToTest));

    Term expectedPolynomial(Polynomial{Monomial(9, {{"x", AlbaNumber::createFraction(2, 3)}}), Monomial(4, {})});
    Term termToExpect(createExpressionIfPossible({expectedPolynomial, Term("^"), Term(AlbaNumber::createFraction(3, 2)), Term("/"), Term(27)}));
    EXPECT_EQ(termToExpect, termToVerify);
}

}

}
