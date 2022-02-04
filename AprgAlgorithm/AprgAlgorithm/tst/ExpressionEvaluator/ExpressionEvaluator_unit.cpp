#include <ExpressionEvaluator/ExpressionEvaluator.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace ExpressionEvaluator
{
template <>
int performUnaryOperation<int, string>(string const& operatorString, int const& value)
{    int result(0);
    if(operatorString == "~")
    {
        result = ~value;
    }
    return result;
}

template <>
int performBinaryOperation<int, string>(int const& value1, string const& operatorString, int const& value2)
{
    int result(0);
    if(operatorString == "+")
    {
        result = value1+value2;
    }
    else if(operatorString == "-")
    {
        result = value1-value2;
    }
    else if(operatorString == "*")
    {
        result = value1*value2;
    }
    else if(operatorString == "/")
    {
        result = value1/value2;
    }
    return result;
}


using InfixEvaluatorForTest = ExpressionInfixEvaluator<int, string>;
using PostfixEvaluatorForTest = ExpressionPostfixEvaluator<int, string>;
using EvaluatorConverterForTest = ExpressionEvaluatorConverter<int, string>;


TEST(ExpressionInfixEvaluatorTest, DoesNotCrashWhenValueAreEmpty)
{
    InfixEvaluatorForTest evaluator;
    evaluator.evaluate();
}

TEST(ExpressionInfixEvaluatorTest, SingleValueIsEvaluatedCorrectly)
{
    InfixEvaluatorForTest evaluator;
    evaluator.addTerm(InfixEvaluatorForTest::Term(5U));
    EXPECT_EQ(5, evaluator.evaluate());
}

TEST(ExpressionInfixEvaluatorTest, PrefixUnaryOperationAreCorrectlyEvaluated)
{
    InfixEvaluatorForTest evaluator;
    evaluator.addTerm(InfixEvaluatorForTest::Term("~", InfixEvaluatorForTest::Term::OperatorSyntaxType::PrefixUnary));
    evaluator.addTerm(InfixEvaluatorForTest::Term(0U));
    EXPECT_EQ(-1, evaluator.evaluate());
}

TEST(ExpressionInfixEvaluatorTest, BinaryOperationAreCorrectlyEvaluated)
{
    InfixEvaluatorForTest evaluator;
    evaluator.addTerm(InfixEvaluatorForTest::Term(123U));
    evaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(InfixEvaluatorForTest::Term(654U));
    EXPECT_EQ(777, evaluator.evaluate());
}

TEST(ExpressionInfixEvaluatorTest, BinaryOperationWithPriorityAreCorrectlyEvaluated)
{
    InfixEvaluatorForTest evaluator;
    evaluator.addTerm(InfixEvaluatorForTest::Term(100U));
    evaluator.addTerm(InfixEvaluatorForTest::Term("*", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary, 2));
    evaluator.addTerm(InfixEvaluatorForTest::Term(10U));
    evaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary, 1));
    evaluator.addTerm(InfixEvaluatorForTest::Term(100U));
    EXPECT_EQ(1100, evaluator.evaluate());
}

TEST(ExpressionInfixEvaluatorTest, BinaryOperationWithCompleteParenthesesAreCorrectlyEvaluated)
{
    InfixEvaluatorForTest evaluator;
    evaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term(123U));
    evaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(InfixEvaluatorForTest::Term(654U));
    evaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    EXPECT_EQ(777, evaluator.evaluate());
}

TEST(ExpressionInfixEvaluatorTest, BinaryOperationWithNoLeftParenthesisAreCorrectlyEvaluated)
{
    InfixEvaluatorForTest evaluator;
    evaluator.addTerm(InfixEvaluatorForTest::Term(123U));
    evaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(InfixEvaluatorForTest::Term(654U));
    evaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    EXPECT_EQ(777, evaluator.evaluate());
}

TEST(ExpressionInfixEvaluatorTest, BinaryOperationWithNoRightParenthesisAreCorrectlyEvaluated)
{
    InfixEvaluatorForTest evaluator;
    evaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term(123U));
    evaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(InfixEvaluatorForTest::Term(654U));
    EXPECT_EQ(777, evaluator.evaluate());
}

