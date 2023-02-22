#include <Common/Randomizer/AlbaSimpleRandomizer.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba
{

TEST(AlbaSimpleRandomizerTest, RandomUniformValuesAreWithinLimits)
{
    AlbaSimpleRandomizer randomizer;
    int const minimumRandomValue(0);
    int const maximumRandomValue(9);
    for(int i=0; i<1000; i++)
    {
        int random(randomizer.getRandomValueInUniformDistribution(minimumRandomValue, maximumRandomValue));
        bool isWithinLimits = random>=minimumRandomValue && random<=maximumRandomValue;
        EXPECT_TRUE(isWithinLimits);
    }
}

TEST(AlbaSimpleRandomizerTest, RandomValuesAreUniformlyDistributed)
{
    AlbaSimpleRandomizer randomizer;
    int const minimumRandomValue(0);
    int const maximumRandomValue(9);
    int numberOfRandomValues(maximumRandomValue-minimumRandomValue+1);
    int const iterations(10000);
    int const allowedDeviation(static_cast<int>(iterations*0.1));
    vector<int> hitsForEachValue(static_cast<unsigned long>(numberOfRandomValues), 0);
    for(int i=0; i<iterations; i++)
    {
        int random(randomizer.getRandomValueInUniformDistribution(minimumRandomValue, maximumRandomValue));
        hitsForEachValue[static_cast<unsigned long>(random)]++;
    }

    ASSERT_FALSE(hitsForEachValue.empty());

    int minimumHits=hitsForEachValue.front();
    int maximumHits=hitsForEachValue.front();
    for(int hits : hitsForEachValue)
    {
        minimumHits = (minimumHits<hits) ? minimumHits : hits;
        maximumHits = (maximumHits>hits) ? maximumHits : hits;
    }

    int deviation(maximumHits-minimumHits);
    EXPECT_LE(deviation, allowedDeviation);
}

}
