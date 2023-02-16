#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <CommonTests/DirectoryConstants.hpp>

#include <gtest/gtest.h>

#include <array>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

namespace alba
{

namespace containerHelper
{

TEST(ContainerTest, GetDelimeterBasedOnFormatWorks)
{
    EXPECT_EQ(", ", getDelimeterBasedOnFormat(StreamFormat::String));
    EXPECT_EQ("\n", getDelimeterBasedOnFormat(StreamFormat::File));
}

TEST(ContainerTest, GetLowerAndUpperConstIteratorsForNonSetWorks)
{
    vector<int> sortedVector{-10,-5,1,2,4,5,23,50};

    auto iteratorPairToVerify(getLowerAndUpperConstIteratorsForNonSet(sortedVector, 7));

    EXPECT_EQ(5, *(iteratorPairToVerify.first));
    EXPECT_EQ(23, *(iteratorPairToVerify.second));
}

TEST(ContainerTest, GetLowerAndUpperValuesForNonSetWorks)
{
    vector<int> sortedVector{-10,-5,1,2,4,5,23,50};

    EXPECT_EQ((pair<int,int>(-10, -10)), getLowerAndUpperValuesForNonSet(sortedVector, -100));
    EXPECT_EQ((pair<int,int>(-10, -10)), getLowerAndUpperValuesForNonSet(sortedVector, -10));
    EXPECT_EQ((pair<int,int>(50, 50)), getLowerAndUpperValuesForNonSet(sortedVector, 50));
    EXPECT_EQ((pair<int,int>(50, 50)), getLowerAndUpperValuesForNonSet(sortedVector, 10000));
    EXPECT_EQ((pair<int,int>(23, 23)), getLowerAndUpperValuesForNonSet(sortedVector, 23));
    EXPECT_EQ((pair<int,int>(5, 23)), getLowerAndUpperValuesForNonSet(sortedVector, 7));
}

TEST(ContainerTest, CountItemsInBetweenForNonSetWorks)
{
    vector<char> sortedVector{'A', 'C', 'E', 'H', 'M', 'R', 'S', 'X'};

    EXPECT_EQ(5U, countItemsInBetweenForNonSet(sortedVector, 'E', 'S'));
    EXPECT_EQ(5U, countItemsInBetweenForNonSet(sortedVector, 'E', 'T'));
    EXPECT_EQ(4U, countItemsInBetweenForNonSet(sortedVector, 'F', 'T'));
}

TEST(ContainerTest, GetItemsInBetweenForNonSetWorks)
{
    vector<char> sortedVector{'A', 'C', 'E', 'H', 'M', 'R', 'S', 'X'};

    vector<char> expectedVector1{'E', 'H', 'M', 'R', 'S'};
    vector<char> expectedVector2{'E', 'H', 'M', 'R', 'S'};
    vector<char> expectedVector3{'H', 'M', 'R', 'S'};
    EXPECT_EQ(expectedVector1, getItemsInBetweenForNonSet(sortedVector, 'E', 'S'));
    EXPECT_EQ(expectedVector2, getItemsInBetweenForNonSet(sortedVector, 'E', 'T'));
    EXPECT_EQ(expectedVector3, getItemsInBetweenForNonSet(sortedVector, 'F', 'T'));
}

TEST(ContainerTest, GetLowerAndUpperConstIteratorsForSetWorks)
{
    set<int> sampleSet{-10,-5,1,2,4,5,23,50};

    auto iteratorPairToVerify(getLowerAndUpperConstIteratorsForNonSet(sampleSet, 7));

    EXPECT_EQ(5, *(iteratorPairToVerify.first));
    EXPECT_EQ(23, *(iteratorPairToVerify.second));
}

TEST(ContainerTest, GetLowerAndUpperValuesForSetWorks)
{
    set<int> sampleSet{-10,-5,1,2,4,5,23,50};

    EXPECT_EQ((pair<int,int>(-10, -10)), getLowerAndUpperValuesForNonSet(sampleSet, -100));
    EXPECT_EQ((pair<int,int>(-10, -10)), getLowerAndUpperValuesForNonSet(sampleSet, -10));
    EXPECT_EQ((pair<int,int>(50, 50)), getLowerAndUpperValuesForNonSet(sampleSet, 50));
    EXPECT_EQ((pair<int,int>(50, 50)), getLowerAndUpperValuesForNonSet(sampleSet, 10000));
    EXPECT_EQ((pair<int,int>(23, 23)), getLowerAndUpperValuesForNonSet(sampleSet, 23));
    EXPECT_EQ((pair<int,int>(5, 23)), getLowerAndUpperValuesForNonSet(sampleSet, 7));
}

TEST(ContainerTest, CountItemsInBetweenForSetWorks)
{
    set<char> sampleSet{'A', 'C', 'E', 'H', 'M', 'R', 'S', 'X'};

    EXPECT_EQ(5U, countItemsInBetweenForNonSet(sampleSet, 'E', 'S'));
    EXPECT_EQ(5U, countItemsInBetweenForNonSet(sampleSet, 'E', 'T'));
    EXPECT_EQ(4U, countItemsInBetweenForNonSet(sampleSet, 'F', 'T'));
}

TEST(ContainerTest, GetItemsInBetweenForSetWorks)
{
    set<char> sampleSet{'A', 'C', 'E', 'H', 'M', 'R', 'S', 'X'};

    set<char> expectedSet1{'E', 'H', 'M', 'R', 'S'};
    set<char> expectedSet2{'E', 'H', 'M', 'R', 'S'};
    set<char> expectedSet3{'H', 'M', 'R', 'S'};
    EXPECT_EQ(expectedSet1, getItemsInBetweenForNonSet(sampleSet, 'E', 'S'));
    EXPECT_EQ(expectedSet2, getItemsInBetweenForNonSet(sampleSet, 'E', 'T'));
    EXPECT_EQ(expectedSet3, getItemsInBetweenForNonSet(sampleSet, 'F', 'T'));
}

TEST(ContainerTest, GetLowerAndUpperConstIteratorsInMapWorks)
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

TEST(ContainerTest, GetLowerAndUpperIteratorsInMapWorks)
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

TEST(ContainerTest, GetLowerAndUpperConstIteratorsInMapWorksOnMultiMap)
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
    PairOfIterators iteratorsToVerify1(getLowerAndUpperConstIteratorsInMap(sampleMap, 0U));
    EXPECT_EQ(firstIterator, iteratorsToVerify1.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify1.second);
    PairOfIterators iteratorsToVerify2(getLowerAndUpperConstIteratorsInMap(sampleMap, 6U));
    EXPECT_EQ(sixthIterator, iteratorsToVerify2.first);
    EXPECT_EQ(sixthIterator, iteratorsToVerify2.second);
    PairOfIterators iteratorsToVerify3(getLowerAndUpperConstIteratorsInMap(sampleMap, 1U));
    EXPECT_EQ(firstIterator, iteratorsToVerify3.first);
    EXPECT_EQ(secondIterator, iteratorsToVerify3.second);
    PairOfIterators iteratorsToVerify4(getLowerAndUpperConstIteratorsInMap(sampleMap, 5U));
    EXPECT_EQ(fifthIterator, iteratorsToVerify4.first);
    EXPECT_EQ(sixthIterator, iteratorsToVerify4.second);
    PairOfIterators iteratorsToVerify5(getLowerAndUpperConstIteratorsInMap(sampleMap, 4U));
    EXPECT_EQ(fourthIterator, iteratorsToVerify5.first);
    EXPECT_EQ(fifthIterator, iteratorsToVerify5.second);
    PairOfIterators iteratorsToVerify6(getLowerAndUpperConstIteratorsInMap(sampleMap, 3U));
    EXPECT_EQ(thirdIterator, iteratorsToVerify6.first);
    EXPECT_EQ(fourthIterator, iteratorsToVerify6.second);
}

TEST(ContainerTest, GetLowerAndUpperIteratorsInMapWorksOnMultiMap)
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
    PairOfIterators iteratorsToVerify1(getLowerAndUpperIteratorsInMap(sampleMap, 0U));
    EXPECT_EQ(firstIterator, iteratorsToVerify1.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify1.second);
    PairOfIterators iteratorsToVerify2(getLowerAndUpperIteratorsInMap(sampleMap, 6U));
    EXPECT_EQ(sixthIterator, iteratorsToVerify2.first);
    EXPECT_EQ(sixthIterator, iteratorsToVerify2.second);
    PairOfIterators iteratorsToVerify3(getLowerAndUpperIteratorsInMap(sampleMap, 1U));
    EXPECT_EQ(firstIterator, iteratorsToVerify3.first);
    EXPECT_EQ(secondIterator, iteratorsToVerify3.second);
    PairOfIterators iteratorsToVerify4(getLowerAndUpperIteratorsInMap(sampleMap, 5U));
    EXPECT_EQ(fifthIterator, iteratorsToVerify4.first);
    EXPECT_EQ(sixthIterator, iteratorsToVerify4.second);
    PairOfIterators iteratorsToVerify5(getLowerAndUpperIteratorsInMap(sampleMap, 4U));
    EXPECT_EQ(fourthIterator, iteratorsToVerify5.first);
    EXPECT_EQ(fifthIterator, iteratorsToVerify5.second);
    PairOfIterators iteratorsToVerify6(getLowerAndUpperIteratorsInMap(sampleMap, 3U));
    EXPECT_EQ(thirdIterator, iteratorsToVerify6.first);
    EXPECT_EQ(fourthIterator, iteratorsToVerify6.second);
}

