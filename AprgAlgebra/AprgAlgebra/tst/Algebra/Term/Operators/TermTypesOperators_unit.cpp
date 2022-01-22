#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(TermOperatorsTest, UnaryPlusOperator_PlusEmptyOperationWorks)
{
    Term term(+Term());

    EXPECT_EQ(Term(), term);
}

TEST(TermOperatorsTest, UnaryPlusOperator_PlusConstantOperationWorks)
{
    Term term(+Constant(6));

    EXPECT_EQ(Term(6), term);
}

TEST(TermOperatorsTest, UnaryPlusOperator_PlusVariableOperationWorks)
{
    Term term(+Variable("x"));

    EXPECT_EQ(Term("x"), term);
}

TEST(TermOperatorsTest, UnaryPlusOperator_PlusMonomialOperationWorks)
{
    Term term(+Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(4, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermOperatorsTest, UnaryPlusOperator_PlusPolynomialOperationWorks)
{
    Term term(+Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}), term);
}

TEST(TermOperatorsTest, UnaryPlusOperator_PlusExpressionOperationWorks)
{
    Term term(+createExpressionIfPossible({54}));

    EXPECT_EQ(Term(createExpressionIfPossible({54})), term);
}

TEST(TermOperatorsTest, UnaryPlusOperator_PlusFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(+absoluteValueFunction);

    EXPECT_EQ(Term(absoluteValueFunction), term);
}

TEST(TermOperatorsTest, UnaryMinusOperator_MinusEmptyOperationWorks)
{
    Term term(-Term());

    EXPECT_EQ(Term(), term);
}

TEST(TermOperatorsTest, UnaryMinusOperator_MinusConstantOperationWorks)
{
    Term term(-Constant(6));

    EXPECT_EQ(Term(-6), term);
}

TEST(TermOperatorsTest, UnaryMinusOperator_MinusVariableOperationWorks)
{
    Term term(-Variable("x"));

    EXPECT_EQ(Term(Monomial(-1, {{"x", 1}})), term);
}

