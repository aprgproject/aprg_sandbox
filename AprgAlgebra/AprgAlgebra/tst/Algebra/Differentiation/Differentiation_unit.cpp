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

    EXPECT_EQ(Term(Constant(0)), differentiationForX.differentiate(Term(5)));
}

TEST(DifferentiationTest, DifferentiateWorksForConstant)
{
    Differentiation differentiationForX("x");

    EXPECT_EQ(Term(Constant(0)), differentiationForX.differentiate(Constant(5)));
}

TEST(DifferentiationTest, DifferentiateWorksForVariable)
{
    Differentiation differentiationForXWithY("x", {"y"});

    EXPECT_EQ(Term(1), differentiationForXWithY.differentiate(Variable("x")));
    EXPECT_EQ(Term(Variable("d[y]/d[x]")), differentiationForXWithY.differentiate(Variable("y")));
    EXPECT_EQ(Term(Constant(0)), differentiationForXWithY.differentiate(Variable("a")));
}

TEST(DifferentiationTest, DifferentiateWorksForMonomial)
{
    Differentiation differentiationForXWithY("x", {"y"});

    Term expectedTerm1(Constant(0));
    Term expectedTerm2(Polynomial(
        {Monomial(30, {{"d2[y]/d[x]2", 1}, {"d[y]/d[x]", 5}, {"x", 7}, {"y", 8}, {"z", 9}}),
         Monomial(35, {{"d[y]/d[x]", 6}, {"x", 6}, {"y", 8}, {"z", 9}}),
         Monomial(40, {{"d[y]/d[x]", 1}, {"x", 7}, {"y", 7}, {"z", 9}})}));
    EXPECT_EQ(expectedTerm1, differentiationForXWithY.differentiate(Monomial(13, {})));
    EXPECT_EQ(expectedTerm2, differentiationForXWithY.differentiate(Monomial(5, {{"d[y]/d[x]", 6}, {"x", 7}, {"y", 8}, {"z", 9}})));
}

TEST(DifferentiationTest, DifferentiateWorksForPolynomial)
{
    Differentiation differentiationForXWithY("x", {"y"});
    Polynomial polynomial1{Monomial(13, {})};
    Polynomial polynomial2{Monomial(-1, {{"x", -2}, {"y", -3}}), Monomial(-4, {{"x", -5}, {"z", -6}})};

    Term expectedTerm1(Constant(0));
    Term expectedTerm2(
                Polynomial{
        Monomial(3, {{"d[y]/d[x]", 1}, {"x", -2}, {"y", -4}}),
                Monomial(2, {{"x", -3}, {"y", -3}}),
                Monomial(20, {{"x", -6}, {"z", -6}})});
    EXPECT_EQ(expectedTerm1, differentiationForXWithY.differentiate(polynomial1));
    EXPECT_EQ(expectedTerm2, differentiationForXWithY.differentiate(polynomial2));
}

TEST(DifferentiationTest, DifferentiateWorksForExpression)
{
    Differentiation differentiationForX("x");
    Term x("x");
    Expression expression01{createExpressionIfPossible({x})};
    Expression expression02{createExpressionIfPossible({cos(x), Term("^"), Term(3)})};

    Term cosSquared{createExpressionIfPossible({cos(x), Term("^"), Term(2)})};
    Term expectedTerm01(1);
    Term expectedTerm02(createExpressionIfPossible({Term(-3), Term("*"), cosSquared, Term("*"), sin(x)}));
    EXPECT_EQ(expectedTerm01, differentiationForX.differentiate(expression01));
    EXPECT_EQ(expectedTerm02, differentiationForX.differentiate(expression02));
}

TEST(DifferentiationTest, DifferentiateWorksForFunction)
{
    Differentiation differentiationForX("x");

    Term x("x");
    EXPECT_EQ(Term(cos(x)), differentiationForX.differentiate(sin(x)));
}

TEST(DifferentiationTest, DifferentiateWorksForEquation)
{
    Differentiation differentiationForXWithY("x", {"y"});
    Term term1ForEquation1(Polynomial{Monomial(1, {{"x", 6}}), Monomial(-2, {{"x", 1}})});
    Term term2ForEquation1(Polynomial{Monomial(3, {{"y", 6}}), Monomial(1, {{"y", 5}}), Monomial(-1, {{"y", 2}})});
    Equation equation1(term1ForEquation1, "=", term2ForEquation1);

    EXPECT_EQ("(18[d[y]/d[x]][y^5] + 5[d[y]/d[x]][y^4] + -6[x^5] + -2[d[y]/d[x]][y] + 2) = 0", differentiationForXWithY.differentiate(equation1).getDisplayableString());
}

