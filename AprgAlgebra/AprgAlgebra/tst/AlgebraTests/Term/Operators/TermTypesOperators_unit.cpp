#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Operators/TermTypeOperators.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(TermTypesOperatorsTest, UnaryPlusOperator_PlusConstantOperationWorks)
{
    Term term(+Constant(6));

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypesOperatorsTest, UnaryPlusOperator_PlusVariableOperationWorks)
{
    Term term(+Variable("x"));

    EXPECT_EQ(Term("x"), term);
}

TEST(TermTypesOperatorsTest, UnaryPlusOperator_PlusMonomialOperationWorks)
{
    Term term(+Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(4, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, UnaryPlusOperator_PlusPolynomialOperationWorks)
{
    Term term(+Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}), term);
}

TEST(TermTypesOperatorsTest, UnaryPlusOperator_PlusExpressionOperationWorks)
{
    Term term(+createExpressionIfPossible({54}));

    EXPECT_EQ(Term(createExpressionIfPossible({54})), term);
}

TEST(TermTypesOperatorsTest, UnaryPlusOperator_PlusFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(+absoluteValueFunction);

    EXPECT_EQ(Term(absoluteValueFunction), term);
}

TEST(TermTypesOperatorsTest, UnaryMinusOperator_MinusConstantOperationWorks)
{
    Term term(-Constant(6));

    EXPECT_EQ(Term(-6), term);
}

TEST(TermTypesOperatorsTest, UnaryMinusOperator_MinusVariableOperationWorks)
{
    Term term(-Variable("x"));

    EXPECT_EQ(Term(Monomial(-1, {{"x", 1}})), term);
}

