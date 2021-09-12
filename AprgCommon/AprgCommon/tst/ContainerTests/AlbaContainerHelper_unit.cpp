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
    PairOfIterators iteratorsToVerify1(getLowerAndUpperConstIteratorsInMap(sampleMap, 0U));
    EXPECT_EQ(firstIterator, iteratorsToVerify1.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify1.second);
    PairOfIterators iteratorsToVerify2(getLowerAndUpperConstIteratorsInMap(sampleMap, 6U));
    EXPECT_EQ(thirdIterator, iteratorsToVerify2.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify2.second);
    PairOfIterators iteratorsToVerify3(getLowerAndUpperConstIteratorsInMap(sampleMap, 1U));
    EXPECT_EQ(firstIterator, iteratorsToVerify3.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify3.second);
    PairOfIterators iteratorsToVerify4(getLowerAndUpperConstIteratorsInMap(sampleMap, 5U));
    EXPECT_EQ(thirdIterator, iteratorsToVerify4.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify4.second);
    PairOfIterators iteratorsToVerify5(getLowerAndUpperConstIteratorsInMap(sampleMap, 4U));
    EXPECT_EQ(secondIterator, iteratorsToVerify5.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify5.second);
    PairOfIterators iteratorsToVerify6(getLowerAndUpperConstIteratorsInMap(sampleMap, 3U));
    EXPECT_EQ(secondIterator, iteratorsToVerify6.first);
    EXPECT_EQ(secondIterator, iteratorsToVerify6.second);
}

TEST(ContainerSetTest, GetLowerAndUpperIteratorsInMap)
{
    map<unsigned int, unsigned int> sampleMap{{1, 10}, {3, 30}, {5, 50}};
    using MapIterator=map<unsigned int, unsigned int>::iterator;
    using PairOfIterators=pair<MapIterator, MapIterator>;

    MapIterator firstIterator=sampleMap.find(1);
    MapIterator secondIterator=sampleMap.find(3);
    MapIterator thirdIterator=sampleMap.find(5);
    PairOfIterators iteratorsToVerify1(getLowerAndUpperIteratorsInMap(sampleMap, 0U));
    EXPECT_EQ(firstIterator, iteratorsToVerify1.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify1.second);
    PairOfIterators iteratorsToVerify2(getLowerAndUpperIteratorsInMap(sampleMap, 6U));
    EXPECT_EQ(thirdIterator, iteratorsToVerify2.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify2.second);
    PairOfIterators iteratorsToVerify3(getLowerAndUpperIteratorsInMap(sampleMap, 1U));
    EXPECT_EQ(firstIterator, iteratorsToVerify3.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify3.second);
    PairOfIterators iteratorsToVerify4(getLowerAndUpperIteratorsInMap(sampleMap, 5U));
    EXPECT_EQ(thirdIterator, iteratorsToVerify4.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify4.second);
    PairOfIterators iteratorsToVerify5(getLowerAndUpperIteratorsInMap(sampleMap, 4U));
    EXPECT_EQ(secondIterator, iteratorsToVerify5.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify5.second);
    PairOfIterators iteratorsToVerify6(getLowerAndUpperIteratorsInMap(sampleMap, 3U));
    EXPECT_EQ(secondIterator, iteratorsToVerify6.first);
    EXPECT_EQ(secondIterator, iteratorsToVerify6.second);
}

TEST(ContainerSetTest, GetLowerAndUpperConstIteratorsInMultiMap)
{
    multimap<unsigned int, unsigned int> sampleMap{{1, 11}, {1, 12}, {3, 31}, {3, 32}, {5, 51}, {5, 52}};
    using MultimapIterator=multimap<unsigned int, unsigned int>::const_iterator;
    using PairOfIterators=pair<MultimapIterator, MultimapIterator>;

    MultimapIterator firstIterator=sampleMap.begin();
    MultimapIterator secondIterator=firstIterator;
    secondIterator++;
    MultimapIterator thirdIterator=secondIterator;
    thirdIterator++;
    MultimapIterator fourthIterator=thirdIterator;
    fourthIterator++;
    MultimapIterator fifthIterator=fourthIterator;
    fifthIterator++;
    MultimapIterator sixthIterator=fifthIterator;
    sixthIterator++;
    PairOfIterators iteratorsToVerify1(getLowerAndUpperConstIteratorsInMultiMap(sampleMap, 0U));
    EXPECT_EQ(firstIterator, iteratorsToVerify1.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify1.second);
    PairOfIterators iteratorsToVerify2(getLowerAndUpperConstIteratorsInMultiMap(sampleMap, 6U));
    EXPECT_EQ(sixthIterator, iteratorsToVerify2.first);
    EXPECT_EQ(sixthIterator, iteratorsToVerify2.second);
    PairOfIterators iteratorsToVerify3(getLowerAndUpperConstIteratorsInMultiMap(sampleMap, 1U));
    EXPECT_EQ(firstIterator, iteratorsToVerify3.first);
    EXPECT_EQ(secondIterator, iteratorsToVerify3.second);
    PairOfIterators iteratorsToVerify4(getLowerAndUpperConstIteratorsInMultiMap(sampleMap, 5U));
    EXPECT_EQ(fifthIterator, iteratorsToVerify4.first);
    EXPECT_EQ(sixthIterator, iteratorsToVerify4.second);
    PairOfIterators iteratorsToVerify5(getLowerAndUpperConstIteratorsInMultiMap(sampleMap, 4U));
    EXPECT_EQ(fourthIterator, iteratorsToVerify5.first);
    EXPECT_EQ(fifthIterator, iteratorsToVerify5.second);
    PairOfIterators iteratorsToVerify6(getLowerAndUpperConstIteratorsInMultiMap(sampleMap, 3U));
    EXPECT_EQ(thirdIterator, iteratorsToVerify6.first);
    EXPECT_EQ(fourthIterator, iteratorsToVerify6.second);
}

