#include <Equation/Constructs/MergeExpressionsByAdditionOrSubtraction.hpp>

#include <gtest/gtest.h>
using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace equation
{

TEST(MergeExpressionsByAdditionOrSubtractionTest, GetResultOfAddingAndSubtractingOfTermsWithExpressionsWorks)
{
    Term termToVerify(getResultOfAddingAndSubtractingOfTermsWithExpressions(TermsWithDetails{}));

    EXPECT_EQ(Term(), termToVerify);
}

}

}