TEST(TermTypesOperatorsTest, UnaryMinusOperator_MinusMonomialOperationWorks)
{
    Term term(-Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(-4, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, UnaryMinusOperator_MinusPolynomialOperationWorks)
{
    Term term(-Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypesOperatorsTest, UnaryMinusOperator_MinusExpressionOperationWorks)
{
    Term term(-createExpressionIfPossible({54}));

    EXPECT_EQ(Term(createExpressionIfPossible({-1, "*", 54})), term);
}

TEST(TermTypesOperatorsTest, UnaryMinusOperator_MinusFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(-absoluteValueFunction);

    Expression expressionToExpect(createExpressionIfPossible({-1, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_EmptyAddConstantOperationWorks)
{
    Term term(Term() + Constant(2));

    EXPECT_EQ(Term(2), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_ConstantAddEmptyOperationWorks)
{
    Term term(Constant(6) + Term());

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_ConstantAddConstantOperationWorks)
{
    Term term(Constant(6) + Constant(2));

    EXPECT_EQ(Term(8), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_ConstantAddVariableOperationWorks)
{
    Term term(Constant(5) + Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_ConstantAddMonomialWithSameMonomialConstantOperationWorks)
{
    Term term(Constant(8) + Monomial(2, {}));

    EXPECT_EQ(Term(10), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_ConstantAddMonomialWithDifferentMonomialConstantOperationWorks)
{
    Term term(Constant(4) + Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_ConstantAddPolynomialOperationWorks)
{
    Term term(Constant(10) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_ConstantAddExpressionOperationWorks)
{
    Term term(Constant(10) + createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_ConstantAddFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) + absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_ConstantAddTermOperationWorks)
{
    Term term(Constant(10) + Term(5));

    EXPECT_EQ(Term(15), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_VariableAddConstantOperationWorks)
{
    Term term(Variable("y") + Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_VariableAddVariableWithSameVariableOperationWorks)
{
    Term term(Variable("i") + Variable("i"));

    EXPECT_EQ(Term(Monomial(2, {{"i", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_VariableAddVariableWithDifferentVariableOperationWorks)
{
    Term term(Variable("i") + Variable("j"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"i", 1}}), Monomial(1, {{"j", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_VariableAddMonomialWithSameMonomialVariableOperationWorks)
{
    Term term(Variable("x") + Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(Monomial(8, {{"x", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_VariableAddMonomialWithDifferentMonomialVariableOperationWorks)
{
    Term term(Variable("x") + Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(7, {{"y", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_VariableAddPolynomialOperationWorks)
{
    Term term(Variable("x") + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_VariableAddExpressionOperationWorks)
{
    Term term(Variable("x") + createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_VariableAddFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") + absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_VariableAddTermOperationWorks)
{
    Term term(Variable("y") + Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_MonomialAddConstantWithSameMonomialConstantOperationWorks)
{
    Term term(Monomial(8, {}) + Constant(2));

    EXPECT_EQ(Term(10), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_MonomialAddConstantWithDifferentMonomialConstantOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) + Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_MonomialAddVariableWithSameMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"x", 1}}) + Variable("x"));

    EXPECT_EQ(Term(Monomial(8, {{"x", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_MonomialAddVariableWithDifferentMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"y", 1}}) + Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(7, {{"y", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_MonomialAddMonomialWithSameMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) + Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(Monomial(12, {{"x", 2}})), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_MonomialAddMonomialWithDifferentMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) + Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(8, {{"x", 2}}), Monomial(4, {{"x", 1}, {"y", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_MonomialAddPolynomialOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_MonomialAddExpressionOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) + createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({Monomial(3, {{"x", 1}}), "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_MonomialAddFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) + absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Monomial(3, {{"x", 1}}), "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_MonomialAddTermOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) + Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_PolynomialAddConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_PolynomialAddVariableOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_PolynomialAddMonomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Monomial(3, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_PolynomialAddPolynomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} + Polynomial{Monomial(15, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 1}}), Monomial(20, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_PolynomialAddExpressionOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_PolynomialAddFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_PolynomialAddTermOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Term(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_ExpressionAddConstantOperationWorks)
{
    Term term(createExpressionIfPossible({54}) + Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_ExpressionAddVariableOperationWorks)
{
    Term term(createExpressionIfPossible({54}) + Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({
                                               54, "+", "x"
                                           }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_ExpressionAddMonomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) + Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "+", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_ExpressionAddPolynomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible({54, "+", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_ExpressionAddExpressionOperationWorks)
{
    Term term(createExpressionIfPossible({54}) + createExpressionIfPossible({87}));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "+", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_ExpressionAddFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) + absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({createExpressionIfPossible({54}), "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_ExpressionAddTermOperationWorks)
{
    Term term(createExpressionIfPossible({54}) + Term(10));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_FunctionAddConstantOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_FunctionAddVariableOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "+", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_FunctionAddMonomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "+", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_FunctionAddPolynomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "+", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_FunctionAddExpressionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "+", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_FunctionAddFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_FunctionAddTermOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction + Term(10));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "+", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_TermAddConstantOperationWorks)
{
    Term term(Term(5) + Constant(10));

    EXPECT_EQ(Term(15), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_TermAddVariableOperationWorks)
{
    Term term(Term(4) + Variable("y"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_TermAddMonomialOperationWorks)
{
    Term term(Term(4) + Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_TermAddPolynomialOperationWorks)
{
    Term term(Term(10) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(15, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_TermAddExpressionOperationWorks)
{
    Term term(Term(10) + createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "+", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryPlusOperator_TermAddFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Term(10) + absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "+", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_EmptyAddConstantOperationWorks)
{
    Term term(Term() - Constant(2));

    EXPECT_EQ(Term(-2), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_ConstantAddEmptyOperationWorks)
{
    Term term(Constant(6) - Term());

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_ConstantSubtractConstantOperationWorks)
{
    Term term(Constant(6) - Constant(2));

    EXPECT_EQ(Term(4), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_ConstantSubtractVariableOperationWorks)
{
    Term term(Constant(5) - Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_ConstantSubtractMonomialWithSameMonomialConstantOperationWorks)
{
    Term term(Constant(8) - Monomial(2, {}));

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_ConstantSubtractMonomialWithDifferentMonomialConstantOperationWorks)
{
    Term term(Constant(4) - Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(-6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_ConstantSubtractPolynomialOperationWorks)
{
    Term term(Constant(10) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_ConstantSubtractExpressionOperationWorks)
{
    Term term(Constant(10) - createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_ConstantSubtractFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) - absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_ConstantSubtractTermOperationWorks)
{
    Term term(Constant(6) - Term(2));

    EXPECT_EQ(Term(4), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_VariableSubtractConstantOperationWorks)
{
    Term term(Variable("y") - Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(-4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_VariableSubtractVariableWithSameVariableOperationWorks)
{
    Term term(Variable("i") - Variable("i"));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_VariableSubtractVariableWithDifferentVariableOperationWorks)
{
    Term term(Variable("i") - Variable("j"));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"i", 1}}), Monomial(-1, {{"j", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_VariableSubtractMonomialWithSameMonomialVariableOperationWorks)
{
    Term term(Variable("x") - Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(Monomial(-6, {{"x", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_VariableSubtractMonomialWithDifferentMonomialVariableOperationWorks)
{
    Term term(Variable("x") - Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-7, {{"y", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_VariableSubtractPolynomialOperationWorks)
{
    Term term(Variable("x") - Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-3, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_VariableSubtractExpressionOperationWorks)
{
    Term term(Variable("x") - createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_VariableSubtractFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") - absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_VariableSubtractTermOperationWorks)
{
    Term term(Variable("y") - Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(-4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_MonomialSubtractConstantWithSameMonomialConstantOperationWorks)
{
    Term term(Monomial(8, {}) - Constant(2));

    EXPECT_EQ(Term(6), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_MonomialSubtractConstantWithDifferentMonomialConstantOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) - Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(-4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_MonomialSubtractVariableWithSameMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"x", 1}}) - Variable("x"));

    EXPECT_EQ(Term(Monomial(6, {{"x", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_MonomialSubtractVariableWithDifferentMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"y", 1}}) - Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(7, {{"y", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_MonomialSubtractMonomialThatResultsInZeroOperationWorks)
{
    Term term(Monomial(4, {{"x", 2}}) - Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_MonomialSubtractMonomialWithSameMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) - Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(Monomial(4, {{"x", 2}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_MonomialSubtractMonomialWithDifferentMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) - Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(8, {{"x", 2}}), Monomial(-4, {{"x", 1}, {"y", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_MonomialSubtractPolynomialOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_MonomialSubtractExpressionOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) - createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({Monomial(3, {{"x", 1}}), "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_MonomialSubtractFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) - absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Monomial(3, {{"x", 1}}), "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_MonomialSubtractTermOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) - Term(4));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 2}, {"y", 4}}), Monomial(-4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_PolynomialSubtractConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_PolynomialSubtractVariableOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(7, {{"x", 1}})} - Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_PolynomialSubtractMonomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - Monomial(3, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(-2, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_PolynomialSubtractPolynomialThatResultsInZeroOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} - Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})});

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_PolynomialSubtractPolynomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} - Polynomial{Monomial(15, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-2, {{"x", 1}}), Monomial(-10, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_PolynomialSubtractExpressionOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_PolynomialSubtractFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_PolynomialSubtractTermOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - Term(10));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_ExpressionSubtractConstantOperationWorks)
{
    Term term(createExpressionIfPossible({54}) - Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_ExpressionSubtractVariableOperationWorks)
{
    Term term(createExpressionIfPossible({54}) - Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "-", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_ExpressionSubtractMonomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) - Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "-", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_ExpressionSubtractPolynomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible({54, "-", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_ExpressionSubtractExpressionOperationWorks)
{
    Term term(createExpressionIfPossible({54}) + createExpressionIfPossible({87}));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "+", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_ExpressionSubtractFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) - absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({createExpressionIfPossible({54}), "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_ExpressionSubtractTermOperationWorks)
{
    Term term(createExpressionIfPossible({54}) - Term(10));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_FunctionSubtractConstantOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_FunctionSubtractVariableOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "-", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_FunctionSubtractMonomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "-", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_FunctionSubtractPolynomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "-", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_FunctionSubtractExpressionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "-", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_FunctionSubtractFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_FunctionSubtractTermOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction - Term(10));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "-", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_TermSubtractConstantOperationWorks)
{
    Term term(Term(5) - Constant(10));

    EXPECT_EQ(Term(-5), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_TermSubtractVariableOperationWorks)
{
    Term term(Term(4) - Variable("y"));

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"y", 1}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_TermSubtractMonomialOperationWorks)
{
    Term term(Term(4) - Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Polynomial{Monomial(-6, {{"x", 2}, {"y", 4}}), Monomial(4, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_TermSubtractPolynomialOperationWorks)
{
    Term term(Term(10) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-1, {{"x", 1}}), Monomial(5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_TermSubtractExpressionOperationWorks)
{
    Term term(Term(10) - createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "-", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMinusOperator_TermSubtractFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Term(10) - absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "-", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_EmptyAddConstantOperationWorks)
{
    Term term(Term() * Constant(2));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_ConstantAddEmptyOperationWorks)
{
    Term term(Constant(6) * Term());

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyConstantOperationWorks)
{
    Term term(Constant(6) * Constant(2));

    EXPECT_EQ(Term(12), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyVariableOperationWorks)
{
    Term term(Constant(5) * Variable("x"));

    EXPECT_EQ(Term(Monomial(5, {{"x", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyMonomialWithSameMonomialConstantOperationWorks)
{
    Term term(Constant(8) * Monomial(2, {}));

    EXPECT_EQ(Term(16), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyMonomialWithDifferentMonomialConstantOperationWorks)
{
    Term term(Constant(4) * Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyPolynomialOperationWorks)
{
    Term term(Constant(10) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyExpressionOperationWorks)
{
    Term term(Constant(10) * createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) * absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyTermOperationWorks)
{
    Term term(Constant(6) * Term(2));

    EXPECT_EQ(Term(12), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_VariableMultiplyConstantOperationWorks)
{
    Term term(Variable("y") * Constant(4));

    EXPECT_EQ(Term(Monomial(4, {{"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_VariableMultiplyVariableWithSameVariableOperationWorks)
{
    Term term(Variable("i") * Variable("i"));

    EXPECT_EQ(Term(Monomial(1, {{"i", 2}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_VariableMultiplyVariableWithDifferentVariableOperationWorks)
{
    Term term(Variable("i") * Variable("j"));

    EXPECT_EQ(Term(Monomial(1, {{"i", 1}, {"j", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_VariableMultiplyMonomialWithSameMonomialVariableOperationWorks)
{
    Term term(Variable("x") * Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(Monomial(7, {{"x", 2}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_VariableMultiplyMonomialWithDifferentMonomialVariableOperationWorks)
{
    Term term(Variable("x") * Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(Monomial(7, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_VariableMultiplyPolynomialOperationWorks)
{
    Term term(Variable("x") * Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 2}}), Monomial(5, {{"x", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_VariableMultiplyExpressionOperationWorks)
{
    Term term(Variable("x") * createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_VariableMultiplyFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") * absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_VariableMultiplyTermOperationWorks)
{
    Term term(Variable("y") * Term(4));

    EXPECT_EQ(Term(Monomial(4, {{"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyConstantWithSameMonomialConstantOperationWorks)
{
    Term term(Monomial(8, {}) * Constant(2));

    EXPECT_EQ(Term(16), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyConstantWithDifferentMonomialConstantOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) * Constant(4));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyVariableWithSameMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"x", 1}}) * Variable("x"));

    EXPECT_EQ(Term(Monomial(7, {{"x", 2}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyVariableWithDifferentMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"y", 1}}) * Variable("x"));

    EXPECT_EQ(Term(Monomial(7, {{"x", 1}, {"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyMonomialWithSameMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) * Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(Monomial(32, {{"x", 4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyMonomialWithDifferentMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) * Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(32, {{"x", 3}, {"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyPolynomialOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(3, {{"x", 2}}), Monomial(15, {{"x", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyExpressionOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) * createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({Monomial(3, {{"x", 1}}), "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) * absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Monomial(3, {{"x", 1}}), "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyTermOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) * Term(4));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyVariableOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})} * Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 2}}), Monomial(5, {{"x", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyMonomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Monomial(3, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(3, {{"x", 2}}), Monomial(15, {{"x", 1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyPolynomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Polynomial{Monomial(2, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 2}}), Monomial(7, {{"x", 1}}), Monomial(10, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyExpressionOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible(
    {createExpressionIfPossible({Monomial(5, {}), "*", 54}),
     "+",
     createExpressionIfPossible({Monomial(1, {{"x", 1}}), "*", 54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyTermOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Term(10));

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyConstantOperationWorks)
{
    Term term(createExpressionIfPossible({54}) * Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyVariableOperationWorks)
{
    Term term(createExpressionIfPossible({54}) * Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "*", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyMonomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) * Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "*", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyPolynomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible(
    {createExpressionIfPossible({54, "*", Monomial(5, {})}),
     "+",
     createExpressionIfPossible({54, "*", Monomial(1, {{"x", 1}})})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyExpressionOperationWorks)
{
    Term term(createExpressionIfPossible({54}) * createExpressionIfPossible({87}));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "*", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) * absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({createExpressionIfPossible({54}), "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyTermOperationWorks)
{
    Term term(createExpressionIfPossible({54}) * Term(10));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_FunctionMultiplyConstantOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_FunctionMultiplyVariableOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "*", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_FunctionMultiplyMonomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "*", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_FunctionMultiplyPolynomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "*", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_FunctionMultiplyExpressionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "*", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_FunctionMultiplyFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_FunctionMultiplyTermOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction * Term(10));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "*", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_TermMultiplyConstantOperationWorks)
{
    Term term(Term(2) * Constant(6));

    EXPECT_EQ(Term(12), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_TermMultiplyVariableOperationWorks)
{
    Term term(Term(4) * Variable("y"));

    EXPECT_EQ(Term(Monomial(4, {{"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_TermMultiplyMonomialOperationWorks)
{
    Term term(Term(4) * Monomial(6, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(24, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_TermMultiplyPolynomialOperationWorks)
{
    Term term(Term(10) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(10, {{"x", 1}}), Monomial(50, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_TermMultiplyExpressionOperationWorks)
{
    Term term(Term(10) * createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "*", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryMultiplyOperator_TermMultiplyFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Term(10) * absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "*", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_EmptyAddConstantOperationWorks)
{
    Term term(Term() / Constant(2));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_ConstantAddEmptyOperationWorks)
{
    Term term(Constant(6) / Term());

    EXPECT_EQ(getPositiveInfinityAsATerm(), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_ConstantDivideConstantOperationWorks)
{
    Term term(Constant(6) / Constant(2));

    EXPECT_EQ(Term(3), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_ConstantDivideVariableOperationWorks)
{
    Term term(Constant(5) / Variable("x"));

    EXPECT_EQ(Term(Monomial(5, {{"x", -1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_ConstantDivideMonomialWithSameMonomialConstantOperationWorks)
{
    Term term(Constant(8) / Monomial(2, {}));

    EXPECT_EQ(Term(4), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_ConstantDivideMonomialWithDifferentMonomialConstantOperationWorks)
{
    Term term(Constant(8) / Monomial(4, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(2, {{"x", -2}, {"y", -4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_ConstantDividePolynomialOperationWorks)
{
    Term term(Constant(10) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(
                  createExpressionIfPossible(
    {Constant(10),
     "/",
     Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_ConstantDivideExpressionOperationWorks)
{
    Term term(Constant(10) / createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_ConstantDivideFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) / absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_ConstantDivideTermOperationWorks)
{
    Term term(Constant(6) / Term(2));

    EXPECT_EQ(Term(3), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_VariableDivideConstantOperationWorks)
{
    Term term(Variable("y") / Constant(4));

    EXPECT_EQ(Term(Monomial(0.25, {{"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_VariableDivideVariableWithSameVariableOperationWorks)
{
    Term term(Variable("i") / Variable("i"));

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_VariableDivideVariableWithDifferentVariableOperationWorks)
{
    Term term(Variable("i") / Variable("j"));

    EXPECT_EQ(Term(Monomial(1, {{"i", 1}, {"j", -1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_VariableDivideMonomialWithSameMonomialVariableOperationWorks)
{
    Term term(Variable("x") / Monomial(4, {{"x", 1}}));

    EXPECT_EQ(Term(0.25), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_VariableDivideMonomialWithDifferentMonomialVariableOperationWorks)
{
    Term term(Variable("x") / Monomial(4, {{"y", 1}}));

    EXPECT_EQ(Term(Monomial(0.25, {{"x", 1}, {"y", -1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_VariableDividePolynomialOperationWorks)
{
    Term term(Variable("x") / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(
                  createExpressionIfPossible({
                                                 Variable("x"),
                                                 "/",
                                                 Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}
                                             })), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_VariableDivideExpressionOperationWorks)
{
    Term term(Variable("x") / createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_VariableDivideFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") / absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_VariableDivideTermOperationWorks)
{
    Term term(Variable("y") / Term(4));

    EXPECT_EQ(Term(Monomial(0.25, {{"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_MonomialDivideConstantWithSameMonomialConstantOperationWorks)
{
    Term term(Monomial(8, {}) / Constant(2));

    EXPECT_EQ(Term(4), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_MonomialDivideConstantWithDifferentMonomialConstantOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) / Constant(4));

    EXPECT_EQ(Term(Monomial(1.5, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_MonomialDivideVariableWithSameMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"x", 1}}) / Variable("x"));

    EXPECT_EQ(Term(7), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_MonomialDivideVariableWithDifferentMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"y", 1}}) / Variable("x"));

    EXPECT_EQ(Term(Monomial(7, {{"x", -1}, {"y", 1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_MonomialDivideMonomialWithSameMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) / Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(2), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_MonomialDivideMonomialWithDifferentMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) / Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(Monomial(2, {{"x", 1}, {"y", -1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_MonomialDividePolynomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Monomial(8, {{"x", 2}}), "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_MonomialDivideExpressionOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) / createExpressionIfPossible({54}));

    Expression expressionToExpect(createExpressionIfPossible(
    {Monomial(3, {{"x", 1}}), "/", 54 }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_MonomialDivideFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) / absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Monomial(3, {{"x", 1}}), "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_MonomialDivideTermOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) / Term(4));

    EXPECT_EQ(Term(Monomial(1.5, {{"x", 2}, {"y", 4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_PolynomialDivideConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / Constant(10));

    EXPECT_EQ(Term(Polynomial{Monomial(0.1, {{"x", 1}}), Monomial(0.5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_PolynomialDivideVariableOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(4, {{"x", 2}})} / Variable("x"));

    EXPECT_EQ(Term(Polynomial{Monomial(4, {{"x", 1}}), Monomial(5, {{"x", -1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_PolynomialDivideMonomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 2}})} / Monomial(2, {{"x", 1}}));

    EXPECT_EQ(Term(Polynomial{Monomial(0.5, {{"x", 1}}), Monomial(2.5, {{"x", -1}})}), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_PolynomialDividePolynomialOperationWorks)
{
    Term term(Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})} / Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})},
     "/",
     Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_PolynomialDivideExpressionOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible(
    {Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_PolynomialDivideFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_PolynomialDivideTermOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / Term(10));

    EXPECT_EQ(Term(Polynomial{Monomial(0.1, {{"x", 1}}), Monomial(0.5, {})}), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_ExpressionDivideConstantOperationWorks)
{
    Term term(createExpressionIfPossible({54}) / Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_ExpressionDivideVariableOperationWorks)
{
    Term term(createExpressionIfPossible({54}) / Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "/", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_ExpressionDivideMonomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) / Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "/", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_ExpressionDividePolynomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible({54, "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_ExpressionDivideExpressionOperationWorks)
{
    Term term(createExpressionIfPossible({54}) / createExpressionIfPossible({87}));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "/", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_ExpressionDivideFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) / absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({createExpressionIfPossible({54}), "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_ExpressionDivideTermOperationWorks)
{
    Term term(createExpressionIfPossible({54}) / Term(10));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_FunctionDivideConstantOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_FunctionDivideVariableOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "/", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_FunctionDivideMonomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "/", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_FunctionDividePolynomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_FunctionDivideExpressionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "/", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_FunctionDivideFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_FunctionDivideTermOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction / Term(10));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "/", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_TermDivideConstantOperationWorks)
{
    Term term(Term(6) / Constant(2));

    EXPECT_EQ(Term(3), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_TermDivideVariableOperationWorks)
{
    Term term(Term(5) / Variable("x"));

    EXPECT_EQ(Term(Monomial(5, {{"x", -1}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_TermDivideMonomialOperationWorks)
{
    Term term(Term(8) / Monomial(4, {{"x", 2}, {"y", 4}}));

    EXPECT_EQ(Term(Monomial(2, {{"x", -2}, {"y", -4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_TermDividePolynomialOperationWorks)
{
    Term term(Term(10) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Constant(10), "/", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_TermDivideExpressionOperationWorks)
{
    Term term(Term(10) / createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "/", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryDivideOperator_TermDivideFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Term(10) / absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "/", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_EmptyAddConstantOperationWorks)
{
    Term term(Term() ^ Constant(2));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_ConstantAddEmptyOperationWorks)
{
    Term term(Constant(6) ^ Term());

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerConstantOperationWorks)
{
    Term term(Constant(6) ^ Constant(2));

    EXPECT_EQ(Term(36), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerConstantOperationWithZeroExponentWorks)
{
    Term term(Constant(6) ^ Constant(0));

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerVariableOperationWorks)
{
    Term term(Constant(5) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Constant(5), "^", Variable("x")})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerMonomialWithSameMonomialConstantOperationWorks)
{
    Term term(Constant(8) ^ Monomial(2, {}));

    EXPECT_EQ(Term(64), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerMonomialWithDifferentMonomialConstantOperationWorks)
{
    Term term(Constant(4) ^ Monomial(6, {{"x", 2}}));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Constant(4), "^", Monomial(6, {{"x", 2}})})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerPolynomialOperationWorks)
{
    Term term(Constant(10) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Constant(10), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerExpressionOperationWorks)
{
    Term term(Constant(10) ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Constant(10) ^ absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerTermOperationWorks)
{
    Term term(Constant(6) ^ Term(2));

    EXPECT_EQ(Term(36), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerConstantOperationWorks)
{
    Term term(Variable("y") ^ Constant(4));

    EXPECT_EQ(Term(Monomial(1, {{"y", 4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerVariableWithSameVariableOperationWorks)
{
    Term term(Variable("i") ^ Variable("i"));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Variable("i"), "^", Variable("i")})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerVariableWithDifferentVariableOperationWorks)
{
    Term term(Variable("i") ^ Variable("j"));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Variable("i"), "^", Variable("j")})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerMonomialWithSameMonomialVariableOperationWorks)
{
    Term term(Variable("x") ^ Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Variable("x"), "^", Monomial(7, {{"x", 1}})})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerMonomialWithDifferentMonomialVariableOperationWorks)
{
    Term term(Variable("x") ^ Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Variable("x"), "^", Monomial(7, {{"y", 1}})})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerPolynomialOperationWorks)
{
    Term term(Variable("x") ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Variable("x"), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerExpressionOperationWorks)
{
    Term term(Variable("x") ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Variable("x") ^ absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({"x", "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerTermOperationWorks)
{
    Term term(Variable("y") ^ Term(4));

    EXPECT_EQ(Term(Monomial(1, {{"y", 4}})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerConstantWithSameMonomialConstantOperationWorks)
{
    Term term(Monomial(8, {}) ^ Constant(2));

    EXPECT_EQ(Term(64), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerConstantWithDifferentMonomialConstantOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) ^ Constant(4));

    EXPECT_EQ(Term(Monomial(1296, {{"x", 8}, {"y", 16}})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerVariableWithSameMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"x", 1}}) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Monomial(7, {{"x", 1}}), "^", Variable("x")})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerVariableWithDifferentMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"y", 1}}) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Monomial(7, {{"y", 1}}), "^", Variable("x")})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerMonomialWithSameMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) ^ Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Monomial(8, {{"x", 2}}), "^", Monomial(4, {{"x", 2}})})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerMonomialWithDifferentMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) ^ Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Monomial(8, {{"x", 2}}), "^", Monomial(4, {{"x", 1}, {"y", 1}})})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerPolynomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Monomial(8, {{"x", 2}}), "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerExpressionOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible(
    {Monomial(3, {{"x", 1}}), "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Monomial(3, {{"x", 1}}) ^ absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Monomial(3, {{"x", 1}}), "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerTermOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) ^ Term(4));

    EXPECT_EQ(Term(Monomial(1296, {{"x", 8}, {"y", 16}})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerZeroOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ 0);

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerPositiveConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Constant(3));

    EXPECT_EQ(Term(Polynomial{
                       Monomial(1, {{"x", 3}}),
                       Monomial(15, {{"x", 2}}),
                       Monomial(75, {{"x", 1}}),
                       Monomial(125, {})
                   }), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerNegativeConstantOperationWorks)
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

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerVariableOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})},
     "^",
     Variable("x")})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerMonomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Monomial(8, {{"x", 2}}));

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})},
     "^",
     Monomial(8, {{"x", 2}})})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerPolynomialOperationWorks)
{
    Term term(Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})} ^ Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
    {Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})},
     "^",
     Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})}})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerExpressionOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible(
    {Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerTermOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Term(3));

    EXPECT_EQ(Term(Polynomial{
                       Monomial(1, {{"x", 3}}),
                       Monomial(15, {{"x", 2}}),
                       Monomial(75, {{"x", 1}}),
                       Monomial(125, {})
                   }), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerConstantOperationWorks)
{
    Term term(createExpressionIfPossible({54}) ^ Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerVariableOperationWorks)
{
    Term term(createExpressionIfPossible({54}) ^ Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "^", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerMonomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) ^ Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible(
    {54, "^", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerPolynomialOperationWorks)
{
    Term term(createExpressionIfPossible({54}) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible(
    {54, "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerExpressionOperationWorks)
{
    Term term(createExpressionIfPossible({54}) ^ createExpressionIfPossible({87}));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "^", 87}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(createExpressionIfPossible({54}) ^ absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({createExpressionIfPossible({54}), "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerTermOperationWorks)
{
    Term term(createExpressionIfPossible({54}) ^ Term(10));

    Expression expressionToExpect(
                createExpressionIfPossible({54, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_FunctionRaiseToPowerConstantOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_FunctionRaiseToPowerVariableOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "^", "x"}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_FunctionRaiseToPowerMonomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "^", Monomial(3, {{"x", 1}})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_FunctionRaiseToPowerPolynomialOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "^", Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_FunctionRaiseToPowerExpressionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "^", createExpressionIfPossible({54})}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_FunctionRaiseToPowerFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_FunctionRaiseToPowerTermOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(absoluteValueFunction ^ Term(10));

    Expression expressionToExpect(
                createExpressionIfPossible({absoluteValueFunction, "^", 10}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_TermRaiseToPowerConstantOperationWithZeroExponentWorks)
{
    Term term(Constant(6) ^ Constant(0));

    EXPECT_EQ(Term(1), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_TermRaiseToPowerVariableOperationWorks)
{
    Term term(Constant(5) ^ Variable("x"));

    EXPECT_EQ(Term(
                  createExpressionIfPossible(
    {Constant(5),
     "^",
     Variable("x")})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_TermRaiseToPowerMonomialOperationWorks)
{
    Term term(Term(4) ^ Monomial(6, {{"x", 2}}));

    EXPECT_EQ(Term(
                  createExpressionIfPossible(
    {Constant(4),
     "^",
     Monomial(6, {{"x", 2}})})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_TermRaiseToPowerPolynomialOperationWorks)
{
    Term term(Term(10) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(
                  createExpressionIfPossible(
    {Constant(10),
     "^",
     Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}})), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_TermRaiseToPowerExpressionOperationWorks)
{
    Term term(Term(10) ^ createExpressionIfPossible({54}));

    Expression expressionToExpect(
                createExpressionIfPossible({10, "^", 54}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryRaiseToPowerOperator_TermRaiseToPowerFunctionOperationWorks)
{
    Function absoluteValueFunction(abs(Expression{}));

    Term term(Term(10) ^ absoluteValueFunction);

    Expression expressionToExpect(
                createExpressionIfPossible({10, "^", absoluteValueFunction}));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermTypesOperatorsTest, ValueIsZeroWhenSubtractingSameConstant)
{
    Term term(Constant(24) - Constant(24));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, ValueIsZeroWhenSubtractingSameVariable)
{
    Term term(Variable("power") - Variable("power"));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, ValueIsZeroWhenSubtractingSameMonomial)
{
    Term term(Monomial(15, {{"x", 4}}) - Monomial(15, {{"x", 4}}));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, ValueIsZeroWhenSubtractingSamePolynomial)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})} - Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, ValueIsZeroWhenMultiplyingZeroToConstant)
{
    Term term(0 * Constant(24));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, ValueIsZeroWhenMultiplyingZeroToVariable)
{
    Term term(0 * Variable("power"));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, ValueIsZeroWhenMultiplyingZeroToMonomial)
{
    Term term(0 * Monomial(15, {{"x", 4}}));

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, ValueIsZeroWhenMultiplyingZeroToPolynomial)
{
    Term term(0 * Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(0), term);
}

TEST(TermTypesOperatorsTest, ValueIsSameWhenMultiplyingOneToConstant)
{
    Term term(Constant(1) * Constant(24));

    EXPECT_EQ(Term(24), term);
}

TEST(TermTypesOperatorsTest, ValueIsSameWhenMultiplyingOneToVariable)
{
    Term term(Constant(1) * Variable("power"));

    EXPECT_EQ(Term(Variable("power")), term);
}

TEST(TermTypesOperatorsTest, ValueIsSameWhenMultiplyingOneToMonomial)
{
    Term term(Constant(1) * Monomial(15, {{"x", 4}}));

    EXPECT_EQ(Term(Monomial(15, {{"x", 4}})), term);
}

TEST(TermTypesOperatorsTest, ValueIsSameWhenMultiplyingOneToPolynomial)
{
    Term term(Constant(1) * Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(Polynomial{Monomial(6, {{"x", 7}}), Monomial(5, {})}), term);
}

}

}
