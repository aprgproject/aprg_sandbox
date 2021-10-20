#include <Algebra/Integration/IntegrationGeometryUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(IntegrationGeometryUtilitiesTest, GetAreaInBetweenTwoTermsInAnIntervalWorks)
{
    Term lowerTerm(Monomial(1, {{"x", 2}}));
    Term higherTerm(Polynomial{Monomial(-1, {{"x", 2}}), Monomial(4, {{"x", 1}})});

    EXPECT_EQ(Term(AlbaNumber::createFraction(-8, 3)), getAreaInBetweenTwoTermsInAnInterval(lowerTerm, higherTerm, "x", 0, 2));
}

}

}
