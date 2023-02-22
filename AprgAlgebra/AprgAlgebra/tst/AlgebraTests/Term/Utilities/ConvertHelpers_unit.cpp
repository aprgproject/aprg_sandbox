#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;

namespace alba
{

namespace algebra
{

TEST(ConvertHelpersTest, CanBeConvertedToConstantWorks)
{
    EXPECT_TRUE(canBeConvertedToConstant(Polynomial()));
    EXPECT_TRUE(canBeConvertedToConstant(Polynomial{Monomial(96, {})}));
    EXPECT_FALSE(canBeConvertedToConstant(Polynomial{Monomial(96, {{"x", 1}})}));
    EXPECT_FALSE(canBeConvertedToConstant(Polynomial{Monomial(96, {}), Monomial(96, {{"x", 1}})}));
}

TEST(ConvertHelpersTest, CanBeConvertedToMonomialWorks)
{
    EXPECT_FALSE(canBeConvertedToMonomial(Term()));
    EXPECT_TRUE(canBeConvertedToMonomial(Term(0)));
    EXPECT_TRUE(canBeConvertedToMonomial(Term(15)));
    EXPECT_TRUE(canBeConvertedToMonomial(Term(Variable("x"))));
    EXPECT_TRUE(canBeConvertedToMonomial(Term(Monomial(96, {{"x", 1}}))));
    EXPECT_TRUE(canBeConvertedToMonomial(Term(Polynomial{Monomial(96, {{"x", 1}})})));
    EXPECT_FALSE(canBeConvertedToMonomial(Term(Polynomial{Monomial(96, {{"x", 1}}), Monomial(73, {{"y", 1}})})));
    EXPECT_FALSE(canBeConvertedToMonomial(Term(createExpressionIfPossible({254}))));
    EXPECT_FALSE(canBeConvertedToMonomial(Term(Expression())));
}

TEST(ConvertHelpersTest, CanBeConvertedToPolynomialWorks)
{
    EXPECT_FALSE(canBeConvertedToPolynomial(Term()));
    EXPECT_TRUE(canBeConvertedToPolynomial(Term(0)));
    EXPECT_TRUE(canBeConvertedToPolynomial(Term(15)));
    EXPECT_TRUE(canBeConvertedToPolynomial(Term(Variable("x"))));
    EXPECT_TRUE(canBeConvertedToPolynomial(Term(Monomial(96, {{"x", 1}}))));
    EXPECT_TRUE(canBeConvertedToPolynomial(Term(Polynomial{Monomial(96, {{"x", 1}})})));
    EXPECT_FALSE(canBeConvertedToPolynomial(Term(createExpressionIfPossible({254}))));
    EXPECT_FALSE(canBeConvertedToPolynomial(Term(Expression())));
}

TEST(ConvertHelpersTest, SimplifyAndConvertMonomialToSimplestTermWorks)
{
    Term termToVerify1(simplifyAndConvertMonomialToSimplestTerm(Monomial()));
    Term termToVerify2(simplifyAndConvertMonomialToSimplestTerm(Monomial(6, {})));
    Term termToVerify3(simplifyAndConvertMonomialToSimplestTerm(Monomial(1, {{"x", 1}})));
    Term termToVerify4(simplifyAndConvertMonomialToSimplestTerm(Monomial(10, {{"x", 0}})));

    ASSERT_EQ(TermType::Constant, termToVerify1.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify1.getConstantValueConstReference().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(6, termToVerify2.getConstantValueConstReference().getDouble());
    ASSERT_EQ(TermType::Variable, termToVerify3.getTermType());
    EXPECT_EQ("x", termToVerify3.getVariableConstReference().getVariableName());
    ASSERT_EQ(TermType::Constant, termToVerify4.getTermType());
    EXPECT_DOUBLE_EQ(10, termToVerify4.getConstantValueConstReference().getDouble());
}

TEST(ConvertHelpersTest, SimplifyAndConvertPolynomialToSimplestTermWorks)
{
    Term termToVerify1(simplifyAndConvertPolynomialToSimplestTerm(Polynomial{}));
    Term termToVerify2(simplifyAndConvertPolynomialToSimplestTerm(Polynomial{Monomial(6, {})}));
    Term termToVerify3(simplifyAndConvertPolynomialToSimplestTerm(Polynomial{Monomial(6, {{"x", 1}}), Monomial(-6, {{"x", 1}})}));

    ASSERT_EQ(TermType::Constant, termToVerify1.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify1.getConstantValueConstReference().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(6, termToVerify2.getConstantValueConstReference().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify3.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify3.getConstantValueConstReference().getDouble());
}

TEST(ConvertHelpersTest, SimplifyAndConvertExpressionToSimplestTermWorks)
{
    Expression expression1(createExpressionIfPossible({88}));
    Expression expression2(createExpressionInAnExpression(expression1));
    Expression expression3(createExpressionInAnExpression(expression2));
    Expression expression4(createExpressionInAnExpression(expression3));

    Term termToVerify1(simplifyAndConvertExpressionToSimplestTerm(createExpressionIfPossible({})));
    Term termToVerify2(simplifyAndConvertExpressionToSimplestTerm(createExpressionIfPossible({expression1})));
    Term termToVerify3(simplifyAndConvertExpressionToSimplestTerm(createExpressionIfPossible({expression2})));
    Term termToVerify4(simplifyAndConvertExpressionToSimplestTerm(createExpressionIfPossible({expression3})));
    Term termToVerify5(simplifyAndConvertExpressionToSimplestTerm(createExpressionIfPossible({expression4})));

    ASSERT_EQ(TermType::Empty, termToVerify1.getTermType());
    ASSERT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(88, termToVerify2.getConstantValueConstReference().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify3.getTermType());
    EXPECT_DOUBLE_EQ(88, termToVerify3.getConstantValueConstReference().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify4.getTermType());
    EXPECT_DOUBLE_EQ(88, termToVerify4.getConstantValueConstReference().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify5.getTermType());
    EXPECT_DOUBLE_EQ(88, termToVerify5.getConstantValueConstReference().getDouble());
}

TEST(ConvertHelpersTest, SimplifyAndConvertFunctionToSimplestTermWorks)
{
    Function function1;
    Function function2("functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });
    Function function3("functionName", Term(createExpressionIfPossible({5, "+", 5})), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });

    Term termToVerify1(simplifyAndConvertFunctionToSimplestTerm(function1));
    Term termToVerify2(simplifyAndConvertFunctionToSimplestTerm(function2));
    Term termToVerify3(simplifyAndConvertFunctionToSimplestTerm(function3));

    ASSERT_TRUE(termToVerify1.isFunction());
    EXPECT_EQ(function1, termToVerify1.getFunctionConstReference());
    EXPECT_EQ(Term(5), termToVerify2);
    EXPECT_EQ(Term(10), termToVerify3);
}

TEST(ConvertHelpersTest, ConvertMonomialToSimplestTermWorks)
{
    Term termToVerify1(convertMonomialToSimplestTerm(Monomial()));
    Term termToVerify2(convertMonomialToSimplestTerm(Monomial(6, {})));
    Term termToVerify3(convertMonomialToSimplestTerm(Monomial(1, {{"x", 1}})));
    Term termToVerify4(convertMonomialToSimplestTerm(Monomial(10, {{"x", 0}})));

    ASSERT_EQ(TermType::Constant, termToVerify1.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify1.getConstantValueConstReference().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(6, termToVerify2.getConstantValueConstReference().getDouble());
    ASSERT_EQ(TermType::Variable, termToVerify3.getTermType());
    EXPECT_EQ("x", termToVerify3.getVariableConstReference().getVariableName());
    ASSERT_EQ(TermType::Monomial, termToVerify4.getTermType());
    Monomial monomialToExpect(10, {{"x", 0}});
    EXPECT_EQ(monomialToExpect, termToVerify4.getMonomialConstReference());
}

TEST(ConvertHelpersTest, ConvertPolynomialToSimplestTermWorks)
{
    Term termToVerify1(convertPolynomialToSimplestTerm(Polynomial{}));
    Term termToVerify2(convertPolynomialToSimplestTerm(Polynomial{Monomial(6, {})}));
    Term termToVerify3(convertPolynomialToSimplestTerm(Polynomial{Monomial(6, {{"x", 1}}), Monomial(-6, {{"x", 1}})}));

    ASSERT_EQ(TermType::Constant, termToVerify1.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify1.getConstantValueConstReference().getDouble());
    ASSERT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(6, termToVerify2.getConstantValueConstReference().getDouble());
    ASSERT_EQ(TermType::Polynomial, termToVerify3.getTermType());
    Polynomial polynomialToExpect{Monomial(6, {{"x", 1}}), Monomial(-6, {{"x", 1}})};
    EXPECT_EQ(polynomialToExpect, termToVerify3.getPolynomialConstReference());
}

TEST(ConvertHelpersTest, ConvertExpressionToSimplestTermWorks)
{
    Term termToVerify1(convertExpressionToSimplestTerm(createExpressionIfPossible({})));
    Term termToVerify2(convertExpressionToSimplestTerm(createExpressionIfPossible({156})));
    Term termToVerify3(convertExpressionToSimplestTerm(createExpressionIfPossible({Monomial(444, {})})));
    Term termToVerify4(convertExpressionToSimplestTerm(createExpressionIfPossible({1, "/", Monomial(444, {})})));

    EXPECT_EQ(Term(), termToVerify1);
    EXPECT_EQ(Term(156), termToVerify2);
    EXPECT_EQ(Term(444), termToVerify3);
    Term termToExpect4(createExpressionIfPossible({1, "/", Monomial(444, {})}));
    EXPECT_EQ(termToExpect4, termToVerify4);
}

TEST(ConvertHelpersTest, ConvertFunctionToSimplestTermWorks)
{
    Function function1;
    Function function2("functionName", Term(5), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });
    Function function3("functionName", Term("x"), [](AlbaNumber const& number) -> AlbaNumber
    {
        return number;
    });
    Term multiplicationAndDivisionExpression(createExpressionIfPossible({"x", "*", "y", "/", "z"}));

    Term termToVerify1(convertFunctionToSimplestTerm(function1));
    Term termToVerify2(convertFunctionToSimplestTerm(function2));
    Term termToVerify3(convertFunctionToSimplestTerm(function3));
    Term termToVerify4(convertFunctionToSimplestTerm(ln(multiplicationAndDivisionExpression)));

    Term termToExpect(createExpressionIfPossible({ln("x"), "+", ln("y"), "-", ln("z")}));
    ASSERT_TRUE(termToVerify1.isFunction());
    EXPECT_EQ(function1, termToVerify1.getFunctionConstReference());
    EXPECT_EQ(Term(5), termToVerify2);
    ASSERT_TRUE(termToVerify3.isFunction());
    EXPECT_EQ(function3, termToVerify3.getFunctionConstReference());
    EXPECT_EQ(termToExpect, termToVerify4);
}

}

}
