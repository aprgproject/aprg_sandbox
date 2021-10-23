#include <Algebra/Operations/AccumulateOperations.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

namespace algebra
{

TEST(AccumulateOperationsTest, AccumulateAndDoOperationOnTermDetailsWorks)
{
    Term termToTest1(45);
    Term termToTest2(45);
    TermWithDetails termWithDetails1(Term(25), TermAssociationType::Positive);
    TermWithDetails termWithDetails2(Term(25), TermAssociationType::Negative);

    accumulateAndDoOperationOnTermDetails(termToTest1, OperatorLevel::AdditionAndSubtraction, termWithDetails1);
    accumulateAndDoOperationOnTermDetails(termToTest2, OperatorLevel::AdditionAndSubtraction, termWithDetails2);

    EXPECT_EQ(Term(70), termToTest1);
    EXPECT_EQ(Term(20), termToTest2);
}

TEST(AccumulateOperationsTest, AccumulateTermsForAdditionAndSubtractionWorks)
{
    Term termToTest(Constant(0));
    Term xToTheY(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));
    Term term1(createExpressionIfPossible({Term(11), Term("*"), xToTheY}));
    Term term2(createExpressionIfPossible({Term(13), Term("*"), xToTheY}));
    Term term3(Constant(0));
    TermsWithDetails termsWithDetails
    {TermWithDetails(term1, TermAssociationType::Negative),
                TermWithDetails(term2, TermAssociationType::Positive),
                TermWithDetails(term3, TermAssociationType::Negative)};

    accumulateTermsForAdditionAndSubtraction(termToTest, termsWithDetails);

    Term termToExpectPart1(createExpressionIfPossible({Term(-11), Term("*"), xToTheY}));
    Term termToExpectPart2(createExpressionIfPossible({Term(13), Term("*"), xToTheY}));
    Term termToExpect(createExpressionIfPossible({termToExpectPart1, Term("+"), termToExpectPart2}));
    EXPECT_EQ(termToExpect, termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsForMultiplicationAndDivisionWorks)
{
    Term termToTest(1);
    Term xToTheY(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));
    Term term1(createExpressionIfPossible({Term(11), Term("*"), xToTheY}));
    Term term2(createExpressionIfPossible({Term(13), Term("*"), xToTheY}));
    Term term3(1);
    TermsWithDetails termsWithDetails
    {TermWithDetails(term1, TermAssociationType::Negative),
                TermWithDetails(term2, TermAssociationType::Positive),
                TermWithDetails(term3, TermAssociationType::Negative)};

    accumulateTermsForMultiplicationAndDivision(termToTest, termsWithDetails);

    Term termToExpect(createExpressionIfPossible({Term(1), Term("/"), Term(11), Term("/"), xToTheY, Term("*"), Term(13), Term("*"), xToTheY}));
    EXPECT_EQ(termToExpect, termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsForRaiseToPowerWorks)
{
    Term termToTest(1);
    Term xToTheY(createExpressionIfPossible({Term("x"), Term("^"), Term("y")}));
    Term term1(createExpressionIfPossible({Term(11), Term("*"), xToTheY}));
    Term term2(createExpressionIfPossible({Term(13), Term("*"), xToTheY}));
    Term term3(1);
    TermsWithDetails termsWithDetails
    {TermWithDetails(term1, TermAssociationType::Negative),
                TermWithDetails(term2, TermAssociationType::Positive),
                TermWithDetails(term3, TermAssociationType::Negative)};

    accumulateTermsForRaiseToPower(termToTest, termsWithDetails);

    Term termToExpectPart1(createExpressionIfPossible({Term(11), Term("*"), xToTheY}));
    Term termToExpectPart2(createExpressionIfPossible({Term(13), Term("*"), xToTheY}));
    Term termToExpect(createExpressionIfPossible({termToExpectPart1, Term("^"), termToExpectPart2}));
    EXPECT_EQ(termToExpect, termToTest);
}

}

}