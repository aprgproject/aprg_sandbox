#include <Common/Container/AlbaContainerHelper.hpp>
#include <Common/File/AlbaFileReader.hpp>
#include <CommonTestsUtilities/DirectoryConstants.hpp>
#include <CommonTestsUtilities/File/BaseFileReaderTest.hpp>

#include <gtest/gtest.h>
#include <array>
#include <map>
#include <set>
#include <stack>
#include <string_view>
#include <vector>

using namespace std;

namespace alba::containerHelper {

struct AlbaContainerHelperReaderTest : public BaseFileReaderTest {
    AlbaContainerHelperReaderTest() : BaseFileReaderTest(APRG_COMMON_TEST_FILE_TO_READ) {}
};

TEST(AlbaContainerHelperTest, GetDelimeterBasedOnFormatWorks) {
    EXPECT_EQ(", ", getDelimeterBasedOnFormat(StreamFormat::String));
    EXPECT_EQ("\n", getDelimeterBasedOnFormat(StreamFormat::File));
}

TEST(AlbaContainerHelperTest, GetLowerAndUpperConstIteratorsForNonSetWorks) {
    vector<int> sortedVector{-10, -5, 1, 2, 4, 5, 23, 50};

    auto iteratorPairToVerify(getLowerAndUpperConstIteratorsForNonSet(sortedVector, 7));
    EXPECT_EQ(5, *(iteratorPairToVerify.first));
    EXPECT_EQ(23, *(iteratorPairToVerify.second));
}

TEST(AlbaContainerHelperTest, GetLowerAndUpperValuesForNonSetWorks) {
    vector<int> sortedVector{-10, -5, 1, 2, 4, 5, 23, 50};

    EXPECT_EQ((pair<int, int>(-10, -10)), getLowerAndUpperValuesForNonSet(sortedVector, -100));    EXPECT_EQ((pair<int, int>(-10, -10)), getLowerAndUpperValuesForNonSet(sortedVector, -10));
    EXPECT_EQ((pair<int, int>(50, 50)), getLowerAndUpperValuesForNonSet(sortedVector, 50));
    EXPECT_EQ((pair<int, int>(50, 50)), getLowerAndUpperValuesForNonSet(sortedVector, 10000));
    EXPECT_EQ((pair<int, int>(23, 23)), getLowerAndUpperValuesForNonSet(sortedVector, 23));
    EXPECT_EQ((pair<int, int>(5, 23)), getLowerAndUpperValuesForNonSet(sortedVector, 7));
}

TEST(AlbaContainerHelperTest, CountItemsInBetweenForNonSetWorks) {
    vector<char> sortedVector{'A', 'C', 'E', 'H', 'M', 'R', 'S', 'X'};

    EXPECT_EQ(5U, countItemsInBetweenForNonSet(sortedVector, 'E', 'S'));    EXPECT_EQ(5U, countItemsInBetweenForNonSet(sortedVector, 'E', 'T'));
    EXPECT_EQ(4U, countItemsInBetweenForNonSet(sortedVector, 'F', 'T'));
}

TEST(AlbaContainerHelperTest, GetItemsInBetweenForNonSetWorks) {
    vector<char> sortedVector{'A', 'C', 'E', 'H', 'M', 'R', 'S', 'X'};

    vector<char> expectedVector1{'E', 'H', 'M', 'R', 'S'};    vector<char> expectedVector2{'E', 'H', 'M', 'R', 'S'};
    vector<char> expectedVector3{'H', 'M', 'R', 'S'};
    EXPECT_EQ(expectedVector1, getItemsInBetweenForNonSet(sortedVector, 'E', 'S'));
    EXPECT_EQ(expectedVector2, getItemsInBetweenForNonSet(sortedVector, 'E', 'T'));
    EXPECT_EQ(expectedVector3, getItemsInBetweenForNonSet(sortedVector, 'F', 'T'));
}

TEST(AlbaContainerHelperTest, GetLowerAndUpperConstIteratorsForSetWorks) {
    set<int> sampleSet{-10, -5, 1, 2, 4, 5, 23, 50};

    auto iteratorPairToVerify(getLowerAndUpperConstIteratorsForNonSet(sampleSet, 7));
    EXPECT_EQ(5, *(iteratorPairToVerify.first));
    EXPECT_EQ(23, *(iteratorPairToVerify.second));
}

TEST(AlbaContainerHelperTest, GetLowerAndUpperValuesForSetWorks) {
    set<int> sampleSet{-10, -5, 1, 2, 4, 5, 23, 50};

    EXPECT_EQ((pair<int, int>(-10, -10)), getLowerAndUpperValuesForNonSet(sampleSet, -100));    EXPECT_EQ((pair<int, int>(-10, -10)), getLowerAndUpperValuesForNonSet(sampleSet, -10));
    EXPECT_EQ((pair<int, int>(50, 50)), getLowerAndUpperValuesForNonSet(sampleSet, 50));
    EXPECT_EQ((pair<int, int>(50, 50)), getLowerAndUpperValuesForNonSet(sampleSet, 10000));
    EXPECT_EQ((pair<int, int>(23, 23)), getLowerAndUpperValuesForNonSet(sampleSet, 23));
    EXPECT_EQ((pair<int, int>(5, 23)), getLowerAndUpperValuesForNonSet(sampleSet, 7));
}

TEST(AlbaContainerHelperTest, CountItemsInBetweenForSetWorks) {
    set<char> sampleSet{'A', 'C', 'E', 'H', 'M', 'R', 'S', 'X'};

    EXPECT_EQ(5U, countItemsInBetweenForNonSet(sampleSet, 'E', 'S'));    EXPECT_EQ(5U, countItemsInBetweenForNonSet(sampleSet, 'E', 'T'));
    EXPECT_EQ(4U, countItemsInBetweenForNonSet(sampleSet, 'F', 'T'));
}

TEST(AlbaContainerHelperTest, GetItemsInBetweenForSetWorks) {
    set<char> sampleSet{'A', 'C', 'E', 'H', 'M', 'R', 'S', 'X'};

    set<char> expectedSet1{'E', 'H', 'M', 'R', 'S'};    set<char> expectedSet2{'E', 'H', 'M', 'R', 'S'};
    set<char> expectedSet3{'H', 'M', 'R', 'S'};
    EXPECT_EQ(expectedSet1, getItemsInBetweenForNonSet(sampleSet, 'E', 'S'));
    EXPECT_EQ(expectedSet2, getItemsInBetweenForNonSet(sampleSet, 'E', 'T'));
    EXPECT_EQ(expectedSet3, getItemsInBetweenForNonSet(sampleSet, 'F', 'T'));
}

TEST(AlbaContainerHelperTest, GetLowerAndUpperConstIteratorsInMapWorks) {
    map<int, int> sampleMap{{1, 10}, {3, 30}, {5, 50}};
    using MapIterator = map<int, int>::const_iterator;
    using PairOfIterators = pair<MapIterator, MapIterator>;
    MapIterator firstIterator = sampleMap.find(1);
    MapIterator secondIterator = sampleMap.find(3);
    MapIterator thirdIterator = sampleMap.find(5);    PairOfIterators iteratorsToVerify1(getLowerAndUpperConstIteratorsInMap(sampleMap, 0));
    EXPECT_EQ(firstIterator, iteratorsToVerify1.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify1.second);
    PairOfIterators iteratorsToVerify2(getLowerAndUpperConstIteratorsInMap(sampleMap, 6));
    EXPECT_EQ(thirdIterator, iteratorsToVerify2.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify2.second);
    PairOfIterators iteratorsToVerify3(getLowerAndUpperConstIteratorsInMap(sampleMap, 1));
    EXPECT_EQ(firstIterator, iteratorsToVerify3.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify3.second);
    PairOfIterators iteratorsToVerify4(getLowerAndUpperConstIteratorsInMap(sampleMap, 5));
    EXPECT_EQ(thirdIterator, iteratorsToVerify4.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify4.second);
    PairOfIterators iteratorsToVerify5(getLowerAndUpperConstIteratorsInMap(sampleMap, 4));
    EXPECT_EQ(secondIterator, iteratorsToVerify5.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify5.second);
    PairOfIterators iteratorsToVerify6(getLowerAndUpperConstIteratorsInMap(sampleMap, 3));
    EXPECT_EQ(secondIterator, iteratorsToVerify6.first);
    EXPECT_EQ(secondIterator, iteratorsToVerify6.second);
}

TEST(AlbaContainerHelperTest, GetLowerAndUpperIteratorsInMapWorks) {
    map<int, int> sampleMap{{1, 10}, {3, 30}, {5, 50}};
    using MapIterator = map<int, int>::iterator;
    using PairOfIterators = pair<MapIterator, MapIterator>;
    MapIterator firstIterator = sampleMap.find(1);
    MapIterator secondIterator = sampleMap.find(3);
    MapIterator thirdIterator = sampleMap.find(5);    PairOfIterators iteratorsToVerify1(getLowerAndUpperIteratorsInMap(sampleMap, 0));
    EXPECT_EQ(firstIterator, iteratorsToVerify1.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify1.second);
    PairOfIterators iteratorsToVerify2(getLowerAndUpperIteratorsInMap(sampleMap, 6));
    EXPECT_EQ(thirdIterator, iteratorsToVerify2.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify2.second);
    PairOfIterators iteratorsToVerify3(getLowerAndUpperIteratorsInMap(sampleMap, 1));
    EXPECT_EQ(firstIterator, iteratorsToVerify3.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify3.second);
    PairOfIterators iteratorsToVerify4(getLowerAndUpperIteratorsInMap(sampleMap, 5));
    EXPECT_EQ(thirdIterator, iteratorsToVerify4.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify4.second);
    PairOfIterators iteratorsToVerify5(getLowerAndUpperIteratorsInMap(sampleMap, 4));
    EXPECT_EQ(secondIterator, iteratorsToVerify5.first);
    EXPECT_EQ(thirdIterator, iteratorsToVerify5.second);
    PairOfIterators iteratorsToVerify6(getLowerAndUpperIteratorsInMap(sampleMap, 3));
    EXPECT_EQ(secondIterator, iteratorsToVerify6.first);
    EXPECT_EQ(secondIterator, iteratorsToVerify6.second);
}

TEST(AlbaContainerHelperTest, GetLowerAndUpperConstIteratorsInMapWorksOnMultiMap) {
    multimap<int, int> sampleMap{{1, 11}, {1, 12}, {3, 31}, {3, 32}, {5, 51}, {5, 52}};
    using MultimapIterator = multimap<int, int>::const_iterator;
    using PairOfIterators = pair<MultimapIterator, MultimapIterator>;
    MultimapIterator firstIterator = begin(sampleMap);
    MultimapIterator secondIterator = firstIterator;
    secondIterator++;    MultimapIterator thirdIterator = secondIterator;
    thirdIterator++;
    MultimapIterator fourthIterator = thirdIterator;
    fourthIterator++;
    MultimapIterator fifthIterator = fourthIterator;
    fifthIterator++;
    MultimapIterator sixthIterator = fifthIterator;
    sixthIterator++;
    PairOfIterators iteratorsToVerify1(getLowerAndUpperConstIteratorsInMap(sampleMap, 0));
    EXPECT_EQ(firstIterator, iteratorsToVerify1.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify1.second);
    PairOfIterators iteratorsToVerify2(getLowerAndUpperConstIteratorsInMap(sampleMap, 6));
    EXPECT_EQ(sixthIterator, iteratorsToVerify2.first);
    EXPECT_EQ(sixthIterator, iteratorsToVerify2.second);
    PairOfIterators iteratorsToVerify3(getLowerAndUpperConstIteratorsInMap(sampleMap, 1));
    EXPECT_EQ(firstIterator, iteratorsToVerify3.first);
    EXPECT_EQ(secondIterator, iteratorsToVerify3.second);
    PairOfIterators iteratorsToVerify4(getLowerAndUpperConstIteratorsInMap(sampleMap, 5));
    EXPECT_EQ(fifthIterator, iteratorsToVerify4.first);
    EXPECT_EQ(sixthIterator, iteratorsToVerify4.second);
    PairOfIterators iteratorsToVerify5(getLowerAndUpperConstIteratorsInMap(sampleMap, 4));
    EXPECT_EQ(fourthIterator, iteratorsToVerify5.first);
    EXPECT_EQ(fifthIterator, iteratorsToVerify5.second);
    PairOfIterators iteratorsToVerify6(getLowerAndUpperConstIteratorsInMap(sampleMap, 3));
    EXPECT_EQ(thirdIterator, iteratorsToVerify6.first);
    EXPECT_EQ(fourthIterator, iteratorsToVerify6.second);
}

TEST(AlbaContainerHelperTest, GetLowerAndUpperIteratorsInMapWorksOnMultiMap) {
    multimap<int, int> sampleMap{{1, 11}, {1, 12}, {3, 31}, {3, 32}, {5, 51}, {5, 52}};
    using MultimapIterator = multimap<int, int>::iterator;
    using PairOfIterators = pair<MultimapIterator, MultimapIterator>;
    MultimapIterator firstIterator = begin(sampleMap);
    MultimapIterator secondIterator = firstIterator;
    secondIterator++;    MultimapIterator thirdIterator = secondIterator;
    thirdIterator++;
    MultimapIterator fourthIterator = thirdIterator;
    fourthIterator++;
    MultimapIterator fifthIterator = fourthIterator;
    fifthIterator++;
    MultimapIterator sixthIterator = fifthIterator;
    sixthIterator++;
    PairOfIterators iteratorsToVerify1(getLowerAndUpperIteratorsInMap(sampleMap, 0));
    EXPECT_EQ(firstIterator, iteratorsToVerify1.first);
    EXPECT_EQ(firstIterator, iteratorsToVerify1.second);
    PairOfIterators iteratorsToVerify2(getLowerAndUpperIteratorsInMap(sampleMap, 6));
    EXPECT_EQ(sixthIterator, iteratorsToVerify2.first);
    EXPECT_EQ(sixthIterator, iteratorsToVerify2.second);
    PairOfIterators iteratorsToVerify3(getLowerAndUpperIteratorsInMap(sampleMap, 1));
    EXPECT_EQ(firstIterator, iteratorsToVerify3.first);
    EXPECT_EQ(secondIterator, iteratorsToVerify3.second);
    PairOfIterators iteratorsToVerify4(getLowerAndUpperIteratorsInMap(sampleMap, 5));
    EXPECT_EQ(fifthIterator, iteratorsToVerify4.first);
    EXPECT_EQ(sixthIterator, iteratorsToVerify4.second);
    PairOfIterators iteratorsToVerify5(getLowerAndUpperIteratorsInMap(sampleMap, 4));
    EXPECT_EQ(fourthIterator, iteratorsToVerify5.first);
    EXPECT_EQ(fifthIterator, iteratorsToVerify5.second);
    PairOfIterators iteratorsToVerify6(getLowerAndUpperIteratorsInMap(sampleMap, 3));
    EXPECT_EQ(thirdIterator, iteratorsToVerify6.first);
    EXPECT_EQ(fourthIterator, iteratorsToVerify6.second);
}

TEST(AlbaContainerHelperTest, GetUnderlyingContainerWorksOnStack) {
    using Adapter = std::stack<int>;
    Adapter adapter({1, 2, 3});
    Adapter::container_type const& containerToVerify(getUnderlyingContainer(adapter));

    Adapter::container_type containerToExpect{1, 2, 3};
    EXPECT_EQ(containerToExpect, containerToVerify);
}

TEST(AlbaContainerHelperTest, GetUnderlyingContainerReferenceWorksOnStack) {
    using Adapter = std::stack<int>;
    Adapter adapter({1, 2, 3});
    Adapter::container_type& containerToVerify(getUnderlyingContainerReference(adapter));
    containerToVerify[0] = 4;
    containerToVerify[1] = 5;    containerToVerify[2] = 6;

    ASSERT_EQ(3U, adapter.size());
    EXPECT_EQ(6, adapter.top());
    adapter.pop();
    EXPECT_EQ(5, adapter.top());
    adapter.pop();
    EXPECT_EQ(4, adapter.top());
    adapter.pop();
    EXPECT_TRUE(adapter.empty());
}

TEST(AlbaContainerHelperTest, GetStringFromContentsOfArrayWorks) {
    array<int, 4> temporaryArray{23, -345, 5324, 1};
    EXPECT_EQ("23, -345, 5324, 1, ", getStringFromContents(temporaryArray));
}

TEST(AlbaContainerHelperTest, GetStringFromContentsOfVectorWorks) {
    vector<int> temporaryVector{23, -345, 5324, 1};
    EXPECT_EQ("23, -345, 5324, 1, ", getStringFromContents(temporaryVector));
}

TEST(AlbaContainerHelperTest, GetStringFromContentsOfSetWorks) {
    set<int> temporarySet{23, -345, 5324, 1};
    EXPECT_EQ("-345, 1, 23, 5324, ", getStringFromContents(temporarySet));
}

TEST(AlbaContainerHelperTest, GetStringFromContentsOfMapWorks) {
    map<int, int> temporaryMap;
    temporaryMap[83] = 95;
    temporaryMap[2348] = 17;
    temporaryMap[-76] = 74;
    EXPECT_EQ("{-76:74}, {83:95}, {2348:17}, ", getStringFromContents(temporaryMap));
}

TEST(AlbaContainerHelperTest, GetStringFromContentsWithNumberFormatWorks) {
    vector<int> temporaryVector{23, -345, 5324, 1};
    EXPECT_EQ(
        "Decimal values: {23, -345, 5324, 1, }\nHexadecimal values: {17, fffffea7, 14cc, 1, }\n",
        getStringInDecimalAndHexadecimalFormat(temporaryVector));
}

TEST_F(AlbaContainerHelperReaderTest, SaveContentsToStreamWorksForAVectorOfIntegersToFile) {
    array<int, 6> temporaryArray{0, -23, 4, 379, -482, 37};

    saveContentsToStream(testFileWriteStream, temporaryArray, StreamFormat::File);
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());
    AlbaFileReader fileReader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ("0", fileReader.getLine());
    EXPECT_EQ("-23", fileReader.getLine());    EXPECT_EQ("4", fileReader.getLine());
    EXPECT_EQ("379", fileReader.getLine());
    EXPECT_EQ("-482", fileReader.getLine());
    EXPECT_EQ("37", fileReader.getLine());    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST_F(AlbaContainerHelperReaderTest, SaveContentsToStreamWorksForAnArrayOfIntegersToFile) {
    vector<int> temporaryVector{0, -23, 4, 379, -482, 37};

    saveContentsToStream(testFileWriteStream, temporaryVector, StreamFormat::File);
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());
    AlbaFileReader fileReader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ("0", fileReader.getLine());
    EXPECT_EQ("-23", fileReader.getLine());    EXPECT_EQ("4", fileReader.getLine());
    EXPECT_EQ("379", fileReader.getLine());
    EXPECT_EQ("-482", fileReader.getLine());
    EXPECT_EQ("37", fileReader.getLine());    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST_F(AlbaContainerHelperReaderTest, SaveContentsToStreamWorksForASetOfIntegersToFile) {
    set<int> temporarySet{0, -23, 4, 379, -482, 37};

    saveContentsToStream(testFileWriteStream, temporarySet, StreamFormat::File);
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());
    AlbaFileReader fileReader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ("-482", fileReader.getLine());
    EXPECT_EQ("-23", fileReader.getLine());    EXPECT_EQ("0", fileReader.getLine());
    EXPECT_EQ("4", fileReader.getLine());
    EXPECT_EQ("37", fileReader.getLine());
    EXPECT_EQ("379", fileReader.getLine());    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST_F(AlbaContainerHelperReaderTest, SaveContentsToStreamWorksForAMapOfIntegersToFile) {
    map<int, int> temporaryMap;
    temporaryMap[83] = 95;
    temporaryMap[2348] = 17;
    temporaryMap[-76] = 74;

    saveContentsToStream(testFileWriteStream, temporaryMap, StreamFormat::File);
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());
    AlbaFileReader fileReader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ("-76", fileReader.getLine());
    EXPECT_EQ("74", fileReader.getLine());    EXPECT_EQ("83", fileReader.getLine());
    EXPECT_EQ("95", fileReader.getLine());
    EXPECT_EQ("2348", fileReader.getLine());
    EXPECT_EQ("17", fileReader.getLine());    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST_F(AlbaContainerHelperReaderTest, FetrieveContentsFromStreamWorksForAVectorOfIntegersFromFile) {
    array<int, 4> temporaryArray{};
    testFileWriteStream << "18723\n";
    testFileWriteStream << "-608\n";
    testFileWriteStream << "-43735\n";
    testFileWriteStream << "23234\n";
    testFileWriteStream.close();
    ifstream testFileReadStream(testFilePathHandler.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());

    retrieveContentsFromStream(testFileReadStream, temporaryArray);

    ASSERT_EQ(4U, temporaryArray.size());
    auto it = begin(temporaryArray);    EXPECT_EQ(18723, *(it++));
    EXPECT_EQ(-608, *(it++));
    EXPECT_EQ(-43735, *(it++));
    EXPECT_EQ(23234, *(it++));
}

TEST_F(AlbaContainerHelperReaderTest, FetrieveContentsFromStreamWorksForAnArrayOfIntegersFromFile) {
    vector<int> temporaryVector;
    testFileWriteStream << "18723\n";
    testFileWriteStream << "-608\n";
    testFileWriteStream << "-43735\n";
    testFileWriteStream << "23234\n";
    testFileWriteStream.close();
    ifstream testFileReadStream(testFilePathHandler.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());

    retrieveContentsFromStream(testFileReadStream, temporaryVector);

    ASSERT_EQ(4U, temporaryVector.size());
    auto it = begin(temporaryVector);    EXPECT_EQ(18723, *(it++));
    EXPECT_EQ(-608, *(it++));
    EXPECT_EQ(-43735, *(it++));
    EXPECT_EQ(23234, *(it++));
}

TEST_F(AlbaContainerHelperReaderTest, FetrieveContentsFromStreamWorksForASetOfIntegersFromFile) {
    set<int> temporarySet;
    testFileWriteStream << "18723\n";
    testFileWriteStream << "-608\n";
    testFileWriteStream << "-43735\n";
    testFileWriteStream << "23234\n";
    testFileWriteStream.close();
    ifstream testFileReadStream(testFilePathHandler.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());

    retrieveContentsFromStream(testFileReadStream, temporarySet);

    ASSERT_EQ(4U, temporarySet.size());
    auto it = begin(temporarySet);    EXPECT_EQ(-43735, *(it++));
    EXPECT_EQ(-608, *(it++));
    EXPECT_EQ(18723, *(it++));
    EXPECT_EQ(23234, *(it++));
}

TEST_F(AlbaContainerHelperReaderTest, FetrieveContentsFromStreamWorksForAMapOfIntegersFromFile) {
    map<int, int> temporaryMap;
    testFileWriteStream << "1\n";
    testFileWriteStream << "2\n";
    testFileWriteStream << "3\n";
    testFileWriteStream << "4\n";
    testFileWriteStream.close();
    ifstream testFileReadStream(testFilePathHandler.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());

    retrieveContentsFromStream(testFileReadStream, temporaryMap);

    ASSERT_EQ(2U, temporaryMap.size());
    auto it = begin(temporaryMap);    EXPECT_EQ(1, it->first);
    EXPECT_EQ(2, it->second);
    it++;
    EXPECT_EQ(3, it->first);
    EXPECT_EQ(4, it->second);
}

}  // namespace alba::containerHelper