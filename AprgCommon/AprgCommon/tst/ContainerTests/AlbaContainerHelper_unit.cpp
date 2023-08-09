#include <Container/AlbaContainerHelper.hpp>
#include <DirectoryConstants.hpp>
#include <File/AlbaFileReader.hpp>

#include <gtest/gtest.h>

#include <array>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace alba::containerHelper;
using namespace std;

namespace alba
{

TEST(ContainerSetTest, GetLowerAndUpperValuesInSet)
{
    set<int> sampleSet{-10,-5,1,2,4,5,23,50};
    EXPECT_EQ((pair<int,int>(-10, -10)), getLowerAndUpperValuesInSet(sampleSet, -100));
    EXPECT_EQ((pair<int,int>(-10, -10)), getLowerAndUpperValuesInSet(sampleSet, -10));
    EXPECT_EQ((pair<int,int>(50, 50)), getLowerAndUpperValuesInSet(sampleSet, 50));
    EXPECT_EQ((pair<int,int>(50, 50)), getLowerAndUpperValuesInSet(sampleSet, 10000));
    EXPECT_EQ((pair<int,int>(23, 23)), getLowerAndUpperValuesInSet(sampleSet, 23));
    EXPECT_EQ((pair<int,int>(5, 23)), getLowerAndUpperValuesInSet(sampleSet, 7));
}

TEST(ContainerSetTest, GetLowerAndUpperConstIteratorsInMap)
{
    map<unsigned int, unsigned int> sampleMap{{1, 10}, {3, 30}, {5, 50}};
    using MapIterator=map<unsigned int, unsigned int>::const_iterator;
    using PairOfIterators=pair<MapIterator, MapIterator>;

    MapIterator firstIterator=sampleMap.find(1);
    MapIterator secondIterator=sampleMap.find(3);
    MapIterator thirdIterator=sampleMap.find(5);
    PairOfIterators iteratorsToVerify1(getLowerAndUpperConstIteratorsInMap(sampleMap, 0u));
    EXPECT_EQ(firstIterator, iteratorsToVerify1.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify1.second);
    PairOfIterators iteratorsToVerify2(getLowerAndUpperConstIteratorsInMap(sampleMap, 6u));
    EXPECT_EQ(thirdIterator, iteratorsToVerify2.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify2.second);
    PairOfIterators iteratorsToVerify3(getLowerAndUpperConstIteratorsInMap(sampleMap, 1u));
    EXPECT_EQ(firstIterator, iteratorsToVerify3.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify3.second);
    PairOfIterators iteratorsToVerify4(getLowerAndUpperConstIteratorsInMap(sampleMap, 5u));
    EXPECT_EQ(thirdIterator, iteratorsToVerify4.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify4.second);
    PairOfIterators iteratorsToVerify5(getLowerAndUpperConstIteratorsInMap(sampleMap, 4u));
    EXPECT_EQ(secondIterator, iteratorsToVerify5.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify5.second);
}

TEST(ContainerSetTest, GetLowerAndUpperIteratorsInMap)
{
    map<unsigned int, unsigned int> sampleMap{{1, 10}, {3, 30}, {5, 50}};
    using MapIterator=map<unsigned int, unsigned int>::iterator;
    using PairOfIterators=pair<MapIterator, MapIterator>;

    MapIterator firstIterator=sampleMap.find(1);
    MapIterator secondIterator=sampleMap.find(3);
    MapIterator thirdIterator=sampleMap.find(5);
    PairOfIterators iteratorsToVerify1(getLowerAndUpperIteratorsInMap(sampleMap, 0u));
    EXPECT_EQ(firstIterator, iteratorsToVerify1.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify1.second);
    PairOfIterators iteratorsToVerify2(getLowerAndUpperIteratorsInMap(sampleMap, 6u));
    EXPECT_EQ(thirdIterator, iteratorsToVerify2.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify2.second);
    PairOfIterators iteratorsToVerify3(getLowerAndUpperIteratorsInMap(sampleMap, 1u));
    EXPECT_EQ(firstIterator, iteratorsToVerify3.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify3.second);
    PairOfIterators iteratorsToVerify4(getLowerAndUpperIteratorsInMap(sampleMap, 5u));
    EXPECT_EQ(thirdIterator, iteratorsToVerify4.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify4.second);
    PairOfIterators iteratorsToVerify5(getLowerAndUpperIteratorsInMap(sampleMap, 4u));
    EXPECT_EQ(secondIterator, iteratorsToVerify5.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify5.second);
}

TEST(ContainerTest, SaveVectorOfIntegersToFile)
{
    std::array<int, 6> temporaryArray{0, -23, 4, 379,- 482, 37};
    ofstream outputTestFile(APRG_COMMON_TEST_FILE_TO_READ);

    saveContentsOfContainerToFile(outputTestFile, temporaryArray);
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
    std::array<int, 4> temporaryArray;
    ofstream outputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    outputTestFile<<"18723"<<endl;
    outputTestFile<<"-608"<<endl;
    outputTestFile<<"-43735"<<endl;
    outputTestFile<<"23234"<<endl;
    outputTestFile.close();

    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    ASSERT_TRUE(inputTestFile.is_open());

    retrieveContentsOfContainerFromFile(inputTestFile, temporaryArray);

    ASSERT_EQ(4u, temporaryArray.size());
    auto it = temporaryArray.begin();
    EXPECT_EQ(18723, *(it++));
    EXPECT_EQ(-608, *(it++));
    EXPECT_EQ(-43735, *(it++));
    EXPECT_EQ(23234, *(it++));
}

TEST(ContainerTest, GetStringFromContentsOfArray)
{
    std::array<int, 4> temporaryArray{23, -345, 5324, 1};
    EXPECT_EQ("23, -345, 5324, 1, ", getStringFromContentsOfContainer(temporaryArray, ", "));
}


TEST(ContainerTest, SaveArrayOfIntegersToFile)
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

TEST(ContainerTest, RetrieveArrayOfIntegersFromFile)
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

}
