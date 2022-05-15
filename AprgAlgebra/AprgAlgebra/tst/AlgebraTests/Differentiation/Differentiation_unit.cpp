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

TEST(DifferentiationTest, DifferentiateWorksForTerm)
{
    Differentiation differentiationForX("x");
    Term constantTerm(5);
    Term variableTerm("x");
    Term monomialTerm(Monomial(1, {{"x", 8}}));
    Term polynomialTerm(Polynomial{Monomial(7, {{"x", 4}}), Monomial(-2, {{"x", 3}}), Monomial(8, {{"x", 1}}), Monomial(5, {})});
    Term expressionTerm(createExpressionIfPossible({cos("x")}));
    Term functionTerm(sin("x"));

    Term termToVerify1(differentiationForX.differentiate(constantTerm));
    Term termToVerify2(differentiationForX.differentiate(variableTerm));
    Term termToVerify3(differentiationForX.differentiate(monomialTerm));
    Term termToVerify4(differentiationForX.differentiate(polynomialTerm));
    Term termToVerify5(differentiationForX.differentiate(expressionTerm));
    Term termToVerify6(differentiationForX.differentiate(functionTerm));

    Term termToExpect1(0);
    Term termToExpect2(1);
    Term termToExpect3(Monomial(8, {{"x", 7}}));
    Term termToExpect4(Polynomial{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})});
    Term termToExpect5(createExpressionIfPossible({-1, "*", sin("x")}));
    Term termToExpect6(cos("x"));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
    EXPECT_EQ(termToExpect6, termToVerify6);
}

TEST(DifferentiationTest, DifferentiateWorksForConstant)
{
    Differentiation differentiationForX("x");

    EXPECT_EQ(Term(0), differentiationForX.differentiate(Constant(5)));
}