TEST(DifferentiationTest, DifferentiateMultipleTimesWorksForTerm)
{
    Differentiation differentiationForX("x");

    Term termToTest(Monomial(3, {{"x", 4}}));
    EXPECT_EQ(Term(Monomial(3, {{"x", 4}})), differentiationForX.differentiateMultipleTimes(termToTest, 0));
    EXPECT_EQ(Term(Monomial(12, {{"x", 3}})), differentiationForX.differentiateMultipleTimes(termToTest, 1));
    EXPECT_EQ(Term(Monomial(36, {{"x", 2}})), differentiationForX.differentiateMultipleTimes(termToTest, 2));
}

TEST(DifferentiationTest, DifferentiateMultipleTimesWorksForEquation)
{
    Differentiation differentiationForX("x");

    Equation equationToTest(Term(Monomial(3, {{"x", 4}})), "=", Term(Monomial(5, {{"x", 6}})));
    Equation equationToExpect1(Term(Monomial(3, {{"x", 4}})), "=", Term(Monomial(5, {{"x", 6}})));
    EXPECT_EQ(equationToExpect1, differentiationForX.differentiateMultipleTimes(equationToTest, 0));
    Equation equationToExpect2(Term(Polynomial({Monomial(30, {{"x", 5}}), Monomial(-12, {{"x", 3}})})), "=", Term(Constant(0)));
    EXPECT_EQ(equationToExpect2, differentiationForX.differentiateMultipleTimes(equationToTest, 1));
    Equation equationToExpect3(Term(Polynomial({Monomial(150, {{"x", 4}}), Monomial(-36, {{"x", 2}})})), "=", Term(Constant(0)));
    EXPECT_EQ(equationToExpect3, differentiationForX.differentiateMultipleTimes(equationToTest, 2));
}

TEST(DifferentiationTest, DifferentiateTermWorks)
{
    Differentiation differentiationForX("x");
    Term x("x");
    Term polynomialTerm(Polynomial({Monomial(7, {{"x", 4}}), Monomial(-2, {{"x", 3}}), Monomial(8, {{"x", 1}}), Monomial(5, {})}));
    Term expressionTerm(createExpressionIfPossible({cos(x)}));

    Term expectedTerm1(Polynomial({Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})}));
    Term expectedTerm2(createExpressionIfPossible({Term(-1), Term("*"), sin(x)}));
    Term expectedTerm3(cos(x));
    EXPECT_EQ(Term(Constant(0)), differentiationForX.differentiateTerm(Term(5)));
    EXPECT_EQ(Term(1), differentiationForX.differentiateTerm(Term("x")));
    EXPECT_EQ(Term(Monomial(8, {{"x", 7}})), differentiationForX.differentiateTerm(Term(Monomial(1, {{"x", 8}}))));
    EXPECT_EQ(expectedTerm1, differentiationForX.differentiateTerm(polynomialTerm));
    EXPECT_EQ(expectedTerm2, differentiationForX.differentiateTerm(expressionTerm));
    EXPECT_EQ(expectedTerm3, differentiationForX.differentiateTerm(Term(sin(x))));
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
    EXPECT_EQ(Monomial(1, {{"d[y]/d[x]", 1}}), differentiationForXWithY.differentiateVariable(Variable("y")));
    EXPECT_EQ(Monomial(0, {}), differentiationForXWithY.differentiateVariable(Variable("a")));
    EXPECT_EQ(Monomial(1, {{"d2[y]/d[x]2", 1}}), differentiationForXWithY.differentiateVariable(Variable("d[y]/d[x]")));
}

