#include <Algebra/Operations/PerformOperations.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(PerformOperationsTest, PerformOperationUnaryOperationWorks)
{
    Term termToVerify1(performOperation(Operator("+"), 215));
    Term termToVerify2(performOperation(Operator("-"), 215));

    EXPECT_EQ(Term(215), termToVerify1);
    EXPECT_EQ(Term(-215), termToVerify2);
}

TEST(PerformOperationsTest, PerformOperationBinaryOperationWorks)
{
    Term termToVerify1(performOperation(Operator("+"), 25, 2));
    Term termToVerify2(performOperation(Operator("-"), 25, 2));
    Term termToVerify3(performOperation(Operator("*"), 25, 2));
    Term termToVerify4(performOperation(Operator("/"), 25, 2));
    Term termToVerify5(performOperation(Operator("^"), 25, 2));

    EXPECT_EQ(Term(27), termToVerify1);
    EXPECT_EQ(Term(23), termToVerify2);
    EXPECT_EQ(Term(50), termToVerify3);
    EXPECT_EQ(Term(12.5), termToVerify4);
    EXPECT_EQ(Term(625), termToVerify5);
}


}

}
