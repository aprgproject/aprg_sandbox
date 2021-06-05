#include <TermOperators.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(TermOperatorsTest, UnaryPlusOperator_PlusConstantOperationWorks)
{
    Term term(+Constant(6));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(6, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, UnaryPlusOperator_PlusVariableOperationWorks)
{
    Term term(+Variable("x"));

    ASSERT_EQ(TermType::Variable, term.getTermType());
    EXPECT_EQ("x", term.getVariableConstReference().getVariableName());
}

TEST(TermOperatorsTest, UnaryPlusOperator_PlusMonomialOperationWorks)
{
    Term term(+Monomial(4, {{"x", 1}, {"y", 1}}));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(4, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
}

TEST(TermOperatorsTest, UnaryPlusOperator_PlusPolynomialOperationWorks)
{
    Term term(+Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, UnaryMinusOperator_MinusConstantOperationWorks)
{
    Term term(-Constant(6));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(-6, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, UnaryMinusOperator_MinusVariableOperationWorks)
{
    Term term(-Variable("x"));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(-1, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
}

TEST(TermOperatorsTest, UnaryMinusOperator_MinusMonomialOperationWorks)
{
    Term term(-Monomial(4, {{"x", 1}, {"y", 1}}));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(-4, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
}

TEST(TermOperatorsTest, UnaryMinusOperator_MinusPolynomialOperationWorks)
{
    Term term(-Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(-5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(-1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_ConstantAddConstantOperationWorks)
{
    Term term(Constant(6) + Constant(2));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(8, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_ConstantAddVariableOperationWorks)
{
    Term term(Constant(5) + Variable("x"));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_ConstantAddMonomialWithSameMonomialConstantOperationWorks)
{
    Term term(Constant(8) + Monomial(2, {}));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(10, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_ConstantAddMonomialWithDifferentMonomialConstantOperationWorks)
{
    Term term(Constant(4) + Monomial(6, {{"x", 2}, {"y", 4}}));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(4, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(6, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap2.size());
    EXPECT_DOUBLE_EQ(2, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(4, variableMap2.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_ConstantAddPolynomialOperationWorks)
{
    Term term(Constant(10) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(15, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_VariableAddConstantOperationWorks)
{
    Term term(Variable("y") + Constant(4));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(1, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(1, variableMap1.at("y").getDouble());
    EXPECT_DOUBLE_EQ(4, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap2.empty());
}

TEST(TermOperatorsTest, BinaryPlusOperator_VariableAddVariableWithSameVariableOperationWorks)
{
    Term term(Variable("i") + Variable("i"));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(2, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("i").getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_VariableAddMonomialWithSameMonomialVariableOperationWorks)
{
    Term term(Variable("x") + Monomial(7, {{"x", 1}}));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(8, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_VariableAddMonomialWithDifferentMonomialVariableOperationWorks)
{
    Term term(Variable("x") + Monomial(7, {{"y", 1}}));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(1, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(1, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(7, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_VariableAddPolynomialOperationWorks)
{
    Term term(Variable("x") + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(2, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_MonomialAddConstantWithSameMonomialConstantOperationWorks)
{
    Term term(Monomial(8, {}) + Constant(2));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(10, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_MonomialAddConstantWithDifferentMonomialConstantOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) + Constant(4));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(6, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap2.size());
    EXPECT_DOUBLE_EQ(2, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(4, variableMap2.at("y").getDouble());
    EXPECT_DOUBLE_EQ(4, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
}

TEST(TermOperatorsTest, BinaryPlusOperator_MonomialAddVariableWithSameMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"x", 1}}) + Variable("x"));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(8, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_MonomialAddVariableWithDifferentMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"y", 1}}) + Variable("x"));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(7, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(1, variableMap1.at("y").getDouble());
    EXPECT_DOUBLE_EQ(1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_MonomialAddMonomialWithSameMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) + Monomial(4, {{"x", 2}}));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(12, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(2, variableMap.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_MonomialAddMonomialWithDifferentMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) + Monomial(4, {{"x", 1}, {"y", 1}}));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(8, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(2, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(4, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_MonomialAddPolynomialOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) + Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(4, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_PolynomialAddConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Constant(10));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(15, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_PolynomialAddVariableOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Variable("x"));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(2, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_PolynomialAddMonomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} + Monomial(3, {{"x", 1}}));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(4, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryPlusOperator_PolynomialAddPolynomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} + Polynomial{Monomial(15, {}), Monomial(4, {{"x", 1}})});

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(20, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(6, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_ConstantSubtractConstantOperationWorks)
{
    Term term(Constant(6) - Constant(2));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(4, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_ConstantSubtractVariableOperationWorks)
{
    Term term(Constant(5) - Variable("x"));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(-1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_ConstantSubtractMonomialWithSameMonomialConstantOperationWorks)
{
    Term term(Constant(8) - Monomial(2, {}));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(6, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_ConstantSubtractMonomialWithDifferentMonomialConstantOperationWorks)
{
    Term term(Constant(4) - Monomial(6, {{"x", 2}, {"y", 4}}));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(4, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(-6, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap2.size());
    EXPECT_DOUBLE_EQ(2, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(4, variableMap2.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_ConstantSubtractPolynomialOperationWorks)
{
    Term term(Constant(10) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(-1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_VariableSubtractConstantOperationWorks)
{
    Term term(Variable("y") - Constant(4));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(1, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(1, variableMap1.at("y").getDouble());
    EXPECT_DOUBLE_EQ(-4, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap2.empty());
}

TEST(TermOperatorsTest, BinaryMinusOperator_VariableSubtractVariableWithSameVariableOperationWorks)
{
    Term term(Variable("i") - Variable("i"));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(0, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_VariableSubtractMonomialWithSameMonomialVariableOperationWorks)
{
    Term term(Variable("x") - Monomial(7, {{"x", 1}}));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(-6, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_VariableSubtractMonomialWithDifferentMonomialVariableOperationWorks)
{
    Term term(Variable("x") - Monomial(7, {{"y", 1}}));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(1, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(1, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(-7, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_VariableSubtractPolynomialOperationWorks)
{
    Term term(Variable("x") - Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})});

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(-3, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(1, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(-5, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap2.empty());
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractConstantWithSameMonomialConstantOperationWorks){
    Term term(Monomial(8, {}) - Constant(2));

    ASSERT_EQ(TermType::Constant, term.getTermType());    EXPECT_DOUBLE_EQ(6, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractConstantWithDifferentMonomialConstantOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) - Constant(4));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(6, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap2.size());
    EXPECT_DOUBLE_EQ(2, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(4, variableMap2.at("y").getDouble());
    EXPECT_DOUBLE_EQ(-4, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractVariableWithSameMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"x", 1}}) - Variable("x"));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(6, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractVariableWithDifferentMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"y", 1}}) - Variable("x"));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(7, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(1, variableMap1.at("y").getDouble());
    EXPECT_DOUBLE_EQ(-1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractMonomialThatResultsInZeroOperationWorks)
{
    Term term(Monomial(4, {{"x", 2}}) - Monomial(4, {{"x", 2}}));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(0, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractMonomialWithSameMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) - Monomial(4, {{"x", 2}}));
    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(4, monomial.getConstantConstReference().getDouble());    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(2, variableMap.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractMonomialWithDifferentMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) - Monomial(4, {{"x", 1}, {"y", 1}}));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(8, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(2, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(-4, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_MonomialSubtractPolynomialOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) - Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(2, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(1, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(-5, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap2.empty());
}

TEST(TermOperatorsTest, BinaryMinusOperator_PolynomialSubtractConstantOperationWorks){
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - Constant(10));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(-5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_PolynomialSubtractVariableOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(7, {{"x", 1}})} - Variable("x"));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(6, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_PolynomialSubtractMonomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} - Monomial(3, {{"x", 1}}));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(-2, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_PolynomialSubtractPolynomialThatResultsInZeroOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} - Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})});

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(0, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryMinusOperator_PolynomialSubtractPolynomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(2, {{"x", 1}})} - Polynomial{Monomial(15, {}), Monomial(4, {{"x", 1}})});
    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());    EXPECT_DOUBLE_EQ(-10, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(-2, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyConstantOperationWorks)
{
    Term term(Constant(6) * Constant(2));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(12, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyVariableOperationWorks)
{
    Term term(Constant(5) * Variable("x"));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(5, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyMonomialWithSameMonomialConstantOperationWorks)
{
    Term term(Constant(8) * Monomial(2, {}));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(16, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyPolynomialOperationWorks)
{
    Term term(Constant(10) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(50, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(10, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_ConstantMultiplyMonomialWithDifferentMonomialConstantOperationWorks)
{
    Term term(Constant(4) * Monomial(6, {{"x", 2}, {"y", 4}}));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(24, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(2, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(4, variableMap.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_VariableMultiplyConstantOperationWorks)
{
    Term term(Variable("y") * Constant(4));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(4, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_VariableMultiplyVariableWithSameVariableOperationWorks)
{
    Term term(Variable("i") * Variable("i"));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(1, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(2, variableMap.at("i").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_VariableMultiplyMonomialWithSameMonomialVariableOperationWorks)
{
    Term term(Variable("x") * Monomial(7, {{"x", 1}}));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(2, variableMap.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_VariableMultiplyMonomialWithDifferentMonomialVariableOperationWorks)
{
    Term term(Variable("x") * Monomial(7, {{"y", 1}}));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_VariableMultiplyPolynomialOperationWorks)
{
    Term term(Variable("x") * Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})});

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(1, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(4, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(2, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyConstantWithSameMonomialConstantOperationWorks)
{
    Term term(Monomial(8, {}) * Constant(2));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(16, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyConstantWithDifferentMonomialConstantOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) * Constant(4));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(24, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(2, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(4, variableMap.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyVariableWithSameMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"x", 1}}) * Variable("x"));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(2, variableMap.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyVariableWithDifferentMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"y", 1}}) * Variable("x"));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyMonomialWithSameMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) * Monomial(4, {{"x", 2}}));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(32, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(4, variableMap.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyMonomialWithDifferentMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) * Monomial(4, {{"x", 1}, {"y", 1}}));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(32, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(3, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_MonomialMultiplyPolynomialOperationWorks)
{
    Term term(Monomial(3, {{"x", 1}}) * Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(15, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(1, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(3, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(2, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Constant(10));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(50, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(10, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyVariableOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(4, {{"x", 1}})} * Variable("x"));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(1, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(4, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(2, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyMonomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Monomial(3, {{"x", 1}}));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(15, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(1, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(3, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(2, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryMultiplyOperator_PolynomialMultiplyPolynomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} * Polynomial{Monomial(2, {}), Monomial(1, {{"x", 1}})});

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(3u, monomials.size());
    EXPECT_DOUBLE_EQ(10, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(7, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(1, monomials.at(2).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap3(monomials.at(2).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap3.size());
    EXPECT_DOUBLE_EQ(2, variableMap3.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_ConstantDivideConstantOperationWorks)
{
    Term term(Constant(6) / Constant(2));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(3, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_ConstantDivideVariableOperationWorks)
{
    Term term(Constant(5) / Variable("x"));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(5, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(-1, variableMap.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_ConstantDivideMonomialWithSameMonomialConstantOperationWorks)
{
    Term term(Constant(8) / Monomial(2, {}));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(4, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_ConstantDivideMonomialWithDifferentMonomialConstantOperationWorks)
{
    Term term(Constant(8) / Monomial(4, {{"x", 2}, {"y", 4}}));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(2, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(-2, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(-4, variableMap.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_ConstantDividePolynomialOperationWorks)
{
    Term term(Constant(10) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Constant, term1.getTermType());
    EXPECT_DOUBLE_EQ(10, term1.getConstantConstReference().getNumberConstReference().getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("/", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Polynomial, term3.getTermType());
    Monomials const& monomials(term3.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_VariableDivideConstantOperationWorks)
{
    Term term(Variable("y") / Constant(4));
    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(0.25, monomial.getConstantConstReference().getDouble());    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_VariableDivideVariableWithSameVariableOperationWorks)
{
    Term term(Variable("i") / Variable("i"));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(1, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_VariableDivideMonomialWithSameMonomialVariableOperationWorks)
{
    Term term(Variable("x") / Monomial(4, {{"x", 1}}));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(0.25, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_VariableDivideMonomialWithDifferentMonomialVariableOperationWorks)
{
    Term term(Variable("x") / Monomial(4, {{"y", 1}}));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(0.25, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(-1, variableMap.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_VariableDividePolynomialOperationWorks)
{
    Term term(Variable("x") / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Variable, term1.getTermType());
    EXPECT_EQ("x", term1.getVariableConstReference().getVariableName());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("/", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Polynomial, term3.getTermType());
    Monomials const& monomials(term3.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDivideConstantWithSameMonomialConstantOperationWorks)
{
    Term term(Monomial(8, {}) / Constant(2));
    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(4, term.getConstantConstReference().getNumberConstReference().getDouble());
}
TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDivideConstantWithDifferentMonomialConstantOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) / Constant(4));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(1.5, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(2, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(4, variableMap.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDivideVariableWithSameMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"x", 1}}) / Variable("x"));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(7, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDivideVariableWithDifferentMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"y", 1}}) / Variable("x"));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
    EXPECT_DOUBLE_EQ(-1, variableMap.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDivideMonomialWithSameMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) / Monomial(4, {{"x", 2}}));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(2, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDivideMonomialWithDifferentMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) / Monomial(4, {{"x", 1}, {"y", 1}}));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(2, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(-1, variableMap.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_MonomialDividePolynomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) / Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Monomial, term1.getTermType());
    Monomial const& monomial(term1.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(8, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMapInMonomial(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMapInMonomial.size());
    EXPECT_DOUBLE_EQ(2, variableMapInMonomial.at("x").getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("/", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Polynomial, term3.getTermType());
    Monomials const& monomials(term3.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_PolynomialDivideConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} / Constant(10));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(0.5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(0.1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_PolynomialDivideVariableOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(4, {{"x", 2}})} / Variable("x"));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(-1, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(4, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_PolynomialDivideMonomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 2}})} / Monomial(2, {{"x", 1}}));

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(2.5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(-1, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(0.5, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryDivideOperator_PolynomialDividePolynomialOperationWorks)
{
    Term term(Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})} / Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Polynomial, term1.getTermType());
    Monomials const& monomials1(term1.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials1.size());
    EXPECT_DOUBLE_EQ(2, monomials1.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials1.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(3, monomials1.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials1.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(4, variableMap2.at("x").getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("/", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Polynomial, term3.getTermType());
    Monomials const& monomials2(term3.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials2.size());
    EXPECT_DOUBLE_EQ(5, monomials2.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap3(monomials2.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap3.empty());
    EXPECT_DOUBLE_EQ(6, monomials2.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap4(monomials2.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap4.size());
    EXPECT_DOUBLE_EQ(7, variableMap4.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerConstantOperationWorks)
{
    Term term(Constant(6) ^ Constant(2));
    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(36, term.getConstantConstReference().getNumberConstReference().getDouble());
}
TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerVariableOperationWorks)
{
    Term term(Constant(5) ^ Variable("x"));

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Constant, term1.getTermType());
    EXPECT_DOUBLE_EQ(5, term1.getConstantConstReference().getNumberConstReference().getDouble());    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ("x", term3.getVariableConstReference().getVariableName());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerMonomialWithSameMonomialConstantOperationWorks)
{
    Term term(Constant(8) ^ Monomial(2, {}));

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(64, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerMonomialWithDifferentMonomialConstantOperationWorks)
{
    Term term(Constant(4) ^ Monomial(6, {{"x", 2}}));

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Constant, term1.getTermType());
    EXPECT_DOUBLE_EQ(4, term1.getConstantConstReference().getNumberConstReference().getDouble());    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Monomial, term3.getTermType());
    Monomial const& monomial(term3.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(6, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(2, variableMap.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_ConstantRaiseToPowerPolynomialOperationWorks)
{
    Term term(Constant(10) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Constant, term1.getTermType());
    EXPECT_DOUBLE_EQ(10, term1.getConstantConstReference().getNumberConstReference().getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Polynomial, term3.getTermType());
    Monomials const& monomials(term3.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerConstantOperationWorks)
{
    Term term(Variable("y") ^ Constant(4));
    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(1, monomial.getConstantConstReference().getDouble());    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(4, variableMap.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerVariableWithSameVariableOperationWorks)
{
    Term term(Variable("i") ^ Variable("i"));

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Variable, term1.getTermType());
    EXPECT_EQ("i", term1.getVariableConstReference().getVariableName());    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ("i", term3.getVariableConstReference().getVariableName());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerMonomialWithSameMonomialVariableOperationWorks)
{
    Term term(Variable("x") ^ Monomial(7, {{"x", 1}}));

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Variable, term1.getTermType());
    EXPECT_EQ("x", term1.getVariableConstReference().getVariableName());    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Monomial, term3.getTermType());
    Monomial const& monomial(term3.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerMonomialWithDifferentMonomialVariableOperationWorks)
{
    Term term(Variable("x") ^ Monomial(7, {{"y", 1}}));

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Variable, term1.getTermType());
    EXPECT_EQ("x", term1.getVariableConstReference().getVariableName());    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Monomial, term3.getTermType());
    Monomial const& monomial(term3.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_VariableRaiseToPowerPolynomialOperationWorks)
{
    Term term(Variable("x") ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Variable, term1.getTermType());
    EXPECT_EQ("x", term1.getVariableConstReference().getVariableName());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Polynomial, term3.getTermType());
    Monomials const& monomials(term3.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerConstantWithSameMonomialConstantOperationWorks)
{
    Term term(Monomial(8, {}) ^ Constant(2));
    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(64, term.getConstantConstReference().getNumberConstReference().getDouble());
}
TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerConstantWithDifferentMonomialConstantOperationWorks)
{
    Term term(Monomial(6, {{"x", 2}, {"y", 4}}) ^ Constant(4));

    ASSERT_EQ(TermType::Monomial, term.getTermType());
    Monomial const& monomial(term.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(1296, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(8, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(16, variableMap.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerVariableWithSameMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"x", 1}}) ^ Variable("x"));

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Monomial, term1.getTermType());
    Monomial const& monomial(term1.getMonomialConstReference());    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ("x", term3.getVariableConstReference().getVariableName());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerVariableWithDifferentMonomialVariableOperationWorks)
{
    Term term(Monomial(7, {{"y", 1}}) ^ Variable("x"));

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Monomial, term1.getTermType());
    Monomial const& monomial(term1.getMonomialConstReference());    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ("x", term3.getVariableConstReference().getVariableName());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerMonomialWithSameMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) ^ Monomial(4, {{"x", 2}}));

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Monomial, term1.getTermType());
    Monomial const& monomial1(term1.getMonomialConstReference());    EXPECT_DOUBLE_EQ(8, monomial1.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomial1.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(2, variableMap1.at("x").getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Monomial, term3.getTermType());
    Monomial const& monomial2(term3.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(4, monomial2.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial2.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(2, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerMonomialWithDifferentMonomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) ^ Monomial(4, {{"x", 1}, {"y", 1}}));

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Monomial, term1.getTermType());
    Monomial const& monomial1(term1.getMonomialConstReference());    EXPECT_DOUBLE_EQ(8, monomial1.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomial1.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(2, variableMap1.at("x").getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Monomial, term3.getTermType());
    Monomial const& monomial2(term3.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(4, monomial2.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial2.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("y").getDouble());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_MonomialRaiseToPowerPolynomialOperationWorks)
{
    Term term(Monomial(8, {{"x", 2}}) ^ Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})});

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Monomial, term1.getTermType());
    Monomial const& monomial(term1.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(8, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMapInMonomial(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMapInMonomial.size());
    EXPECT_DOUBLE_EQ(2, variableMapInMonomial.at("x").getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Polynomial, term3.getTermType());
    Monomials const& monomials(term3.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerZeroOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ 0);

    ASSERT_EQ(TermType::Constant, term.getTermType());
    EXPECT_DOUBLE_EQ(1, term.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerPositiveConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ 3);

    ASSERT_EQ(TermType::Polynomial, term.getTermType());
    Monomials const& monomials(term.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(4u, monomials.size());
    EXPECT_DOUBLE_EQ(125, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(75, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(15, monomials.at(2).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap3(monomials.at(2).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap3.size());
    EXPECT_DOUBLE_EQ(2, variableMap3.at("x").getDouble());
    EXPECT_DOUBLE_EQ(1, monomials.at(3).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap4(monomials.at(3).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap4.size());
    EXPECT_DOUBLE_EQ(3, variableMap4.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerNegativeConstantOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ -3);

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Constant, term1.getTermType());
    EXPECT_DOUBLE_EQ(1, term1.getConstantConstReference().getNumberConstReference().getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("/", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Polynomial, term3.getTermType());
    Monomials const& monomials(term3.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(4u, monomials.size());
    EXPECT_DOUBLE_EQ(125, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(75, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(15, monomials.at(2).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap3(monomials.at(2).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap3.size());
    EXPECT_DOUBLE_EQ(2, variableMap3.at("x").getDouble());
    EXPECT_DOUBLE_EQ(1, monomials.at(3).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap4(monomials.at(3).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap4.size());
    EXPECT_DOUBLE_EQ(3, variableMap4.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerVariableOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Variable("x"));

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Polynomial, term1.getTermType());
    Monomials const& monomials(term1.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ("x", term3.getVariableConstReference().getVariableName());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerMonomialOperationWorks)
{
    Term term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})} ^ Monomial(8, {{"x", 2}}));

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Polynomial, term1.getTermType());
    Monomials const& monomials(term1.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Monomial, term3.getTermType());
    Monomial const& monomial(term3.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(8, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMapInMonomial(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMapInMonomial.size());
    EXPECT_DOUBLE_EQ(2, variableMapInMonomial.at("x").getDouble());
}

TEST(TermOperatorsTest, BinaryRaiseToPowerOperator_PolynomialRaiseToPowerPolynomialOperationWorks)
{
    Term term(Polynomial{Monomial(2, {}), Monomial(3, {{"x", 4}})} ^ Polynomial{Monomial(5, {}), Monomial(6, {{"x", 7}})});

    ASSERT_EQ(TermType::Expression, term.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(term.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Polynomial, term1.getTermType());
    Monomials const& monomials1(term1.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials1.size());
    EXPECT_DOUBLE_EQ(2, monomials1.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials1.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(3, monomials1.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials1.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(4, variableMap2.at("x").getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Polynomial, term3.getTermType());
    Monomials const& monomials2(term3.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials2.size());
    EXPECT_DOUBLE_EQ(5, monomials2.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap3(monomials2.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap3.empty());
    EXPECT_DOUBLE_EQ(6, monomials2.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap4(monomials2.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap4.size());
    EXPECT_DOUBLE_EQ(7, variableMap4.at("x").getDouble());
}

}

}