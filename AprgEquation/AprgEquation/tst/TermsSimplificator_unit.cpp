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
    EXPECT_EQ(TermType::Constant, termsToVerify.at(0).getTermType());
    EXPECT_DOUBLE_EQ(7, termsToVerify.at(0).getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermsSimplificatorTest, ConstantAddVariablePatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term(5), Term("+"), Term("x")});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(TermType::Polynomial, termsToVerify.at(0).getTermType());
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
    EXPECT_EQ(TermType::Polynomial, termsToVerify.at(0).getTermType());
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
    EXPECT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
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
    EXPECT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
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
    EXPECT_EQ(TermType::ExpressionWithSingleTerm, termsToVerify.at(0).getTermType());
    WrappedTerms::BaseTermPointers const& baseTermPointersToVerify(termsToVerify.at(0).getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    EXPECT_EQ(TermType::Constant, term1.getTermType());
    EXPECT_DOUBLE_EQ(5, term1.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("^", term2.getOperatorConstReference().getOperatorString());
    EXPECT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ("x", term3.getVariableConstReference().getVariableName());
}

TEST(TermsSimplificatorTest, VariableAddConstantPatternCanBeSimplified)
{
    TermsSimplificator simplificator(Terms{Term("y"), Term("+"), Term(4)});

    simplificator.simplify();

    Terms termsToVerify(simplificator.getTermsConstReference());
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(TermType::Polynomial, termsToVerify.at(0).getTermType());
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
    EXPECT_EQ(TermType::Polynomial, termsToVerify.at(0).getTermType());
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
    EXPECT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
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
    EXPECT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
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
    EXPECT_EQ(TermType::Monomial, termsToVerify.at(0).getTermType());
    Monomial const& monomial(termsToVerify.at(0).getMonomialConstReference());
    EXPECT_DOUBLE_EQ(1, monomial.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap(monomial.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap.size());
    EXPECT_DOUBLE_EQ(4, variableMap.at("y").getDouble());
}

}

}
