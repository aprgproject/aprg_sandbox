#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Limit/Continuity.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(ContinuityTest, GetContinuityDomainWorksOnSine)
{
    Term termToTest(sin(Term("x")));

    SolutionSet continuityDomain(getContinuityDomain(termToTest));

    AlbaNumberIntervals const& intervalToVerify(continuityDomain.getAcceptedIntervals());
    ASSERT_EQ(1U, intervalToVerify.size());
    EXPECT_EQ(createAllRealValuesInterval(), intervalToVerify.at(0));
}

TEST(ContinuityTest, GetContinuityDomainWorksOnCosine)
{
    Term termToTest(cos(Term("x")));

    SolutionSet continuityDomain(getContinuityDomain(termToTest));

    AlbaNumberIntervals const& intervalToVerify(continuityDomain.getAcceptedIntervals());
    ASSERT_EQ(1U, intervalToVerify.size());
    EXPECT_EQ(createAllRealValuesInterval(), intervalToVerify.at(0));
}

}

}