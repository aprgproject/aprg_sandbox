#include <Algebra/Series/SummationSeriesOfArithmeticSeries.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{


TEST(SummationSeriesOfArithmeticSeriesTest, IsConvergentWorks)
{
    SummationSeriesOfArithmeticSeries seriesWithDifferenceLessThanOne(1, AlbaNumber::createFraction(1, 2));

    EXPECT_TRUE(seriesWithDifferenceLessThanOne.hasAValidSummationModel());
    EXPECT_FALSE(seriesWithDifferenceLessThanOne.isConvergent());
}

}

}
