#include <BooleanAlgebra/Operations/PerformOperations.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

TEST(PerformOperationsTest, PerformOperationUnaryOperationWorks)
{
    Term termToVerify1(performOperation(Operator("~"), false));
    Term termToVerify2(performOperation(Operator("~"), true));

    EXPECT_EQ(Term(true), termToVerify1);
    EXPECT_EQ(Term(false), termToVerify2);
}

TEST(PerformOperationsTest, PerformOperationBinaryOperationWorks)
{
    Term termToVerify1(performOperation(Operator("&"), false, false));
    Term termToVerify2(performOperation(Operator("&"), false, true));
    Term termToVerify3(performOperation(Operator("&"), true, false));
    Term termToVerify4(performOperation(Operator("&"), true, true));
    Term termToVerify5(performOperation(Operator("|"), false, false));
    Term termToVerify6(performOperation(Operator("|"), false, true));
    Term termToVerify7(performOperation(Operator("|"), true, false));
    Term termToVerify8(performOperation(Operator("|"), true, true));

    EXPECT_EQ(Term(false), termToVerify1);
    EXPECT_EQ(Term(false), termToVerify2);
    EXPECT_EQ(Term(false), termToVerify3);
    EXPECT_EQ(Term(true), termToVerify4);
    EXPECT_EQ(Term(false), termToVerify5);
    EXPECT_EQ(Term(true), termToVerify6);
    EXPECT_EQ(Term(true), termToVerify7);
    EXPECT_EQ(Term(true), termToVerify8);
}

}

}
