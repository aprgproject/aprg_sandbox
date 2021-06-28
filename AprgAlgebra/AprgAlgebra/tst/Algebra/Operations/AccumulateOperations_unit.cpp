#include <Algebra/Operations/AccumulateOperations.hpp>
#include <Algebra/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;
using TermWithDetails=alba::algebra::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::algebra::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace algebra
{

TEST(AccumulateOperationsTest, AccumulateAndDoOperationOnTermDetailsWorks)
{
    Term newTerm1(45);
    Term newTerm2(45);
    TermWithDetails termWithDetails1(Term(25), TermAssociationType::Positive);
    TermWithDetails termWithDetails2(Term(25), TermAssociationType::Negative);

    accumulateAndDoOperationOnTermDetails(newTerm1, OperatorLevel::AdditionAndSubtraction, termWithDetails1);
    accumulateAndDoOperationOnTermDetails(newTerm2, OperatorLevel::AdditionAndSubtraction, termWithDetails2);

    EXPECT_EQ(Term(70), newTerm1);
    EXPECT_EQ(Term(20), newTerm2);
}

}

}
