#include <PerformOperation.hpp>
#include <Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;

namespace alba
{

namespace equation
{

TEST(PerformOperationTest, PerformOperationUnaryOperationWorks)
{
    Term termToVerify1(performOperation(Operator("+"), Term(215)));
    Term termToVerify2(performOperation(Operator("-"), Term(215)));

    EXPECT_EQ(Term(215), termToVerify1);
    EXPECT_EQ(Term(-215), termToVerify2);
}

TEST(PerformOperationTest, PerformOperationBinaryOperationWorks)
{
    Term termToVerify1(performOperation(Operator("+"), Term(25), Term(2)));
    Term termToVerify2(performOperation(Operator("-"), Term(25), Term(2)));
    Term termToVerify3(performOperation(Operator("*"), Term(25), Term(2)));
    Term termToVerify4(performOperation(Operator("/"), Term(25), Term(2)));
    Term termToVerify5(performOperation(Operator("^"), Term(25), Term(2)));

    EXPECT_EQ(Term(27), termToVerify1);
    EXPECT_EQ(Term(23), termToVerify2);
    EXPECT_EQ(Term(50), termToVerify3);
    EXPECT_EQ(Term(12.5), termToVerify4);
    EXPECT_EQ(Term(625), termToVerify5);
}

TEST(PerformOperationTest, AccumulateAndDoOperationOnTermDetailsWorks)
{
    Term newTerm1(45);
    Term newTerm2(45);
    TermWithDetails termWithDetails1(getBaseTermConstReferenceFromTerm(Term(25)), TermAssociationType::Positive);
    TermWithDetails termWithDetails2(getBaseTermConstReferenceFromTerm(Term(25)), TermAssociationType::Negative);

    accumulateAndDoOperationOnTermDetails(newTerm1, OperatorLevel::AdditionAndSubtraction, termWithDetails1);
    accumulateAndDoOperationOnTermDetails(newTerm2, OperatorLevel::AdditionAndSubtraction, termWithDetails2);

    EXPECT_EQ(Term(70), newTerm1);
    EXPECT_EQ(Term(20), newTerm2);
}



}

}
