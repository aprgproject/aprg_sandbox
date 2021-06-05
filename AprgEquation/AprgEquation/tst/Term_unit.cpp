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
    EXPECT_DOUBLE_EQ(4353, constant1.  getConstantConstReference().getNumberConstReference().getDouble());

    ASSERT_EQ(TermType::Constant, constant2.getTermType());
    EXPECT_DOUBLE_EQ(-3248, constant2.  getConstantConstReference().getNumberConstReference().getDouble());

    ASSERT_EQ(TermType::Constant, constant3.getTermType());
    EXPECT_DOUBLE_EQ(1.0112749349522983, constant3.  getConstantConstReference().getNumberConstReference().getDouble());

    ASSERT_EQ(TermType::Constant, constant4.getTermType());
    EXPECT_DOUBLE_EQ(-34.8767, constant4.  getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(TermTest, TermsAsVariablesWorkAsExpected)
{
    Term variable1("");
    Term variable2("x");
    Term variable3("power");

    ASSERT_EQ(TermType::Variable, variable1.getTermType());
    EXPECT_EQ("", variable1.getVariableConstReference().getVariableName());

    ASSERT_EQ(TermType::Variable, variable2.getTermType());
    EXPECT_EQ("x", variable2.getVariableConstReference().getVariableName());

    ASSERT_EQ(TermType::Variable, variable3.getTermType());
    EXPECT_EQ("power", variable3.getVariableConstReference().getVariableName());
}

TEST(TermTest, TermsAsOperatorsWorkAsExpected)
{
    Term variable1("+");
    Term variable2("-");
    Term variable3("*");
    Term variable4("/");

    ASSERT_EQ(TermType::Operator, variable1.getTermType());
    EXPECT_EQ("+", variable1.getOperatorConstReference().getOperatorString());

    ASSERT_EQ(TermType::Operator, variable2.getTermType());
    EXPECT_EQ("-", variable2.getOperatorConstReference().getOperatorString());

    ASSERT_EQ(TermType::Operator, variable3.getTermType());
    EXPECT_EQ("*", variable3.getOperatorConstReference().getOperatorString());

    ASSERT_EQ(TermType::Operator, variable4.getTermType());
    EXPECT_EQ("/", variable4.getOperatorConstReference().getOperatorString());
}

TEST(TermTest, TermsAsMonomialsWorkAsExpected)
{
    Term monomial1(Monomial(3, {}));
    Term monomial2(Monomial(1.5, {{"distance", 3.75}}));
    Term monomial3(Monomial(-1.5, {{"distance", -3.75}, {"power", 4.5}}));

    ASSERT_EQ(TermType::Monomial, monomial1.getTermType());
    EXPECT_DOUBLE_EQ(3, monomial1.getMonomialConstReference().getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomial1.getMonomialConstReference().getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());

    ASSERT_EQ(TermType::Monomial, monomial2.getTermType());
    EXPECT_DOUBLE_EQ(1.5, monomial2.getMonomialConstReference().getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial2.getMonomialConstReference().getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap2.size());
    Monomial::VariableExponentPair const& variable2(*variableMap2.begin());
    EXPECT_EQ("distance", variable2.first);
    EXPECT_DOUBLE_EQ(3.75, variable2.second.getDouble());

    ASSERT_EQ(TermType::Monomial, monomial3.getTermType());
    EXPECT_DOUBLE_EQ(-1.5, monomial3.getMonomialConstReference().getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap3(monomial3.getMonomialConstReference().getVariablesToExponentsMapConstReference());
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
    Monomials const& monomials1(polynomial1.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_TRUE(monomials1.empty());

    //For polynomial2
    ASSERT_EQ(TermType::Polynomial, polynomial2.getTermType());
    Monomials const& monomials2(polynomial2.getPolynomialConstReference().getMonomialsConstReference());
    ASSERT_EQ(1u, monomials2.size());
    Monomial const& monomial2(monomials2.front());
    EXPECT_DOUBLE_EQ(3, monomial2.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial2.getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap2.empty());

    //For polynomial3
    ASSERT_EQ(TermType::Polynomial, polynomial3.getTermType());
    Monomials const& monomials3(polynomial3.getPolynomialConstReference().getMonomialsConstReference());
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
    Term expressionTerm1(Expression{});
    Term expressionTerm2(createExpression(Terms{Term(5), Term("+"), Term("interest")}));

    //For expression1
    ASSERT_EQ(TermType::Expression, expressionTerm1.getTermType());
    Expression const& expression1(expressionTerm1.getExpressionConstReference());
    EXPECT_EQ(OperatorLevel::Unknown, expression1.getCommonOperatorLevel());
    TermsWithPriorityAndAssociation::TermsWithDetails const& termsToVerify1(expression1.getTerms().getTermsWithDetails());
    ASSERT_TRUE(termsToVerify1.empty());

    //For expression2
    ASSERT_EQ(TermType::Expression, expressionTerm2.getTermType());
    Expression const& expression2(expressionTerm2.getExpressionConstReference());
    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, expression2.getCommonOperatorLevel());
    TermsWithPriorityAndAssociation::TermsWithDetails const& termsToVerify2(expression2.getTerms().getTermsWithDetails());
    ASSERT_EQ(2u, termsToVerify2.size());
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Positive, termsToVerify2.at(0).association);
    Term const& termToVerify1 = *dynamic_cast<Term const*const>(termsToVerify2.at(0).baseTermSharedPointer.get());
    EXPECT_EQ(Term(5), termToVerify1);
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Positive, termsToVerify2.at(1).association);
    Term const& termToVerify2 = *dynamic_cast<Term const*const>(termsToVerify2.at(1).baseTermSharedPointer.get());
    EXPECT_EQ(Term("interest"), termToVerify2);
}

