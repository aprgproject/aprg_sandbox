#include <Algebra/Differentiation/Differentiation.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(DifferentiationTest, DifferentiateWorksForConstant)
{
    Differentiation differentiationForX("x");

    EXPECT_EQ(Term(Constant(0)), differentiationForX.differentiate(Constant(5)));
}

TEST(DifferentiationTest, DifferentiateWorksForVariable)
{
    Differentiation differentiationForXWithY("x", {"y"});

    EXPECT_EQ(Term(1), differentiationForXWithY.differentiate(Variable("x")));
    EXPECT_EQ(Term("dy/dx"), differentiationForXWithY.differentiate(Variable("y")));
    EXPECT_EQ(Term(Constant(0)), differentiationForXWithY.differentiate(Variable("a")));
}

TEST(DifferentiationTest, DifferentiateWorksForMonomial)
{
    Differentiation differentiationForX("x");

    EXPECT_EQ(Term(Constant(0)), differentiationForX.differentiate(Monomial(13, {})));
    EXPECT_EQ(Term(Constant(0)), differentiationForX.differentiate(Monomial(13, {{"x", 0}})));
    EXPECT_EQ(Term(Monomial(8, {{"x", 7}})), differentiationForX.differentiate(Monomial(1, {{"x", 8}})));
    EXPECT_EQ(Term(Monomial(42, {{"x", 6}, {"y", 8}, {"z", 9}})), differentiationForX.differentiate(Monomial(6, {{"x", 7}, {"y", 8}, {"z", 9}})));
}

TEST(DifferentiationTest, DifferentiateWorksForPolynomial)
{
    Differentiation differentiationForX("x");
    Polynomial polynomial1{Monomial(0, {})};
    Polynomial polynomial2{Monomial(5, {{"x", 0}})};
    Polynomial polynomial3{Monomial(7, {{"x", 4}}), Monomial(-2, {{"x", 3}}), Monomial(8, {{"x", 1}}), Monomial(5, {})};

    Term expectedTerm1(Constant(0));
    Term expectedTerm2(Constant(0));
    Term expectedTerm3(Polynomial{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})});
    EXPECT_EQ(expectedTerm1, differentiationForX.differentiate(polynomial1));
    EXPECT_EQ(expectedTerm2, differentiationForX.differentiate(polynomial2));
    EXPECT_EQ(expectedTerm3, differentiationForX.differentiate(polynomial3));
}

TEST(DifferentiationTest, DifferentiateConstantWorks)
{
    Differentiation differentiationForX("x");
    EXPECT_EQ(AlbaNumber(0), differentiationForX.differentiateConstant(Constant(5)));
}
TEST(DifferentiationTest, DifferentiateVariableWorks)
{
    Differentiation differentiationForXWithY("x", {"y"});

    EXPECT_EQ(Monomial(1, {}), differentiationForXWithY.differentiateVariable(Variable("x")));
    EXPECT_EQ(Monomial(1, {{"dy/dx", 1}}), differentiationForXWithY.differentiateVariable(Variable("y")));
    EXPECT_EQ(Monomial(0, {}), differentiationForXWithY.differentiateVariable(Variable("a")));
}

TEST(DifferentiationTest, DifferentiateMonomialWorks)
{
    Differentiation differentiationForX("x");

    EXPECT_EQ(Monomial(0, {}), differentiationForX.differentiateMonomial(Monomial(13, {})));
    EXPECT_EQ(Monomial(0, {}), differentiationForX.differentiateMonomial(Monomial(13, {{"x", 0}})));
    EXPECT_EQ(Monomial(8, {{"x", 7}}), differentiationForX.differentiateMonomial(Monomial(1, {{"x", 8}})));
    EXPECT_EQ(Monomial(-15, {{"x", -6}}), differentiationForX.differentiateMonomial(Monomial(3, {{"x", -5}})));
    EXPECT_EQ(Monomial(42, {{"x", 6}, {"y", 8}, {"z", 9}}), differentiationForX.differentiateMonomial(Monomial(6, {{"x", 7}, {"y", 8}, {"z", 9}})));
}