TEST(DifferentiationTest, DifferentiateMonomialWorks)
{
    Differentiation differentiationForXWithY("x", {"y"});

    EXPECT_EQ(Polynomial(),
              differentiationForXWithY.differentiateMonomial(Monomial(13, {})));
    EXPECT_EQ(Polynomial(),
              differentiationForXWithY.differentiateMonomial(Monomial(13, {{"x", 0}})));
    EXPECT_EQ(Polynomial({Monomial(8, {{"x", 7}})}),
              differentiationForXWithY.differentiateMonomial(Monomial(1, {{"x", 8}})));
    EXPECT_EQ(Polynomial({Monomial(-15, {{"x", -6}})}),
              differentiationForXWithY.differentiateMonomial(Monomial(3, {{"x", -5}})));
    EXPECT_EQ(Polynomial(),
              differentiationForXWithY.differentiateMonomial(Monomial(3, {{"z", -5}})));
    EXPECT_EQ(Polynomial(
    {Monomial(30, {{"d2[y]/d[x]2", 1}, {"d[y]/d[x]", 5}, {"x", 7}, {"y", 8}, {"z", 9}}),
     Monomial(35, {{"d[y]/d[x]", 6}, {"x", 6}, {"y", 8}, {"z", 9}}),
     Monomial(40, {{"d[y]/d[x]", 1}, {"x", 7}, {"y", 7}, {"z", 9}})}),
              differentiationForXWithY.differentiateMonomial(Monomial(5, {{"d[y]/d[x]", 6}, {"x", 7}, {"y", 8}, {"z", 9}})));
}

TEST(DifferentiationTest, DifferentiatePolynomialWorks)
{
    Differentiation differentiationForXWithY("x", {"y"});
    Polynomial polynomial1{Monomial(0, {})};
    Polynomial polynomial2{Monomial(5, {{"x", 0}})};
    Polynomial polynomial3{Monomial(7, {{"x", 4}}), Monomial(-2, {{"x", 3}}), Monomial(8, {{"x", 1}}), Monomial(5, {})};
    Polynomial polynomial4{Monomial(-1, {{"x", -2}, {"y", -3}}), Monomial(-4, {{"x", -5}, {"z", -6}})};
    Polynomial polynomial5{Monomial(1, {{"a", 2}}), Monomial(3, {{"b", 4}}), Monomial(5, {{"c", 6}}), Monomial(7, {})};

    Polynomial expectedPolynomial1;
    Polynomial expectedPolynomial2;
    Polynomial expectedPolynomial3{Monomial(28, {{"x", 3}}), Monomial(-6, {{"x", 2}}), Monomial(8, {})};
    Polynomial expectedPolynomial4
    {
        Monomial(3, {{"d[y]/d[x]", 1}, {"x", -2}, {"y", -4}}),
                Monomial(2, {{"x", -3}, {"y", -3}}),
                Monomial(20, {{"x", -6}, {"z", -6}})};
    Polynomial expectedPolynomial5;
    EXPECT_EQ(expectedPolynomial1, differentiationForXWithY.differentiatePolynomial(polynomial1));
    EXPECT_EQ(expectedPolynomial2, differentiationForXWithY.differentiatePolynomial(polynomial2));
    EXPECT_EQ(expectedPolynomial3, differentiationForXWithY.differentiatePolynomial(polynomial3));
    EXPECT_EQ(expectedPolynomial4, differentiationForXWithY.differentiatePolynomial(polynomial4));
    EXPECT_EQ(expectedPolynomial5, differentiationForXWithY.differentiatePolynomial(polynomial5));
}

