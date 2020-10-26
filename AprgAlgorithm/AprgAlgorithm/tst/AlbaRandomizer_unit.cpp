#include <Randomizer/AlbaRandomizer.hpp>

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

using namespace alba;
using namespace std;

TEST(AlbaRandomizer, RandomUniformValuesAreWithinLimits)
{
    AlbaRandomizer randomizer;
    int const minimumRandomValue(0);
    int const maximumRandomValue(9);
    for(int i=0; i<1000; i++)
    {
        int random(randomizer.getRandomValueInUniformDistribution(minimumRandomValue, maximumRandomValue));
        bool isWithinLimits = random>=minimumRandomValue && random<=maximumRandomValue;
        EXPECT_TRUE(isWithinLimits);
    }
}

TEST(AlbaRandomizer, RandomValuesAreUniformlyDistributed)
{
    AlbaRandomizer randomizer;
    int const minimumRandomValue(0);
    int const maximumRandomValue(9);
    int numberOfRandomValues(maximumRandomValue-minimumRandomValue+1);
    int const iterations(10000);
    int const allowedDeviation(iterations*0.1);
    vector<int> hitsForEachValue(numberOfRandomValues, 0);
    for(int i=0; i<iterations; i++)
    {
        int random(randomizer.getRandomValueInUniformDistribution(minimumRandomValue, maximumRandomValue));
        hitsForEachValue[random]++;
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