TEST(TermOperatorsTest, UnaryMinusOperator_MinusMonomialOperationWorks)
{
    Term term(-Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(-4, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermOperatorsTest, UnaryMinusOperator_MinusPolynomialOperationWorks)
{
    Term term(-Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermOperatorsTest, UnaryMinusOperator_MinusExpressionOperationWorks)
{
    Term term(-createExpressionIfPossible({54}));

    EXPECT_EQ(Term(createExpressionIfPossible({-1, "*", 54})), term);
}

TEST(TermOperatorsTest, UnaryMinusOperator_MinusFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(-absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({-1, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_EmptyAddConstantOperationWorks)
{
    Term term(Term() + Constant(2));

    EXPECT_EQ(Term(2), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ConstantAddEmptyOperationWorks)
{
    Term term(Constant(6) + Term());

    EXPECT_EQ(Term(6), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ConstantAddConstantOperationWorks)
{
    Term term(Constant(6) + Constant(2));

    EXPECT_EQ(Term(8), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ConstantAddVariableOperationWorks)
{
    Term term(Constant(5) + Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ConstantAddMonomialWithSameMonomialConstantOperationWorks)
{
    Term term(Constant(8) + Monomial(2, {}));

    EXPECT_EQ(Term(10), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ConstantAddMonomialWithDifferentMonomialConstantOperationWorks)
{
    Term term(Constant(4) + Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ConstantAddPolynomialOperationWorks)
{
    Term term(Constant(10) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ConstantAddExpressionOperationWorks)
{
    Term term(Constant(10) + createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ConstantAddFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) + absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ConstantAddTermOperationWorks)
{
    Term term(Constant(10) + Term(5));

    EXPECT_EQ(Term(15), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_VariableAddConstantOperationWorks)
{
    Term term(Variable("y") + Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_VariableAddVariableWithSameVariableOperationWorks)
{
    Term term(Variable("i") + Variable("i"));

    EXPECT_EQ(Term(Monomial(2, {{"i", 1}})), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_VariableAddVariableWithDifferentVariableOperationWorks)
{
    Term term(Variable("i") + Variable("j"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"i", 1}}), Monomial(1, {{"j", 1}})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_VariableAddMonomialWithSameMonomialVariableOperationWorks)
{
    Term term(Variable("x") + Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(Monomial(8, {{"x", 1}})), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_VariableAddMonomialWithDifferentMonomialVariableOperationWorks)
{
    Term term(Variable("x") + Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(7, {{"y", 1}})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_VariableAddPolynomialOperationWorks)
{
    Term term(Variable("x") + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_VariableAddExpressionOperationWorks)
{
    Term term(Variable("x") + createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_VariableAddFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") + absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_VariableAddTermOperationWorks)
{
    Term term(Variable("y") + Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_MonomialAddConstantWithSameMonomialConstantOperationWorks)
{
    Term term(Monomial(8, {}) + Constant(2));

    EXPECT_EQ(Term(10), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_MonomialAddConstantWithDifferentMonomialConstantOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) + Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_MonomialAddVariableWithSameMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"x", 1}}) + Variable("x"));

    EXPECT_EQ(Term(Monomial(8, {{"x", 1}})), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_MonomialAddVariableWithDifferentMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"y", 1}}) + Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(7, {{"y", 1}})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_MonomialAddMonomialWithSameMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) + Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(Monomial(12, {{"x", 2}})), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_MonomialAddMonomialWithDifferentMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) + Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(8, {{"x", 2}}), Monomial(4, {{"x", 1}, {"y", 1}})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_MonomialAddPolynomialOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_MonomialAddExpressionOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) + createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({Monomial(3, {{"x", 1}}), "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_MonomialAddFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) + absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Monomial(3, {{"x", 1}}), "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_MonomialAddTermOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) + Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_PolynomialAddConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_PolynomialAddVariableOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_PolynomialAddMonomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Monomial(3, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_PolynomialAddPolynomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} + Polynomial{Monomial(15, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 1}}), Monomial(20, {})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_PolynomialAddExpressionOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_PolynomialAddFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_PolynomialAddTermOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + 10);

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ExpressionAddConstantOperationWorks)
{
    Term term(createExpressionIfPossible({54}) + Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ExpressionAddVariableOperationWorks)
{
    Term term(createExpressionIfPossible({54}) + Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({
                                               54, "+", "x"
                                           }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ExpressionAddMonomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) + Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "+", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ExpressionAddPolynomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible({54, "+", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ExpressionAddExpressionOperationWorks)
{
    Term term(createExpressionIfPossible({54}) + createExpressionIfPossible({87}));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "+", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ExpressionAddFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) + absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({createExpressionIfPossible({54}), "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ExpressionAddTermOperationWorks)
{
    Term term(createExpressionIfPossible({54}) + 10);

    Expression expressionToExpect(
                createExpressionIfPossible({54, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_FunctionAddConstantOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_FunctionAddVariableOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "+", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_FunctionAddMonomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "+", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_FunctionAddPolynomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "+", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_FunctionAddExpressionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "+", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_FunctionAddFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_FunctionAddTermOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + 10);

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_TermAddConstantOperationWorks)
{
    Term term(Term(5) + Constant(10));

    EXPECT_EQ(Term(15), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_TermAddVariableOperationWorks)
{
    Term term(Term(4) + Variable("y"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_TermAddMonomialOperationWorks)
{
    Term term(Term(4) + Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_TermAddPolynomialOperationWorks)
{
    Term term(10 + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_TermAddExpressionOperationWorks)
{
    Term term(10 + createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_TermAddFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(10 + absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_TermAddTermOperationWorks)
{
    Term term(Term(5) + 10);

    EXPECT_EQ(Term(15), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_EmptyAddConstantOperationWorks)
{
    Term term(Term() - Constant(2));

    EXPECT_EQ(Term(-2), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ConstantAddEmptyOperationWorks)
{
    Term term(Constant(6) - Term());

    EXPECT_EQ(Term(6), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ConstantSubtractConstantOperationWorks)
{
    Term term(Constant(6) - Constant(2));

    EXPECT_EQ(Term(4), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ConstantSubtractVariableOperationWorks)
{
    Term term(Constant(5) - Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ConstantSubtractMonomialWithSameMonomialConstantOperationWorks)
{
    Term term(Constant(8) - Monomial(2, {}));

    EXPECT_EQ(Term(6), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ConstantSubtractMonomialWithDifferentMonomialConstantOperationWorks)
{
    Term term(Constant(4) - Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(-6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ConstantSubtractPolynomialOperationWorks)
{
    Term term(Constant(10) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ConstantSubtractExpressionOperationWorks)
{
    Term term(Constant(10) - createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ConstantSubtractFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) - absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ConstantSubtractTermOperationWorks)
{
    Term term(Constant(6) - Term(2));

    EXPECT_EQ(Term(4), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_VariableSubtractConstantOperationWorks)
{
    Term term(Variable("y") - Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(-4, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_VariableSubtractVariableWithSameVariableOperationWorks)
{
    Term term(Variable("i") - Variable("i"));

    EXPECT_EQ(Term(0), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_VariableSubtractVariableWithDifferentVariableOperationWorks)
{
    Term term(Variable("i") - Variable("j"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"i", 1}}), Monomial(-1, {{"j", 1}})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_VariableSubtractMonomialWithSameMonomialVariableOperationWorks)
{
    Term term(Variable("x") - Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(Monomial(-6, {{"x", 1}})), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_VariableSubtractMonomialWithDifferentMonomialVariableOperationWorks)
{
    Term term(Variable("x") - Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-7, {{"y", 1}})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_VariableSubtractPolynomialOperationWorks)
{
    Term term(Variable("x") - Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-3, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_VariableSubtractExpressionOperationWorks)
{
    Term term(Variable("x") - createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_VariableSubtractFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") - absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_VariableSubtractTermOperationWorks)
{
    Term term(Variable("y") - Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(-4, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractConstantWithSameMonomialConstantOperationWorks)
{
    Term term(Monomial(8, {}) - Constant(2));

    EXPECT_EQ(Term(6), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractConstantWithDifferentMonomialConstantOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) - Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(-4, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractVariableWithSameMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"x", 1}}) - Variable("x"));

    EXPECT_EQ(Term(Monomial(6, {{"x", 1}})), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractVariableWithDifferentMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"y", 1}}) - Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(7, {{"y", 1}})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractMonomialThatResultsInZeroOperationWorks)
{
    Term term(Monomial(4, {{"x", 2}}) - Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(0), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractMonomialWithSameMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) - Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(Monomial(4, {{"x", 2}})), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractMonomialWithDifferentMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) - Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(8, {{"x", 2}}), Monomial(-4, {{"x", 1}, {"y", 1}})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractPolynomialOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractExpressionOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) - createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({Monomial(3, {{"x", 1}}), "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) - absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Monomial(3, {{"x", 1}}), "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractTermOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) - Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(-4, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_PolynomialSubtractConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_PolynomialSubtractVariableOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(7, {{"x", 1}})} - Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_PolynomialSubtractMonomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - Monomial(3, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(-2, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_PolynomialSubtractPolynomialThatResultsInZeroOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} - Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})});

    EXPECT_EQ(Term(0), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_PolynomialSubtractPolynomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} - Polynomial{Monomial(15, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-2, {{"x", 1}}), Monomial(-10, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_PolynomialSubtractExpressionOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_PolynomialSubtractFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_PolynomialSubtractTermOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - 10);

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ExpressionSubtractConstantOperationWorks)
{
    Term term(createExpressionIfPossible({54}) - Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ExpressionSubtractVariableOperationWorks)
{
    Term term(createExpressionIfPossible({54}) - Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "-", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ExpressionSubtractMonomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) - Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "-", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ExpressionSubtractPolynomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible({54, "-", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ExpressionSubtractExpressionOperationWorks)
{
    Term term(createExpressionIfPossible({54}) + createExpressionIfPossible({87}));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "+", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ExpressionSubtractFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) - absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({createExpressionIfPossible({54}), "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ExpressionSubtractTermOperationWorks)
{
    Term term(createExpressionIfPossible({54}) - 10);

    Expression expressionToExpect(
                createExpressionIfPossible({54, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_FunctionSubtractConstantOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_FunctionSubtractVariableOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "-", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_FunctionSubtractMonomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "-", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_FunctionSubtractPolynomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "-", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_FunctionSubtractExpressionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "-", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_FunctionSubtractFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_FunctionSubtractTermOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - 10);

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_TermSubtractConstantOperationWorks)
{
    Term term(Term(5) - Constant(10));

    EXPECT_EQ(Term(-5), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_TermSubtractVariableOperationWorks)
{
    Term term(Term(4) - Variable("y"));

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_TermSubtractMonomialOperationWorks)
{
    Term term(Term(4) - Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(-6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_TermSubtractPolynomialOperationWorks)
{
    Term term(10 - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_TermSubtractExpressionOperationWorks)
{
    Term term(10 - createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_TermSubtractFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(10 - absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_TermSubtractTermOperationWorks)
{
    Term term(Term(5) - 10);

    EXPECT_EQ(Term(-5), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_EmptyAddConstantOperationWorks)
{
    Term term(Term() * Constant(2));

    EXPECT_EQ(Term(0), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ConstantAddEmptyOperationWorks)
{
    Term term(Constant(6) * Term());

    EXPECT_EQ(Term(0), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyConstantOperationWorks)
{
    Term term(Constant(6) * Constant(2));

    EXPECT_EQ(Term(12), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyVariableOperationWorks)
{
    Term term(Constant(5) * Variable("x"));

    EXPECT_EQ(Term(Monomial(5, {{"x", 1}})), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyMonomialWithSameMonomialConstantOperationWorks)
{
    Term term(Constant(8) * Monomial(2, {}));

    EXPECT_EQ(Term(16), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyMonomialWithDifferentMonomialConstantOperationWorks)
{
    Term term(Constant(4) * Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyPolynomialOperationWorks)
{
    Term term(Constant(10) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyExpressionOperationWorks)
{
    Term term(Constant(10) * createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) * absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyTermOperationWorks)
{
    Term term(Constant(6) * Term(2));

    EXPECT_EQ(Term(12), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_VariableMultiplyConstantOperationWorks)
{
    Term term(Variable("y") * Constant(4));

    EXPECT_EQ(Term(Monomial(4, {{"y", 1}})), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_VariableMultiplyVariableWithSameVariableOperationWorks)
{
    Term term(Variable("i") * Variable("i"));

    EXPECT_EQ(Term(Monomial(1, {{"i", 2}})), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_VariableMultiplyVariableWithDifferentVariableOperationWorks)
{
    Term term(Variable("i") * Variable("j"));

    EXPECT_EQ(Term(Monomial(1, {{"i", 1}, {"j", 1}})), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_VariableMultiplyMonomialWithSameMonomialVariableOperationWorks)
{
    Term term(Variable("x") * Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(Monomial(7, {{"x", 2}})), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_VariableMultiplyMonomialWithDifferentMonomialVariableOperationWorks)
{
    Term term(Variable("x") * Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(Monomial(7, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_VariableMultiplyPolynomialOperationWorks)
{
    Term term(Variable("x") * Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 2}}), Monomial(5, {{"x", 1}})}), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_VariableMultiplyExpressionOperationWorks)
{
    Term term(Variable("x") * createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_VariableMultiplyFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") * absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_VariableMultiplyTermOperationWorks)
{
    Term term(Variable("y") * Term(4));

    EXPECT_EQ(Term(Monomial(4, {{"y", 1}})), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyConstantWithSameMonomialConstantOperationWorks)
{
    Term term(Monomial(8, {}) * Constant(2));

    EXPECT_EQ(Term(16), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyConstantWithDifferentMonomialConstantOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) * Constant(4));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyVariableWithSameMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"x", 1}}) * Variable("x"));

    EXPECT_EQ(Term(Monomial(7, {{"x", 2}})), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyVariableWithDifferentMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"y", 1}}) * Variable("x"));

    EXPECT_EQ(Term(Monomial(7, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyMonomialWithSameMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) * Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(Monomial(32, {{"x", 4}})), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyMonomialWithDifferentMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) * Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(32, {{"x", 3}, {"y", 1}})), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyPolynomialOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(3, {{"x", 2}}), Monomial(15, {{"x", 1}})}), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyExpressionOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) * createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({Monomial(3, {{"x", 1}}), "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) * absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Monomial(3, {{"x", 1}}), "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyTermOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) * Term(4));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyVariableOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})} * Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 2}}), Monomial(5, {{"x", 1}})}), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyMonomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Monomial(3, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(3, {{"x", 2}}), Monomial(15, {{"x", 1}})}), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyPolynomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Polynomial{Monomial(2, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(7, {{"x", 1}}), Monomial(10, {})}), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyExpressionOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible(
    {createExpressionIfPossible({Monomial(5, {}), "*", 54}),
     "+",
     createExpressionIfPossible({Monomial(1, {{"x", 1}}), "*", 54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyTermOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * 10);

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyConstantOperationWorks)
{
    Term term(createExpressionIfPossible({54}) * Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyVariableOperationWorks)
{
    Term term(createExpressionIfPossible({54}) * Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "*", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyMonomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) * Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "*", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyPolynomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible(
    {createExpressionIfPossible({54, "*", Monomial(5, {})}),
     "+",
     createExpressionIfPossible({54, "*", Monomial(1, {{"x", 1}})})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyExpressionOperationWorks)
{
    Term term(createExpressionIfPossible({54}) * createExpressionIfPossible({87}));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "*", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) * absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({createExpressionIfPossible({54}), "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyTermOperationWorks)
{
    Term term(createExpressionIfPossible({54}) * 10);

    Expression expressionToExpect(
                createExpressionIfPossible({54, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_FunctionMultiplyConstantOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_FunctionMultiplyVariableOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "*", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_FunctionMultiplyMonomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "*", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_FunctionMultiplyPolynomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "*", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_FunctionMultiplyExpressionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "*", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_FunctionMultiplyFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_FunctionMultiplyTermOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * 10);

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_TermMultiplyConstantOperationWorks)
{
    Term term(Term(2) * Constant(6));

    EXPECT_EQ(Term(12), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_TermMultiplyVariableOperationWorks)
{
    Term term(Term(4) * Variable("y"));

    EXPECT_EQ(Term(Monomial(4, {{"y", 1}})), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_TermMultiplyMonomialOperationWorks)
{
    Term term(Term(4) * Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_TermMultiplyPolynomialOperationWorks)
{
    Term term(10 * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_TermMultiplyExpressionOperationWorks)
{
    Term term(10 * createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_TermMultiplyFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(10 * absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_TermMultiplyTermOperationWorks)
{
    Term term(Term(5) * 10);

    EXPECT_EQ(Term(50), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_EmptyAddConstantOperationWorks)
{
    Term term(Term() / Constant(2));

    EXPECT_EQ(Term(0), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ConstantAddEmptyOperationWorks)
{
    Term term(Constant(6) / Term());

    EXPECT_EQ(Term(AlbaNumber(AlbaNumber::Value::PositiveInfinity)), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ConstantDivideConstantOperationWorks)
{
    Term term(Constant(6) / Constant(2));

    EXPECT_EQ(Term(3), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ConstantDivideVariableOperationWorks)
{
    Term term(Constant(5) / Variable("x"));

    EXPECT_EQ(Term(Monomial(5, {{"x", -1}})), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ConstantDivideMonomialWithSameMonomialConstantOperationWorks)
{
    Term term(Constant(8) / Monomial(2, {}));

    EXPECT_EQ(Term(4), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ConstantDivideMonomialWithDifferentMonomialConstantOperationWorks)
{
    Term term(Constant(8) / Monomial(4, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(2, {{"x", -2}, {"y", -4}})), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ConstantDividePolynomialOperationWorks)
{
    Term term(Constant(10) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(
                  createExpressionIfPossible(
    {Constant(10),
     "/",
     Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ConstantDivideExpressionOperationWorks)
{
    Term term(Constant(10) / createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ConstantDivideFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) / absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ConstantDivideTermOperationWorks)
{
    Term term(Constant(6) / Term(2));

    EXPECT_EQ(Term(3), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_VariableDivideConstantOperationWorks)
{
    Term term(Variable("y") / Constant(4));

    EXPECT_EQ(Term(Monomial(0.25, {{"y", 1}})), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_VariableDivideVariableWithSameVariableOperationWorks)
{
    Term term(Variable("i") / Variable("i"));

    EXPECT_EQ(Term(1), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_VariableDivideVariableWithDifferentVariableOperationWorks)
{
    Term term(Variable("i") / Variable("j"));

    EXPECT_EQ(Term(Monomial(1, {{"i", 1}, {"j", -1}})), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_VariableDivideMonomialWithSameMonomialVariableOperationWorks)
{
    Term term(Variable("x") / Monomial(4, {{"x", 1}}));

    EXPECT_EQ(Term(0.25), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_VariableDivideMonomialWithDifferentMonomialVariableOperationWorks)
{
    Term term(Variable("x") / Monomial(4, {{"y", 1}}));

    EXPECT_EQ(Term(Monomial(0.25, {{"x", 1}, {"y", -1}})), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_VariableDividePolynomialOperationWorks)
{
    Term term(Variable("x") / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(
                  createExpressionIfPossible({
                                                 Variable("x"),
                                                 "/",
                                                 Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}
                                             })), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_VariableDivideExpressionOperationWorks)
{
    Term term(Variable("x") / createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_VariableDivideFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") / absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_VariableDivideTermOperationWorks)
{
    Term term(Variable("y") / Term(4));

    EXPECT_EQ(Term(Monomial(0.25, {{"y", 1}})), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDivideConstantWithSameMonomialConstantOperationWorks)
{
    Term term(Monomial(8, {}) / Constant(2));

    EXPECT_EQ(Term(4), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDivideConstantWithDifferentMonomialConstantOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) / Constant(4));

    EXPECT_EQ(Term(Monomial(1.5, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDivideVariableWithSameMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"x", 1}}) / Variable("x"));

    EXPECT_EQ(Term(7), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDivideVariableWithDifferentMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"y", 1}}) / Variable("x"));

    EXPECT_EQ(Term(Monomial(7, {{"x", -1}, {"y", 1}})), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDivideMonomialWithSameMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) / Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(2), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDivideMonomialWithDifferentMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) / Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(2, {{"x", 1}, {"y", -1}})), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDividePolynomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Monomial(8, {{"x", 2}}), "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDivideExpressionOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) / createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible(
    {Monomial(3, {{"x", 1}}), "/", 54 }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDivideFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) / absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Monomial(3, {{"x", 1}}), "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDivideTermOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) / Term(4));

    EXPECT_EQ(Term(Monomial(1.5, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_PolynomialDivideConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(0.1, {{"x", 1}}), Monomial(0.5, {})}), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_PolynomialDivideVariableOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(4, {{"x", 2}})} / Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 1}}), Monomial(5, {{"x", -1}})}), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_PolynomialDivideMonomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 2}})} / Monomial(2, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(0.5, {{"x", 1}}), Monomial(2.5, {{"x", -1}})}), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_PolynomialDividePolynomialOperationWorks)
{
    Term term(Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})} / Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})},
     "/",
     Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})}})), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_PolynomialDivideExpressionOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible(
    {Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_PolynomialDivideFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_PolynomialDivideTermOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / 10);

    EXPECT_EQ(Term(Polynomial{Monomial(0.1, {{"x", 1}}), Monomial(0.5, {})}), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ExpressionDivideConstantOperationWorks)
{
    Term term(createExpressionIfPossible({54}) / Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ExpressionDivideVariableOperationWorks)
{
    Term term(createExpressionIfPossible({54}) / Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "/", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ExpressionDivideMonomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) / Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "/", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ExpressionDividePolynomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible({54, "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ExpressionDivideExpressionOperationWorks)
{
    Term term(createExpressionIfPossible({54}) / createExpressionIfPossible({87}));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "/", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ExpressionDivideFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) / absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({createExpressionIfPossible({54}), "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ExpressionDivideTermOperationWorks)
{
    Term term(createExpressionIfPossible({54}) / 10);

    Expression expressionToExpect(
                createExpressionIfPossible({54, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_FunctionDivideConstantOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_FunctionDivideVariableOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "/", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_FunctionDivideMonomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "/", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_FunctionDividePolynomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_FunctionDivideExpressionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "/", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_FunctionDivideFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_FunctionDivideTermOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / 10);

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_TermDivideConstantOperationWorks)
{
    Term term(6 / Constant(2));

    EXPECT_EQ(Term(3), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_TermDivideVariableOperationWorks)
{
    Term term(Term(5) / Variable("x"));

    EXPECT_EQ(Term(Monomial(5, {{"x", -1}})), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_TermDivideMonomialOperationWorks)
{
    Term term(Term(8) / Monomial(4, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(2, {{"x", -2}, {"y", -4}})), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_TermDividePolynomialOperationWorks)
{
    Term term(10 / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Constant(10), "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_TermDivideExpressionOperationWorks)
{
    Term term(10 / createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_TermDivideFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(10 / absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_TermDivideTermOperationWorks)
{
    Term term(6 / Term(2));

    EXPECT_EQ(Term(3), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_EmptyAddConstantOperationWorks)
{
    Term term(Term() ^ Constant(2));

    EXPECT_EQ(Term(0), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantAddEmptyOperationWorks)
{
    Term term(Constant(6) ^ Term());

    EXPECT_EQ(Term(1), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerConstantOperationWorks)
{
    Term term(Constant(6) ^ Constant(2));

    EXPECT_EQ(Term(36), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerConstantOperationWithZeroExponentWorks)
{
    Term term(Constant(6) ^ Constant(0));

    EXPECT_EQ(Term(1), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerVariableOperationWorks)
{
    Term term(Constant(5) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Constant(5), "^", Variable("x")})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerMonomialWithSameMonomialConstantOperationWorks)
{
    Term term(Constant(8) ^ Monomial(2, {}));

    EXPECT_EQ(Term(64), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerMonomialWithDifferentMonomialConstantOperationWorks)
{
    Term term(Constant(4) ^ Monomial(6, {{"x", 2}}));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Constant(4), "^", Monomial(6, {{"x", 2}})})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerPolynomialOperationWorks)
{
    Term term(Constant(10) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Constant(10), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerExpressionOperationWorks)
{
    Term term(Constant(10) ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) ^ absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerTermOperationWorks)
{
    Term term(Constant(6) ^ Term(2));

    EXPECT_EQ(Term(36), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerConstantOperationWorks)
{
    Term term(Variable("y") ^ Constant(4));

    EXPECT_EQ(Term(Monomial(1, {{"y", 4}})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerVariableWithSameVariableOperationWorks)
{
    Term term(Variable("i") ^ Variable("i"));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Variable("i"), "^", Variable("i")})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerVariableWithDifferentVariableOperationWorks)
{
    Term term(Variable("i") ^ Variable("j"));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Variable("i"), "^", Variable("j")})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerMonomialWithSameMonomialVariableOperationWorks)
{
    Term term(Variable("x") ^ Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Variable("x"), "^", Monomial(7, {{"x", 1}})})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerMonomialWithDifferentMonomialVariableOperationWorks)
{
    Term term(Variable("x") ^ Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Variable("x"), "^", Monomial(7, {{"y", 1}})})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerPolynomialOperationWorks)
{
    Term term(Variable("x") ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Variable("x"), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerExpressionOperationWorks)
{
    Term term(Variable("x") ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") ^ absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerTermOperationWorks)
{
    Term term(Variable("y") ^ Term(4));

    EXPECT_EQ(Term(Monomial(1, {{"y", 4}})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerConstantWithSameMonomialConstantOperationWorks)
{
    Term term(Monomial(8, {}) ^ Constant(2));

    EXPECT_EQ(Term(64), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerConstantWithDifferentMonomialConstantOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) ^ Constant(4));

    EXPECT_EQ(Term(Monomial(1296, {{"x", 8}, {"y", 16}})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerVariableWithSameMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"x", 1}}) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Monomial(7, {{"x", 1}}), "^", Variable("x")})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerVariableWithDifferentMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"y", 1}}) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Monomial(7, {{"y", 1}}), "^", Variable("x")})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerMonomialWithSameMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) ^ Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Monomial(8, {{"x", 2}}), "^", Monomial(4, {{"x", 2}})})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerMonomialWithDifferentMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) ^ Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Monomial(8, {{"x", 2}}), "^", Monomial(4, {{"x", 1}, {"y", 1}})})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerPolynomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Monomial(8, {{"x", 2}}), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerExpressionOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible(
    {Monomial(3, {{"x", 1}}), "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) ^ absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Monomial(3, {{"x", 1}}), "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerTermOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) ^ Term(4));

    EXPECT_EQ(Term(Monomial(1296, {{"x", 8}, {"y", 16}})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerZeroOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ 0);

    EXPECT_EQ(Term(1), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerPositiveConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Constant(3));

    EXPECT_EQ(Term(Polynomial{
                       Monomial(1, {{"x", 3}}),
                       Monomial(15, {{"x", 2}}),
                       Monomial(75, {{"x", 1}}),
                       Monomial(125, {})
                   }), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerNegativeConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Constant(-3));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Constant(1),
     "/",
     Polynomial{
         Monomial(1, {{"x", 3}}),
         Monomial(15, {{"x", 2}}),
         Monomial(75, {{"x", 1}}),
         Monomial(125, {})
     }})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerVariableOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})},
     "^",
     Variable("x")})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerMonomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Monomial(8, {{"x", 2}}));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})},
     "^",
     Monomial(8, {{"x", 2}})})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerPolynomialOperationWorks)
{
    Term term(Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})} ^ Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})},
     "^",
     Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})}})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerExpressionOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible(
    {Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerTermOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Term(3));

    EXPECT_EQ(Term(Polynomial{
                       Monomial(1, {{"x", 3}}),
                       Monomial(15, {{"x", 2}}),
                       Monomial(75, {{"x", 1}}),
                       Monomial(125, {})
                   }), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerConstantOperationWorks)
{
    Term term(createExpressionIfPossible({54}) ^ Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerVariableOperationWorks)
{
    Term term(createExpressionIfPossible({54}) ^ Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "^", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerMonomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) ^ Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible(
    {54, "^", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}
TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerPolynomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible(
    {54, "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}
TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerExpressionOperationWorks)
{
    Term term(createExpressionIfPossible({54}) ^ createExpressionIfPossible({87}));
    Expression expressionToExpect(
                createExpressionIfPossible({54, "^", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) ^ absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({createExpressionIfPossible({54}), "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerTermOperationWorks)
{
    Term term(createExpressionIfPossible({54}) ^ 10);

    Expression expressionToExpect(
                createExpressionIfPossible({54, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_FunctionRaiseToPowerConstantOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_FunctionRaiseToPowerVariableOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "^", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_FunctionRaiseToPowerMonomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "^", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_FunctionRaiseToPowerPolynomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_FunctionRaiseToPowerExpressionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "^", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_FunctionRaiseToPowerFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_FunctionRaiseToPowerTermOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ 10);

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_TermRaiseToPowerConstantOperationWithZeroExponentWorks)
{
    Term term(Constant(6) ^ Constant(0));

    EXPECT_EQ(Term(1), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_TermRaiseToPowerVariableOperationWorks)
{
    Term term(Constant(5) ^ Variable("x"));

    EXPECT_EQ(Term(
                  createExpressionIfPossible(
    {Constant(5),
     "^",
     Variable("x")})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_TermRaiseToPowerMonomialOperationWorks)
{
    Term term(Term(4) ^ Monomial(6, {{"x", 2}}));

    EXPECT_EQ(Term(
                  createExpressionIfPossible(
    {Constant(4),
     "^",
     Monomial(6, {{"x", 2}})})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_TermRaiseToPowerPolynomialOperationWorks)
{
    Term term(10 ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(
                  createExpressionIfPossible(
    {Constant(10),
     "^",
     Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_TermRaiseToPowerExpressionOperationWorks)
{
    Term term(10 ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_TermRaiseToPowerFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(10 ^ absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_TermRaiseToPowerTermOperationWorks)
{
    Term term(6 ^ Term(2));

    EXPECT_EQ(Term(36), term);
}

TEST(TermOperatorsTest, ValueIsZeroWhenSubtractingSameConstant)
{
    Term term(Constant(24) - Constant(24));

    EXPECT_EQ(Term(0), term);
}

TEST(TermOperatorsTest, ValueIsZeroWhenSubtractingSameVariable)
{
    Term term(Variable("power") - Variable("power"));

    EXPECT_EQ(Term(0), term);
}

TEST(TermOperatorsTest, ValueIsZeroWhenSubtractingSameMonomial)
{
    Term term(Monomial(15, {{"x", 4}}) - Monomial(15, {{"x", 4}}));

    EXPECT_EQ(Term(0), term);
}

TEST(TermOperatorsTest, ValueIsZeroWhenSubtractingSamePolynomial)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})} - Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(0), term);
}

TEST(TermOperatorsTest, ValueIsZeroWhenMultiplyingZeroToConstant)
{
    Term term(0 * Constant(24));

    EXPECT_EQ(Term(0), term);
}

TEST(TermOperatorsTest, ValueIsZeroWhenMultiplyingZeroToVariable)
{
    Term term(0 * Variable("power"));

    EXPECT_EQ(Term(0), term);
}

TEST(TermOperatorsTest, ValueIsZeroWhenMultiplyingZeroToMonomial)
{
    Term term(0 * Monomial(15, {{"x", 4}}));

    EXPECT_EQ(Term(0), term);
}

TEST(TermOperatorsTest, ValueIsZeroWhenMultiplyingZeroToPolynomial)
{
    Term term(0 * Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(0), term);
}

TEST(TermOperatorsTest, ValueIsSameWhenMultiplyingOneToConstant)
{
    Term term(Constant(1) * Constant(24));

    EXPECT_EQ(Term(24), term);
}

TEST(TermOperatorsTest, ValueIsSameWhenMultiplyingOneToVariable)
{
    Term term(Constant(1) * Variable("power"));

    EXPECT_EQ(Term(Variable("power")), term);
}

TEST(TermOperatorsTest, ValueIsSameWhenMultiplyingOneToMonomial)
{
    Term term(Constant(1) * Monomial(15, {{"x", 4}}));

    EXPECT_EQ(Term(Monomial(15, {{"x", 4}})), term);
}

TEST(TermOperatorsTest, ValueIsSameWhenMultiplyingOneToPolynomial)
{
    Term term(Constant(1) * Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 7}}), Monomial(5, {})}), term);
}

}

}
