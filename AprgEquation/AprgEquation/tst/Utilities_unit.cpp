#include <Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(UtilitiesTest, IsOperatorWorksCorrectly)
{
    EXPECT_FALSE(isOperator(""));
    EXPECT_TRUE(isOperator("+"));
    EXPECT_TRUE(isOperator("-"));
    EXPECT_TRUE(isOperator("*"));
    EXPECT_TRUE(isOperator("/"));
    EXPECT_TRUE(isOperator("^"));
    EXPECT_FALSE(isOperator("add"));
}

TEST(UtilitiesTest, CanBeAddedOrSubtractedForBothMonomialsWorksCorrectly)
{
    Monomial monomial1;
    Monomial monomial2(-54, {{"x", 6}, {"y", -1.25}});
    Monomial monomial3(100, {{"x", 6}, {"y", -1.25}});
    Monomial monomial4(100, {{"x", 5}, {"y", -1}});
    Monomial monomial5(645, {{"i", 20}, {"y", 30}});

    EXPECT_TRUE(canBeAddedOrSubtracted(monomial1, monomial1));
    EXPECT_TRUE(canBeAddedOrSubtracted(monomial2, monomial2));
    EXPECT_TRUE(canBeAddedOrSubtracted(monomial3, monomial3));
    EXPECT_TRUE(canBeAddedOrSubtracted(monomial4, monomial4));
    EXPECT_TRUE(canBeAddedOrSubtracted(monomial5, monomial5));
    EXPECT_FALSE(canBeAddedOrSubtracted(monomial1, monomial2));
    EXPECT_TRUE(canBeAddedOrSubtracted(monomial2, monomial3));
    EXPECT_FALSE(canBeAddedOrSubtracted(monomial2, monomial4));
    EXPECT_FALSE(canBeAddedOrSubtracted(monomial2, monomial5));
}

TEST(UtilitiesTest, CanBeAddedOrSubtractedForMonomialAndVariableWorksCorrectly)
{
    Monomial monomial1;
    Monomial monomial2(12, {{"x", 1}});
    Monomial monomial3(34, {{"x", 1.25}});
    Monomial monomial4(56, {{"x", 1}, {"y", 1}});
    Variable variable("x");

    EXPECT_FALSE(canBeAddedOrSubtracted(monomial1, variable));
    EXPECT_TRUE(canBeAddedOrSubtracted(monomial2, variable));
    EXPECT_FALSE(canBeAddedOrSubtracted(monomial3, variable));
    EXPECT_FALSE(canBeAddedOrSubtracted(monomial4, variable));
}