TEST(DifferentiationTest, DifferentiateWorksForVariable)
{
    Differentiation differentiationForXWithY("x", {"y"});

    Term termToVerify1(differentiationForXWithY.differentiate(Variable("x")));
    Term termToVerify2(differentiationForXWithY.differentiate(Variable("y")));
    Term termToVerify3(differentiationForXWithY.differentiate(Variable("a")));

    Term termToExpect1(1);
    Term termToExpect2(Variable("d[y]/d[x]"));
    Term termToExpect3(0);
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(DifferentiationTest, DifferentiateWorksForMonomial)
{
    Differentiation differentiationForXWithY("x", {"y"});

    Term termToVerify1(differentiationForXWithY.differentiate(Monomial(13, {})));
    Term termToVerify2(differentiationForXWithY.differentiate(Monomial(5, {{"d[y]/d[x]", 6}, {"x", 7}, {"y", 8}, {"z", 9}})));

    Term termToExpect1(0);
    Term termToExpect2(Polynomial(
    {Monomial(30, {{"d2[y]/d[x]2", 1}, {"d[y]/d[x]", 5}, {"x", 7}, {"y", 8}, {"z", 9}}),
     Monomial(35, {{"d[y]/d[x]", 6}, {"x", 6}, {"y", 8}, {"z", 9}}),
     Monomial(40, {{"d[y]/d[x]", 1}, {"x", 7}, {"y", 7}, {"z", 9}})}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
}

TEST(DifferentiationTest, DifferentiateWorksForPolynomial)
{
    Differentiation differentiationForXWithY("x", {"y"});
    Polynomial polynomial1{Monomial(13, {})};
    Polynomial polynomial2{Monomial(-1, {{"x", -2}, {"y", -3}}), Monomial(-4, {{"x", -5}, {"z", -6}})};

    Term termToVerify1(differentiationForXWithY.differentiate(polynomial1));
    Term termToVerify2(differentiationForXWithY.differentiate(polynomial2));

    Term termToExpect1(0);
    Term termToExpect2(
                Polynomial{
                    Monomial(3, {{"d[y]/d[x]", 1}, {"x", -2}, {"y", -4}}),
                    Monomial(2, {{"x", -3}, {"y", -3}}),
                    Monomial(20, {{"x", -6}, {"z", -6}})});
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
}

TEST(DifferentiationTest, DifferentiateWorksForExpression)
{
    Differentiation differentiationForX("x");
    Expression expression01{createExpressionIfPossible({"x"})};
    Expression expression02{createExpressionIfPossible({cos("x"), "^", 3})};

    Term termToVerify1(differentiationForX.differentiate(expression01));
    Term termToVerify2(differentiationForX.differentiate(expression02));

    Term cosSquared{createExpressionIfPossible({cos("x"), "^", 2})};
    Term termToExpect01(1);
    Term termToExpect02(createExpressionIfPossible({-3, "*", cosSquared, "*", sin("x")}));
    EXPECT_EQ(termToExpect01, termToVerify1);
    EXPECT_EQ(termToExpect02, termToVerify2);
}

TEST(DifferentiationTest, DifferentiateWorksForFunction)
{
    Differentiation differentiationForX("x");

    EXPECT_EQ(Term(cos("x")), differentiationForX.differentiate(sin("x")));
}

TEST(DifferentiationTest, DifferentiateWorksForEquation)
{
    Differentiation differentiationForXWithY("x", {"y"});
    Term term1ForEquation1(Polynomial{Monomial(1, {{"x", 6}}), Monomial(-2, {{"x", 1}})});
    Term term2ForEquation1(Polynomial{Monomial(3, {{"y", 6}}), Monomial(1, {{"y", 5}}), Monomial(-1, {{"y", 2}})});
    Equation equation1(term1ForEquation1, "=", term2ForEquation1);

    EXPECT_EQ("(18[d[y]/d[x]][y^5] + 5[d[y]/d[x]][y^4] + -6[x^5] + -2[d[y]/d[x]][y] + 2) = 0",
              differentiationForXWithY.differentiate(equation1).getDisplayableString());
}

TEST(DifferentiationTest, DifferentiateWithDefiniteValueWorks)
{
    Differentiation differentiationForX("x");
    Term termToTest1(Monomial(1, {{"x", 1}}));
    Term termToTest2(Monomial(1, {{"x", 2}}));
    Term termToTest3(Monomial(1, {{"x", 3}}));

    Term termToVerify1(differentiationForX.differentiateWithDefiniteValue(termToTest1, 5));
    Term termToVerify2(differentiationForX.differentiateWithDefiniteValue(termToTest2, 5));
    Term termToVerify3(differentiationForX.differentiateWithDefiniteValue(termToTest3, 5));

    Term termToExpect1(1);
    Term termToExpect2(10);
    Term termToExpect3(75);
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(DifferentiationTest, DifferentiateMultipleTimesWorksForTerm)
{
    Differentiation differentiationForX("x");
    Term termToTest(Monomial(3, {{"x", 4}}));

    Term termToVerify1(differentiationForX.differentiateMultipleTimes(termToTest, 0));
    Term termToVerify2(differentiationForX.differentiateMultipleTimes(termToTest, 1));
    Term termToVerify3(differentiationForX.differentiateMultipleTimes(termToTest, 2));

    Term termToExpect1(Monomial(3, {{"x", 4}}));
    Term termToExpect2(Monomial(12, {{"x", 3}}));
    Term termToExpect3(Monomial(36, {{"x", 2}}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
}

TEST(DifferentiationTest, DifferentiateMultipleTimesWorksForEquation)
{
    Differentiation differentiationForX("x");
    Equation equationToTest(Monomial(3, {{"x", 4}}), "=", Monomial(5, {{"x", 6}}));

    Equation equationToVerify1(differentiationForX.differentiateMultipleTimes(equationToTest, 0));
    Equation equationToVerify2(differentiationForX.differentiateMultipleTimes(equationToTest, 1));
    Equation equationToVerify3(differentiationForX.differentiateMultipleTimes(equationToTest, 2));

    Equation equationToExpect1(Monomial(3, {{"x", 4}}), "=", Monomial(5, {{"x", 6}}));
    Equation equationToExpect2(Polynomial{Monomial(5, {{"x", 5}}), Monomial(-2, {{"x", 3}})}, "=", 0);
    Equation equationToExpect3(Polynomial{Monomial(25, {{"x", 4}}), Monomial(-6, {{"x", 2}})}, "=", 0);
    EXPECT_EQ(equationToExpect1, equationToVerify1);
    EXPECT_EQ(equationToExpect2, equationToVerify2);
    EXPECT_EQ(equationToExpect3, equationToVerify3);
}

TEST(DifferentiationTest, DifferentiateConstantWorks)
{
    Differentiation differentiationForX("x");

    EXPECT_EQ(AlbaNumber(0), differentiationForX.differentiateConstant(Constant(5)));
}

TEST(DifferentiationTest, DifferentiateVariableWorks)
{
    Differentiation differentiationForXWithY("x", {"y"});

    Monomial monomialToVerify1(differentiationForXWithY.differentiateVariable(Variable("x")));
    Monomial monomialToVerify2(differentiationForXWithY.differentiateVariable(Variable("y")));
    Monomial monomialToVerify3(differentiationForXWithY.differentiateVariable(Variable("a")));
    Monomial monomialToVerify4(differentiationForXWithY.differentiateVariable(Variable("d[y]/d[x]")));

    Monomial monomialToExpect1(1, {});
    Monomial monomialToExpect2(1, {{"d[y]/d[x]", 1}});
    Monomial monomialToExpect3(0, {});
    Monomial monomialToExpect4(1, {{"d2[y]/d[x]2", 1}});
    EXPECT_EQ(monomialToExpect1, monomialToVerify1);
    EXPECT_EQ(monomialToExpect2, monomialToVerify2);
    EXPECT_EQ(monomialToExpect3, monomialToVerify3);
    EXPECT_EQ(monomialToExpect4, monomialToVerify4);
}

TEST(DifferentiationTest, DifferentiateMonomialWorks)
{
    Differentiation differentiationForXWithY("x", {"y"});

    Polynomial polynomialToVerify1(differentiationForXWithY.differentiateMonomial(Monomial(13, {})));
    Polynomial polynomialToVerify2(differentiationForXWithY.differentiateMonomial(Monomial(13, {{"x", 0}})));
    Polynomial polynomialToVerify3(differentiationForXWithY.differentiateMonomial(Monomial(1, {{"x", 8}})));
    Polynomial polynomialToVerify4(differentiationForXWithY.differentiateMonomial(Monomial(3, {{"x", -5}})));
    Polynomial polynomialToVerify5(differentiationForXWithY.differentiateMonomial(Monomial(3, {{"z", -5}})));
    Polynomial polynomialToVerify6(differentiationForXWithY.differentiateMonomial(Monomial(5, {{"d[y]/d[x]", 6}, {"x", 7}, {"y", 8}, {"z", 9}})));

    Polynomial polynomialToExpect1;
    Polynomial polynomialToExpect2;
    Polynomial polynomialToExpect3{Monomial(8, {{"x", 7}})};
    Polynomial polynomialToExpect4{Monomial(-15, {{"x", -6}})};
    Polynomial polynomialToExpect5;
    Polynomial polynomialToExpect6
    {Monomial(30, {{"d2[y]/d[x]2", 1}, {"d[y]/d[x]", 5}, {"x", 7}, {"y", 8}, {"z", 9}}),
                Monomial(35, {{"d[y]/d[x]", 6}, {"x", 6}, {"y", 8}, {"z", 9}}),
                Monomial(40, {{"d[y]/d[x]", 1}, {"x", 7}, {"y", 7}, {"z", 9}})};
    EXPECT_EQ(polynomialToExpect1, polynomialToVerify1);
    EXPECT_EQ(polynomialToExpect2, polynomialToVerify2);
    EXPECT_EQ(polynomialToExpect3, polynomialToVerify3);
    EXPECT_EQ(polynomialToExpect4, polynomialToVerify4);
    EXPECT_EQ(polynomialToExpect5, polynomialToVerify5);
    EXPECT_EQ(polynomialToExpect6, polynomialToVerify6);
}

TEST(DifferentiationTest, DifferentiatePolynomialWorks)
{
    Differentiation differentiationForXWithY("x", {"y"});
    Polynomial polynomial1{Monomial(0, {})};
    Polynomial polynomial2{Monomial(5, {{"x", 0}})};
    Polynomial polynomial3{Monomial(7, {{"x", 4}}), Monomial(-2, {{"x", 3}}), Monomial(8, {{"x", 1}}), Monomial(5, {})};
    Polynomial polynomial4{Monomial(-1, {{"x", -2}, {"y", -3}}), Monomial(-4, {{"x", -5}, {"z", -6}})};
    Polynomial polynomial5{Monomial(1, {{"a", 2}}), Monomial(3, {{"b", 4}}), Monomial(5, {{"c", 6}}), Monomial(7, {})};

    Polynomial polynomialToVerify1(differentiationForXWithY.differentiatePolynomial(polynomial1));
    Polynomial polynomialToVerify2(differentiationForXWithY.differentiatePolynomial(polynomial2));
    Polynomial polynomialToVerify3(differentiationForXWithY.differentiatePolynomial(polynomial3));
    Polynomial polynomialToVerify4(differentiationForXWithY.differentiatePolynomial(polynomial4));
    Polynomial polynomialToVerify5(differentiationForXWithY.differentiatePolynomial(polynomial5));

    Polynomial polynomialToExpect1;
    Polynomial polynomialToExpect2;
    Polynomial polynomialToExpect3{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};
    Polynomial polynomialToExpect4
    {Monomial(3, {{"d[y]/d[x]", 1}, {"x", -2}, {"y", -4}}),
                Monomial(2, {{"x", -3}, {"y", -3}}),
                Monomial(20, {{"x", -6}, {"z", -6}})};
    Polynomial polynomialToExpect5;
    EXPECT_EQ(polynomialToExpect1, polynomialToVerify1);
    EXPECT_EQ(polynomialToExpect2, polynomialToVerify2);
    EXPECT_EQ(polynomialToExpect3, polynomialToVerify3);
    EXPECT_EQ(polynomialToExpect4, polynomialToVerify4);
    EXPECT_EQ(polynomialToExpect5, polynomialToVerify5);
}

TEST(DifferentiationTest, DifferentiateExpressionWorks)
{
    Differentiation differentiationForXWithY("x", {"y"});
    Expression expression01{createExpressionIfPossible({"x"})};
    Expression expression02{createExpressionIfPossible({cos("x")})};
    Expression expression03{createExpressionIfPossible({cos("y")})};
    Expression expression04{createExpressionIfPossible({sin("x"), "+", cos("x")})};
    Expression expression05{createExpressionIfPossible({sin("x"), "-", cos("x")})};
    Expression expression06{createExpressionIfPossible({sin("x"), "*", cos("x")})};
    Expression expression07{createExpressionIfPossible({sin("x"), "/", cos("x")})};
    Expression expression08{createExpressionIfPossible({cos("x"), "^", 3})};
    Expression expression09{createExpressionIfPossible({3, "^", cos("x")})};
    Expression expression10{createExpressionIfPossible({sin("x"), "^", cos("x")})};

    Term expressionToVerify01(differentiationForXWithY.differentiateExpression(expression01));
    Term expressionToVerify02(differentiationForXWithY.differentiateExpression(expression02));
    Term expressionToVerify03(differentiationForXWithY.differentiateExpression(expression03));
    Term expressionToVerify04(differentiationForXWithY.differentiateExpression(expression04));
    Term expressionToVerify05(differentiationForXWithY.differentiateExpression(expression05));
    Term expressionToVerify06(differentiationForXWithY.differentiateExpression(expression06));
    Term expressionToVerify07(differentiationForXWithY.differentiateExpression(expression07));
    Term expressionToVerify08(differentiationForXWithY.differentiateExpression(expression08));
    Term expressionToVerify09(differentiationForXWithY.differentiateExpression(expression09));
    Term expressionToVerify10(differentiationForXWithY.differentiateExpression(expression10));

    Term sinSquared{createExpressionIfPossible({sin("x"), "^", 2})};
    Term cosSquared{createExpressionIfPossible({cos("x"), "^", 2})};
    Term termToExpect01(1);
    Term termToExpect02(createExpressionIfPossible({-1, "*", sin("x")}));
    Term termToExpect03(createExpressionIfPossible({Monomial(-1, {{"d[y]/d[x]", 1}}), "*", sin("y")}));
    Term termToExpect04(createExpressionIfPossible({cos("x"), "-", sin("x")}));
    Term termToExpect05(createExpressionIfPossible({cos("x"), "+", sin("x")}));
    Term termToExpect06(createExpressionIfPossible({cosSquared, "-", sinSquared}));
    Term expectedNumerator07(createExpressionIfPossible({cosSquared, "+", sinSquared}));
    Term expectedDenominator07(createExpressionIfPossible({cosSquared}));
    Term termToExpect07(createExpressionIfPossible({expectedNumerator07, "/", expectedDenominator07}));
    Term termToExpect08(createExpressionIfPossible({-3, "*", cosSquared, "*", sin("x")}));
    Term termToExpect09(createExpressionIfPossible({-1.09861228866811, "*", 3, "^", cos("x"), "*", sin("x")}));
    EXPECT_EQ(termToExpect01, expressionToVerify01);
    EXPECT_EQ(termToExpect02, expressionToVerify02);
    EXPECT_EQ(termToExpect03, expressionToVerify03);
    EXPECT_EQ(termToExpect04, expressionToVerify04);
    EXPECT_EQ(termToExpect05, expressionToVerify05);
    EXPECT_EQ(termToExpect06, expressionToVerify06);
    EXPECT_EQ(termToExpect07, expressionToVerify07);
    EXPECT_EQ(termToExpect08, expressionToVerify08);
    EXPECT_EQ(termToExpect09, expressionToVerify09);
    EXPECT_TRUE(isNan(expressionToVerify10));
}

TEST(DifferentiationTest, DifferentiateFunctionWorksWithFunctionsInCommonFunctionLibrary)
{
    Differentiation differentiationForXWithY("x", {"y"});

    Term termToVerify01(differentiationForXWithY.differentiateFunction(abs("x")));
    Term termToVerify02(differentiationForXWithY.differentiateFunction(ln("x")));
    Term termToVerify03(differentiationForXWithY.differentiateFunction(log("x")));
    Term termToVerify04(differentiationForXWithY.differentiateFunction(sin("x")));
    Term termToVerify05(differentiationForXWithY.differentiateFunction(cos("x")));
    Term termToVerify06(differentiationForXWithY.differentiateFunction(cos("y")));
    Term termToVerify07(differentiationForXWithY.differentiateFunction(tan("x")));
    Term termToVerify08(differentiationForXWithY.differentiateFunction(csc("x")));
    Term termToVerify09(differentiationForXWithY.differentiateFunction(sec("x")));
    Term termToVerify10(differentiationForXWithY.differentiateFunction(cot("x")));
    Term termToVerify11(differentiationForXWithY.differentiateFunction(arcsin("x")));
    Term termToVerify12(differentiationForXWithY.differentiateFunction(arccos("x")));
    Term termToVerify13(differentiationForXWithY.differentiateFunction(arctan("x")));
    Term termToVerify14(differentiationForXWithY.differentiateFunction(arccsc("x")));
    Term termToVerify15(differentiationForXWithY.differentiateFunction(arcsec("x")));
    Term termToVerify16(differentiationForXWithY.differentiateFunction(arccot("x")));
    Term termToVerify17(differentiationForXWithY.differentiateFunction(sinh("x")));
    Term termToVerify18(differentiationForXWithY.differentiateFunction(cosh("x")));
    Term termToVerify19(differentiationForXWithY.differentiateFunction(tanh("x")));
    Term termToVerify20(differentiationForXWithY.differentiateFunction(csch("x")));
    Term termToVerify21(differentiationForXWithY.differentiateFunction(sech("x")));
    Term termToVerify22(differentiationForXWithY.differentiateFunction(coth("x")));

    Term cscSquared(createExpressionIfPossible({csc("x"), "^", 2}));
    Term termToExpect01(sgn("x"));
    Term termToExpect02(Monomial(1, {{"x", -1}}));
    Term termToExpect03(Monomial(2.302585092994046, {{"x", -1}}));
    Term termToExpect04(cos("x"));
    Term termToExpect05(createExpressionIfPossible({-1, "*", sin("x")}));
    Term termToExpect06(createExpressionIfPossible({Monomial(-1, {{"d[y]/d[x]", 1}}), "*", sin("y")}));
    Term termToExpect07(createExpressionIfPossible({sec("x"), "^", 2}));
    Term termToExpect08(createExpressionIfPossible({-1, "*", cot("x"), "*", csc("x")}));
    Term termToExpect09(createExpressionIfPossible({sec("x"), "*", tan("x")}));
    Term termToExpect10(createExpressionIfPossible({-1, "*", cscSquared}));
    string stringToExpect11("(1/((-1[x^2] + 1)^(1/2)))");
    string stringToExpect12("(-1/((-1[x^2] + 1)^(1/2)))");
    string stringToExpect13("(1/(1[x^2] + 1))");
    string stringToExpect14("(-1/x/((1[x] + -1)^(1/2))/((1[x] + 1)^(1/2)))");
    string stringToExpect15("(1/x/((1[x] + -1)^(1/2))/((1[x] + 1)^(1/2)))");
    string stringToExpect16("(-1/(1[x^2] + 1))");
    string stringToExpect17("cosh(x)");
    string stringToExpect18("sinh(x)");
    string stringToExpect19("(sech(x)^2)");
    string stringToExpect20("(-1*coth(x)*csch(x))");
    string stringToExpect21("(-1*sech(x)*tanh(x))");
    string stringToExpect22("(-1*(csch(x)^2))");
    EXPECT_EQ(termToExpect01, termToVerify01);
    EXPECT_EQ(termToExpect02, termToVerify02);
    EXPECT_EQ(termToExpect03, termToVerify03);
    EXPECT_EQ(termToExpect04, termToVerify04);
    EXPECT_EQ(termToExpect05, termToVerify05);
    EXPECT_EQ(termToExpect06, termToVerify06);
    EXPECT_EQ(termToExpect07, termToVerify07);
    EXPECT_EQ(termToExpect08, termToVerify08);
    EXPECT_EQ(termToExpect09, termToVerify09);
    EXPECT_EQ(termToExpect10, termToVerify10);
    EXPECT_EQ(stringToExpect11, termToVerify11.getDisplayableString());
    EXPECT_EQ(stringToExpect12, termToVerify12.getDisplayableString());
    EXPECT_EQ(stringToExpect13, termToVerify13.getDisplayableString());
    EXPECT_EQ(stringToExpect14, termToVerify14.getDisplayableString());
    EXPECT_EQ(stringToExpect15, termToVerify15.getDisplayableString());
    EXPECT_EQ(stringToExpect16, termToVerify16.getDisplayableString());
    EXPECT_EQ(stringToExpect17, termToVerify17.getDisplayableString());
    EXPECT_EQ(stringToExpect18, termToVerify18.getDisplayableString());
    EXPECT_EQ(stringToExpect19, termToVerify19.getDisplayableString());
    EXPECT_EQ(stringToExpect20, termToVerify20.getDisplayableString());
    EXPECT_EQ(stringToExpect21, termToVerify21.getDisplayableString());
    EXPECT_EQ(stringToExpect22, termToVerify22.getDisplayableString());
}

TEST(DifferentiationTest, DifferentiateFunctionWorksWithChainRule)
{
    Differentiation differentiationForX("x");
    Function functionToTest(sin(Monomial(10, {{"x", 8}})));

    Term termToVerify(differentiationForX.differentiateFunction(functionToTest));

    Term termToExpect(createExpressionIfPossible({Monomial(80, {{"x", 7}}), "*", cos(Monomial(10, {{"x", 8}}))}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(DifferentiationTest, DifferentiateEquationWorks)
{
    Differentiation differentiationForXWithY("x", {"y"});
    Term term1ForEquation1(Polynomial{Monomial(1, {{"x", 6}}), Monomial(-2, {{"x", 1}})});
    Term term2ForEquation1(Polynomial{Monomial(3, {{"y", 6}}), Monomial(1, {{"y", 5}}), Monomial(-1, {{"y", 2}})});
    Equation equation1(term1ForEquation1, "=", term2ForEquation1);
    Term term1ForEquation2(Polynomial{Monomial(3, {{"x", 4}, {"y", 2}}), Monomial(-7, {{"x", 1}, {"y", 3}})});
    Term term2ForEquation2(Polynomial{Monomial(4, {}), Monomial(8, {{"y", 1}})});
    Equation equation2(term1ForEquation2, "=", term2ForEquation2);

    Equation equationToVerify1(differentiationForXWithY.differentiateEquation(equation1));
    Equation equationToVerify2(differentiationForXWithY.differentiateEquation(equation2));

    string stringToExpect1("(18[d[y]/d[x]][y^5] + 5[d[y]/d[x]][y^4] + -6[x^5] + -2[d[y]/d[x]][y] + 2) = 0");
    string stringToExpect2("(6[d[y]/d[x]][x^4][y] + 12[x^3][y^2] + -21[d[y]/d[x]][x][y^2] + -7[y^3] + -8[d[y]/d[x]]) = 0");
    EXPECT_EQ(stringToExpect1, equationToVerify1.getDisplayableString());
    EXPECT_EQ(stringToExpect2, equationToVerify2.getDisplayableString());
}

TEST(DifferentiationTest, DifferentiateWorksOnOneOverPolynomial)
{
    Differentiation differentiationForX("x");
    Term numerator(1);
    Term denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(2, {{"x", 1}}), Monomial(2, {})});
    Term termToTest(createExpressionIfPossible({numerator, "/", denominator}));

    Term termToVerify(differentiationForX.differentiate(termToTest));

    Term expectedNumeratorPart(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})});
    Term expectedNumerator(createExpressionIfPossible({-2, "*", expectedNumeratorPart}));
    Term expectedDenominator(Polynomial{Monomial(1, {{"x", 4}}), Monomial(4, {{"x", 3}}), Monomial(8, {{"x", 2}}), Monomial(8, {{"x", 1}}), Monomial(4, {})});
    Term termToExpect(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(termToExpect, termToVerify);
}

TEST(DifferentiationTest, DifferentiateTwoMultipliedTermsWorks)
{
    Differentiation differentiationForX("x");
    Term term1(Polynomial{Monomial(2, {{"x", 2}}), Monomial(-4, {{"x", 1}})});
    Term term2(Polynomial{Monomial(3, {{"x", 2}}), Monomial(7, {{"x", 1}})});

    Term termToVerify(differentiationForX.differentiateTwoMultipliedTerms(term1, term2));

    string stringToExpect("(((2[x^2] + -4[x])*(6[x] + 7))+((3[x^2] + 7[x])*(4[x] + -4)))");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(DifferentiationTest, DifferentiateTwoDividedTermsWorks)
{
    Differentiation differentiationForX("x");
    Term numerator(Polynomial{Monomial(2, {{"x", 3}}), Monomial(4, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {{"x", 1}}), Monomial(1, {})});

    Term termToVerify(differentiationForX.differentiateTwoDividedTerms(numerator, denominator));

    string stringToExpect("((((1[x^2] + -4[x] + 1)*6[x^2])-((2[x^3] + 4)*(2[x] + -4)))/((1[x^2] + -4[x] + 1)^2))");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(DifferentiationTest, DifferentiateWorksWithTermRaiseToTerm)
{
    Differentiation differentiationForX("x");
    Term termToTest1(createExpressionIfPossible({"n", "^", "n"}));
    Term termToTest2(createExpressionIfPossible({"n", "^", "x"}));
    Term termToTest3(createExpressionIfPossible({"x", "^", "n"}));
    Term termToTest4(createExpressionIfPossible({"x", "^", "x"}));

    Term termToVerify1(differentiationForX.differentiate(termToTest1));
    Term termToVerify2(differentiationForX.differentiate(termToTest2));
    Term termToVerify3(differentiationForX.differentiate(termToTest3));
    Term termToVerify4(differentiationForX.differentiate(termToTest4));

    Term termToExpect1(0);
    Term termToExpect2(createExpressionIfPossible({"n", "^", "x", "*", ln("n")}));
    Term exponentForTerm3(Polynomial{Monomial(1, {{"n", 1}}), Monomial(-1, {})});
    Term termToExpect3(createExpressionIfPossible({"n", "*", "x", "^", exponentForTerm3}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_TRUE(isNan(termToVerify4));
}

TEST(DifferentiationTest, DifferentiateWorksWithDivisionExpressionRaiseToAConstant)
{
    Differentiation differentiationForX("x");
    Term subTerm1(createExpressionIfPossible({2, "/", Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {})}}));
    Term termToTest(createExpressionIfPossible({subTerm1, "^", 5}));

    Term termToVerify(differentiationForX.differentiate(termToTest));

    string stringToExpect("(-160/((1[x] + -1)^6))");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(DifferentiationTest, DifferentiateWorksWithChainRule)
{
    Differentiation differentiationForX("x");
    Term termToTest(createExpressionIfPossible({sec(Monomial(2, {{"x", 2}})), "^", 4}));

    Term termToVerify(differentiationForX.differentiate(termToTest));

    string stringToExpect("(16[x]*(sec(2[x^2])^4)*tan(2[x^2]))");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

TEST(DifferentiationTest, DifferentiateWorksWithSquareRootOfAPolynomial)
{
    Differentiation differentiationForX("x");
    Polynomial subPolynomial{Monomial(2, {{"x", 3}}), Monomial(-4, {{"x", 1}}), Monomial(5, {})};
    Term termToTest(createExpressionIfPossible({subPolynomial, "^", AlbaNumber::createFraction(1, 2)}));

    Term termToVerify(differentiationForX.differentiate(termToTest));

    string stringToExpect("((3[x^2] + -2)/((2[x^3] + -4[x] + 5)^(1/2)))");
    EXPECT_EQ(stringToExpect, termToVerify.getDisplayableString());
}

}

}
