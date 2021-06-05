#include <PerformOperation.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace equation
{

TEST(PerformOperationTest, PerformOperationUnaryOperation)
{
    Term termToVerify1(performOperation(Operator("+"), Term(215)));
    Term termToVerify2(performOperation(Operator("-"), Term(215)));

    ASSERT_EQ(TermType::Constant, termToVerify1.getTermType());
    EXPECT_DOUBLE_EQ(215, termToVerify1.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(-215, termToVerify2.getConstantConstReference().getNumberConstReference().getDouble());
}

TEST(PerformOperationTest, PerformOperationBinaryOperation)
{
    Term termToVerify1(performOperation(Operator("+"), Term(25), Term(2)));
    Term termToVerify2(performOperation(Operator("-"), Term(25), Term(2)));
    Term termToVerify3(performOperation(Operator("*"), Term(25), Term(2)));
    Term termToVerify4(performOperation(Operator("/"), Term(25), Term(2)));
    Term termToVerify5(performOperation(Operator("^"), Term(25), Term(2)));

    ASSERT_EQ(TermType::Constant, termToVerify1.getTermType());
    EXPECT_DOUBLE_EQ(27, termToVerify1.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Constant, termToVerify2.getTermType());
    EXPECT_DOUBLE_EQ(23, termToVerify2.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Constant, termToVerify3.getTermType());
    EXPECT_DOUBLE_EQ(50, termToVerify3.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Constant, termToVerify4.getTermType());
    EXPECT_DOUBLE_EQ(12.5, termToVerify4.getConstantConstReference().getNumberConstReference().getDouble());
    EXPECT_EQ(TermType::Constant, termToVerify5.getTermType());
    EXPECT_DOUBLE_EQ(625, termToVerify5.getConstantConstReference().getNumberConstReference().getDouble());
}

}

}
