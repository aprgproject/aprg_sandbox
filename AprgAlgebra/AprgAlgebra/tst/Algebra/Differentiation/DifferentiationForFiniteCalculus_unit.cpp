#include <Algebra/Differentiation/DifferentiationForFiniteCalculus.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForTerm)
{
    DifferentiationForFiniteCalculus differentiationForX("x");

    EXPECT_EQ(Term(Constant(0)), differentiationForX.differentiate(Term(5)));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForConstant)
{
    DifferentiationForFiniteCalculus differentiationForX("x");

    EXPECT_EQ(Term(Constant(0)), differentiationForX.differentiate(Constant(5)));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForVariable)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Polynomial xPlusOne{Monomial(1, {{"x", 1}}), Monomial(1, {})};

    EXPECT_EQ(Term(xPlusOne), differentiationForX.differentiate(Variable("x")));
    EXPECT_EQ(Term(Constant(0)), differentiationForX.differentiate(Variable("y")));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForMonomial)
{
    DifferentiationForFiniteCalculus differentiationForX("x");

    Term expectedTerm1(Constant(0));
    Term expectedTerm2(Polynomial(
    {Monomial(35, {{"x", 6}, {"y", 8}, {"z", 9}}),
     Monomial(105, {{"x", 5}, {"y", 8}, {"z", 9}}),
     Monomial(175, {{"x", 4}, {"y", 8}, {"z", 9}}),
     Monomial(175, {{"x", 3}, {"y", 8}, {"z", 9}}),
     Monomial(105, {{"x", 2}, {"y", 8}, {"z", 9}}),
     Monomial(35, {{"x", 1}, {"y", 8}, {"z", 9}}),
     Monomial(5, {{"y", 8}, {"z", 9}})}));
    Term expectedTerm3(createExpressionIfPossible(
    {Term(Monomial(-5, {{"x", -2}, {"y", 8}, {"z", 9}})),
     Term("+"),
     Term(createExpressionIfPossible(
     {Term(Monomial(5, {{"y", 8}, {"z", 9}})),
      Term("/"),
      Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})})
     }))}));
    EXPECT_EQ(expectedTerm1, differentiationForX.differentiate(Monomial(13, {})));
    EXPECT_EQ(expectedTerm2, differentiationForX.differentiate(Monomial(5, {{"x", 7}, {"y", 8}, {"z", 9}})));
    EXPECT_EQ(expectedTerm3, differentiationForX.differentiate(Monomial(5, {{"x", -2}, {"y", 8}, {"z", 9}})));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForPolynomial)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Polynomial polynomial1{Monomial(13, {})};
    Polynomial polynomial2{Monomial(-1, {{"x", 2}, {"y", -3}}), Monomial(-4, {{"x", 3}, {"z", -6}})};
    Polynomial polynomial3{Monomial(-1, {{"x", -2}, {"y", -3}}), Monomial(-4, {{"x", -5}, {"z", -6}})};

    Term expectedTerm1(Constant(0));
    Term expectedTerm2(Polynomial
    {Monomial(-2, {{"x", 1}, {"y", -3}}),
     Monomial(-1, {{"y", -3}}),
     Monomial(-12, {{"x", 2}, {"z", -6}}),
     Monomial(-12, {{"x", 1}, {"z", -6}}),
     Monomial(-4, {{"z", -6}})});
    Term polynomial1OfTerm3(Polynomial
    {Monomial(1, {{"x", -2}, {"y", -3}}),
     Monomial(4, {{"x", -5}, {"z", -6}})});
    Term polynomial2OfTerm3(Polynomial
    {Monomial(1, {{"x", 2}, {"y", 3}}),
     Monomial(2, {{"x", 1}, {"y", 3}}),
     Monomial(1, {{"y", 3}})});
    Term polynomial3OfTerm3(Polynomial
    {Monomial(1, {{"x", 5}, {"z", 6}}),
     Monomial(5, {{"x", 4}, {"z", 6}}),
     Monomial(10, {{"x", 3}, {"z", 6}}),
     Monomial(10, {{"x", 2}, {"z", 6}}),
     Monomial(5, {{"x", 1}, {"z", 6}}),
     Monomial(1, {{"z", 6}})});
    Expression expression1OfTerm3(createExpressionIfPossible(
    {Term(1),
     Term("/"),
     Term(polynomial2OfTerm3)}));
    Expression expression2OfTerm3(createExpressionIfPossible(
    {Term(4),
     Term("/"),
     Term(polynomial3OfTerm3)}));
    Term expectedTerm3(createExpressionIfPossible(
    {Term(polynomial1OfTerm3),
     Term("-"),
     Term(expression1OfTerm3),
     Term("-"),
     Term(expression2OfTerm3)}));
    EXPECT_EQ(expectedTerm1, differentiationForX.differentiate(polynomial1));
    EXPECT_EQ(expectedTerm2, differentiationForX.differentiate(polynomial2));
    EXPECT_EQ(expectedTerm3, differentiationForX.differentiate(polynomial3));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForExpression)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Term x("x");
    Term xPlusOne(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression expression01{createExpressionIfPossible({x})};
    Expression expression02{createExpressionIfPossible({Term(3), Term("^"), x})};

    Term expectedTerm01(1);
    Term expectedTerm02(createExpressionIfPossible({Term(3), Term("^"), Term(xPlusOne), Term("-"), Term(3), Term("^"), x}));
    EXPECT_EQ(expectedTerm01, differentiationForX.differentiate(expression01));
    EXPECT_EQ(expectedTerm02, differentiationForX.differentiate(expression02));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForFunction)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Term x("x");
    Term xPlusOne(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});\

    Term expectedTerm(createExpressionIfPossible({Term(sin(xPlusOne)), Term("-"), Term(sin(x))}));
    EXPECT_EQ(expectedTerm, differentiationForX.differentiate(sin(x)));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForEquation)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Term term1ForEquation1(Polynomial{Monomial(1, {{"x", 6}}), Monomial(-2, {{"x", 1}})});
    Term term2ForEquation1(Polynomial{Monomial(3, {{"y", 6}}), Monomial(1, {{"y", 5}}), Monomial(-1, {{"y", 2}})});
    Equation equation1(term1ForEquation1, "=", term2ForEquation1);

    EXPECT_EQ("(6[x^5] + 15[x^4] + 20[x^3] + 15[x^2] + 6[x] + -1) = 0",
              differentiationForX.differentiate(equation1).getDisplayableString());
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateMultipleTimesWorksForTerm)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Term termToTest(Monomial(3, {{"x", 4}}));

    Term expectedTerm1(Monomial(3, {{"x", 4}}));
    Term expectedTerm2(Polynomial
    {Monomial(12, {{"x", 3}}),
     Monomial(18, {{"x", 2}}),
     Monomial(12, {{"x", 1}}),
     Monomial(3, {})});
    Term expectedTerm3(Polynomial
    {Monomial(36, {{"x", 2}}),
     Monomial(72, {{"x", 1}}),
     Monomial(42, {})});
    EXPECT_EQ(expectedTerm1, differentiationForX.differentiateMultipleTimes(termToTest, 0));
    EXPECT_EQ(expectedTerm2, differentiationForX.differentiateMultipleTimes(termToTest, 1));
    EXPECT_EQ(expectedTerm3, differentiationForX.differentiateMultipleTimes(termToTest, 2));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateMultipleTimesWorksForEquation)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Equation equationToTest(Term(Monomial(3, {{"x", 4}})), "=", Term(Monomial(5, {{"x", 6}})));

    EXPECT_EQ("3[x^4] = 5[x^6]",
              differentiationForX.differentiateMultipleTimes(equationToTest, 0).getDisplayableString());
    EXPECT_EQ("(30[x^5] + 75[x^4] + 88[x^3] + 57[x^2] + 18[x] + 2) = 0",
              differentiationForX.differentiateMultipleTimes(equationToTest, 1).getDisplayableString());
    EXPECT_EQ("(150[x^4] + 600[x^3] + 1014[x^2] + 828[x] + 268) = 0",
              differentiationForX.differentiateMultipleTimes(equationToTest, 2).getDisplayableString());
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateTermWorks)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Term x("x");
    Term xPlusOne(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term polynomialTerm(Polynomial{Monomial(-2, {{"x", 2}}), Monomial(8, {{"x", 1}}), Monomial(5, {})});
    Expression expressionTerm{createExpressionIfPossible({Term(3), Term("^"), x})};

    Term expectedTerm1(Polynomial{Monomial(15, {{"x", 2}}), Monomial(15, {{"x", 1}}), Monomial(5, {})});
    Term expectedTerm2(Polynomial{Monomial(-4, {{"x", 1}}), Monomial(6, {})});
    Term expectedTerm3(createExpressionIfPossible({Term(3), Term("^"), Term(xPlusOne), Term("-"), Term(3), Term("^"), x}));
    EXPECT_EQ(Term(Constant(0)), differentiationForX.differentiateTerm(Term(5)));
    EXPECT_EQ(xPlusOne, differentiationForX.differentiateTerm(Term("x")));
    EXPECT_EQ(expectedTerm1, differentiationForX.differentiateTerm(Term(Monomial(5, {{"x", 3}}))));
    EXPECT_EQ(expectedTerm2, differentiationForX.differentiateTerm(polynomialTerm));
    EXPECT_EQ(expectedTerm3, differentiationForX.differentiateTerm(expressionTerm));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateConstantWorks)
{
    DifferentiationForFiniteCalculus differentiationForX("x");

    EXPECT_EQ(AlbaNumber(0), differentiationForX.differentiateConstant(Constant(5)));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateVariableWorks)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Polynomial zeroPolynomial(createPolynomialFromConstant(0));
    Polynomial xPlusOne{Monomial(1, {{"x", 1}}), Monomial(1, {})};

    EXPECT_EQ(xPlusOne, differentiationForX.differentiateVariable(Variable("x")));
    EXPECT_EQ(zeroPolynomial, differentiationForX.differentiateVariable(Variable("y")));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateMonomialWorks)
{
    DifferentiationForFiniteCalculus differentiationForX("x");

    Term expectedTerm1(Constant(0));
    Term expectedTerm2(Polynomial(
    {Monomial(35, {{"x", 6}, {"y", 8}, {"z", 9}}),
     Monomial(105, {{"x", 5}, {"y", 8}, {"z", 9}}),
     Monomial(175, {{"x", 4}, {"y", 8}, {"z", 9}}),
     Monomial(175, {{"x", 3}, {"y", 8}, {"z", 9}}),
     Monomial(105, {{"x", 2}, {"y", 8}, {"z", 9}}),
     Monomial(35, {{"x", 1}, {"y", 8}, {"z", 9}}),
     Monomial(5, {{"y", 8}, {"z", 9}})}));
    Term expectedTerm3(createExpressionIfPossible(
    {Term(Monomial(-5, {{"x", -2}, {"y", 8}, {"z", 9}})),
     Term("+"),
     Term(createExpressionIfPossible(
     {Term(Monomial(5, {{"y", 8}, {"z", 9}})),
      Term("/"),
      Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})})
     }))}));
    EXPECT_EQ(expectedTerm1, differentiationForX.differentiateMonomial(Monomial(13, {})));
    EXPECT_EQ(expectedTerm2, differentiationForX.differentiateMonomial(Monomial(5, {{"x", 7}, {"y", 8}, {"z", 9}})));
    EXPECT_EQ(expectedTerm3, differentiationForX.differentiateMonomial(Monomial(5, {{"x", -2}, {"y", 8}, {"z", 9}})));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiatePolynomialWorks)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Polynomial polynomial1{Monomial(13, {})};
    Polynomial polynomial2{Monomial(-1, {{"x", 2}, {"y", -3}}), Monomial(-4, {{"x", 3}, {"z", -6}})};
    Polynomial polynomial3{Monomial(-1, {{"x", -2}, {"y", -3}}), Monomial(-4, {{"x", -5}, {"z", -6}})};

    Term expectedTerm1(Constant(0));
    Term expectedTerm2(Polynomial
    {Monomial(-2, {{"x", 1}, {"y", -3}}),
     Monomial(-1, {{"y", -3}}),
     Monomial(-12, {{"x", 2}, {"z", -6}}),
     Monomial(-12, {{"x", 1}, {"z", -6}}),
     Monomial(-4, {{"z", -6}})});
    Term polynomial1OfTerm3(Polynomial
    {Monomial(1, {{"x", -2}, {"y", -3}}),
     Monomial(4, {{"x", -5}, {"z", -6}})});
    Term polynomial2OfTerm3(Polynomial
    {Monomial(1, {{"x", 2}, {"y", 3}}),
     Monomial(2, {{"x", 1}, {"y", 3}}),
     Monomial(1, {{"y", 3}})});
    Term polynomial3OfTerm3(Polynomial
    {Monomial(1, {{"x", 5}, {"z", 6}}),
     Monomial(5, {{"x", 4}, {"z", 6}}),
     Monomial(10, {{"x", 3}, {"z", 6}}),
     Monomial(10, {{"x", 2}, {"z", 6}}),
     Monomial(5, {{"x", 1}, {"z", 6}}),
     Monomial(1, {{"z", 6}})});
    Expression expression1OfTerm3(createExpressionIfPossible(
    {Term(1),
     Term("/"),
     Term(polynomial2OfTerm3)}));
    Expression expression2OfTerm3(createExpressionIfPossible(
    {Term(4),
     Term("/"),
     Term(polynomial3OfTerm3)}));
    Term expectedTerm3(createExpressionIfPossible(
    {Term(polynomial1OfTerm3),
     Term("-"),
     Term(expression1OfTerm3),
     Term("-"),
     Term(expression2OfTerm3)}));
    EXPECT_EQ(expectedTerm1, differentiationForX.differentiatePolynomial(polynomial1));
    EXPECT_EQ(expectedTerm2, differentiationForX.differentiatePolynomial(polynomial2));
    EXPECT_EQ(expectedTerm3, differentiationForX.differentiatePolynomial(polynomial3));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateExpressionWorks)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Term x("x");
    Term xPlusOne(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression expression01{createExpressionIfPossible({x})};
    Expression expression02{createExpressionIfPossible({Term(3), Term("^"), x})};

    Term expectedTerm01(1);
    Term expectedTerm02(createExpressionIfPossible({Term(3), Term("^"), Term(xPlusOne), Term("-"), Term(3), Term("^"), x}));
    EXPECT_EQ(expectedTerm01, differentiationForX.differentiateExpression(expression01));
    EXPECT_EQ(expectedTerm02, differentiationForX.differentiateExpression(expression02));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateFunctionWorks)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Term x("x");
    Term xPlusOne(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});

    Term expectedTerm(createExpressionIfPossible({Term(sin(xPlusOne)), Term("-"), Term(sin(x))}));
    EXPECT_EQ(expectedTerm, differentiationForX.differentiate(sin(x)));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateEquationWorks)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Term term1ForEquation1(Polynomial{Monomial(1, {{"x", 6}}), Monomial(-2, {{"x", 1}})});
    Term term2ForEquation1(Polynomial{Monomial(3, {{"y", 6}}), Monomial(1, {{"y", 5}}), Monomial(-1, {{"y", 2}})});
    Equation equation1(term1ForEquation1, "=", term2ForEquation1);
    Term term1ForEquation2(Polynomial{Monomial(3, {{"x", 4}, {"y", 2}}), Monomial(-7, {{"x", 1}, {"y", 3}})});
    Term term2ForEquation2(Polynomial{Monomial(4, {}), Monomial(8, {{"y", 1}})});
    Equation equation2(term1ForEquation2, "=", term2ForEquation2);

    EXPECT_EQ("(6[x^5] + 15[x^4] + 20[x^3] + 15[x^2] + 6[x] + -1) = 0",
              differentiationForX.differentiateEquation(equation1).getDisplayableString());
    EXPECT_EQ("(12[x^3][y^2] + 18[x^2][y^2] + 12[x][y^2] + -7[y^3] + 3[y^2]) = 0",
              differentiationForX.differentiateEquation(equation2).getDisplayableString());
}

}

}