TEST(DifferentiationTest, DifferentiatePolynomialWorks)
{
    Differentiation differentiationForX("x");
    Polynomial polynomial1{Monomial(0, {})};
    Polynomial polynomial2{Monomial(5, {{"x", 0}})};
    Polynomial polynomial3{Monomial(7, {{"x", 4}}), Monomial(-2, {{"x", 3}}), Monomial(8, {{"x", 1}}), Monomial(5, {})};

    Polynomial expectedPolynomial1;
    Polynomial expectedPolynomial2;
    Polynomial expectedPolynomial3{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};
    EXPECT_EQ(expectedPolynomial1, differentiationForX.differentiatePolynomial(polynomial1));
    EXPECT_EQ(expectedPolynomial2, differentiationForX.differentiatePolynomial(polynomial2));
    EXPECT_EQ(expectedPolynomial3, differentiationForX.differentiatePolynomial(polynomial3));
}

TEST(DifferentiationTest, DifferentiateExpressionWorks)
{
    Differentiation differentiationForX("x");
    Term x("x");
    Expression expression1{createExpressionIfPossible({x})};
    Expression expression2{createExpressionIfPossible({cos(x)})};
    Expression expression3{createExpressionIfPossible({sin(x), Term("+"), cos(x)})};
    Expression expression4{createExpressionIfPossible({sin(x), Term("-"), cos(x)})};
    Expression expression5{createExpressionIfPossible({sin(x), Term("*"), cos(x)})};
    Expression expression6{createExpressionIfPossible({sin(x), Term("/"), cos(x)})};
    Expression expression7{createExpressionIfPossible({cos(x), Term("^"), Term(3)})};
    Expression expression8{createExpressionIfPossible({Term(3), Term("^"), cos(x)})};
    Expression expression9{createExpressionIfPossible({sin(x), Term("^"), cos(x)})};

    Term expectedTerm1(1);
    Term expectedTerm2(createExpressionIfPossible({Term(-1), Term("*"), sin(x)}));
    Term expectedTerm3(createExpressionIfPossible({cos(x), Term("-"), sin(x)}));
    Term expectedTerm4(createExpressionIfPossible({cos(x), Term("+"), sin(x)}));
    Term expectedTerm5(createExpressionIfPossible({Term(-1), Term("*"), sin(x), Term("*"), sin(x), Term("+"), cos(x), Term("*"), cos(x)}));
    Term expectedNumerator6(createExpressionIfPossible({cos(x), Term("*"), cos(x), Term("+"), sin(x), Term("*"), sin(x)}));
    Term expectedDenominator6(createExpressionIfPossible({cos(x), Term("^"), Term(2)}));
    Term expectedTerm6(createExpressionIfPossible({expectedNumerator6, Term("/"), expectedDenominator6}));
    Term expectedTerm7(createExpressionIfPossible({Term(-3), Term("*"), cos(x), Term("^"), Term(2), Term("*"), sin(x)}));
    Term expectedTerm8(createExpressionIfPossible({Term(-1.09861228866811), Term("*"), Term(3), Term("^"), cos(x), Term("*"), sin(x)}));
    EXPECT_EQ(expectedTerm1, differentiationForX.differentiateExpression(expression1));
    EXPECT_EQ(expectedTerm2, differentiationForX.differentiateExpression(expression2));
    EXPECT_EQ(expectedTerm3, differentiationForX.differentiateExpression(expression3));
    EXPECT_EQ(expectedTerm4, differentiationForX.differentiateExpression(expression4));
    EXPECT_EQ(expectedTerm5, differentiationForX.differentiateExpression(expression5));
    EXPECT_EQ(expectedTerm6, differentiationForX.differentiateExpression(expression6));
    EXPECT_EQ(expectedTerm7, differentiationForX.differentiateExpression(expression7));
    EXPECT_EQ(expectedTerm8, differentiationForX.differentiateExpression(expression8));
    EXPECT_TRUE(isNotANumber(differentiationForX.differentiateExpression(expression9)));
}

TEST(DifferentiationTest, DifferentiateFunctionWorksWithTrigonometricFunction)
{
    Differentiation differentiationForX("x");

    Term x("x");
    EXPECT_EQ(Term(cos(x)), differentiationForX.differentiateFunction(sin(x)));
    EXPECT_EQ(Term(createExpressionIfPossible({Term(-1), Term("*"), sin(x)})), differentiationForX.differentiateFunction(cos(x)));
    EXPECT_EQ(Term(createExpressionIfPossible({sec(x), Term("^"), Term(2)})), differentiationForX.differentiateFunction(tan(x)));
    EXPECT_EQ(Term(createExpressionIfPossible({Term(-1), Term("*"), csc(x), Term("*"), cot(x)})), differentiationForX.differentiateFunction(csc(x)));
    EXPECT_EQ(Term(createExpressionIfPossible({sec(x), Term("*"), tan(x)})), differentiationForX.differentiateFunction(sec(x)));
    EXPECT_EQ(Term(createExpressionIfPossible({Term(-1), Term("*"), csc(x), Term("^"), Term(2)})), differentiationForX.differentiateFunction(cot(x)));
}