TEST(ContainerTest, GetUnderlyingContainerWorksOnStack)
{
    using Adapter=std::stack<unsigned int>;
    Adapter adapter({1U, 2U, 3U});

    Adapter::container_type const& containerToVerify(getUnderlyingContainer(adapter));

    Adapter::container_type containerToExpect{1U, 2U, 3U};
    EXPECT_EQ(containerToExpect, containerToVerify);
}

TEST(ContainerTest, GetUnderlyingContainerReferenceWorksOnStack)
{
    using Adapter=std::stack<unsigned int>;
    Adapter adapter({1U, 2U, 3U});

    Adapter::container_type& containerToVerify(getUnderlyingContainerReference(adapter));
    containerToVerify[0] = 4U;
    containerToVerify[1] = 5U;
    containerToVerify[2] = 6U;

    ASSERT_EQ(3U, adapter.size());
    EXPECT_EQ(6U, adapter.top());
    adapter.pop();
    EXPECT_EQ(5U, adapter.top());
    adapter.pop();
    EXPECT_EQ(4U, adapter.top());
    adapter.pop();
    EXPECT_TRUE(adapter.empty());
}

TEST(ContainerTest, SaveContentsToStreamWorksForAVectorOfIntegersToFile)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    array<int, 6> temporaryArray{0, -23, 4, 379,- 482, 37};
    ofstream outputTestFile(testFilePath.getFullPath());

    saveContentsToStream(outputTestFile, temporaryArray, StreamFormat::File);
    outputTestFile.close();

    ifstream inputTestFile(testFilePath.getFullPath());
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

