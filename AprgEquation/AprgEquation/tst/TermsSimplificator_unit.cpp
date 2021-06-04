#include <TermsSimplificator.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(TermsSimplificatorTest, ConstantOperatorConstantPatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term(5), Term("+"), Term(2)});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(7, termsToVerify.at(0).getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermsSimplificatorTest, ConstantAddVariablePatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term(5), Term("+"), Term("x")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Polynomial, termsToVerify.at(0).getTermType());
    Monomials const& monomials(termsToVerify.at(0).getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermsSimplificatorTest, ConstantSubtractVariablePatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term(5), Term("-"), Term("x")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Polynomial, termsToVerify.at(0).getTermType());
    Monomials const& monomials(termsToVerify.at(0).getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(5, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(-1, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(1, variableMap2.at("x").getDouble());
}

TEST(TermsSimplificatorTest, ConstantMultiplyVariablePatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term(5), Term("*"), Term("x")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(5, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
}

TEST(TermsSimplificatorTest, ConstantDivideVariablePatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term(5), Term("/"), Term("x")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(5, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(-1, variableMap.at("x").getDouble());
}

TEST(TermsSimplificatorTest, ConstantRaiseToPowerVariablePatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term(5), Term("^"), Term("x")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::ExpressionWithSingleTerm, termsToVerify.at(0).getTermType());
    WrappedTerms::BaseTermPointers const& baseTermPointersToVerify(termsToVerify.at(0).getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Constant, term1.getTermType());
    EXPECT_DOUBLE_EQ(5, term1.getConstantConstReference().getNumberConstReference().getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ("x", term3.getVariableConstReference().getVariableName());
}

TEST(TermsSimplificatorTest, VariableAddConstantPatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("y"), Term("+"), Term(4)});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Polynomial, termsToVerify.at(0).getTermType());
    Monomials const& monomials(termsToVerify.at(0).getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(1, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(1, variableMap1.at("y").getDouble());
    EXPECT_DOUBLE_EQ(4, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap2.empty());
}

TEST(TermsSimplificatorTest, VariableSubtractConstantPatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("y"), Term("-"), Term(4)});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Polynomial, termsToVerify.at(0).getTermType());
    Monomials const& monomials(termsToVerify.at(0).getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials.size());
    EXPECT_DOUBLE_EQ(1, monomials.at(0).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomials.at(0).getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(1, variableMap1.at("y").getDouble());
    EXPECT_DOUBLE_EQ(-4, monomials.at(1).getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomials.at(1).getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap2.empty());
}

TEST(TermsSimplificatorTest, VariableMultiplyConstantPatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("y"), Term("*"), Term(4)});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(4, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
}

TEST(TermsSimplificatorTest, VariableDivideConstantPatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("y"), Term("/"), Term(4)});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(0.25, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
}

TEST(TermsSimplificatorTest, VariableRaiseToPowerConstantPatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("y"), Term("^"), Term(4)});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(1, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(4, variableMap.at("y").getDouble());
}

TEST(TermsSimplificatorTest, VariableAddVariablePatternWithSameVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("i"), Term("+"), Term("i")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(2, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("i").getDouble());
}

