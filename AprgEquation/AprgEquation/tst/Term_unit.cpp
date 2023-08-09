#include <Term.hpp>

#include <Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(TermTest, TermsAsConstantsWorkAsExpected)
{
    Term constant1(4353);
    Term constant2(-3248);
    Term constant3(AlbaNumber(3498, 3459));
    Term constant4(-34.8767);

    ASSERT_EQ(TermType::Constant, constant1.getTermType());
    EXPECT_DOUBLE_EQ(4353, constant1.getConstantReference().getNumberConstReference().getDouble());

    ASSERT_EQ(TermType::Constant, constant2.getTermType());
    EXPECT_DOUBLE_EQ(-3248, constant2.getConstantReference().getNumberConstReference().getDouble());

    ASSERT_EQ(TermType::Constant, constant3.getTermType());
    EXPECT_DOUBLE_EQ(1.0112749349522983, constant3.getConstantReference().getNumberConstReference().getDouble());

    ASSERT_EQ(TermType::Constant, constant4.getTermType());
    EXPECT_DOUBLE_EQ(-34.8767, constant4.getConstantReference().getNumberConstReference().getDouble());
}

TEST(TermTest, TermsAsVariablesWorkAsExpected)
{
    Term variable1("");
    Term variable2("x");
    Term variable3("power");

    ASSERT_EQ(TermType::Variable, variable1.getTermType());
    EXPECT_EQ("", variable1.getVariableReference().getVariableName());

    ASSERT_EQ(TermType::Variable, variable2.getTermType());
    EXPECT_EQ("x", variable2.getVariableReference().getVariableName());

    ASSERT_EQ(TermType::Variable, variable3.getTermType());
    EXPECT_EQ("power", variable3.getVariableReference().getVariableName());
}

TEST(TermTest, TermsAsOperatorsWorkAsExpected)
{
    Term variable1("+");
    Term variable2("-");
    Term variable3("*");
    Term variable4("/");

    ASSERT_EQ(TermType::Operator, variable1.getTermType());
    EXPECT_EQ("+", variable1.getOperatorReference().getOperatorString());

    ASSERT_EQ(TermType::Operator, variable2.getTermType());
    EXPECT_EQ("-", variable2.getOperatorReference().getOperatorString());

    ASSERT_EQ(TermType::Operator, variable3.getTermType());
    EXPECT_EQ("*", variable3.getOperatorReference().getOperatorString());

    ASSERT_EQ(TermType::Operator, variable4.getTermType());
    EXPECT_EQ("/", variable4.getOperatorReference().getOperatorString());
}