TEST(ExpressionInfixEvaluatorTest, ComplicatedOperationsAndParenthesesAreCorrectlyEvaluated)
{
    InfixEvaluatorForTest evaluator;
    evaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term(1U));
    evaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term(2U));
    evaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(InfixEvaluatorForTest::Term(3U));
    evaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term("*", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term(4U));
    evaluator.addTerm(InfixEvaluatorForTest::Term("*", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(InfixEvaluatorForTest::Term(5U));
    evaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    EXPECT_EQ(101, evaluator.evaluate());
}

TEST(ExpressionPostfixEvaluatorTest, DoesNotCrashWhenValueAreEmpty)
{
    PostfixEvaluatorForTest evaluator;
    EXPECT_FALSE(evaluator.isEvaluationPossible());
    evaluator.evaluate();
}

TEST(ExpressionPostfixEvaluatorTest, SingleValueIsEvaluatedCorrectly)
{
    PostfixEvaluatorForTest evaluator;
    evaluator.addTerm(PostfixEvaluatorForTest::Term(5U));
    EXPECT_TRUE(evaluator.isEvaluationPossible());
    EXPECT_EQ(5, evaluator.evaluate());
}

TEST(ExpressionPostfixEvaluatorTest, PrefixUnaryOperationAreCorrectlyEvaluated)
{
    PostfixEvaluatorForTest evaluator;
    evaluator.addTerm(PostfixEvaluatorForTest::Term(0U));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("~", PostfixEvaluatorForTest::Term::OperatorSyntaxType::PrefixUnary));
    EXPECT_TRUE(evaluator.isEvaluationPossible());
    EXPECT_EQ(-1, evaluator.evaluate());
}

