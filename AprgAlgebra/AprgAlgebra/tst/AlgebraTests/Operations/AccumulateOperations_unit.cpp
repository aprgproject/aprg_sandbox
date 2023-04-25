#include <Algebra/Operations/AccumulateOperations.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaNumberConstants;
using namespace std;

namespace alba {

namespace algebra {

TEST(AccumulateOperationsTest, AccumulateAndDoOperationOnTermDetailsWorks) {
    Term termToTest1(45);
    Term termToTest2(45);
    TermWithDetails termWithDetails1(Term(25), TermAssociationType::Positive);
    TermWithDetails termWithDetails2(Term(25), TermAssociationType::Negative);

    accumulateAndDoOperationOnTermDetails(termToTest1, OperatorLevel::AdditionAndSubtraction, termWithDetails1);
    accumulateAndDoOperationOnTermDetails(termToTest2, OperatorLevel::AdditionAndSubtraction, termWithDetails2);

    EXPECT_EQ(Term(70), termToTest1);
    EXPECT_EQ(Term(20), termToTest2);
}

TEST(AccumulateOperationsTest, AccumulateTermsForAdditionAndSubtractionWorks) {
    Term termToTest(0);
    Term xToTheY(createExpressionIfPossible({"x", "^", "y"}));
    Term term1(createExpressionIfPossible({11, "*", xToTheY}));
    Term term2(createExpressionIfPossible({13, "*", xToTheY}));
    Term term3(0);
    TermsWithDetails termsWithDetails{
        TermWithDetails(term1, TermAssociationType::Negative), TermWithDetails(term2, TermAssociationType::Positive),
        TermWithDetails(term3, TermAssociationType::Negative)};

    accumulateTermsForAdditionAndSubtraction(termToTest, termsWithDetails);

    Term termToExpectPart1(createExpressionIfPossible({-11, "*", xToTheY}));
    Term termToExpectPart2(createExpressionIfPossible({13, "*", xToTheY}));
    Term termToExpect(createExpressionIfPossible({termToExpectPart1, "+", termToExpectPart2}));
    EXPECT_EQ(termToExpect, termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsForAdditionAndSubtractionWorksWithEmptyTermAtTheStart) {
    Term termToTest;
    Term term1;
    Term term2(0);
    TermsWithDetails termsWithDetails{
        TermWithDetails(term1, TermAssociationType::Positive), TermWithDetails(term2, TermAssociationType::Positive)};

    accumulateTermsForAdditionAndSubtraction(termToTest, termsWithDetails);

    EXPECT_EQ(Term(0), termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsForAdditionAndSubtractionWorksWithNan) {
    Term termToTest;
    Term term1(1);
    Term term2(2);
    Term term3(ALBA_NUMBER_NOT_A_NUMBER);
    TermsWithDetails termsWithDetails{
        TermWithDetails(term1, TermAssociationType::Positive), TermWithDetails(term2, TermAssociationType::Positive),
        TermWithDetails(term3, TermAssociationType::Positive)};

    accumulateTermsForAdditionAndSubtraction(termToTest, termsWithDetails);

    EXPECT_TRUE(isNan(termToTest));
}

TEST(AccumulateOperationsTest, AccumulateTermsForMultiplicationAndDivisionWorks) {
    Term termToTest(1);
    Term xToTheY(createExpressionIfPossible({"x", "^", "y"}));
    Term term1(createExpressionIfPossible({11, "*", xToTheY}));
    Term term2(createExpressionIfPossible({13, "*", xToTheY}));
    Term term3(1);
    TermsWithDetails termsWithDetails{
        TermWithDetails(term1, TermAssociationType::Negative), TermWithDetails(term2, TermAssociationType::Positive),
        TermWithDetails(term3, TermAssociationType::Negative)};

    accumulateTermsForMultiplicationAndDivision(termToTest, termsWithDetails);

    Term termToExpect(createExpressionIfPossible({1, "/", 11, "/", xToTheY, "*", 13, "*", xToTheY}));
    EXPECT_EQ(termToExpect, termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsForMultiplicationAndDivisionWorksWithEmptyTermAtTheStart) {
    Term termToTest;
    Term term1;
    Term term2(1);
    TermsWithDetails termsWithDetails{
        TermWithDetails(term1, TermAssociationType::Positive), TermWithDetails(term2, TermAssociationType::Positive)};

    accumulateTermsForMultiplicationAndDivision(termToTest, termsWithDetails);

    EXPECT_EQ(Term(1), termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsForRaiseToPowerWorks) {
    Term termToTest(1);
    Term xToTheY(createExpressionIfPossible({"x", "^", "y"}));
    Term term1(createExpressionIfPossible({11, "*", xToTheY}));
    Term term2(createExpressionIfPossible({13, "*", xToTheY}));
    Term term3(1);
    TermsWithDetails termsWithDetails{
        TermWithDetails(term1, TermAssociationType::Negative), TermWithDetails(term2, TermAssociationType::Positive),
        TermWithDetails(term3, TermAssociationType::Negative)};

    accumulateTermsForRaiseToPower(termToTest, termsWithDetails);

    Term termToExpectPart1(createExpressionIfPossible({11, "*", xToTheY}));
    Term termToExpectPart2(createExpressionIfPossible({13, "*", xToTheY}));
    Term termToExpect(createExpressionIfPossible({termToExpectPart1, "^", termToExpectPart2}));
    EXPECT_EQ(termToExpect, termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsForRaiseToPowerWorksWithEmptyTermAtTheStart) {
    Term termToTest;
    Term term1;
    Term term2(1);
    TermsWithDetails termsWithDetails{
        TermWithDetails(term1, TermAssociationType::Positive), TermWithDetails(term2, TermAssociationType::Positive)};

    accumulateTermsForRaiseToPower(termToTest, termsWithDetails);

    EXPECT_EQ(Term(1), termToTest);
}

}  // namespace algebra

}  // namespace alba