TEST(DifferentiationTest, DifferentiateExpressionWorks)
{
    Differentiation differentiationForXWithY("x", {"y"});
    Term x("x");
    Term y("y");
    Expression expression01{createExpressionIfPossible({x})};
    Expression expression02{createExpressionIfPossible({cos(x)})};
    Expression expression03{createExpressionIfPossible({cos(y)})};
    Expression expression04{createExpressionIfPossible({sin(x), Term("+"), cos(x)})};
    Expression expression05{createExpressionIfPossible({sin(x), Term("-"), cos(x)})};
    Expression expression06{createExpressionIfPossible({sin(x), Term("*"), cos(x)})};
    Expression expression07{createExpressionIfPossible({sin(x), Term("/"), cos(x)})};
    Expression expression08{createExpressionIfPossible({cos(x), Term("^"), Term(3)})};
    Expression expression09{createExpressionIfPossible({Term(3), Term("^"), cos(x)})};
    Expression expression10{createExpressionIfPossible({sin(x), Term("^"), cos(x)})};

    Term sinSquared{createExpressionIfPossible({sin(x), Term("^"), Term(2)})};
    Term cosSquared{createExpressionIfPossible({cos(x), Term("^"), Term(2)})};
    Term expectedTerm01(1);
    Term expectedTerm02(createExpressionIfPossible({Term(-1), Term("*"), sin(x)}));
    Term expectedTerm03(createExpressionIfPossible({Term(Monomial(-1, {{"d[y]/d[x]", 1}})), Term("*"), sin(y)}));
    Term expectedTerm04(createExpressionIfPossible({cos(x), Term("-"), sin(x)}));
    Term expectedTerm05(createExpressionIfPossible({cos(x), Term("+"), sin(x)}));
    Term expectedTerm06(createExpressionIfPossible({cosSquared, Term("-"), sinSquared}));
    Term expectedNumerator07(createExpressionIfPossible({cosSquared, Term("+"), sinSquared}));
    Term expectedDenominator07(createExpressionIfPossible({cosSquared}));
    Term expectedTerm07(createExpressionIfPossible({expectedNumerator07, Term("/"), expectedDenominator07}));
    Term expectedTerm08(createExpressionIfPossible({Term(-3), Term("*"), cosSquared, Term("*"), sin(x)}));
    Term expectedTerm09(createExpressionIfPossible({Term(-1.09861228866811), Term("*"), Term(3), Term("^"), cos(x), Term("*"), sin(x)}));
    EXPECT_EQ(expectedTerm01, differentiationForXWithY.differentiateExpression(expression01));
    EXPECT_EQ(expectedTerm02, differentiationForXWithY.differentiateExpression(expression02));
    EXPECT_EQ(expectedTerm03, differentiationForXWithY.differentiateExpression(expression03));
    EXPECT_EQ(expectedTerm04, differentiationForXWithY.differentiateExpression(expression04));
    EXPECT_EQ(expectedTerm05, differentiationForXWithY.differentiateExpression(expression05));
    EXPECT_EQ(expectedTerm06, differentiationForXWithY.differentiateExpression(expression06));
    EXPECT_EQ(expectedTerm07, differentiationForXWithY.differentiateExpression(expression07));
    EXPECT_EQ(expectedTerm08, differentiationForXWithY.differentiateExpression(expression08));
    EXPECT_EQ(expectedTerm09, differentiationForXWithY.differentiateExpression(expression09));
    EXPECT_TRUE(isNotANumber(differentiationForXWithY.differentiateExpression(expression10)));
}

TEST(DifferentiationTest, DifferentiateFunctionWorksWithTrigonometricFunction)
{
    Differentiation differentiationForXWithY("x", {"y"});

    Term x("x");
    Term y("y");
    Term cscSquared(createExpressionIfPossible({csc(x), Term("^"), Term(2)}));
    EXPECT_EQ(Term(cos(x)), differentiationForXWithY.differentiateFunction(sin(x)));
    EXPECT_EQ(Term(createExpressionIfPossible({Term(-1), Term("*"), sin(x)})), differentiationForXWithY.differentiateFunction(cos(x)));
    EXPECT_EQ(Term(createExpressionIfPossible({Term(Monomial(-1, {{"d[y]/d[x]", 1}})), Term("*"), sin(y)})), differentiationForXWithY.differentiateFunction(cos(y)));
    EXPECT_EQ(Term(createExpressionIfPossible({sec(x), Term("^"), Term(2)})), differentiationForXWithY.differentiateFunction(tan(x)));
    EXPECT_EQ(Term(createExpressionIfPossible({Term(-1), Term("*"), cot(x), Term("*"), csc(x)})), differentiationForXWithY.differentiateFunction(csc(x)));
    EXPECT_EQ(Term(createExpressionIfPossible({sec(x), Term("*"), tan(x)})), differentiationForXWithY.differentiateFunction(sec(x)));
    EXPECT_EQ(Term(createExpressionIfPossible({Term(-1), Term("*"), cscSquared})), differentiationForXWithY.differentiateFunction(cot(x)));
}