TEST(ExpressionPostfixEvaluatorTest, BinaryOperationAreCorrectlyEvaluated)
{
    PostfixEvaluatorForTest evaluator;
    evaluator.addTerm(PostfixEvaluatorForTest::Term(123U));
    evaluator.addTerm(PostfixEvaluatorForTest::Term(654U));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("+", PostfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    EXPECT_TRUE(evaluator.isEvaluationPossible());
    EXPECT_EQ(777, evaluator.evaluate());
}

TEST(ExpressionPostfixEvaluatorTest,ParenthesesAreIgnoredWhenEvaluated)
{
    PostfixEvaluatorForTest evaluator;
    evaluator.addTerm(PostfixEvaluatorForTest::Term("(", PostfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    evaluator.addTerm(PostfixEvaluatorForTest::Term(123U));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("(", PostfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    evaluator.addTerm(PostfixEvaluatorForTest::Term(654U));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("+", PostfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(PostfixEvaluatorForTest::Term(")", PostfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    EXPECT_TRUE(evaluator.isEvaluationPossible());
    EXPECT_EQ(777, evaluator.evaluate());
}

TEST(ExpressionPostfixEvaluatorTest, ComplicatedOperationssAreCorrectlyEvaluated)
{
    PostfixEvaluatorForTest evaluator;
    evaluator.addTerm(PostfixEvaluatorForTest::Term(1U));
    evaluator.addTerm(PostfixEvaluatorForTest::Term(2U));
    evaluator.addTerm(PostfixEvaluatorForTest::Term(3U));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("+", PostfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(PostfixEvaluatorForTest::Term(4U));
    evaluator.addTerm(PostfixEvaluatorForTest::Term(5U));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("*", PostfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("*", PostfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("+", PostfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    EXPECT_TRUE(evaluator.isEvaluationPossible());
    EXPECT_EQ(101, evaluator.evaluate());
}

TEST(ExpressionPostfixEvaluatorTest, EvaluationIsNotPossibleForIncompleteOperandForUnaryOperation)
{
    PostfixEvaluatorForTest evaluator;
    evaluator.addTerm(PostfixEvaluatorForTest::Term("~", PostfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    EXPECT_FALSE(evaluator.isEvaluationPossible());
    evaluator.evaluate();
}

TEST(ExpressionPostfixEvaluatorTest, EvaluationIsNotPossibleForIncompleteOperandsForBinaryOperation)
{
    PostfixEvaluatorForTest evaluator;
    evaluator.addTerm(PostfixEvaluatorForTest::Term(1U));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("+", PostfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    EXPECT_FALSE(evaluator.isEvaluationPossible());
    EXPECT_EQ(1, evaluator.evaluate());
}

TEST(ExpressionEvaluatorConverterTest, InfixToPostfixConvertionWorksForUnaryOperation)
{
    InfixEvaluatorForTest infixEvaluator;
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("~", InfixEvaluatorForTest::Term::OperatorSyntaxType::PrefixUnary));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(0U));
    EXPECT_EQ(-1, infixEvaluator.evaluate());

    EvaluatorConverterForTest evaluatorConverter;
    PostfixEvaluatorForTest postfixEvaluator(evaluatorConverter.convertInfixToPostfix(infixEvaluator));
    PostfixEvaluatorForTest::Terms terms(postfixEvaluator.getTerms());
    ASSERT_EQ(2U, terms.size());
    EXPECT_EQ(0, terms[0].getValue());
    EXPECT_EQ("~", terms[1].getOperator());
    EXPECT_EQ(-1, postfixEvaluator.evaluate());
}

TEST(ExpressionEvaluatorConverterTest, InfixToPostfixConvertionWorksForBinaryOperation)
{
    InfixEvaluatorForTest infixEvaluator;
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(123U));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(654U));
    EXPECT_EQ(777, infixEvaluator.evaluate());

    EvaluatorConverterForTest evaluatorConverter;
    PostfixEvaluatorForTest postfixEvaluator(evaluatorConverter.convertInfixToPostfix(infixEvaluator));
    PostfixEvaluatorForTest::Terms terms(postfixEvaluator.getTerms());
    ASSERT_EQ(3U, terms.size());
    EXPECT_EQ(123, terms[0].getValue());
    EXPECT_EQ(654, terms[1].getValue());
    EXPECT_EQ("+", terms[2].getOperator());
    EXPECT_EQ(777, postfixEvaluator.evaluate());
}

TEST(ExpressionEvaluatorConverterTest, InfixToPostfixConvertionWorksForBinaryOperationWithPriority)
{
    InfixEvaluatorForTest infixEvaluator;
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(100U));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("*", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary, 2));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(10U));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary, 1));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(100U));
    EXPECT_EQ(1100, infixEvaluator.evaluate());

    EvaluatorConverterForTest evaluatorConverter;
    PostfixEvaluatorForTest postfixEvaluator(evaluatorConverter.convertInfixToPostfix(infixEvaluator));
    PostfixEvaluatorForTest::Terms terms(postfixEvaluator.getTerms());
    ASSERT_EQ(5U, terms.size());
    EXPECT_EQ(100, terms[0].getValue());
    EXPECT_EQ(10, terms[1].getValue());
    EXPECT_EQ("*", terms[2].getOperator());
    EXPECT_EQ(100, terms[3].getValue());
    EXPECT_EQ("+", terms[4].getOperator());
    EXPECT_EQ(1100, postfixEvaluator.evaluate());
}

TEST(ExpressionEvaluatorConverterTest, InfixToPostfixConvertionWorksForComplicatedOperationsWithParentheses)
{
    InfixEvaluatorForTest infixEvaluator;
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(1U));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(2U));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(3U));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("*", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(4U));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("*", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(5U));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    EXPECT_EQ(101, infixEvaluator.evaluate());

    EvaluatorConverterForTest evaluatorConverter;
    PostfixEvaluatorForTest postfixEvaluator(evaluatorConverter.convertInfixToPostfix(infixEvaluator));
    PostfixEvaluatorForTest::Terms terms(postfixEvaluator.getTerms());
    ASSERT_EQ(9U, terms.size());
    EXPECT_EQ(1, terms[0].getValue());
    EXPECT_EQ(2, terms[1].getValue());
    EXPECT_EQ(3, terms[2].getValue());
    EXPECT_EQ("+", terms[3].getOperator());
    EXPECT_EQ(4, terms[4].getValue());
    EXPECT_EQ(5, terms[5].getValue());
    EXPECT_EQ("*", terms[6].getOperator());
    EXPECT_EQ("*", terms[7].getOperator());
    EXPECT_EQ("+", terms[8].getOperator());
    EXPECT_EQ(101, postfixEvaluator.evaluate());
}

TEST(ExpressionEvaluatorConverterTest, PostfixInfixToConvertionWorks)
{
    PostfixEvaluatorForTest postfixEvaluator;
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term(1U));
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term(2U));
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term(3U));
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term(4U));
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term(5U));
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term("*", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term("*", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));

    EvaluatorConverterForTest evaluatorConverter;
    InfixEvaluatorForTest infixEvaluator(evaluatorConverter.convertPostfixToInfix(postfixEvaluator));
    InfixEvaluatorForTest::Terms terms(infixEvaluator.getTerms());

    //((5*4)*(3+2))+1
    ASSERT_EQ(15U, terms.size());
    EXPECT_TRUE(terms[0].isStartGroupOperator());
    EXPECT_TRUE(terms[1].isStartGroupOperator());
    EXPECT_EQ(5, terms[2].getValue());
    EXPECT_EQ("*", terms[3].getOperator());
    EXPECT_EQ(4, terms[4].getValue());
    EXPECT_TRUE(terms[5].isEndGroupOperator());
    EXPECT_EQ("*", terms[6].getOperator());
    EXPECT_TRUE(terms[7].isStartGroupOperator());
    EXPECT_EQ(3, terms[8].getValue());
    EXPECT_EQ("+", terms[9].getOperator());
    EXPECT_EQ(2, terms[10].getValue());
    EXPECT_TRUE(terms[11].isEndGroupOperator());
    EXPECT_TRUE(terms[12].isEndGroupOperator());
    EXPECT_EQ("+", terms[13].getOperator());
    EXPECT_EQ(1, terms[14].getValue());
    EXPECT_EQ(101, postfixEvaluator.evaluate());
}

}

}

}