#include <BooleanAlgebra/Term/Operators/TermTypeOperators.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace booleanAlgebra {

TEST(TermTypesOperatorsTest, UnaryNotOperator_NotConstantOperationWorks) {
    Term term(~Constant(false));

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, UnaryNotOperator_NotVariableTermOperationWorks) {
    Term term(~VariableTerm("x"));

    EXPECT_EQ(Term("x'"), term);
}

TEST(TermTypesOperatorsTest, UnaryNotOperator_NotExpressionOperationWorks) {
    Term term(~createExpressionIfPossible({false}));

    EXPECT_EQ(Term(createExpressionIfPossible({true})), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperator_EmptyAndConstantOperationWorks) {
    Term term(Term() & Constant(true));

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperator_ConstantAndEmptyOperationWorks) {
    Term term(Constant(true) & Term());

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperator_ConstantAndConstantOperationWorks) {
    Term term(Constant(true) & Constant(false));

    EXPECT_EQ(Term(false), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperator_ConstantAndVariableTermOperationWorks) {
    Term term(Constant(true) & VariableTerm("x"));

    Term termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperator_ConstantAndExpressionOperationWorks) {
    Term term(Constant(true) & createExpressionIfPossible({false}));

    Term termToExpect(false);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperator_ConstantAndTermOperationWorks) {
    Term term(Constant(true) & Term(false));

    EXPECT_EQ(Term(false), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperator_VariableTermAndConstantOperationWorks) {
    Term term(VariableTerm("x") & Constant(true));

    Term termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperator_VariableTermAndVariableTermOperationWorks) {
    Term term(VariableTerm("x") & VariableTerm("y"));

    Term termToExpect(createExpressionIfPossible({"x", "&", "y"}));
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperator_VariableTermAndExpressionOperationWorks) {
    Term term(VariableTerm("x") & createExpressionIfPossible({true}));

    Term termToExpect("x");
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperator_VariableTermAndTermOperationWorks) {
    Term term(VariableTerm("x") & Term(true));

    Term termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperator_ExpressionAndConstantOperationWorks) {
    Term term(createExpressionIfPossible({false}) & Constant(true));

    Term termToExpect(false);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperator_ExpressionAndVariableTermOperationWorks) {
    Term term(createExpressionIfPossible({true}) & VariableTerm("x"));

    Term termToExpect("x");
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperator_ExpressionAndTermOperationWorks) {
    Term term(createExpressionIfPossible({false}) & Term(true));

    Term termToExpect(false);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperator_TermAndConstantOperationWorks) {
    Term term(Term(true) & Constant(false));

    EXPECT_EQ(Term(false), term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperator_TermAndVariableTermOperationWorks) {
    Term term(Term(true) & VariableTerm("x"));

    Term termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryAndOperator_TermAndExpressionOperationWorks) {
    Term term(Term(true) & createExpressionIfPossible({false}));

    Term termToExpect(false);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperator_EmptyOrConstantOperationWorks) {
    Term term(Term() | Constant(false));

    EXPECT_EQ(Term(false), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperator_ConstantOrEmptyOperationWorks) {
    Term term(Constant(false) | Term());

    EXPECT_EQ(Term(false), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperator_ConstantOrConstantOperationWorks) {
    Term term(Constant(true) | Constant(false));

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperator_ConstantOrVariableTermOperationWorks) {
    Term term(Constant(false) | VariableTerm("x"));

    Term termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperator_ConstantOrExpressionOperationWorks) {
    Term term(Constant(true) | createExpressionIfPossible({false}));

    Term termToExpect(true);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperator_ConstantOrTermOperationWorks) {
    Term term(Constant(true) | Term(false));

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperator_VariableTermOrConstantOperationWorks) {
    Term term(VariableTerm("x") | Constant(false));

    Term termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperator_VariableTermOrVariableTermOperationWorks) {
    Term term(VariableTerm("x") | VariableTerm("y"));

    Term termToExpect(createExpressionIfPossible({"x", "|", "y"}));
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperator_VariableTermOrExpressionOperationWorks) {
    Term term(VariableTerm("x") | createExpressionIfPossible({false}));

    Term termToExpect("x");
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperator_VariableTermOrTermOperationWorks) {
    Term term(VariableTerm("x") | Term(false));

    Term termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperator_ExpressionOrConstantOperationWorks) {
    Term term(createExpressionIfPossible({false}) | Constant(true));

    Term termToExpect(true);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperator_ExpressionOrVariableTermOperationWorks) {
    Term term(createExpressionIfPossible({false}) | VariableTerm("x"));

    Term termToExpect("x");
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperator_ExpressionOrTermOperationWorks) {
    Term term(createExpressionIfPossible({false}) | Term(true));

    Term termToExpect(true);
    EXPECT_EQ(Term(termToExpect), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperator_TermOrConstantOperationWorks) {
    Term term(Term(true) | Constant(false));

    EXPECT_EQ(Term(true), term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperator_TermOrVariableTermOperationWorks) {
    Term term(Term(false) | VariableTerm("x"));

    Term termToExpect("x");
    EXPECT_EQ(termToExpect, term);
}

TEST(TermTypesOperatorsTest, BinaryOrOperator_TermOrExpressionOperationWorks) {
    Term term(Term(true) | createExpressionIfPossible({false}));

    Term termToExpect(true);
    EXPECT_EQ(Term(termToExpect), term);
}

}  // namespace booleanAlgebra

}  // namespace alba