TEST(TermTest, EqualityOperatorWorks)
{
    Term term1;
    Term term2(Constant(5));
    Term term3(Constant(10));
    Term term4(Variable("length"));
    Term term5(Constant(5));

    EXPECT_TRUE(term1==term1);
    EXPECT_FALSE(term1==term2);
    EXPECT_TRUE(term2==term2);
    EXPECT_FALSE(term2==term3);
    EXPECT_FALSE(term2==term4);
    EXPECT_TRUE(term2==term5);
}

TEST(TermTest, IsConstantWorks)
{
    Term term1;
    Term term2(Constant(1));
    Term term3(Variable("length"));
    Term term4(Operator("+"));
    Term term5(Monomial(1, {}));
    Term term6(Polynomial{});
    Term term7(Expression{});

    EXPECT_FALSE(term1.isConstant());
    EXPECT_TRUE(term2.isConstant());
    EXPECT_FALSE(term3.isConstant());
    EXPECT_FALSE(term4.isConstant());
    EXPECT_FALSE(term5.isConstant());
    EXPECT_FALSE(term6.isConstant());
    EXPECT_FALSE(term7.isConstant());
}

TEST(TermTest, IsVariableWorks)
{
    Term term1;
    Term term2(Constant(1));
    Term term3(Variable("length"));
    Term term4(Operator("+"));
    Term term5(Monomial(1, {}));
    Term term6(Polynomial{});
    Term term7(Expression{});

    EXPECT_FALSE(term1.isVariable());
    EXPECT_FALSE(term2.isVariable());
    EXPECT_TRUE(term3.isVariable());
    EXPECT_FALSE(term4.isVariable());
    EXPECT_FALSE(term5.isVariable());
    EXPECT_FALSE(term6.isVariable());
    EXPECT_FALSE(term7.isVariable());
}

TEST(TermTest, IsOperatorWorks)
{
    Term term1;
    Term term2(Constant(1));
    Term term3(Variable("length"));
    Term term4(Operator("+"));
    Term term5(Monomial(1, {}));
    Term term6(Polynomial{});
    Term term7(Expression{});

    EXPECT_FALSE(term1.isOperator());
    EXPECT_FALSE(term2.isOperator());
    EXPECT_FALSE(term3.isOperator());
    EXPECT_TRUE(term4.isOperator());
    EXPECT_FALSE(term5.isOperator());
    EXPECT_FALSE(term6.isOperator());
    EXPECT_FALSE(term7.isOperator());
}

TEST(TermTest, IsMonomialWorks)
{
    Term term1;
    Term term2(Constant(1));
    Term term3(Variable("length"));
    Term term4(Operator("+"));
    Term term5(Monomial(1, {}));
    Term term6(Polynomial{});
    Term term7(Expression{});

    EXPECT_FALSE(term1.isMonomial());
    EXPECT_FALSE(term2.isMonomial());
    EXPECT_FALSE(term3.isMonomial());
    EXPECT_FALSE(term4.isMonomial());
    EXPECT_TRUE(term5.isMonomial());
    EXPECT_FALSE(term6.isMonomial());
    EXPECT_FALSE(term7.isMonomial());
}

TEST(TermTest, IsPolynomialWorks)
{
    Term term1;
    Term term2(Constant(1));
    Term term3(Variable("length"));
    Term term4(Operator("+"));
    Term term5(Monomial(1, {}));
    Term term6(Polynomial{});
    Term term7(Expression{});

    EXPECT_FALSE(term1.isPolynomial());
    EXPECT_FALSE(term2.isPolynomial());
    EXPECT_FALSE(term3.isPolynomial());
    EXPECT_FALSE(term4.isPolynomial());
    EXPECT_FALSE(term5.isPolynomial());
    EXPECT_TRUE(term6.isPolynomial());
    EXPECT_FALSE(term7.isPolynomial());
}

TEST(TermTest, IsExpressionWorks)
{
    Term term1;
    Term term2(Constant(1));
    Term term3(Variable("length"));
    Term term4(Operator("+"));
    Term term5(Monomial(1, {}));
    Term term6(Polynomial{});
    Term term7(Expression{});

    EXPECT_FALSE(term1.isExpression());
    EXPECT_FALSE(term2.isExpression());
    EXPECT_FALSE(term3.isExpression());
    EXPECT_FALSE(term4.isExpression());
    EXPECT_FALSE(term5.isExpression());
    EXPECT_FALSE(term6.isExpression());
    EXPECT_TRUE(term7.isExpression());
}