TEST(TermTest, TermsAsMonomialsWorkAsExpected)
{
    Term monomial1(Monomial(3, {}));
    Term monomial2(Monomial(1.5, {{"distance", 3.75}}));
    Term monomial3(Monomial(-1.5, {{"distance", -3.75}, {"power", 4.5}}));

    ASSERT_EQ(TermType::Monomial, monomial1.getTermType());
    EXPECT_DOUBLE_EQ(3, monomial1.getMonomialReference().getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomial1.getMonomialReference().getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());

    ASSERT_EQ(TermType::Monomial, monomial2.getTermType());
    EXPECT_DOUBLE_EQ(1.5, monomial2.getMonomialReference().getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial2.getMonomialReference().getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    Monomial::VariableExponentPair const& variable2(*variableMap2.begin());
    EXPECT_EQ("distance", variable2.first);
    EXPECT_DOUBLE_EQ(3.75, variable2.second.getDouble());

    ASSERT_EQ(TermType::Monomial, monomial3.getTermType());
    EXPECT_DOUBLE_EQ(-1.5, monomial3.getMonomialReference().getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap3(monomial3.getMonomialReference().getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap3.size());
    Monomial::VariablesToExponentsMap::const_iterator variableMap3It = variableMap3.cbegin();
    Monomial::VariableExponentPair const& variable3_1(*variableMap3It);
    EXPECT_EQ("distance", variable3_1.first);
    EXPECT_DOUBLE_EQ(-3.75, variable3_1.second.getDouble());
    variableMap3It++;
    Monomial::VariableExponentPair const& variable3_2(*variableMap3It);
    EXPECT_EQ("power", variable3_2.first);
    EXPECT_DOUBLE_EQ(4.5, variable3_2.second.getDouble());
}

TEST(TermTest, TermsAsPolynomialsWorkAsExpected)
{
    Term polynomial1(Polynomial{});
    Term polynomial2(Polynomial({Monomial(3, {})}));
    Term polynomial3(Polynomial({Monomial(3, {}), Monomial(-1.5, {{"distance", -3.75}, {"power", 4.5}})}));

    //For polynomial1
    ASSERT_EQ(TermType::Polynomial, polynomial1.getTermType());
    Monomials const& monomials1(polynomial1.getPolynomialReference().getMonomialsConstReference());
    ASSERT_TRUE(monomials1.empty());

    //For polynomial2
    ASSERT_EQ(TermType::Polynomial, polynomial2.getTermType());
    Monomials const& monomials2(polynomial2.getPolynomialReference().getMonomialsConstReference());
    ASSERT_EQ(1u, monomials2.size());
    Monomial const& monomial2(monomials2.front());
    EXPECT_DOUBLE_EQ(3, monomial2.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial2.getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap2.empty());

    //For polynomial3
    ASSERT_EQ(TermType::Polynomial, polynomial3.getTermType());
    Monomials const& monomials3(polynomial3.getPolynomialReference().getMonomialsConstReference());
    ASSERT_EQ(2u, monomials3.size());

    Monomial const& monomial3_1(monomials3.front());
    EXPECT_DOUBLE_EQ(3, monomial3_1.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap3_1(monomial3_1.getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap3_1.empty());

    Monomial const& monomial3_2(monomials3.back());
    EXPECT_DOUBLE_EQ(-1.5, monomial3_2.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap3_2(monomial3_2.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap3_2.size());
    Monomial::VariablesToExponentsMap::const_iterator variableMap3It = variableMap3_2.cbegin();
    Monomial::VariableExponentPair const& variable3_1(*variableMap3It);
    EXPECT_EQ("distance", variable3_1.first);
    EXPECT_DOUBLE_EQ(-3.75, variable3_1.second.getDouble());
    variableMap3It++;
    Monomial::VariableExponentPair const& variable3_2(*variableMap3It);
    EXPECT_EQ("power", variable3_2.first);
    EXPECT_DOUBLE_EQ(4.5, variable3_2.second.getDouble());
}

TEST(TermTest, TermsAsExpressionsWorkAsExpected)
{
    Term expression1(Expression{});
    Term expression2(createExpression(Terms{Term(5), Term("+"), Term("interest")}));

    //For expression1
    ASSERT_EQ(TermType::ExpressionWithSingleTerm, expression1.getTermType());
    ASSERT_TRUE(expression1.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference().empty());

    //For expression2
    ASSERT_EQ(TermType::ExpressionWithMutipleTerms, expression2.getTermType());
    BaseTermSharedPointers const& baseTermPointersToVerify(expression2.getExpressionConstReference().getWrappedTermsConstReference().getBaseTermPointersConstReference());
    ASSERT_EQ(3u, baseTermPointersToVerify.size());
    Term term1(*dynamic_cast<Term*>(baseTermPointersToVerify.at(0).get()));
    Term term2(*dynamic_cast<Term*>(baseTermPointersToVerify.at(1).get()));
    Term term3(*dynamic_cast<Term*>(baseTermPointersToVerify.at(2).get()));
    ASSERT_EQ(TermType::Constant, term1.getTermType());
    EXPECT_DOUBLE_EQ(5, term1.getConstantConstReference().getNumberConstReference().getDouble());
    ASSERT_EQ(TermType::Operator, term2.getTermType());
    EXPECT_EQ("+", term2.getOperatorConstReference().getOperatorString());
    ASSERT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ("interest", term3.getVariableConstReference().getVariableName());
}

}

}
