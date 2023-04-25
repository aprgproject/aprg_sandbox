#include <Algebra/Series/SpecificSeries/PSeries.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algebra {

TEST(PSeriesTest, IsSummationModelValidWorks) {
    PSeries series(2);

    EXPECT_FALSE(series.isSummationModelValid());
}

TEST(PSeriesTest, GetValueAtIndexWorks) {
    PSeries series(2);

    EXPECT_EQ(Term(1), series.getValueAtIndex(0));
    EXPECT_EQ(Term(AlbaNumber::createFraction(5, 4)), series.getValueAtIndex(1));
    EXPECT_EQ(Term(AlbaNumber::createFraction(49, 36)), series.getValueAtIndex(2));
    EXPECT_EQ(Term(AlbaNumber::createFraction(205, 144)), series.getValueAtIndex(3));
}

}  // namespace algebra

}  // namespace alba
