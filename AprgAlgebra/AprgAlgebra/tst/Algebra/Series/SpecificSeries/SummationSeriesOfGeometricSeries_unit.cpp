#include <Algebra/Series/SpecificSeries/SummationSeriesOfGeometricSeries.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

namespace algebra
{

TEST(SummationSeriesOfGeometricSeriesTest, IsConvergentWorks)
{
    SummationSeriesOfGeometricSeries seriesWithMultiplierLessThanOne(1, AlbaNumber::createFraction(1, 2));
    SummationSeriesOfGeometricSeries seriesWithMultiplierEqualsToOne(1, 1);
    SummationSeriesOfGeometricSeries seriesWithMultiplierMoreThanOne(1, 2);

    EXPECT_TRUE(seriesWithMultiplierLessThanOne.isSummationModelValid());
    EXPECT_TRUE(seriesWithMultiplierEqualsToOne.isSummationModelValid());
    EXPECT_TRUE(seriesWithMultiplierMoreThanOne.isSummationModelValid());
    EXPECT_TRUE(seriesWithMultiplierLessThanOne.isConvergent());
    EXPECT_FALSE(seriesWithMultiplierEqualsToOne.isConvergent());
    EXPECT_FALSE(seriesWithMultiplierMoreThanOne.isConvergent());}

}
}
