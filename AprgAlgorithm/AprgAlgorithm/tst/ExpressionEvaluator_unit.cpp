#include <gtest/gtest.h>

#include <string>

namespace alba
{
namespace ExpressionEvaluator
{
int performUnaryOperation(std::string const& operatorString, int const value);
int performBinaryOperation(int const value1, std::string const& operatorString, int const value2);
}
}

#include <ExpressionEvaluator/ExpressionEvaluator.hpp>


using namespace std;

namespace alba
{

namespace ExpressionEvaluator
{

int performUnaryOperation(string const& operatorString, int const value)
{
    int result(0);
    if(operatorString == "~")
    {
        result = ~value;
    }
    return result;
}

int performBinaryOperation(int const value1, string const& operatorString, int const value2)
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
    evaluator.addTerm(InfixEvaluatorForTest::Term(5u));
    EXPECT_EQ(5u, evaluator.evaluate());
}

TEST(ExpressionInfixEvaluatorTest, PrefixUnaryOperationAreCorrectlyEvaluated)
{
    InfixEvaluatorForTest evaluator;
    evaluator.addTerm(InfixEvaluatorForTest::Term("~", InfixEvaluatorForTest::Term::OperatorSyntaxType::PrefixUnary));
    evaluator.addTerm(InfixEvaluatorForTest::Term(0u));
    EXPECT_EQ(0xFFFFFFFFu, evaluator.evaluate());
}

TEST(ExpressionInfixEvaluatorTest, BinaryOperationAreCorrectlyEvaluated)
{
    InfixEvaluatorForTest evaluator;
    evaluator.addTerm(InfixEvaluatorForTest::Term(123u));
    evaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(InfixEvaluatorForTest::Term(654u));
    EXPECT_EQ(777u, evaluator.evaluate());
}

TEST(ExpressionInfixEvaluatorTest, BinaryOperationWithPriorityAreCorrectlyEvaluated)
{
    InfixEvaluatorForTest evaluator;
    evaluator.addTerm(InfixEvaluatorForTest::Term(100u));
    evaluator.addTerm(InfixEvaluatorForTest::Term("*", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary, 2));
    evaluator.addTerm(InfixEvaluatorForTest::Term(10u));
    evaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary, 1));
    evaluator.addTerm(InfixEvaluatorForTest::Term(100u));
    EXPECT_EQ(1100u, evaluator.evaluate());
}

TEST(ExpressionInfixEvaluatorTest, BinaryOperationWithCompleteParenthesesAreCorrectlyEvaluated)
{
    InfixEvaluatorForTest evaluator;
    evaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term(123u));
    evaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(InfixEvaluatorForTest::Term(654u));
    evaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    EXPECT_EQ(777u, evaluator.evaluate());
}

TEST(ExpressionInfixEvaluatorTest, BinaryOperationWithNoLeftParenthesisAreCorrectlyEvaluated)
{
    InfixEvaluatorForTest evaluator;
    evaluator.addTerm(InfixEvaluatorForTest::Term(123u));
    evaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(InfixEvaluatorForTest::Term(654u));
    evaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    EXPECT_EQ(777u, evaluator.evaluate());
}

TEST(ExpressionInfixEvaluatorTest, BinaryOperationWithNoRightParenthesisAreCorrectlyEvaluated)
{
    InfixEvaluatorForTest evaluator;
    evaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term(123u));
    evaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(InfixEvaluatorForTest::Term(654u));
    EXPECT_EQ(777u, evaluator.evaluate());
}

TEST(ExpressionInfixEvaluatorTest, ComplicatedOperationsAndParenthesesAreCorrectlyEvaluated)
{
    InfixEvaluatorForTest evaluator;
    evaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term(1u));
    evaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term(2u));
    evaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(InfixEvaluatorForTest::Term(3u));
    evaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term("*", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term(4u));
    evaluator.addTerm(InfixEvaluatorForTest::Term("*", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(InfixEvaluatorForTest::Term(5u));
    evaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    evaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    EXPECT_EQ(101u, evaluator.evaluate());
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
    evaluator.addTerm(PostfixEvaluatorForTest::Term(5u));
    EXPECT_TRUE(evaluator.isEvaluationPossible());
    EXPECT_EQ(5u, evaluator.evaluate());
}

TEST(ExpressionPostfixEvaluatorTest, PrefixUnaryOperationAreCorrectlyEvaluated)
{
    PostfixEvaluatorForTest evaluator;
    evaluator.addTerm(PostfixEvaluatorForTest::Term(0u));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("~", PostfixEvaluatorForTest::Term::OperatorSyntaxType::PrefixUnary));
    EXPECT_TRUE(evaluator.isEvaluationPossible());
    EXPECT_EQ(0xFFFFFFFFu, evaluator.evaluate());
}