TEST(ContainerTest, SaveContentsToStreamWorksForAnArrayOfIntegersToFile)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    vector<int> temporaryVector{0, -23, 4, 379,- 482, 37};
    ofstream outputTestFile(testFilePath.getFullPath());

    saveContentsToStream(outputTestFile, temporaryVector, StreamFormat::File);
    outputTestFile.close();

    ifstream inputTestFile(testFilePath.getFullPath());
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

TEST(ContainerTest, SaveContentsToStreamWorksForASetOfIntegersToFile)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    set<int> temporarySet{0, -23, 4, 379,- 482, 37};
    ofstream outputTestFile(testFilePath.getFullPath());

    saveContentsToStream(outputTestFile, temporarySet, StreamFormat::File);
    outputTestFile.close();

    ifstream inputTestFile(testFilePath.getFullPath());
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

TEST(ContainerTest, SaveContentsToStreamWorksForAMapOfIntegersToFile)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    map<int,int> temporaryMap;
    temporaryMap[83] = 95;
    temporaryMap[2348] = 17;
    temporaryMap[-76] = 74;
    ofstream outputTestFile(testFilePath.getFullPath());

    saveContentsToStream(outputTestFile, temporaryMap, StreamFormat::File);
    outputTestFile.close();

    ifstream inputTestFile(testFilePath.getFullPath());
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

TEST(ContainerTest, FetrieveContentsFromStreamWorksForAVectorOfIntegersFromFile)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    array<int, 4> temporaryArray{};
    ofstream outputTestFile(testFilePath.getFullPath());
    outputTestFile<<"18723"<<endl;
    outputTestFile<<"-608"<<endl;
    outputTestFile<<"-43735"<<endl;
    outputTestFile<<"23234"<<endl;
    outputTestFile.close();
    ifstream inputTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());

    retrieveContentsFromStream(inputTestFile, temporaryArray);

    ASSERT_EQ(4U, temporaryArray.size());
    auto it = temporaryArray.begin();
    EXPECT_EQ(18723, *(it++));
    EXPECT_EQ(-608, *(it++));
    EXPECT_EQ(-43735, *(it++));
    EXPECT_EQ(23234, *(it++));
}

