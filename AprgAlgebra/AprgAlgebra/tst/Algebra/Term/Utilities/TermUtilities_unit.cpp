#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;

namespace alba
{

namespace algebra
{

TEST(TermUtilitiesTest, IsNegatedTermSimplerWorks)
{
    Term x("x");
    Term xToTheX(createExpressionIfPossible({x, Term("^"), x}));
    Term negativeXToTheX(createExpressionIfPossible({Term(-1), Term("*"), x, Term("^"), x}));

    EXPECT_FALSE(isNegatedTermSimpler(xToTheX, negativeXToTheX));
    EXPECT_TRUE(isNegatedTermSimpler(negativeXToTheX, xToTheX));
    EXPECT_FALSE(isNegatedTermSimpler(Term(Monomial(5, {})), Term(Monomial(-5, {}))));
    EXPECT_TRUE(isNegatedTermSimpler(Term(Monomial(-5, {})), Term(Monomial(5, {}))));
}

TEST(TermUtilitiesTest, IsNonEmptyOrNonOperatorTypeWorks)
{
    Term term1;
    Term term2(1);
    Term term3(Variable("length"));
    Term term4(Operator("+"));
    Term term5(Monomial(1, {}));
    Term term6(Polynomial{});
    Term term7(Expression{});
    Term term8(Function{});

    EXPECT_FALSE(isNonEmptyOrNonOperatorType(term1));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term2));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term3));
    EXPECT_FALSE(isNonEmptyOrNonOperatorType(term4));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term5));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term6));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term7));
    EXPECT_TRUE(isNonEmptyOrNonOperatorType(term8));
}

TEST(TermUtilitiesTest, IsNonEmptyOrNonOperatorOrNonExpressionTypeWorks)
{
    Term term1;
    Term term2(1);
    Term term3(Variable("length"));
    Term term4(Operator("+"));
    Term term5(Monomial(1, {}));
    Term term6(Polynomial{});
    Term term7(Expression{});
    Term term8(Function{});

    EXPECT_FALSE(isNonEmptyOrNonOperatorOrNonExpressionType(term1));
    EXPECT_TRUE(isNonEmptyOrNonOperatorOrNonExpressionType(term2));
    EXPECT_TRUE(isNonEmptyOrNonOperatorOrNonExpressionType(term3));
    EXPECT_FALSE(isNonEmptyOrNonOperatorOrNonExpressionType(term4));
    EXPECT_TRUE(isNonEmptyOrNonOperatorOrNonExpressionType(term5));
    EXPECT_TRUE(isNonEmptyOrNonOperatorOrNonExpressionType(term6));
    EXPECT_FALSE(isNonEmptyOrNonOperatorOrNonExpressionType(term7));
    EXPECT_TRUE(isNonEmptyOrNonOperatorOrNonExpressionType(term8));
}

TEST(TermUtilitiesTest, IsARadicalTermWorks)
{
    Term x("x");
    Term nonMonomialOrExpressionTerm(x);
    Term monomialWithIntegerExponent(Monomial(1, {{"x", 34}}));
    Term monomialWithDoubleExponent(Monomial(1, {{"x", 3.4}}));
    Term nonRaiseToPowerExpressionTerm(createExpressionIfPossible({x, Term("*"), x}));
    Term raiseToIntegerExpressionTerm(createExpressionIfPossible({x, Term("^"), Term(5)}));
    Term raiseToDoubleExpressionTerm(createExpressionIfPossible({x, Term("^"), Term(1.79)}));
    Term multipleRaiseToPowerExpressionTerm(createExpressionIfPossible({x, Term("^"), Term(1.79), Term("^"), Term("y")}));
    Term raiseToMonomialWithDoubleExpressionTerm(createExpressionIfPossible({x, Term("^"), Term(Monomial(2.84, {{"x", 2}, {"y", 3}}))}));

    EXPECT_FALSE(isARadicalTerm(nonMonomialOrExpressionTerm));
    EXPECT_FALSE(isARadicalTerm(monomialWithIntegerExponent));
    EXPECT_TRUE(isARadicalTerm(monomialWithDoubleExponent));
    EXPECT_FALSE(isARadicalTerm(nonRaiseToPowerExpressionTerm));
    EXPECT_FALSE(isARadicalTerm(raiseToIntegerExpressionTerm));
    EXPECT_TRUE(isARadicalTerm(raiseToDoubleExpressionTerm));
    EXPECT_TRUE(isARadicalTerm(multipleRaiseToPowerExpressionTerm));
    EXPECT_TRUE(isARadicalTerm(raiseToMonomialWithDoubleExpressionTerm));
}

