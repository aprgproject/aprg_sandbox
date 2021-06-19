#include <Equation/Term/TermOperators.hpp>
#include <Equation/Utilities.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba
{

namespace equation
{

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
    Term term(+createExpressionIfPossible(Terms{Term(54)}));

    EXPECT_EQ(Term(createExpressionIfPossible(Terms{Term(54)})), term);
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
    Term term(-createExpressionIfPossible(Terms{Term(54)}));

    EXPECT_EQ(Term(createExpressionIfPossible(Terms{Term(54), Term("*"), Term(-1)})), term);
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
    Term term(Constant(10) + createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(10), Term("+"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
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
    Term term(Variable("x") + createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term("x"), Term("+"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
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
    Term term(Monomial(3, {{"x", 1}}) + createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Monomial(3, {{"x", 1}}), Term("+"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
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
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, Term("+"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ExpressionAddConstantOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) + Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("+"), Term(10)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ExpressionAddVariableOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) + Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("+"), Term("x")
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ExpressionAddMonomialOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) + Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("+"), Term(Monomial(3, {{"x", 1}}))
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ExpressionAddPolynomialOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("+"), Term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})})
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryPlusOperator_ExpressionAddExpressionOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) + createExpressionIfPossible(Terms{Term(87)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("+"), Term(87)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
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
    Term term(Constant(10) - createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(10), Term("-"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_VariableSubtractConstantOperationWorks)
{
    Term term(Variable("y") - Constant(4));

    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"y", 1}}), Monomial(-4, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_VariableSubtractVariableWithSameVariableOperationWorks)
{
    Term term(Variable("i") - Variable("i"));

    EXPECT_EQ(Term(Constant(0)), term);
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
    Term term(Variable("x") - createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term("x"), Term("-"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
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

    EXPECT_EQ(Term(Constant(0)), term);
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
    Term term(Monomial(3, {{"x", 1}}) - createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Monomial(3, {{"x", 1}}), Term("-"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
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

    EXPECT_EQ(Term(Constant(0)), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_PolynomialSubtractPolynomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} - Polynomial{Monomial(15, {}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(Polynomial{Monomial(-2, {{"x", 1}}), Monomial(-10, {})}), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_PolynomialSubtractExpressionOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, Term("-"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ExpressionSubtractConstantOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) - Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("-"), Term(10)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ExpressionSubtractVariableOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) - Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("-"), Term("x")
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ExpressionSubtractMonomialOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) - Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("-"), Term(Monomial(3, {{"x", 1}}))
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ExpressionSubtractPolynomialOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("-"), Term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})})
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMinusOperator_ExpressionSubtractExpressionOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) + createExpressionIfPossible(Terms{Term(87)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("+"), Term(87)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
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
    Term term(Constant(10) * createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(10), Term("*"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
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
    Term term(Variable("x") * createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term("x"), Term("*"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
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
    Term term(Monomial(3, {{"x", 1}}) * createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Monomial(3, {{"x", 1}}), Term("*"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
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
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(Monomial(5, {})), Term("*"), Term(54)})),
                        Term("+"),
                        Term(createExpressionIfPossible(Terms{Term(Monomial(1, {{"x", 1}})), Term("*"), Term(54)}))
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyConstantOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) * Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("*"), Term(10)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyVariableOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) * Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("*"), Term("x")
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyMonomialOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) * Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("*"), Term(Monomial(3, {{"x", 1}}))
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyPolynomialOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(createExpressionIfPossible(Terms{Term(54), Term("*"), Term(Monomial(5, {}))})),
                        Term("+"),
                        Term(createExpressionIfPossible(Terms{Term(54), Term("*"), Term(Monomial(1, {{"x", 1}}))}))
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ExpressionMultiplyExpressionOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) * createExpressionIfPossible(Terms{Term(87)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("*"), Term(87)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
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

    EXPECT_EQ(Term(createExpressionIfPossible(
                       Terms{
                           Constant(10),
                           Operator("/"),
                           Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}
                       })), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ConstantDivideExpressionOperationWorks)
{
    Term term(Constant(10) / createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(10), Term("/"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
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

    EXPECT_EQ(Term(createExpressionIfPossible(
                       Terms{
                           Variable("x"),
                           Operator("/"),
                           Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}
                       })), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_VariableDivideExpressionOperationWorks)
{
    Term term(Variable("x") / createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term("x"), Term("/"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
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
                       Terms{
                           Monomial(8, {{"x", 2}}),
                           Operator("/"),
                           Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}
                       })), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDivideExpressionOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) / createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Monomial(3, {{"x", 1}}), Term("/"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
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
                       Terms{
                           Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})},
                           Operator("/"),
                           Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})}
                       })), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_PolynomialDivideExpressionOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, Term("/"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ExpressionDivideConstantOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) / Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("/"), Term(10)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ExpressionDivideVariableOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) / Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("/"), Term("x")
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ExpressionDivideMonomialOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) / Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("/"), Term(Monomial(3, {{"x", 1}}))
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ExpressionDividePolynomialOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("/"), Term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})})
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryDivideOperator_ExpressionDivideExpressionOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) / createExpressionIfPossible(Terms{Term(87)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("/"), Term(87)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerConstantOperationWorks)
{
    Term term(Constant(6) ^ Constant(2));

    EXPECT_EQ(Term(36), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerVariableOperationWorks)
{
    Term term(Constant(5) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible(
                       Terms{
                           Constant(5),
                           Operator("^"),
                           Variable("x")
                       })), term);
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
                       Terms{
                           Constant(4),
                           Operator("^"),
                           Monomial(6, {{"x", 2}})
                       })), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerPolynomialOperationWorks)
{
    Term term(Constant(10) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
                       Terms{
                           Constant(10),
                           Operator("^"),
                           Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}
                       })), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerExpressionOperationWorks)
{
    Term term(Constant(10) ^ createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(10), Term("^"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
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
                       Terms{
                           Variable("i"),
                           Operator("^"),
                           Variable("i")
                       })), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerVariableWithDifferentVariableOperationWorks)
{
    Term term(Variable("i") ^ Variable("j"));

    EXPECT_EQ(Term(createExpressionIfPossible(
                       Terms{
                           Variable("i"),
                           Operator("^"),
                           Variable("j")
                       })), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerMonomialWithSameMonomialVariableOperationWorks)
{
    Term term(Variable("x") ^ Monomial(7, {{"x", 1}}));

    EXPECT_EQ(Term(createExpressionIfPossible(
                       Terms{
                           Variable("x"),
                           Operator("^"),
                           Monomial(7, {{"x", 1}})
                       })), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerMonomialWithDifferentMonomialVariableOperationWorks)
{
    Term term(Variable("x") ^ Monomial(7, {{"y", 1}}));

    EXPECT_EQ(Term(createExpressionIfPossible(
                       Terms{
                           Variable("x"),
                           Operator("^"),
                           Monomial(7, {{"y", 1}})
                       })), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerPolynomialOperationWorks)
{
    Term term(Variable("x") ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
                       Terms{
                           Variable("x"),
                           Operator("^"),
                           Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}
                       })), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerExpressionOperationWorks)
{
    Term term(Variable("x") ^ createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term("x"), Term("^"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
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
                       Terms{
                           Monomial(7, {{"x", 1}}),
                           Operator("^"),
                           Variable("x")
                       })), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerVariableWithDifferentMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"y", 1}}) ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible(
                       Terms{
                           Monomial(7, {{"y", 1}}),
                           Operator("^"),
                           Variable("x")
                       })), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerMonomialWithSameMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) ^ Monomial(4, {{"x", 2}}));

    EXPECT_EQ(Term(createExpressionIfPossible(
                       Terms{
                           Monomial(8, {{"x", 2}}),
                           Operator("^"),
                           Monomial(4, {{"x", 2}})
                       })), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerMonomialWithDifferentMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) ^ Monomial(4, {{"x", 1}, {"y", 1}}));

    EXPECT_EQ(Term(createExpressionIfPossible(
                       Terms{
                           Monomial(8, {{"x", 2}}),
                           Operator("^"),
                           Monomial(4, {{"x", 1}, {"y", 1}})
                       })), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerPolynomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
                       Terms{
                           Monomial(8, {{"x", 2}}),
                           Operator("^"),
                           Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}
                       })), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerExpressionOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) ^ createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Monomial(3, {{"x", 1}}), Term("^"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerZeroOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ 0);

    EXPECT_EQ(Term(1), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerPositiveConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ 3);

    EXPECT_EQ(Term(Polynomial{
                       Monomial(1, {{"x", 3}}),
                       Monomial(15, {{"x", 2}}),
                       Monomial(75, {{"x", 1}}),
                       Monomial(125, {})
                   }), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerNegativeConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ -3);

    EXPECT_EQ(Term(createExpressionIfPossible(
                       Terms{
                           Constant(1),
                           Operator("/"),
                           Polynomial{
                               Monomial(1, {{"x", 3}}),
                               Monomial(15, {{"x", 2}}),
                               Monomial(75, {{"x", 1}}),
                               Monomial(125, {})
                           }
                       })), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerVariableOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Variable("x"));

    EXPECT_EQ(Term(createExpressionIfPossible(
                       Terms{
                           Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})},
                           Operator("^"),
                           Variable("x")
                       })), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerMonomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Monomial(8, {{"x", 2}}));

    EXPECT_EQ(Term(createExpressionIfPossible(
                       Terms{
                           Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})},
                           Operator("^"),
                           Monomial(8, {{"x", 2}})
                       })), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerPolynomialOperationWorks)
{
    Term term(Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})} ^ Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(createExpressionIfPossible(
                       Terms{
                           Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})},
                           Operator("^"),
                           Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})}
                       })), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerExpressionOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ createExpressionIfPossible(Terms{Term(54)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}, Term("^"), Term(54)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerConstantOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) ^ Constant(10));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("^"), Term(10)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerVariableOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) ^ Variable("x"));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("^"), Term("x")
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerMonomialOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) ^ Monomial(3, {{"x", 1}}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("^"), Term(Monomial(3, {{"x", 1}}))
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerPolynomialOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("^"), Term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})})
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ExpressionRaiseToPowerExpressionOperationWorks)
{
    Term term(createExpressionIfPossible(Terms{Term(54)}) ^ createExpressionIfPossible(Terms{Term(87)}));

    Expression expressionToExpect(
                createExpressionIfPossible(
                    Terms{
                        Term(54), Term("^"), Term(87)
                    }));
    EXPECT_EQ(Term(expressionToExpect), term);
}