TEST(ContainerTest, FetrieveContentsFromStreamWorksForAnArrayOfIntegersFromFile)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    vector<int> temporaryVector;
    ofstream outputTestFile(testFilePath.getFullPath());
    outputTestFile<<"18723"<<endl;
    outputTestFile<<"-608"<<endl;
    outputTestFile<<"-43735"<<endl;
    outputTestFile<<"23234"<<endl;
    outputTestFile.close();
    ifstream inputTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());

    retrieveContentsFromStream(inputTestFile, temporaryVector);

    ASSERT_EQ(4U, temporaryVector.size());
    auto it = temporaryVector.begin();
    EXPECT_EQ(18723, *(it++));
    EXPECT_EQ(-608, *(it++));
    EXPECT_EQ(-43735, *(it++));
    EXPECT_EQ(23234, *(it++));
}

TEST(ContainerTest, FetrieveContentsFromStreamWorksForASetOfIntegersFromFile)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    set<int> temporarySet;
    ofstream outputTestFile(testFilePath.getFullPath());
    outputTestFile<<"18723"<<endl;
    outputTestFile<<"-608"<<endl;
    outputTestFile<<"-43735"<<endl;
    outputTestFile<<"23234"<<endl;
    outputTestFile.close();
    ifstream inputTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());

    retrieveContentsFromStream(inputTestFile, temporarySet);

    ASSERT_EQ(4U, temporarySet.size());
    auto it = temporarySet.begin();
    EXPECT_EQ(-43735, *(it++));
    EXPECT_EQ(-608, *(it++));
    EXPECT_EQ(18723, *(it++));
    EXPECT_EQ(23234, *(it++));
}

TEST(ContainerTest, FetrieveContentsFromStreamWorksForAMapOfIntegersFromFile)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    map<int,int> temporaryMap;
    ofstream outputTestFile(testFilePath.getFullPath());
    outputTestFile<<"1"<<endl;
    outputTestFile<<"2"<<endl;
    outputTestFile<<"3"<<endl;
    outputTestFile<<"4"<<endl;
    outputTestFile.close();
    ifstream inputTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());

    retrieveContentsFromStream(inputTestFile, temporaryMap);

    ASSERT_EQ(2U, temporaryMap.size());
    auto it = temporaryMap.begin();
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(2, it->second);
    it++;
    EXPECT_EQ(3, it->first);
    EXPECT_EQ(4, it->second);
}

TEST(ContainerTest, GetStringFromContentsOfArrayWorks)
{
    array<int, 4> temporaryArray{23, -345, 5324, 1};
    EXPECT_EQ("23, -345, 5324, 1, ", getStringFromContents(temporaryArray));
}

TEST(ContainerTest, GetStringFromContentsOfVectorWorks)
{
    vector<int> temporaryVector{23, -345, 5324, 1};
    EXPECT_EQ("23, -345, 5324, 1, ", getStringFromContents(temporaryVector));
}

TEST(ContainerTest, GetStringFromContentsOfSetWorks)
{
    set<int> temporarySet{23, -345, 5324, 1};
    EXPECT_EQ("-345, 1, 23, 5324, ", getStringFromContents(temporarySet));
}

TEST(ContainerTest, GetStringFromContentsOfMapWorks)
{
    map<int,int> temporaryMap;
    temporaryMap[83] = 95;
    temporaryMap[2348] = 17;
    temporaryMap[-76] = 74;
    EXPECT_EQ("{-76:74}, {83:95}, {2348:17}, ", getStringFromContents(temporaryMap));
}

TEST(ContainerTest, GetStringFromContentsWithNumberFormatWorks)
{
    vector<int> temporaryVector{23, -345, 5324, 1};
    EXPECT_EQ("Decimal values: {23, 4294966951, 5324, 1, }\nHexadecimal values: {17, fffffea7, 14cc, 1, }\n",
              getStringInDecimalAndHexadecimalFormat(temporaryVector));
}

}

}
