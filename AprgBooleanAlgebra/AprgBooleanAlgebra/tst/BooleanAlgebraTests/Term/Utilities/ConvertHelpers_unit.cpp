#include <BooleanAlgebra/Term/Utilities/ConvertHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace booleanAlgebra
{

TEST(ConvertHelpersTest, SimplifyAndConvertExpressionToSimplestTermWorks)
{
    Expression expression1(createExpressionIfPossible({true}));
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
    EXPECT_TRUE(termToVerify2.getBooleanValue());
    ASSERT_EQ(TermType::Constant, termToVerify3.getTermType());
    EXPECT_TRUE(termToVerify3.getBooleanValue());
    ASSERT_EQ(TermType::Constant, termToVerify4.getTermType());
    EXPECT_TRUE(termToVerify4.getBooleanValue());
    ASSERT_EQ(TermType::Constant, termToVerify5.getTermType());
    EXPECT_TRUE(termToVerify5.getBooleanValue());
}

TEST(ConvertHelpersTest, ConvertExpressionToSimplestTermWorks)
{
    Term termToVerify1(convertExpressionToSimplestTerm(createExpressionIfPossible({})));
    Term termToVerify2(convertExpressionToSimplestTerm(createExpressionIfPossible({true})));
    Term termToVerify3(convertExpressionToSimplestTerm(createExpressionIfPossible({"x", "&", "y"})));

    EXPECT_EQ(Term(), termToVerify1);
    EXPECT_EQ(Term(true), termToVerify2);
    Term termToExpect3(createExpressionIfPossible({"x", "&", "y"}));
    EXPECT_EQ(termToExpect3, termToVerify3);
}

}

}