TEST(ExpressionPostfixEvaluatorTest, BinaryOperationAreCorrectlyEvaluated)
{
    PostfixEvaluatorForTest evaluator;
    evaluator.addTerm(PostfixEvaluatorForTest::Term(123u));
    evaluator.addTerm(PostfixEvaluatorForTest::Term(654u));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("+", PostfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    EXPECT_TRUE(evaluator.isEvaluationPossible());
    EXPECT_EQ(777u, evaluator.evaluate());
}

TEST(ExpressionPostfixEvaluatorTest,ParenthesesAreIgnoredWhenEvaluated)
{
    PostfixEvaluatorForTest evaluator;
    evaluator.addTerm(PostfixEvaluatorForTest::Term("(", PostfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    evaluator.addTerm(PostfixEvaluatorForTest::Term(123u));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("(", PostfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    evaluator.addTerm(PostfixEvaluatorForTest::Term(654u));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("+", PostfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(PostfixEvaluatorForTest::Term(")", PostfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    EXPECT_TRUE(evaluator.isEvaluationPossible());
    EXPECT_EQ(777u, evaluator.evaluate());
}

TEST(ExpressionPostfixEvaluatorTest, ComplicatedOperationssAreCorrectlyEvaluated)
{
    PostfixEvaluatorForTest evaluator;
    evaluator.addTerm(PostfixEvaluatorForTest::Term(1u));
    evaluator.addTerm(PostfixEvaluatorForTest::Term(2u));
    evaluator.addTerm(PostfixEvaluatorForTest::Term(3u));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("+", PostfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(PostfixEvaluatorForTest::Term(4u));
    evaluator.addTerm(PostfixEvaluatorForTest::Term(5u));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("*", PostfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("*", PostfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("+", PostfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    EXPECT_TRUE(evaluator.isEvaluationPossible());
    EXPECT_EQ(101u, evaluator.evaluate());
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
    evaluator.addTerm(PostfixEvaluatorForTest::Term(1u));
    evaluator.addTerm(PostfixEvaluatorForTest::Term("+", PostfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    EXPECT_FALSE(evaluator.isEvaluationPossible());
    EXPECT_EQ(1u, evaluator.evaluate());
}

TEST(ExpressionEvaluatorConverterTest, InfixToPostfixConvertionWorksForUnaryOperation)
{
    InfixEvaluatorForTest infixEvaluator;
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("~", InfixEvaluatorForTest::Term::OperatorSyntaxType::PrefixUnary));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(0u));
    EXPECT_EQ(0xFFFFFFFFu, infixEvaluator.evaluate());

    EvaluatorConverterForTest evaluatorConverter;
    PostfixEvaluatorForTest postfixEvaluator(evaluatorConverter.convertInfixToPostfix(infixEvaluator));
    PostfixEvaluatorForTest::Terms terms(postfixEvaluator.getTerms());
    ASSERT_EQ(2u, terms.size());
    EXPECT_EQ(0u, terms[0].getValue());
    EXPECT_EQ("~", terms[1].getOperator());
    EXPECT_EQ(0xFFFFFFFFu, postfixEvaluator.evaluate());
}

TEST(ExpressionEvaluatorConverterTest, InfixToPostfixConvertionWorksForBinaryOperation)
{
    InfixEvaluatorForTest infixEvaluator;
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(123u));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(654u));
    EXPECT_EQ(777u, infixEvaluator.evaluate());

    EvaluatorConverterForTest evaluatorConverter;
    PostfixEvaluatorForTest postfixEvaluator(evaluatorConverter.convertInfixToPostfix(infixEvaluator));
    PostfixEvaluatorForTest::Terms terms(postfixEvaluator.getTerms());
    ASSERT_EQ(3u, terms.size());
    EXPECT_EQ(123u, terms[0].getValue());
    EXPECT_EQ(654u, terms[1].getValue());
    EXPECT_EQ("+", terms[2].getOperator());
    EXPECT_EQ(777u, postfixEvaluator.evaluate());
}

TEST(ExpressionEvaluatorConverterTest, InfixToPostfixConvertionWorksForBinaryOperationWithPriority)
{
    InfixEvaluatorForTest infixEvaluator;
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(100u));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("*", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary, 2));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(10u));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary, 1));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(100u));
    EXPECT_EQ(1100u, infixEvaluator.evaluate());

    EvaluatorConverterForTest evaluatorConverter;
    PostfixEvaluatorForTest postfixEvaluator(evaluatorConverter.convertInfixToPostfix(infixEvaluator));
    PostfixEvaluatorForTest::Terms terms(postfixEvaluator.getTerms());
    ASSERT_EQ(5u, terms.size());
    EXPECT_EQ(100u, terms[0].getValue());
    EXPECT_EQ(10u, terms[1].getValue());
    EXPECT_EQ("*", terms[2].getOperator());
    EXPECT_EQ(100u, terms[3].getValue());
    EXPECT_EQ("+", terms[4].getOperator());
    EXPECT_EQ(1100u, postfixEvaluator.evaluate());
}

TEST(ExpressionEvaluatorConverterTest, InfixToPostfixConvertionWorksForComplicatedOperationsWithParentheses)
{
    InfixEvaluatorForTest infixEvaluator;
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(1u));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(2u));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(3u));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("*", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("(", InfixEvaluatorForTest::Term::OperatorSyntaxType::StartGroup));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(4u));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term("*", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(5u));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    infixEvaluator.addTerm(InfixEvaluatorForTest::Term(")", InfixEvaluatorForTest::Term::OperatorSyntaxType::EndGroup));
    EXPECT_EQ(101u, infixEvaluator.evaluate());

    EvaluatorConverterForTest evaluatorConverter;
    PostfixEvaluatorForTest postfixEvaluator(evaluatorConverter.convertInfixToPostfix(infixEvaluator));
    PostfixEvaluatorForTest::Terms terms(postfixEvaluator.getTerms());
    ASSERT_EQ(9u, terms.size());
    EXPECT_EQ(1u, terms[0].getValue());
    EXPECT_EQ(2u, terms[1].getValue());
    EXPECT_EQ(3u, terms[2].getValue());
    EXPECT_EQ("+", terms[3].getOperator());
    EXPECT_EQ(4u, terms[4].getValue());
    EXPECT_EQ(5u, terms[5].getValue());
    EXPECT_EQ("*", terms[6].getOperator());
    EXPECT_EQ("*", terms[7].getOperator());
    EXPECT_EQ("+", terms[8].getOperator());
    EXPECT_EQ(101u, postfixEvaluator.evaluate());
}