TEST(ContainerSetTest, GetLowerAndUpperIteratorsInMultiMap)
{
    multimap<unsigned int, unsigned int> sampleMap{{1, 11}, {1, 12}, {3, 31}, {3, 32}, {5, 51}, {5, 52}};
    using MultimapIterator=multimap<unsigned int, unsigned int>::iterator;
    using PairOfIterators=pair<MultimapIterator, MultimapIterator>;

    MultimapIterator firstIterator=sampleMap.begin();
    MultimapIterator secondIterator=firstIterator;
    secondIterator++;
    MultimapIterator thirdIterator=secondIterator;
    thirdIterator++;
    MultimapIterator fourthIterator=thirdIterator;
    fourthIterator++;
    MultimapIterator fifthIterator=fourthIterator;
    fifthIterator++;
    MultimapIterator sixthIterator=fifthIterator;
    sixthIterator++;
    PairOfIterators iteratorsToVerify1(getLowerAndUpperIteratorsInMultiMap(sampleMap, 0U));
    EXPECT_EQ(firstIterator, iteratorsToVerify1.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify1.second);
    PairOfIterators iteratorsToVerify2(getLowerAndUpperIteratorsInMultiMap(sampleMap, 6U));
    EXPECT_EQ(sixthIterator, iteratorsToVerify2.first);
    EXPECT_EQ(sixthIterator, iteratorsToVerify2.second);
    PairOfIterators iteratorsToVerify3(getLowerAndUpperIteratorsInMultiMap(sampleMap, 1U));
    EXPECT_EQ(firstIterator, iteratorsToVerify3.first);
    EXPECT_EQ(secondIterator, iteratorsToVerify3.second);
    PairOfIterators iteratorsToVerify4(getLowerAndUpperIteratorsInMultiMap(sampleMap, 5U));
    EXPECT_EQ(fifthIterator, iteratorsToVerify4.first);
    EXPECT_EQ(sixthIterator, iteratorsToVerify4.second);
    PairOfIterators iteratorsToVerify5(getLowerAndUpperIteratorsInMultiMap(sampleMap, 4U));
    EXPECT_EQ(fourthIterator, iteratorsToVerify5.first);
    EXPECT_EQ(fifthIterator, iteratorsToVerify5.second);
    PairOfIterators iteratorsToVerify6(getLowerAndUpperIteratorsInMultiMap(sampleMap, 3U));
    EXPECT_EQ(thirdIterator, iteratorsToVerify6.first);
    EXPECT_EQ(fourthIterator, iteratorsToVerify6.second);
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
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}
TEST(ContainerTest, RetrieveVectorOfIntegersFromFile)
{
    std::array<int, 4> temporaryArray{};    ofstream outputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    outputTestFile<<"18723"<<endl;
    outputTestFile<<"-608"<<endl;
    outputTestFile<<"-43735"<<endl;
    outputTestFile<<"23234"<<endl;
    outputTestFile.close();

    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    ASSERT_TRUE(inputTestFile.is_open());

    retrieveContentsOfContainerFromFile(inputTestFile, temporaryArray);

    ASSERT_EQ(4U, temporaryArray.size());
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
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}
TEST(ContainerTest, RetrieveArrayOfIntegersFromFile)
{
    vector<int> temporaryVector;    ofstream outputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    outputTestFile<<"18723"<<endl;
    outputTestFile<<"-608"<<endl;
    outputTestFile<<"-43735"<<endl;
    outputTestFile<<"23234"<<endl;
    outputTestFile.close();

    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    ASSERT_TRUE(inputTestFile.is_open());

    retrieveContentsOfContainerFromFile(inputTestFile, temporaryVector);

    ASSERT_EQ(4U, temporaryVector.size());
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
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}
TEST(ContainerTest, RetrieveSetOfIntegersFromFile)
{
    set<int> temporarySet;    ofstream outputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    outputTestFile<<"18723"<<endl;
    outputTestFile<<"-608"<<endl;
    outputTestFile<<"-43735"<<endl;
    outputTestFile<<"23234"<<endl;
    outputTestFile.close();

    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    ASSERT_TRUE(inputTestFile.is_open());

    retrieveContentsOfContainerFromFile(inputTestFile, temporarySet);

    ASSERT_EQ(4U, temporarySet.size());
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
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}
TEST(ContainerTest, RetrieveMapOfIntegersFromFile)
{
    map<int,int> temporaryMap;    ofstream outputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    outputTestFile<<"1"<<endl;
    outputTestFile<<"2"<<endl;
    outputTestFile<<"3"<<endl;
    outputTestFile<<"4"<<endl;
    outputTestFile.close();

    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    ASSERT_TRUE(inputTestFile.is_open());

    retrieveContentsOfContainerFromFile(inputTestFile, temporaryMap);

    ASSERT_EQ(2U, temporaryMap.size());
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
