#include <Container/AlbaContainerHelper.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace std;
using namespace alba::containerHelper;

TEST(ContainerSetTest, GetInclusiveRangeFromSet)
{
    set<int> sampleSet{-10,-5,1,2,4,5,23,50};
    EXPECT_EQ((pair<int,int>(-10, -10)), getInclusiveRangeFromSet(sampleSet, -100));
    EXPECT_EQ((pair<int,int>(-10, -5)), getInclusiveRangeFromSet(sampleSet, -10));
    EXPECT_EQ((pair<int,int>(50, 50)), getInclusiveRangeFromSet(sampleSet, 50));
    EXPECT_EQ((pair<int,int>(50, 50)), getInclusiveRangeFromSet(sampleSet, 10000));
    EXPECT_EQ((pair<int,int>(23, 50)), getInclusiveRangeFromSet(sampleSet, 23));
    EXPECT_EQ((pair<int,int>(5, 23)), getInclusiveRangeFromSet(sampleSet, 7));
}