TEST(DifferentiationTest, DifferentiateFunctionWorksWithChainRule)
{
    Differentiation differentiationForX("x");
    Function functionToTest(sin(Term(Monomial(10, {{"x", 8}}))));

    Term expectedTerm(createExpressionIfPossible({Term(Monomial(80, {{"x", 7}})), Term("*"), cos(Term(Monomial(10, {{"x", 8}})))}));
    EXPECT_EQ(expectedTerm, differentiationForX.differentiateFunction(functionToTest));
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

    EXPECT_EQ("(18[d[y]/d[x]][y^5] + 5[d[y]/d[x]][y^4] + -6[x^5] + -2[d[y]/d[x]][y] + 2) = 0", differentiationForXWithY.differentiateEquation(equation1).getDisplayableString());
    EXPECT_EQ("(6[d[y]/d[x]][x^4][y] + 12[x^3][y^2] + -21[d[y]/d[x]][x][y^2] + -7[y^3] + -8[d[y]/d[x]]) = 0", differentiationForXWithY.differentiateEquation(equation2).getDisplayableString());
}

TEST(DifferentiationTest, DifferentiateTwoMultipliedTermsWorks)
{
    Differentiation differentiationForX("x");
    Term term1(Polynomial{Monomial(2, {{"x", 2}}), Monomial(-4, {{"x", 1}})});
    Term term2(Polynomial{Monomial(3, {{"x", 2}}), Monomial(7, {{"x", 1}})});

    Term termToVerify(differentiationForX.differentiateTwoMultipliedTerms(term1, term2));

    Term expectedTerm(Polynomial{Monomial(24, {{"x", 3}}), Monomial(6, {{"x", 2}}), Monomial(-56, {{"x", 1}})});
    EXPECT_EQ(expectedTerm, termToVerify);
}

TEST(DifferentiationTest, DifferentiateTwoDividedTermsWorks)
{
    Differentiation differentiationForX("x");
    Term numerator(Polynomial{Monomial(2, {{"x", 3}}), Monomial(4, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-4, {{"x", 1}}), Monomial(1, {})});

    Term termToVerify(differentiationForX.differentiateTwoDividedTerms(numerator, denominator));

    Term expectedNumeratorPart(Polynomial{Monomial(1, {{"x", 4}}), Monomial(-8, {{"x", 3}}), Monomial(3, {{"x", 2}}), Monomial(-4, {{"x", 1}}), Monomial(8, {})});
    Term expectedNumerator(createExpressionIfPossible({Term(2), Term("*"), expectedNumeratorPart}));
    Term expectedDenominator(Polynomial{Monomial(1, {{"x", 4}}), Monomial(-8, {{"x", 3}}), Monomial(18, {{"x", 2}}), Monomial(-8, {{"x", 1}}), Monomial(1, {})});
    Term expectedTerm(createExpressionIfPossible({expectedNumerator, Term("/"), expectedDenominator}));
    EXPECT_EQ(expectedTerm, termToVerify);
}

TEST(DifferentiationTest, DifferentiateWorksWithDivisionExpressionRaiseToAConstant)
{
    Differentiation differentiationForX("x");
    Term subTerm1(createExpressionIfPossible({Term(2), Term("/"), Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {})})}));
    Term termToTest(createExpressionIfPossible({subTerm1, Term("^"), Term(5)}));

    Term termToVerify(differentiationForX.differentiate(termToTest));

    EXPECT_EQ("(-160/((1[x] + -1)^6))", termToVerify.getDisplayableString());
}

TEST(DifferentiationTest, DifferentiateWorksWithChainRule)
{
    Differentiation differentiationForX("x");
    Term termToTest(createExpressionIfPossible({sec(Term(Monomial(2, {{"x", 2}}))), Term("^"), Term(4)}));

    Term termToVerify(differentiationForX.differentiate(termToTest));

    EXPECT_EQ("(16[x]*(sec(2[x^2])^4)*tan(2[x^2]))", termToVerify.getDisplayableString());
}

TEST(DifferentiationTest, DifferentiateWorksWithSquareRootOfAPolynomial)
{
    Differentiation differentiationForX("x");
    Polynomial subPolynomial{Monomial(2, {{"x", 3}}), Monomial(-4, {{"x", 1}}), Monomial(5, {})};
    Term termToTest(createExpressionIfPossible({Term(subPolynomial), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));

    Term termToVerify(differentiationForX.differentiate(termToTest));

    EXPECT_EQ("((3[x^2] + -2)/((2[x^3] + -4[x] + 5)^(1/2)))", termToVerify.getDisplayableString());
}

}

}
