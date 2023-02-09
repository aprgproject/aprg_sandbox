#include <Algebra/Differentiation/DifferentiationForFiniteCalculus.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForTerm)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Term termToTest(5);

    EXPECT_EQ(Term(0), differentiationForX.differentiate(termToTest));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForConstant)
{
    DifferentiationForFiniteCalculus differentiationForX("x");

    EXPECT_EQ(Term(0), differentiationForX.differentiate(Constant(5)));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForVariable)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Polynomial xPlusOne{Monomial(1, {{"x", 1}}), Monomial(1, {})};

    EXPECT_EQ(Term(xPlusOne), differentiationForX.differentiate(Variable("x")));
    EXPECT_EQ(Term(0), differentiationForX.differentiate(Variable("y")));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForMonomial)
{
    DifferentiationForFiniteCalculus differentiationForX("x");

    Term termToVerify1(differentiationForX.differentiate(Monomial(13, {})));
    Term termToVerify2(differentiationForX.differentiate(Monomial(5, {{"x", 7}, {"y", 8}, {"z", 9}})));
    Term termToVerify3(differentiationForX.differentiate(Monomial(5, {{"x", -2}, {"y", 8}, {"z", 9}})));

    Term termToExpect1(0);
    Term termToExpect2(Polynomial(
    {Monomial(35, {{"x", 6}, {"y", 8}, {"z", 9}}),
     Monomial(105, {{"x", 5}, {"y", 8}, {"z", 9}}),
     Monomial(175, {{"x", 4}, {"y", 8}, {"z", 9}}),
     Monomial(175, {{"x", 3}, {"y", 8}, {"z", 9}}),
     Monomial(105, {{"x", 2}, {"y", 8}, {"z", 9}}),
     Monomial(35, {{"x", 1}, {"y", 8}, {"z", 9}}),
     Monomial(5, {{"y", 8}, {"z", 9}})}));
    Term termToExpect3(createExpressionIfPossible(
    {Monomial(-5, {{"x", -2}, {"y", 8}, {"z", 9}}), "+",
     createExpressionIfPossible(
     {Monomial(5, {{"y", 8}, {"z", 9}}), "/", Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})}
     })}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForPolynomial)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Polynomial polynomial1{Monomial(13, {})};
    Polynomial polynomial2{Monomial(-1, {{"x", 2}, {"y", -3}}), Monomial(-4, {{"x", 3}, {"z", -6}})};
    Polynomial polynomial3{Monomial(-1, {{"x", -2}, {"y", -3}}), Monomial(-4, {{"x", -5}, {"z", -6}})};

    Term termToVerify1(differentiationForX.differentiate(polynomial1));
    Term termToVerify2(differentiationForX.differentiate(polynomial2));
    Term termToVerify3(differentiationForX.differentiate(polynomial3));

    Term termToExpect1(0);
    Term termToExpect2(Polynomial
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
    Expression expression1OfTerm3(createExpressionIfPossible({1, "/", polynomial2OfTerm3}));
    Expression expression2OfTerm3(createExpressionIfPossible({4, "/", polynomial3OfTerm3}));
    Term termToExpect3(createExpressionIfPossible(
    {polynomial1OfTerm3, "-", expression1OfTerm3, "-", expression2OfTerm3}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForExpression)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Term xPlusOne(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression expression01{createExpressionIfPossible({"x"})};
    Expression expression02{createExpressionIfPossible({3, "^", "x"})};

    Term termToVerify1(differentiationForX.differentiate(expression01));
    Term termToVerify2(differentiationForX.differentiate(expression02));

    Term termToExpect1(1);
    Term termToExpect2(createExpressionIfPossible({3, "^", xPlusOne, "-", 3, "^", "x"}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForFunction)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Term xPlusOne(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});

    Term termToVerify(differentiationForX.differentiate(sin("x")));

    Term termToExpect(createExpressionIfPossible({sin(xPlusOne), "-", sin("x")}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksForEquation)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Term term1ForEquation(Polynomial{Monomial(1, {{"x", 6}}), Monomial(-2, {{"x", 1}})});
    Term term2ForEquation(Polynomial{Monomial(3, {{"y", 6}}), Monomial(1, {{"y", 5}}), Monomial(-1, {{"y", 2}})});
    Equation equation(term1ForEquation, "=", term2ForEquation);

    Equation equationToVerify(differentiationForX.differentiate(equation));

    string stringToExpect("(6[x^5] + 15[x^4] + 20[x^3] + 15[x^2] + 6[x] + -1) = 0");
    EXPECT_EQ(stringToExpect, convertToString(equationToVerify));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateMultipleTimesWorksForTerm)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Term termToTest(Monomial(3, {{"x", 4}}));

    Term termToVerify1(differentiationForX.differentiateMultipleTimes(termToTest, 0));
    Term termToVerify2(differentiationForX.differentiateMultipleTimes(termToTest, 1));
    Term termToVerify3(differentiationForX.differentiateMultipleTimes(termToTest, 2));

    Term termToExpect1(Monomial(3, {{"x", 4}}));
    Term termToExpect2(Polynomial
    {Monomial(12, {{"x", 3}}),
     Monomial(18, {{"x", 2}}),
     Monomial(12, {{"x", 1}}),
     Monomial(3, {})});
    Term termToExpect3(Polynomial
    {Monomial(36, {{"x", 2}}),
     Monomial(72, {{"x", 1}}),
     Monomial(42, {})});
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateMultipleTimesWorksForEquation)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Equation equationToTest(Monomial(3, {{"x", 4}}), "=", Monomial(5, {{"x", 6}}));

    Equation equationToVerify1(differentiationForX.differentiateMultipleTimes(equationToTest, 0));
    Equation equationToVerify2(differentiationForX.differentiateMultipleTimes(equationToTest, 1));
    Equation equationToVerify3(differentiationForX.differentiateMultipleTimes(equationToTest, 2));

    string stringToExpect1("3[x^4] = 5[x^6]");
    string stringToExpect2("(30[x^5] + 75[x^4] + 88[x^3] + 57[x^2] + 18[x] + 2) = 0");
    string stringToExpect3("(75[x^4] + 300[x^3] + 507[x^2] + 414[x] + 134) = 0");
    EXPECT_EQ(stringToExpect1, convertToString(equationToVerify1));
    EXPECT_EQ(stringToExpect2, convertToString(equationToVerify2));
    EXPECT_EQ(stringToExpect3, convertToString(equationToVerify3));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateTermWorks)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Term xPlusOne(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term polynomialTerm(Polynomial{Monomial(-2, {{"x", 2}}), Monomial(8, {{"x", 1}}), Monomial(5, {})});
    Expression expressionTerm{createExpressionIfPossible({3, "^", "x"})};

    Term termToVerify1(differentiationForX.differentiateTerm(5));
    Term termToVerify2(differentiationForX.differentiateTerm("x"));
    Term termToVerify3(differentiationForX.differentiateTerm(Monomial(5, {{"x", 3}})));
    Term termToVerify4(differentiationForX.differentiateTerm(polynomialTerm));
    Term termToVerify5(differentiationForX.differentiateTerm(expressionTerm));

    Term termToExpect1(0);
    Term termToExpect2(xPlusOne);
    Term termToExpect3(Polynomial{Monomial(15, {{"x", 2}}), Monomial(15, {{"x", 1}}), Monomial(5, {})});
    Term termToExpect4(Polynomial{Monomial(-4, {{"x", 1}}), Monomial(6, {})});
    Term termToExpect5(createExpressionIfPossible({3, "^", xPlusOne, "-", 3, "^", "x"}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateConstantWorks)
{
    DifferentiationForFiniteCalculus differentiationForX("x");

    EXPECT_EQ(AlbaNumber(0), differentiationForX.differentiateConstant(Constant(5)));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateVariableWorks)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Polynomial zeroPolynomial(createPolynomialFromNumber(0));
    Polynomial xPlusOne{Monomial(1, {{"x", 1}}), Monomial(1, {})};

    EXPECT_EQ(xPlusOne, differentiationForX.differentiateVariable(Variable("x")));
    EXPECT_EQ(zeroPolynomial, differentiationForX.differentiateVariable(Variable("y")));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateMonomialWorks)
{
    DifferentiationForFiniteCalculus differentiationForX("x");

    Term termToVerify1(differentiationForX.differentiateMonomial(Monomial(13, {})));
    Term termToVerify2(differentiationForX.differentiateMonomial(Monomial(5, {{"x", 7}, {"y", 8}, {"z", 9}})));
    Term termToVerify3(differentiationForX.differentiateMonomial(Monomial(5, {{"x", -2}, {"y", 8}, {"z", 9}})));

    Term termToExpect1(0);
    Term termToExpect2(Polynomial(
    {Monomial(35, {{"x", 6}, {"y", 8}, {"z", 9}}),
     Monomial(105, {{"x", 5}, {"y", 8}, {"z", 9}}),
     Monomial(175, {{"x", 4}, {"y", 8}, {"z", 9}}),
     Monomial(175, {{"x", 3}, {"y", 8}, {"z", 9}}),
     Monomial(105, {{"x", 2}, {"y", 8}, {"z", 9}}),
     Monomial(35, {{"x", 1}, {"y", 8}, {"z", 9}}),
     Monomial(5, {{"y", 8}, {"z", 9}})}));
    Term termToExpect3(createExpressionIfPossible(
    {Monomial(-5, {{"x", -2}, {"y", 8}, {"z", 9}}), "+",
     createExpressionIfPossible(
     {Monomial(5, {{"y", 8}, {"z", 9}}), "/", Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(1, {})}
     })}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiatePolynomialWorks)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Polynomial polynomial1{Monomial(13, {})};
    Polynomial polynomial2{Monomial(-1, {{"x", 2}, {"y", -3}}), Monomial(-4, {{"x", 3}, {"z", -6}})};
    Polynomial polynomial3{Monomial(-1, {{"x", -2}, {"y", -3}}), Monomial(-4, {{"x", -5}, {"z", -6}})};

    Term termToVerify1(differentiationForX.differentiatePolynomial(polynomial1));
    Term termToVerify2(differentiationForX.differentiatePolynomial(polynomial2));
    Term termToVerify3(differentiationForX.differentiatePolynomial(polynomial3));

    Term termToExpect1(0);
    Term termToExpect2(Polynomial
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
    {1, "/", polynomial2OfTerm3}));
    Expression expression2OfTerm3(createExpressionIfPossible(
    {4, "/", polynomial3OfTerm3}));
    Term termToExpect3(createExpressionIfPossible(
    {polynomial1OfTerm3, "-", expression1OfTerm3, "-", expression2OfTerm3}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateExpressionWorks)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Term xPlusOne(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Expression expression01{createExpressionIfPossible({"x"})};
    Expression expression02{createExpressionIfPossible({3, "^", "x"})};

    Term termToVerify1(differentiationForX.differentiateExpression(expression01));
    Term termToVerify2(differentiationForX.differentiateExpression(expression02));

    Term termToExpect1(1);
    Term termToExpect2(createExpressionIfPossible({3, "^", xPlusOne, "-", 3, "^", "x"}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateWorksWithTermRaiseToTerm)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Term termToTest1(createExpressionIfPossible({"n", "^", "n"}));
    Term termToTest2(createExpressionIfPossible({"n", "^", "x"}));
    Term termToTest3(createExpressionIfPossible({"x", "^", "n"}));
    Term termToTest4(createExpressionIfPossible({"x", "^", "x"}));

    Term termToVerify1(differentiationForX.differentiate(termToTest1));
    Term termToVerify2(differentiationForX.differentiate(termToTest2));
    Term termToVerify3(differentiationForX.differentiate(termToTest3));
    Term termToVerify4(differentiationForX.differentiate(termToTest4));

    Term termToExpect1(0);
    string stringToExpect2("((n^(1[x] + 1))-(n^x))");
    string stringToExpect3("(((1[x] + 1)^n)-(x^n))");
    string stringToExpect4("(((1[x] + 1)^(1[x] + 1))-(x^x))");
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(stringToExpect2, convertToString(termToVerify2));
    EXPECT_EQ(stringToExpect3, convertToString(termToVerify3));
    EXPECT_EQ(stringToExpect4, convertToString(termToVerify4));
}

TEST(DifferentiationForFiniteCalculusTest, DifferentiateFunctionWorks)
{
    DifferentiationForFiniteCalculus differentiationForX("x");
    Term xPlusOne(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});

    Term termToVerify(differentiationForX.differentiate(sin("x")));

    Term termToExpect(createExpressionIfPossible({sin(xPlusOne), "-", sin("x")}));
    EXPECT_EQ(termToExpect, termToVerify);
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

    Equation equationToVerify1(differentiationForX.differentiate(equation1));
    Equation equationToVerify2(differentiationForX.differentiate(equation2));

    string stringToExpect1("(6[x^5] + 15[x^4] + 20[x^3] + 15[x^2] + 6[x] + -1) = 0");
    string stringToExpect2("(12[x^3][y^2] + 18[x^2][y^2] + 12[x][y^2] + -7[y^3] + 3[y^2]) = 0");
    EXPECT_EQ(stringToExpect1, convertToString(equationToVerify1));
    EXPECT_EQ(stringToExpect2, convertToString(equationToVerify2));
}

}

}