TEST(ExpressionEvaluatorConverterTest, PostfixInfixToConvertionWorks)
{
    PostfixEvaluatorForTest postfixEvaluator;
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term(1u));
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term(2u));
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term(3u));
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term(4u));
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term(5u));
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term("*", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term("*", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));
    postfixEvaluator.addTerm(InfixEvaluatorForTest::Term("+", InfixEvaluatorForTest::Term::OperatorSyntaxType::Binary));

    EvaluatorConverterForTest evaluatorConverter;
    InfixEvaluatorForTest infixEvaluator(evaluatorConverter.convertPostfixToInfix(postfixEvaluator));
    InfixEvaluatorForTest::Terms terms(infixEvaluator.getTerms());

    //((5*4)*(3+2))+1
    ASSERT_EQ(15u, terms.size());
    EXPECT_TRUE(terms[0].isStartGroupOperator());
    EXPECT_TRUE(terms[1].isStartGroupOperator());
    EXPECT_EQ(5u, terms[2].getValue());
    EXPECT_EQ("*", terms[3].getOperator());
    EXPECT_EQ(4u, terms[4].getValue());
    EXPECT_TRUE(terms[5].isEndGroupOperator());
    EXPECT_EQ("*", terms[6].getOperator());
    EXPECT_TRUE(terms[7].isStartGroupOperator());
    EXPECT_EQ(3u, terms[8].getValue());
    EXPECT_EQ("+", terms[9].getOperator());
    EXPECT_EQ(2u, terms[10].getValue());
    EXPECT_TRUE(terms[11].isEndGroupOperator());
    EXPECT_TRUE(terms[12].isEndGroupOperator());
    EXPECT_EQ("+", terms[13].getOperator());
    EXPECT_EQ(1u, terms[14].getValue());
    EXPECT_EQ(101u, postfixEvaluator.evaluate());
}

}

}