TEST(TermsSimplificatorTest, VariableSubtractVariablePatternWithSameVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("i"), Term("-"), Term("i")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(0, termsToVerify.at(0).getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermsSimplificatorTest, VariableMultiplyVariablePatternWithSameVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("i"), Term("*"), Term("i")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(1, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(2, variableMap.at("i").getDouble());
}

TEST(TermsSimplificatorTest, VariableDivideVariablePatternWithSameVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("i"), Term("/"), Term("i")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(1, termsToVerify.at(0).getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermsSimplificatorTest, VariableRaiseToPowerVariablePatternWithSameVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("i"), Term("^"), Term("i")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::ExpressionWithSingleTerm, termsToVerify.at(0).getTermType());
    WrappedTerms::BaseTermPointers const& baseTermPointersToVerify(termsToVerify.at(0).getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Variable, term1.getTermType());
    EXPECT_EQ("i", term1.getVariableConstReference().getVariableName());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ("i", term3.getVariableConstReference().getVariableName());
}

TEST(TermsSimplificatorTest, MonomialAddVariablePatternWithSameMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(7, {{"x", 1}}), Term("+"), Term("x")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(8, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
}

TEST(TermsSimplificatorTest, MonomialSubtractVariablePatternWithSameMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(7, {{"x", 1}}), Term("-"), Term("x")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(6, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
}

TEST(TermsSimplificatorTest, MonomialMultiplyVariablePatternWithSameMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(7, {{"x", 1}}), Term("*"), Term("x")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(2, variableMap.at("x").getDouble());
}

TEST(TermsSimplificatorTest, MonomialDivideVariablePatternWithSameMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(7, {{"x", 1}}), Term("/"), Term("x")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(7, termsToVerify.at(0).getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermsSimplificatorTest, MonomialRaiseToPowerVariablePatternWithSameMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(7, {{"x", 1}}), Term("^"), Term("x")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::ExpressionWithSingleTerm, termsToVerify.at(0).getTermType());
    WrappedTerms::BaseTermPointers const& baseTermPointersToVerify(termsToVerify.at(0).getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Monomial, term1.getTermType());
    Monomial const& monomial(term1.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ("x", term3.getVariableConstReference().getVariableName());
}

TEST(TermsSimplificatorTest, MonomialAddVariablePatternWithDifferentMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(7, {{"y", 1}}), Term("+"), Term("x")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Polynomial, termsToVerify.at(0).getTermType());
    Monomials const& monomials(termsToVerify.at(0).getPolynomialConstReference().getMonomialsConstReference());
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

TEST(TermsSimplificatorTest, MonomialSubtractVariablePatternWithDifferentMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(7, {{"y", 1}}), Term("-"), Term("x")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Polynomial, termsToVerify.at(0).getTermType());
    Monomials const& monomials(termsToVerify.at(0).getPolynomialConstReference().getMonomialsConstReference());
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

TEST(TermsSimplificatorTest, MonomialMultiplyVariablePatternWithDifferentMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(7, {{"y", 1}}), Term("*"), Term("x")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
}

TEST(TermsSimplificatorTest, MonomialDivideVariablePatternWithDifferentMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(7, {{"y", 1}}), Term("/"), Term("x")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
    EXPECT_DOUBLE_EQ(-1, variableMap.at("x").getDouble());
}

TEST(TermsSimplificatorTest, MonomialRaiseToPowerVariablePatternWithDifferentMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(7, {{"y", 1}}), Term("^"), Term("x")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::ExpressionWithSingleTerm, termsToVerify.at(0).getTermType());
    WrappedTerms::BaseTermPointers const& baseTermPointersToVerify(termsToVerify.at(0).getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Monomial, term1.getTermType());
    Monomial const& monomial(term1.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ("x", term3.getVariableConstReference().getVariableName());
}

TEST(TermsSimplificatorTest, ConstantAddMonomialPatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term(4), Term("+"), Monomial(6, {{"x", 2}, {"y", 4}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Polynomial, termsToVerify.at(0).getTermType());
    Monomials const& monomials(termsToVerify.at(0).getPolynomialConstReference().getMonomialsConstReference());
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

TEST(TermsSimplificatorTest, ConstantSubtractMonomialPatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term(4), Term("-"), Monomial(6, {{"x", 2}, {"y", 4}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Polynomial, termsToVerify.at(0).getTermType());
    Monomials const& monomials(termsToVerify.at(0).getPolynomialConstReference().getMonomialsConstReference());
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

TEST(TermsSimplificatorTest, ConstantMultiplyMonomialPatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term(4), Term("*"), Monomial(6, {{"x", 2}, {"y", 4}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(24, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(2, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(4, variableMap.at("y").getDouble());
}

TEST(TermsSimplificatorTest, ConstantDivideMonomialPatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term(8), Term("/"), Monomial(4, {{"x", 2}, {"y", 4}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(2, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(-2, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(-4, variableMap.at("y").getDouble());
}

TEST(TermsSimplificatorTest, ConstantRaiseToPowerMonomialPatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term(4), Term("^"), Monomial(6, {{"x", 2}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::ExpressionWithSingleTerm, termsToVerify.at(0).getTermType());
    WrappedTerms::BaseTermPointers const& baseTermPointersToVerify(termsToVerify.at(0).getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Constant, term1.getTermType());
    EXPECT_DOUBLE_EQ(4, term1.getConstantConstReference().getNumberConstReference().getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Monomial, term3.getTermType());
    Monomial const& monomial(term3.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(6, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(2, variableMap.at("x").getDouble());
}

TEST(TermsSimplificatorTest, VariableAddMonomialPatternWithSameMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("x"), Term("+"),  Monomial(7, {{"x", 1}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(8, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
}

TEST(TermsSimplificatorTest, VariableSubtractMonomialPatternWithSameMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("x"), Term("-"),  Monomial(7, {{"x", 1}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(-6, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
}

TEST(TermsSimplificatorTest, VariableMultiplyMonomialPatternWithSameMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("x"), Term("*"),  Monomial(7, {{"x", 1}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(2, variableMap.at("x").getDouble());
}

TEST(TermsSimplificatorTest, VariableDivideMonomialPatternWithSameMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("x"), Term("/"),  Monomial(4, {{"x", 1}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(0.25, termsToVerify.at(0).getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermsSimplificatorTest, VariableRaiseToPowerMonomialPatternWithSameMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("x"), Term("^"),  Monomial(7, {{"x", 1}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::ExpressionWithSingleTerm, termsToVerify.at(0).getTermType());
    WrappedTerms::BaseTermPointers const& baseTermPointersToVerify(termsToVerify.at(0).getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Variable, term1.getTermType());
    EXPECT_EQ("x", term1.getVariableConstReference().getVariableName());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Monomial, term3.getTermType());
    Monomial const& monomial(term3.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
}

TEST(TermsSimplificatorTest, VariableAddMonomialPatternWithDifferentMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("x"), Term("+"), Monomial(7, {{"y", 1}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Polynomial, termsToVerify.at(0).getTermType());
    Monomials const& monomials(termsToVerify.at(0).getPolynomialConstReference().getMonomialsConstReference());
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

TEST(TermsSimplificatorTest, VariableSubtractMonomialPatternWithDifferentMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("x"), Term("-"), Monomial(7, {{"y", 1}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Polynomial, termsToVerify.at(0).getTermType());
    Monomials const& monomials(termsToVerify.at(0).getPolynomialConstReference().getMonomialsConstReference());
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

TEST(TermsSimplificatorTest, VariableMultiplyMonomialPatternWithDifferentMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("x"), Term("*"), Monomial(7, {{"y", 1}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
}

TEST(TermsSimplificatorTest, VariableDivideMonomialPatternWithDifferentMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("x"), Term("/"), Monomial(4, {{"y", 1}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(0.25, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(-1, variableMap.at("y").getDouble());
}

TEST(TermsSimplificatorTest, VariableRaiseToPowerMonomialPatternWithDifferentMonomialVariableCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("x"), Term("^"), Monomial(7, {{"y", 1}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::ExpressionWithSingleTerm, termsToVerify.at(0).getTermType());
    WrappedTerms::BaseTermPointers const& baseTermPointersToVerify(termsToVerify.at(0).getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Variable, term1.getTermType());
    EXPECT_EQ("x", term1.getVariableConstReference().getVariableName());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Monomial, term3.getTermType());
    Monomial const& monomial(term3.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(7, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
}

TEST(TermsSimplificatorTest, MonomialAddMonomialPatternWithSameMonomialCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(8, {{"x", 2}}), Term("+"), Monomial(4, {{"x", 2}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(12, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(2, variableMap.at("x").getDouble());
}

TEST(TermsSimplificatorTest, MonomialSubtractMonomialPatternWithSameMonomialCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(8, {{"x", 2}}), Term("-"), Monomial(4, {{"x", 2}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(4, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(2, variableMap.at("x").getDouble());
}

TEST(TermsSimplificatorTest, MonomialMultiplyMonomialPatternWithSameMonomialCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(8, {{"x", 2}}), Term("*"), Monomial(4, {{"x", 2}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(32, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(4, variableMap.at("x").getDouble());
}

TEST(TermsSimplificatorTest, MonomialDivideMonomialPatternWithSameMonomialCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(8, {{"x", 2}}), Term("/"), Monomial(4, {{"x", 2}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(2, termsToVerify.at(0).getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermsSimplificatorTest, MonomialRaiseToPowerMonomialPatternWithSameMonomialCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(8, {{"x", 2}}), Term("^"), Monomial(4, {{"x", 2}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::ExpressionWithSingleTerm, termsToVerify.at(0).getTermType());
    WrappedTerms::BaseTermPointers const& baseTermPointersToVerify(termsToVerify.at(0).getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Monomial, term1.getTermType());
    Monomial const& monomial1(term1.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(8, monomial1.getConstantConstReference().getDouble());
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

TEST(TermsSimplificatorTest, MonomialAddMonomialPatternWithDifferentMonomialCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(8, {{"x", 2}}), Term("+"), Monomial(4, {{"x", 1}, {"y", 1}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Polynomial, termsToVerify.at(0).getTermType());
    Monomials const& monomials(termsToVerify.at(0).getPolynomialConstReference().getMonomialsConstReference());
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

TEST(TermsSimplificatorTest, MonomialSubtractMonomialPatternWithDifferentMonomialCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(8, {{"x", 2}}), Term("-"), Monomial(4, {{"x", 1}, {"y", 1}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Polynomial, termsToVerify.at(0).getTermType());
    Monomials const& monomials(termsToVerify.at(0).getPolynomialConstReference().getMonomialsConstReference());
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

TEST(TermsSimplificatorTest, MonomialMultiplyMonomialPatternWithDifferentMonomialCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(8, {{"x", 2}}), Term("*"), Monomial(4, {{"x", 1}, {"y", 1}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(32, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(3, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(1, variableMap.at("y").getDouble());
}

TEST(TermsSimplificatorTest, MonomialDivideMonomialPatternWithDifferentMonomialCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(8, {{"x", 2}}), Term("/"), Monomial(4, {{"x", 1}, {"y", 1}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(2, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap.size());
    EXPECT_DOUBLE_EQ(1, variableMap.at("x").getDouble());
    EXPECT_DOUBLE_EQ(-1, variableMap.at("y").getDouble());
}

TEST(TermsSimplificatorTest, MonomialRaiseToPowerMonomialPatternWithDifferentMonomialCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Monomial(8, {{"x", 2}}), Term("^"), Monomial(4, {{"x", 1}, {"y", 1}})});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    ASSERT_EQ(TermType::ExpressionWithSingleTerm, termsToVerify.at(0).getTermType());
    WrappedTerms::BaseTermPointers const& baseTermPointersToVerify(termsToVerify.at(0).getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Monomial, term1.getTermType());
    Monomial const& monomial1(term1.getMonomialConstReference());
    EXPECT_DOUBLE_EQ(8, monomial1.getConstantConstReference().getDouble());
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

}

}