TEST(TermTest, IsValueTermWorks)
{
    Term term1;
    Term term2(Constant(1));
    Term term3(Variable("length"));
    Term term4(Operator("+"));
    Term term5(Monomial(1, {}));
    Term term6(Polynomial{});
    Term term7(Expression{});

    EXPECT_FALSE(term1.isValueTerm());
    EXPECT_TRUE(term2.isValueTerm());
    EXPECT_TRUE(term3.isValueTerm());
    EXPECT_FALSE(term4.isValueTerm());
    EXPECT_TRUE(term5.isValueTerm());
    EXPECT_TRUE(term6.isValueTerm());
    EXPECT_TRUE(term7.isValueTerm());
}

TEST(TermTest, IsValueTermButNotAnExpressionWorks)
{
    Term term1;
    Term term2(Constant(1));
    Term term3(Variable("length"));
    Term term4(Operator("+"));
    Term term5(Monomial(1, {}));
    Term term6(Polynomial{});
    Term term7(Expression{});

    EXPECT_FALSE(term1.isValueTermButNotAnExpression());
    EXPECT_TRUE(term2.isValueTermButNotAnExpression());
    EXPECT_TRUE(term3.isValueTermButNotAnExpression());
    EXPECT_FALSE(term4.isValueTermButNotAnExpression());
    EXPECT_TRUE(term5.isValueTermButNotAnExpression());
    EXPECT_TRUE(term6.isValueTermButNotAnExpression());
    EXPECT_FALSE(term7.isValueTermButNotAnExpression());
}

TEST(TermTest, IsTheValueZeroWorks)
{
    Term term1;
    Term term2(Constant(1));
    Term term3(Variable("length"));
    Term term4(Operator("+"));
    Term term5(Monomial(1, {}));
    Term term6(Polynomial{});
    Term term7(Expression{});
    Term term8(Constant(0));

    EXPECT_FALSE(term1.isTheValueZero());
    EXPECT_FALSE(term2.isTheValueZero());
    EXPECT_FALSE(term3.isTheValueZero());
    EXPECT_FALSE(term4.isTheValueZero());
    EXPECT_FALSE(term5.isTheValueZero());
    EXPECT_FALSE(term6.isTheValueZero());
    EXPECT_FALSE(term7.isTheValueZero());
    EXPECT_TRUE(term8.isTheValueZero());
}

TEST(TermTest, IsTheValueOneWorks)
{
    Term term1;
    Term term2(Constant(0));
    Term term3(Variable("length"));
    Term term4(Operator("+"));
    Term term5(Monomial(1, {}));
    Term term6(Polynomial{});
    Term term7(Expression{});
    Term term8(Constant(1));

    EXPECT_FALSE(term1.isTheValueOne());
    EXPECT_FALSE(term2.isTheValueOne());
    EXPECT_FALSE(term3.isTheValueOne());
    EXPECT_FALSE(term4.isTheValueOne());
    EXPECT_FALSE(term5.isTheValueOne());
    EXPECT_FALSE(term6.isTheValueOne());
    EXPECT_FALSE(term7.isTheValueOne());
    EXPECT_TRUE(term8.isTheValueOne());
}

TEST(TermTest, GetTermTypeWorks)
{
    Term term1;
    Term term2(Constant(0));
    Term term3(Variable("length"));
    Term term4(Operator("+"));
    Term term5(Monomial(1, {}));
    Term term6(Polynomial{});
    Term term7(Expression{});

    EXPECT_EQ(TermType::Empty, term1.getTermType());
    EXPECT_EQ(TermType::Constant, term2.getTermType());
    EXPECT_EQ(TermType::Variable, term3.getTermType());
    EXPECT_EQ(TermType::Operator, term4.getTermType());
    EXPECT_EQ(TermType::Monomial, term5.getTermType());
    EXPECT_EQ(TermType::Polynomial, term6.getTermType());
    EXPECT_EQ(TermType::Expression, term7.getTermType());
}

TEST(TermTest, GetDisplayableStringWorks)
{
    Term term1;
    Term term2(Constant(0));
    Term term3(Variable("length"));
    Term term4(Operator("+"));
    Term term5(Monomial(-1.5, {{"distance", -3.75}, {"power", 4.5}}));
    Term term6(Polynomial({Monomial(3, {}), Monomial(-1.5, {{"distance", -3.75}, {"power", 4.5}})}));
    Term term7(createExpression(Terms{Term(5), Term("+"), Term("interest")}));

    EXPECT_TRUE(term1.getDisplayableString().empty());
    EXPECT_EQ("0", term2.getDisplayableString());
    EXPECT_EQ("length", term3.getDisplayableString());
    EXPECT_EQ("+", term4.getDisplayableString());
    EXPECT_EQ("-1.5|distance^-3.75||power^4.5|", term5.getDisplayableString());
    EXPECT_EQ("(3 + -1.5|distance^-3.75||power^4.5|)", term6.getDisplayableString());
    EXPECT_EQ("5+interest", term7.getDisplayableString());
}

}

}