TEST(DifferentiationTest, DifferentiateFunctionWorksWithChainRule)
{
    Differentiation differentiationForX("x");
    Function functionToTest(sin(Term(Monomial(10, {{"x", 8}}))));

    Term expectedTerm(createExpressionIfPossible({Term(Monomial(80, {{"x", 7}})), Term("*"), cos(Term(Monomial(10, {{"x", 8}})))}));
    EXPECT_EQ(expectedTerm, differentiationForX.differentiateFunction(functionToTest));
}

TEST(DifferentiationTest, DifferentiateTwoMultipliedTermsWorks)
{
    Differentiation differentiationForX("x");
    Term term1(Polynomial{Monomial(2, {{"x", 3}}), Monomial(-4, {{"x", 2}})});
    Term term2(Polynomial{Monomial(3, {{"x", 5}}), Monomial(1, {{"x", 2}})});

    Term expectedTerm(Polynomial{Monomial(48, {{"x", 7}}), Monomial(-84, {{"x", 6}}), Monomial(10, {{"x", 4}}), Monomial(-16, {{"x", 3}})});
    EXPECT_EQ(expectedTerm, differentiationForX.differentiateTwoMultipliedTerms(term1, term2));
}

TEST(DifferentiationTest, DifferentiateTwoDividedTermsWorks)
{
    Differentiation differentiationForX("x");
    Term numerator(Polynomial{Monomial(2, {{"x", 3}}), Monomial(4, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {{"x", 1}}), Monomial(1, {})});

    Term expectedNumerator(Polynomial{Monomial(2, {{"x", 4}}), Monomial(-16, {{"x", 3}}), Monomial(6, {{"x", 2}}), Monomial(-8, {{"x", 1}}), Monomial(16, {})});
    Term expectedDenominator(Polynomial{Monomial(1, {{"x", 4}}), Monomial(-8, {{"x", 3}}), Monomial(18, {{"x", 2}}), Monomial(-8, {{"x", 1}}), Monomial(1, {})});
    Term expectedTerm(createExpressionIfPossible({expectedNumerator, Term("/"), expectedDenominator}));
    EXPECT_EQ(expectedTerm, differentiationForX.differentiateTwoDividedTerms(numerator, denominator));
}

TEST(DifferentiationTest, DifferentiateWorksWithDivisionExpressionRaiseToAConstant)
{
    Differentiation differentiationForX("x");
    Term subTerm1(createExpressionIfPossible({Term(2), Term("/"), Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {})})}));
    Term termToTest(createExpressionIfPossible({subTerm1, Term("^"), Term(5)}));

    EXPECT_EQ("(-10*((2/(1[x] + -1))^4)/(1[x^2] + -2[x] + 1))", differentiationForX.differentiate(termToTest).getDisplayableString());
}

TEST(DifferentiationTest, DifferentiateWorksWithChainRule)
{
    Differentiation differentiationForX("x");
    Term termToTest(createExpressionIfPossible({sec(Term(Monomial(2, {{"x", 2}}))), Term("^"), Term(4)}));

    EXPECT_EQ("(16[x]*(sec(2[x^2])^3)*sec(2[x^2])*tan(2[x^2]))", differentiationForX.differentiate(termToTest).getDisplayableString());
}

TEST(DifferentiationTest, DifferentiateWorksWithSquareRootOfAPolynomial)
{
    Differentiation differentiationForX("x");
    Polynomial subPolynomial{Monomial(2, {{"x", 3}}), Monomial(-4, {{"x", 1}}), Monomial(5, {})};
    Term termToTest(createExpressionIfPossible({Term(subPolynomial), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));

    EXPECT_EQ("((3[x^2] + -2)/((2[x^3] + -4[x] + 5)^(1/2)))", differentiationForX.differentiate(termToTest).getDisplayableString());
}

}

}