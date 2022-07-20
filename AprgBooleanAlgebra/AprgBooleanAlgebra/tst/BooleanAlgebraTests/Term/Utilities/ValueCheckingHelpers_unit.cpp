#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <gtest/gtest.h>

#include <cmath>

namespace alba
{

namespace booleanAlgebra
{

TEST(ValueCheckingHelpersTest, WillHaveNoEffectOnAndOperationWorksWithTerm)
{
    EXPECT_TRUE(willHaveNoEffectOnAndOperation(Term()));
    EXPECT_FALSE(willHaveNoEffectOnAndOperation(Term(false)));
    EXPECT_TRUE(willHaveNoEffectOnAndOperation(Term(true)));
    EXPECT_FALSE(willHaveNoEffectOnAndOperation(Term(VariableTerm("x", false))));
    EXPECT_FALSE(willHaveNoEffectOnAndOperation(Term(VariableTerm("x", true))));
    EXPECT_TRUE(willHaveNoEffectOnAndOperation(Term(Expression())));
}

TEST(ValueCheckingHelpersTest, WillHaveNoEffectOnAndOperationWorksWithExpression)
{
    EXPECT_TRUE(willHaveNoEffectOnAndOperation(Expression()));
    EXPECT_FALSE(willHaveNoEffectOnAndOperation(createExpressionIfPossible({false})));
    EXPECT_TRUE(willHaveNoEffectOnAndOperation(createExpressionIfPossible({true})));
    EXPECT_FALSE(willHaveNoEffectOnAndOperation(createExpressionIfPossible({"x"})));
}

TEST(ValueCheckingHelpersTest, WillHaveNoEffectOnOrOperationWorksWithTerm)
{
    EXPECT_TRUE(willHaveNoEffectOnOrOperation(Term()));
    EXPECT_TRUE(willHaveNoEffectOnOrOperation(Term(false)));
    EXPECT_FALSE(willHaveNoEffectOnOrOperation(Term(true)));
    EXPECT_FALSE(willHaveNoEffectOnOrOperation(Term(VariableTerm("x", false))));
    EXPECT_FALSE(willHaveNoEffectOnOrOperation(Term(VariableTerm("x", true))));
    EXPECT_TRUE(willHaveNoEffectOnOrOperation(Term(Expression())));
}

TEST(ValueCheckingHelpersTest, WillHaveNoEffectOnOrOperationWorksWithExpression)
{
    EXPECT_TRUE(willHaveNoEffectOnOrOperation(Expression()));
    EXPECT_TRUE(willHaveNoEffectOnOrOperation(createExpressionIfPossible({false})));
    EXPECT_FALSE(willHaveNoEffectOnOrOperation(createExpressionIfPossible({true})));
    EXPECT_FALSE(willHaveNoEffectOnOrOperation(createExpressionIfPossible({"x"})));
}

TEST(ValueCheckingHelpersTest, IsTheValueWorksWithTerm)
{
    Term term1;
    Term term2(false);
    Term term3(true);
    Term term4(VariableTerm("x"));
    Term term5(Operator("&"));
    Term term6(Expression{});

    EXPECT_FALSE(isTheValue(term1, false));
    EXPECT_FALSE(isTheValue(term1, true));
    EXPECT_TRUE(isTheValue(term2, false));
    EXPECT_FALSE(isTheValue(term2, true));
    EXPECT_FALSE(isTheValue(term3, false));
    EXPECT_TRUE(isTheValue(term3, true));
    EXPECT_FALSE(isTheValue(term4, false));
    EXPECT_FALSE(isTheValue(term4, true));
    EXPECT_FALSE(isTheValue(term5, false));
    EXPECT_FALSE(isTheValue(term5, true));
    EXPECT_FALSE(isTheValue(term6, false));
    EXPECT_FALSE(isTheValue(term6, true));
}

TEST(ValueCheckingHelpersTest, IsTheValueWorksWithConstant)
{
    Constant constant1;
    Constant constant2(false);
    Constant constant3(true);

    EXPECT_TRUE(isTheValue(constant1, false));
    EXPECT_FALSE(isTheValue(constant1, true));
    EXPECT_TRUE(isTheValue(constant2, false));
    EXPECT_FALSE(isTheValue(constant2, true));
    EXPECT_FALSE(isTheValue(constant3, false));
    EXPECT_TRUE(isTheValue(constant3, true));
}

TEST(ValueCheckingHelpersTest, IsTheValueWorksWithExpression)
{
    EXPECT_FALSE(isTheValue(Expression(), false));
    EXPECT_FALSE(isTheValue(Expression(), true));
    EXPECT_TRUE(isTheValue(createExpressionIfPossible({false}), false));
    EXPECT_FALSE(isTheValue(createExpressionIfPossible({false}), true));
    EXPECT_FALSE(isTheValue(createExpressionIfPossible({true}), false));
    EXPECT_TRUE(isTheValue(createExpressionIfPossible({true}), true));
    EXPECT_FALSE(isTheValue(createExpressionIfPossible({"x"}), false));
    EXPECT_FALSE(isTheValue(createExpressionIfPossible({"x"}), true));
}

}

}