TEST(UtilitiesTest, ConvertPolynomialToSimplestTermWorksCorrectly)
{
    Term termToVerify1(convertPolynomialToSimplestTerm(Polynomial{}));
    Term termToVerify2(convertPolynomialToSimplestTerm(Polynomial{Monomial(6, {})}));
    Term termToVerify3(convertPolynomialToSimplestTerm(Polynomial{Monomial(6, {{"x", 1}}), Monomial(-6, {{"x", 1}})}));

    ASSERT_EQ(TermType::Constant, termToVerify1.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify1.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(6, termToVerify2.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Constant, termToVerify3.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify3.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(UtilitiesTest, CreateSimplifiedPolynomialWorksCorrectly)
{
    Polynomial polynomial1(createSimplifiedPolynomial(Polynomial{Monomial(0, {{"x", 1}}), Monomial(0, {{"x", 1}})}));
    Polynomial polynomial2(createSimplifiedPolynomial(Polynomial{Monomial(6, {})}));
    Polynomial polynomial3(createSimplifiedPolynomial(Polynomial{Monomial(6, {}), Monomial(-6, {})}));

    Monomials const& monomials1(polynomial1.getMonomialsConstReference());
    ASSERT_TRUE(monomials1.empty());

    Monomials const& monomials2(polynomial2.getMonomialsConstReference());
    ASSERT_EQ(1u, monomials2.size());
    EXPECT_DOUBLE_EQ(6, monomials2.at(0).getConstantConstReference().getDouble());
    ASSERT_TRUE(monomials2.at(0).getVariablesToExponentsMapConstReference().empty());

    Monomials const& monomials3(polynomial3.getMonomialsConstReference());
    ASSERT_EQ(1u, monomials3.size());
    EXPECT_DOUBLE_EQ(0, monomials3.at(0).getConstantConstReference().getDouble());
    ASSERT_TRUE(monomials3.at(0).getVariablesToExponentsMapConstReference().empty());
}

TEST(UtilitiesTest, ConvertMonomialToSimplestTermWorksCorrectly)
{
    Term termToVerify1(convertMonomialToSimplestTerm(Monomial()));
    Term termToVerify2(convertMonomialToSimplestTerm(Monomial(6, {})));
    Term termToVerify3(convertMonomialToSimplestTerm(Monomial(1, {{"x", 1}})));
    Term termToVerify4(convertMonomialToSimplestTerm(Monomial(10, {{"x", 0}})));

    ASSERT_EQ(TermType::Constant, termToVerify1.getTermType());
    EXPECT_DOUBLE_EQ(0, termToVerify1.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(6, termToVerify2.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Variable, termToVerify3.getTermType());
    EXPECT_EQ("x", termToVerify3.getVariableConstReference().getVariableName());
    ASSERT_EQ(TermType::Constant, termToVerify4.getTermType());
    EXPECT_DOUBLE_EQ(10, termToVerify4.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(UtilitiesTest, CreateSimplifiedMonomialWorksCorrectly)
{
    Monomial monomial1(createSimplifiedMonomial(Monomial()));
    Monomial monomial2(createSimplifiedMonomial(Monomial(6, {})));
    Monomial monomial3(createSimplifiedMonomial(Monomial(1, {{"x", 1}})));
    Monomial monomial4(createSimplifiedMonomial(Monomial(10, {{"x", 0}})));

    EXPECT_DOUBLE_EQ(0, monomial1.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomial1.getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap1.empty());
    EXPECT_DOUBLE_EQ(6, monomial2.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial2.getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap2.empty());
    EXPECT_DOUBLE_EQ(1, monomial3.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap3(monomial3.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap3.size());
    EXPECT_DOUBLE_EQ(1, variableMap3.at("x").getDouble());
    EXPECT_DOUBLE_EQ(10, monomial4.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap4(monomial4.getVariablesToExponentsMapConstReference());
    ASSERT_TRUE(variableMap4.empty());
}

TEST(UtilitiesTest, MultiplyMonomialsWorksCorrectly)
{
    Monomial monomial1(multiplyMonomials(Monomial(16, {{"x", 5}}), Monomial(8, {{"x", 3}})));
    Monomial monomial2(multiplyMonomials(Monomial(20, {{"x", 7}}), Monomial(8, {{"y", 4}})));

    EXPECT_DOUBLE_EQ(128, monomial1.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomial1.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(8, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(160, monomial2.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial2.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap2.size());
    EXPECT_DOUBLE_EQ(7, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(4, variableMap2.at("y").getDouble());
}

TEST(UtilitiesTest, DivideMonomialsWorksCorrectly)
{
    Monomial monomial1(divideMonomials(Monomial(16, {{"x", 5}}), Monomial(8, {{"x", 3}})));
    Monomial monomial2(divideMonomials(Monomial(20, {{"x", 7}}), Monomial(8, {{"y", 4}})));

    EXPECT_DOUBLE_EQ(2, monomial1.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap1(monomial1.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(1u, variableMap1.size());
    EXPECT_DOUBLE_EQ(2, variableMap1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(2.5, monomial2.getConstantConstReference().getDouble());
    Monomial::VariablesToExponentsMap const& variableMap2(monomial2.getVariablesToExponentsMapConstReference());
    ASSERT_EQ(2u, variableMap2.size());
    EXPECT_DOUBLE_EQ(7, variableMap2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(-4, variableMap2.at("y").getDouble());
}

TEST(UtilitiesTest, CreateVariableMapAndRemoveZeroExponentsWorksCorrectly)
{
    Monomial::VariablesToExponentsMap variableMap1(
                createVariableMapAndRemoveZeroExponents(
                    Monomial::VariablesToExponentsMap{}));
    Monomial::VariablesToExponentsMap variableMap2(
                createVariableMapAndRemoveZeroExponents(
                    Monomial::VariablesToExponentsMap{{"x", 7}, {"y", 0}}));
    Monomial::VariablesToExponentsMap variableMap3(
                createVariableMapAndRemoveZeroExponents(
                    Monomial::VariablesToExponentsMap{{"x", 0}, {"y", 0}}));

    ASSERT_TRUE(variableMap1.empty());
    ASSERT_EQ(1u, variableMap2.size());
    EXPECT_DOUBLE_EQ(7, variableMap2.at("x").getDouble());
    ASSERT_TRUE(variableMap3.empty());
}

TEST(UtilitiesTest, PerformChangeForVariablesWorksCorrectly)
{
    Monomial::VariablesToExponentsMap variablesToExponents{{"x", 1}, {"y", 2}, {"z", 3}};

    performChangeForVariables(variablesToExponents, [](string const &, AlbaNumber & exponent)
    {
        exponent=exponent*3;
    });

    ASSERT_EQ(3u, variablesToExponents.size());
    EXPECT_DOUBLE_EQ(3, variablesToExponents.at("x").getDouble());
    EXPECT_DOUBLE_EQ(6, variablesToExponents.at("y").getDouble());
    EXPECT_DOUBLE_EQ(9, variablesToExponents.at("z").getDouble());
}

TEST(UtilitiesTest, CombineVariableExponentMapByMultiplicationWorksCorrectly)
{
    Monomial::VariablesToExponentsMap variableMap1{{"x", 7}, {"y", 8}};
    Monomial::VariablesToExponentsMap variableMap2{{"x", 1}, {"y", -8}};
    Monomial::VariablesToExponentsMap variableMap3{{"z", 5}};

    Monomial::VariablesToExponentsMap variableMapToVerify1(combineVariableExponentMapByMultiplication(variableMap1, variableMap2));
    Monomial::VariablesToExponentsMap variableMapToVerify2(combineVariableExponentMapByMultiplication(variableMap1, variableMap3));

    ASSERT_EQ(2u, variableMapToVerify1.size());
    EXPECT_DOUBLE_EQ(8, variableMapToVerify1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(0, variableMapToVerify1.at("y").getDouble());
    ASSERT_EQ(3u, variableMapToVerify2.size());
    EXPECT_DOUBLE_EQ(7, variableMapToVerify2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(8, variableMapToVerify2.at("y").getDouble());
    EXPECT_DOUBLE_EQ(5, variableMapToVerify2.at("z").getDouble());
}

TEST(UtilitiesTest, CombineVariableExponentMapByDivisionWorksCorrectly)
{
    Monomial::VariablesToExponentsMap variableMap1{{"x", 7}, {"y", 8}};
    Monomial::VariablesToExponentsMap variableMap2{{"x", 1}, {"y", 8}};
    Monomial::VariablesToExponentsMap variableMap3{{"z", 5}};

    Monomial::VariablesToExponentsMap variableMapToVerify1(combineVariableExponentMapByDivision(variableMap1, variableMap2));
    Monomial::VariablesToExponentsMap variableMapToVerify2(combineVariableExponentMapByDivision(variableMap1, variableMap3));

    ASSERT_EQ(2u, variableMapToVerify1.size());
    EXPECT_DOUBLE_EQ(6, variableMapToVerify1.at("x").getDouble());
    EXPECT_DOUBLE_EQ(0, variableMapToVerify1.at("y").getDouble());
    ASSERT_EQ(3u, variableMapToVerify2.size());
    EXPECT_DOUBLE_EQ(7, variableMapToVerify2.at("x").getDouble());
    EXPECT_DOUBLE_EQ(8, variableMapToVerify2.at("y").getDouble());
    EXPECT_DOUBLE_EQ(-5, variableMapToVerify2.at("z").getDouble());
}

TEST(UtilitiesTest, CreateExpressionWorksCorrectly)
{
    Expression expressionToTest(createExpression(Terms{Term(10), Term("/"), Term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})})}));

    TermsWithPriorityAndAssociation::TermsWithDetails termsToVerify(expressionToTest.getTerms().getTermsWithDetails());

    EXPECT_EQ(OperatorLevel::MultiplicationAndDivision, expressionToTest.getCommonOperatorLevel());
    ASSERT_EQ(2u, termsToVerify.size());
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Positive, termsToVerify.at(0).association);
    Term const& termToVerify1 = *dynamic_cast<Term const*const>(termsToVerify.at(0).baseTermSharedPointer.get());
    EXPECT_EQ(Term(10), termToVerify1);
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Negative, termsToVerify.at(1).association);
    Term const& termToVerify2 = *dynamic_cast<Term const*const>(termsToVerify.at(1).baseTermSharedPointer.get());
    EXPECT_EQ(Term(Polynomial{Monomial(5, {}), Monomial(1, {{"x", 1}})}), termToVerify2);
}

TEST(UtilitiesTest, CreateExpressionDoesNotSimplify)
{
    Expression expressionToTest(createExpression(Terms{Term(7.625), Term("+"), Term(2.375)}));

    TermsWithPriorityAndAssociation::TermsWithDetails termsToVerify(expressionToTest.getTerms().getTermsWithDetails());

    EXPECT_EQ(OperatorLevel::AdditionAndSubtraction, expressionToTest.getCommonOperatorLevel());
    ASSERT_EQ(2u, termsToVerify.size());
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Positive, termsToVerify.at(0).association);
    Term const& termToVerify1 = *dynamic_cast<Term const*const>(termsToVerify.at(0).baseTermSharedPointer.get());
    EXPECT_EQ(Term(7.625), termToVerify1);
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Positive, termsToVerify.at(1).association);
    Term const& termToVerify2 = *dynamic_cast<Term const*const>(termsToVerify.at(1).baseTermSharedPointer.get());
    EXPECT_EQ(Term(2.375), termToVerify2);
}

TEST(UtilitiesTest, CreateSimplifiedExpressionWorksCorrectly)
{
    Expression expressionToTest(createSimplifiedExpression(Terms{Term(7.625), Term("+"), Term(2.375)}));

    TermsWithPriorityAndAssociation::TermsWithDetails termsToVerify(expressionToTest.getTerms().getTermsWithDetails());

    EXPECT_EQ(OperatorLevel::Unknown, expressionToTest.getCommonOperatorLevel());
    ASSERT_EQ(1u, termsToVerify.size());
    EXPECT_EQ(TermsWithPriorityAndAssociation::AssociationType::Positive, termsToVerify.at(0).association);
    Term const& termToVerify1 = *dynamic_cast<Term const*const>(termsToVerify.at(0).baseTermSharedPointer.get());
    EXPECT_EQ(Term(10), termToVerify1);
}

}

}