TEST(ValueCheckingHelpersTest, IsANegativeTermWorks)
{
    Term x("x");
    EXPECT_TRUE(isANegativeTerm(Term(-1)));
    EXPECT_FALSE(isANegativeTerm(Term(1)));
    EXPECT_FALSE(isANegativeTerm(x));
    EXPECT_TRUE(isANegativeTerm(Term(Monomial(-1, {{"x", 1}}))));
    EXPECT_FALSE(isANegativeTerm(Term(Monomial(1, {{"x", 1}}))));
    EXPECT_TRUE(isANegativeTerm(Term(Polynomial{Monomial(-1, {{"x", 3}}), Monomial(4, {}), })));
    EXPECT_FALSE(isANegativeTerm(Term(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-4, {}), })));
    EXPECT_TRUE(isANegativeTerm(Term(createExpressionIfPossible({Term(-5), Term("+"), x}))));
    EXPECT_FALSE(isANegativeTerm(Term(createExpressionIfPossible({Term(5), Term("+"), x}))));
    EXPECT_FALSE(isANegativeTerm(Term(abs(Term(-5)))));
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
    EXPECT_TRUE(isANegativeExpression(createExpressionIfPossible({Term(-5), Term("+"), x})));
    EXPECT_FALSE(isANegativeExpression(createExpressionIfPossible({Term(5), Term("+"), x})));
    EXPECT_TRUE(isANegativeExpression(createExpressionIfPossible({Term(-5), Term("*"), x})));
    EXPECT_FALSE(isANegativeExpression(createExpressionIfPossible({Term(-5), Term("*"), Term(-3)})));
    EXPECT_FALSE(isANegativeExpression(createExpressionIfPossible({Term(-5), Term("^"), x})));
    EXPECT_FALSE(isANegativeExpression(createExpressionIfPossible({Term(5), Term("^"), x})));
}

TEST(TermUtilitiesTest, GetConstantFactorWorks)
{
    Term x("x");
    EXPECT_EQ(AlbaNumber(5), getConstantFactor(Term(5)));
    EXPECT_EQ(AlbaNumber(6), getConstantFactor(Term(Monomial(6, {{"x", 7}}))));
    EXPECT_EQ(AlbaNumber(4), getConstantFactor(Term(Polynomial{Monomial(8, {{"x", 3}}), Monomial(12, {{"x", 4}})})));
    EXPECT_EQ(AlbaNumber(1), getConstantFactor(x));
}

TEST(TermUtilitiesTest, EvaluateAndGetInputOutputPairWorks)
{
    AlbaNumbers inputNumbers{-2,-1,0,1,2};

    AlbaNumberPairs inputAndOutputPairs(
                evaluateAndGetInputOutputPair(
                    inputNumbers,
                    "x",
                    Term(Monomial(-2, {{"x", 3}}))
                    ));

    ASSERT_EQ(5U, inputAndOutputPairs.size());
    EXPECT_EQ(AlbaNumber(-2), inputAndOutputPairs.at(0).first);
    EXPECT_EQ(AlbaNumber(16), inputAndOutputPairs.at(0).second);
    EXPECT_EQ(AlbaNumber(-1), inputAndOutputPairs.at(1).first);
    EXPECT_EQ(AlbaNumber(2), inputAndOutputPairs.at(1).second);
    EXPECT_EQ(AlbaNumber(0), inputAndOutputPairs.at(2).first);
    EXPECT_EQ(AlbaNumber(0), inputAndOutputPairs.at(2).second);
    EXPECT_EQ(AlbaNumber(1), inputAndOutputPairs.at(3).first);
    EXPECT_EQ(AlbaNumber(-2), inputAndOutputPairs.at(3).second);
    EXPECT_EQ(AlbaNumber(2), inputAndOutputPairs.at(4).first);
    EXPECT_EQ(AlbaNumber(-16), inputAndOutputPairs.at(4).second);
}

