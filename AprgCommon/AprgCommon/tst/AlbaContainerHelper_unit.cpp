#include <Container/AlbaContainerHelper.hpp>

#include <DirectoryConstants.hpp>
#include <File/AlbaFileReader.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace alba;
using namespace alba::containerHelper;
using namespace std;

TEST(ContainerSetTest, GetRangeFromSetBasedFromValue)
{
    set<int> sampleSet{-10,-5,1,2,4,5,23,50};
    EXPECT_EQ((pair<int,int>(-10, -10)), getRangeFromSetBasedFromValue(sampleSet, -100));
    EXPECT_EQ((pair<int,int>(-10, -5)), getRangeFromSetBasedFromValue(sampleSet, -10));
    EXPECT_EQ((pair<int,int>(50, 50)), getRangeFromSetBasedFromValue(sampleSet, 50));
    EXPECT_EQ((pair<int,int>(50, 50)), getRangeFromSetBasedFromValue(sampleSet, 10000));
    EXPECT_EQ((pair<int,int>(23, 50)), getRangeFromSetBasedFromValue(sampleSet, 23));
    EXPECT_EQ((pair<int,int>(5, 23)), getRangeFromSetBasedFromValue(sampleSet, 7));
}

TEST(ContainerTest, SaveVectorOfIntegersToFile)
{
    vector<int> sampleVector{0,23,97,4,82,379,482,37};
    ofstream outputTestFile(APRG_COMMON_TEST_FILE_TO_READ);

    saveContentsOfContainerToFile(outputTestFile, sampleVector);

    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ("0", fileReader.getLine());
    EXPECT_EQ("23", fileReader.getLine());
    EXPECT_EQ("97", fileReader.getLine());
    EXPECT_EQ("4", fileReader.getLine());
    EXPECT_EQ("82", fileReader.getLine());
    EXPECT_EQ("379", fileReader.getLine());
    EXPECT_EQ("482", fileReader.getLine());
    EXPECT_EQ("37", fileReader.getLine());
    EXPECT_EQ("", fileReader.getLine());
    EXPECT_FALSE(fileReader.isNotFinished());
}