TEST(TermOperatorsTest, ValueIsZeroWhenSubtractingSameConstant)
{
    Term term(Constant(24) - Constant(24));

    EXPECT_EQ(Term(Constant(0)), term);
}

TEST(TermOperatorsTest, ValueIsZeroWhenSubtractingSameVariable)
{
    Term term(Variable("power") - Variable("power"));

    EXPECT_EQ(Term(Constant(0)), term);
}

TEST(TermOperatorsTest, ValueIsZeroWhenSubtractingSameMonomial)
{
    Term term(Monomial(15, {{"x", 4}}) - Monomial(15, {{"x", 4}}));

    EXPECT_EQ(Term(Constant(0)), term);
}

TEST(TermOperatorsTest, ValueIsZeroWhenSubtractingSamePolynomial)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})} - Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(Constant(0)), term);
}

TEST(TermOperatorsTest, ValueIsZeroWhenMultiplyingZeroToConstant)
{
    Term term(Constant(0) * Constant(24));

    EXPECT_EQ(Term(Constant(0)), term);
}

TEST(TermOperatorsTest, ValueIsZeroWhenMultiplyingZeroToVariable)
{
    Term term(Constant(0) * Variable("power"));

    EXPECT_EQ(Term(Constant(0)), term);
}

TEST(TermOperatorsTest, ValueIsZeroWhenMultiplyingZeroToMonomial)
{
    Term term(Constant(0) * Monomial(15, {{"x", 4}}));

    EXPECT_EQ(Term(Constant(0)), term);
}

TEST(TermOperatorsTest, ValueIsZeroWhenMultiplyingZeroToPolynomial)
{
    Term term(Constant(0) * Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    EXPECT_EQ(Term(Constant(0)), term);
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