TEST(TermUtilitiesTest, NegateTermWorks)
{
    Term sinX(sin(Term("x")));
    Term sinY(sin(Term("y")));
    Term sinZ(sin(Term("z")));
    Term term1(createExpressionIfPossible({sinX, Term("+"), sinY, Term("-"), sinZ}));
    Term term2(createExpressionIfPossible({sinX, Term("*"), sinY, Term("/"), sinZ}));
    Term term3(createExpressionIfPossible({sinX, Term("^"), sinY, Term("^"), sinZ}));

    Term termToVerify1(negateTerm(Term(5)));
    Term termToVerify2(negateTerm(Term("x")));
    Term termToVerify3(negateTerm(term1));
    Term termToVerify4(negateTerm(term2));
    Term termToVerify5(negateTerm(term3));

    Term termToExpect1(-5);
    Term termToExpect2(Monomial(-1, {{"x", 1}}));
    Term termToExpect3(createExpressionIfPossible({sinZ, Term("-"), sinX, Term("-"), sinY}));
    Term termToExpect4(createExpressionIfPossible({Term(-1), Term("*"), sinX, Term("*"), sinY, Term("/"), sinZ}));
    Term termToExpect5(createExpressionIfPossible({Term(-1), Term("*"), sinX, Term("^"), Term("("), sinY, Term("*"), sinZ, Term(")")}));
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
}

TEST(TermUtilitiesTest, ConvertPositiveTermIfNegativeWorks)
{
    EXPECT_EQ(Term(5), convertPositiveTermIfNegative(Term(-5)));
    EXPECT_EQ(Term(5), convertPositiveTermIfNegative(Term(5)));
    EXPECT_EQ(Term("x"), convertPositiveTermIfNegative(Term(Monomial(-1, {{"x", 1}}))));
    EXPECT_EQ(Term("x"), convertPositiveTermIfNegative(Term(Monomial(-1, {{"x", 1}}))));
}

TEST(TermUtilitiesTest, InvertTermWorks)
{
    Term termToTest1(5);
    Term termToTest2("x");
    Term termToTest3(Monomial(1, {{"x", 4}}));
    Term termToTest4(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-1, {})});
    Term termToTest5(createExpressionIfPossible({Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));

    Term termToVerify1(invertTerm(termToTest1, "x"));
    Term termToVerify2(invertTerm(termToTest2, "x"));
    Term termToVerify3(invertTerm(termToTest3, "x"));
    Term termToVerify4(invertTerm(termToTest4, "x"));
    Term termToVerify5(invertTerm(termToTest5, "x"));

    Term termToExpect1;
    Term termToExpect2("x");
    Term termToExpect3(Monomial(1, {{"x", AlbaNumber::createFraction(1, 4)}}));
    Term termToExpect4(createExpressionIfPossible({Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})}), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    Term termToExpect5(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-1, {})});
    EXPECT_EQ(termToExpect1, termToVerify1);
    EXPECT_EQ(termToExpect2, termToVerify2);
    EXPECT_EQ(termToExpect3, termToVerify3);
    EXPECT_EQ(termToExpect4, termToVerify4);
    EXPECT_EQ(termToExpect5, termToVerify5);
}

TEST(TermUtilitiesTest, NegateExpressionWorks)
{
    Term x("x");
    Expression expression1(createExpressionIfPossible({Term(-5), Term("+"), x}));
    Expression expression2(createExpressionIfPossible({Term(5), Term("+"), x}));
    Expression expression3(createExpressionIfPossible({Term(-5), Term("*"), x}));
    Expression expression4(createExpressionIfPossible({Term(-5), Term("*"), Term(-3)}));
    Expression expression5(createExpressionIfPossible({Term(-5), Term("^"), x}));

    Expression expressionToVerify1(negateExpression(expression1));
    Expression expressionToVerify2(negateExpression(expression2));
    Expression expressionToVerify3(negateExpression(expression3));
    Expression expressionToVerify4(negateExpression(expression4));
    Expression expressionToVerify5(negateExpression(expression5));

    Expression expectedExpression1(createExpressionIfPossible({Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})})}));
    Expression expectedExpression2(createExpressionIfPossible({Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(-5, {})})}));
    Expression expectedExpression3(createExpressionIfPossible({Term(Monomial(5, {{"x", 1}}))}));
    Expression expectedExpression4(createExpressionIfPossible({Term(-15)}));
    Expression subExpression5(createExpressionIfPossible({Term(-5), Term("^"), x}));
    Expression expectedExpression5(createExpressionIfPossible({Term(-1), Term("*"), Term(subExpression5)}));
    EXPECT_EQ(expectedExpression1, expressionToVerify1);
    EXPECT_EQ(expectedExpression2, expressionToVerify2);
    EXPECT_EQ(expectedExpression3, expressionToVerify3);
    EXPECT_EQ(expectedExpression4, expressionToVerify4);
    EXPECT_EQ(expectedExpression5, expressionToVerify5);
}

}

}
