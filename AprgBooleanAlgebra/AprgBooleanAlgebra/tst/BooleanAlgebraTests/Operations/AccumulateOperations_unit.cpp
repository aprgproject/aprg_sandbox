#include <BooleanAlgebra/Operations/AccumulateOperations.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace booleanAlgebra
{


TEST(AccumulateOperationsTest, AccumulateAndDoOperationOnWrappedTermWorks)
{
    Term termToTest1(true);
    Term termToTest2(true);

    accumulateAndDoOperationOnWrappedTerm(termToTest1, OperatorType::And, Term(true));
    accumulateAndDoOperationOnWrappedTerm(termToTest2, OperatorType::And, Term(false));

    EXPECT_EQ(Term(true), termToTest1);
    EXPECT_EQ(Term(false), termToTest2);
}

TEST(AccumulateOperationsTest, AccumulateTermsWithAndOperationWorks)
{
    Term termToTest(true);
    Term term1(createExpressionIfPossible({"a", "&", "b"}));
    Term term2(createExpressionIfPossible({"c", "&", "d"}));
    Term term3(createExpressionIfPossible({"e", "&", "f"}));
    Term term4(createExpressionIfPossible({"g", "&", "h"}));
    WrappedTerms wrappedTerms{term1, term2, term3, term4};

    accumulateTermsWithAndOperation(termToTest, wrappedTerms);

    Term termToExpect(createExpressionIfPossible({"a", "&", "b", "&", "c", "&", "d", "&", "e", "&", "f", "&", "g", "&", "h"}));
    EXPECT_EQ(termToExpect, termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsWithAndOperationWorksWithEmptyTermAtTheStart)
{
    Term termToTest;
    Term term1;
    Term term2(true);
    WrappedTerms wrappedTerms{term1, term2};

    accumulateTermsWithAndOperation(termToTest, wrappedTerms);

    EXPECT_EQ(Term(true), termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsWithOrOperationWorks)
{
    Term termToTest(false);
    Term term1(createExpressionIfPossible({"a", "|", "b"}));
    Term term2(createExpressionIfPossible({"c", "|", "d"}));
    Term term3(createExpressionIfPossible({"e", "|", "f"}));
    Term term4(createExpressionIfPossible({"g", "|", "h"}));
    WrappedTerms wrappedTerms{term1, term2, term3, term4};

    accumulateTermsWithOrOperation(termToTest, wrappedTerms);

    Term termToExpect(createExpressionIfPossible({"a", "|", "b", "|", "c", "|", "d", "|", "e", "|", "f", "|", "g", "|", "h"}));
    EXPECT_EQ(termToExpect, termToTest);
}

TEST(AccumulateOperationsTest, AccumulateTermsWithOrOperationWorksWithEmptyTermAtTheStart)
{
    Term termToTest;
    Term term1;
    Term term2(false);
    WrappedTerms wrappedTerms{term1, term2};

    accumulateTermsWithOrOperation(termToTest, wrappedTerms);

    EXPECT_EQ(Term(false), termToTest);
}


}

}
