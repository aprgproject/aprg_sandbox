#include <BooleanAlgebra/Simplification/SimplificationUtilities.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace booleanAlgebra
{

namespace Simplification
{

TEST(SimplificationUtilitiesTest, SimplifyAndCopyTermsAndChangeOperatorLevelIfNeededWorksForOneTerm)
{
    WrappedTerms inputWrappedTerms;
    inputWrappedTerms.emplace_back(Term("x"));
    OperatorLevel operatorLevel(OperatorLevel::Unknown);
    WrappedTerms outputWrappedTerms;

    simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(outputWrappedTerms, operatorLevel, inputWrappedTerms);

    WrappedTerms expectedWrappedTerms;
    expectedWrappedTerms.emplace_back(Term("x"));
    EXPECT_EQ(expectedWrappedTerms, outputWrappedTerms);
}

TEST(SimplificationUtilitiesTest, SimplifyAndCopyTermsAndChangeOperatorLevelIfNeededWorksForOneTermWithManyExpressions)
{
    Term oneTerm(createExpressionInAnExpression(createExpressionInAnExpression(createAndWrapExpressionFromATerm("x"))));
    WrappedTerms inputWrappedTerms;
    inputWrappedTerms.emplace_back(oneTerm);
    OperatorLevel operatorLevel(OperatorLevel::Unknown);
    WrappedTerms outputWrappedTerms;

    simplifyAndCopyTermsAndChangeOperatorLevelIfNeeded(outputWrappedTerms, operatorLevel, inputWrappedTerms);

    WrappedTerms expectedWrappedTerms;
    expectedWrappedTerms.emplace_back(Term("x"));
    EXPECT_EQ(expectedWrappedTerms, outputWrappedTerms);
}

}

}

}
