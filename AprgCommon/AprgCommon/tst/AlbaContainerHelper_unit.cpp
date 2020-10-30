#include <Container/AlbaContainerHelper.hpp>

#include <DirectoryConstants.hpp>
#include <File/AlbaFileReader.hpp>

#include <gtest/gtest.h>

#include <map>
#include <set>
#include <string>
#include <vector>

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
    vector<int> temporaryVector{0, -23, 4, 379,- 482, 37};
    ofstream outputTestFile(APRG_COMMON_TEST_FILE_TO_READ);

    saveContentsOfContainerToFile(outputTestFile, temporaryVector);
    outputTestFile.close();

    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ("0", fileReader.getLine());
    EXPECT_EQ("-23", fileReader.getLine());
    EXPECT_EQ("4", fileReader.getLine());
    EXPECT_EQ("379", fileReader.getLine());
    EXPECT_EQ("-482", fileReader.getLine());
    EXPECT_EQ("37", fileReader.getLine());
    EXPECT_EQ("", fileReader.getLine());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(ContainerTest, RetrieveVectorOfIntegersFromFile)
{
    vector<int> temporaryVector;
    ofstream outputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    outputTestFile<<"18723"<<endl;
    outputTestFile<<"-608"<<endl;
    outputTestFile<<"-43735"<<endl;
    outputTestFile<<"23234"<<endl;
    outputTestFile.close();

    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    ASSERT_TRUE(inputTestFile.is_open());

    retrieveContentsOfContainerFromFile(inputTestFile, temporaryVector);

    ASSERT_EQ(4u, temporaryVector.size());
    auto it = temporaryVector.begin();
    EXPECT_EQ(18723, *(it++));
    EXPECT_EQ(-608, *(it++));
    EXPECT_EQ(-43735, *(it++));
    EXPECT_EQ(23234, *(it++));
}

TEST(ContainerTest, GetStringFromContentsOfVector)
{
    vector<int> temporaryVector{23, -345, 5324, 1};
    EXPECT_EQ("23, -345, 5324, 1, ", getStringFromContentsOfContainer(temporaryVector, ", "));
}

TEST(ContainerTest, SaveSetOfIntegersToFile)
{
    set<int> temporarySet{0, -23, 4, 379,- 482, 37};
    ofstream outputTestFile(APRG_COMMON_TEST_FILE_TO_READ);

    saveContentsOfContainerToFile(outputTestFile, temporarySet);
    outputTestFile.close();

    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ("-482", fileReader.getLine());
    EXPECT_EQ("-23", fileReader.getLine());
    EXPECT_EQ("0", fileReader.getLine());
    EXPECT_EQ("4", fileReader.getLine());
    EXPECT_EQ("37", fileReader.getLine());
    EXPECT_EQ("379", fileReader.getLine());
    EXPECT_EQ("", fileReader.getLine());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(ContainerTest, RetrieveSetOfIntegersFromFile)
{
    set<int> temporarySet;
    ofstream outputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    outputTestFile<<"18723"<<endl;
    outputTestFile<<"-608"<<endl;
    outputTestFile<<"-43735"<<endl;
    outputTestFile<<"23234"<<endl;
    outputTestFile.close();

    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    ASSERT_TRUE(inputTestFile.is_open());

    retrieveContentsOfContainerFromFile(inputTestFile, temporarySet);

    ASSERT_EQ(4u, temporarySet.size());
    auto it = temporarySet.begin();
    EXPECT_EQ(-43735, *(it++));
    EXPECT_EQ(-608, *(it++));
    EXPECT_EQ(18723, *(it++));
    EXPECT_EQ(23234, *(it++));
}

TEST(ContainerTest, GetStringFromContentsOfSet)
{
    set<int> temporarySet{23, -345, 5324, 1};
    EXPECT_EQ("-345, 1, 23, 5324, ", getStringFromContentsOfContainer(temporarySet, ", "));
}

TEST(ContainerTest, SaveMapOfIntegersToFile)
{
    map<int,int> temporaryMap;
    temporaryMap[83] = 95;
    temporaryMap[2348] = 17;
    temporaryMap[-76] = 74;

    ofstream outputTestFile(APRG_COMMON_TEST_FILE_TO_READ);

    saveContentsOfContainerToFile(outputTestFile, temporaryMap);
    outputTestFile.close();

    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ("-76", fileReader.getLine());
    EXPECT_EQ("74", fileReader.getLine());
    EXPECT_EQ("83", fileReader.getLine());
    EXPECT_EQ("95", fileReader.getLine());
    EXPECT_EQ("2348", fileReader.getLine());
    EXPECT_EQ("17", fileReader.getLine());
    EXPECT_EQ("", fileReader.getLine());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(ContainerTest, RetrieveMapOfIntegersFromFile)
{
    map<int,int> temporaryMap;
    ofstream outputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    outputTestFile<<"1"<<endl;
    outputTestFile<<"2"<<endl;
    outputTestFile<<"3"<<endl;
    outputTestFile<<"4"<<endl;
    outputTestFile.close();

    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    ASSERT_TRUE(inputTestFile.is_open());

    retrieveContentsOfContainerFromFile(inputTestFile, temporaryMap);

    ASSERT_EQ(2u, temporaryMap.size());
    auto it = temporaryMap.begin();
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(2, it->second);
    it++;
    EXPECT_EQ(3, it->first);
    EXPECT_EQ(4, it->second);
}

TEST(ContainerTest, GetStringFromContentsOfMap)
{
    map<int,int> temporaryMap;
    temporaryMap[83] = 95;
    temporaryMap[2348] = 17;
    temporaryMap[-76] = 74;
    EXPECT_EQ("[-76:74], [83:95], [2348:17], ", getStringFromContentsOfContainer(temporaryMap, ", "));
}
