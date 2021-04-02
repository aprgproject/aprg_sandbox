#include <LargeSorter/AlbaLargeSorter.hpp>

#include <PathHandlers/AlbaPathHandler.hpp>

#include <gtest/gtest.h>

#include <algorithm>#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace alba;
using namespace std;

#define ALBA_LARGE_SORTER_TEST_FILE APRG_DIR R"(AprgAlgorithm\AprgAlgorithm\tst\FilesForTests\LargeSorterTest\Test1.txt)"
#define ALBA_LARGE_SORTER_BLOCK_DIR APRG_DIR R"(AprgAlgorithm\AprgAlgorithm\tst\FilesForTests\LargeSorterTest\blocks\)"

class TestObject
{public:
    TestObject()
    {}
    TestObject(int valueInteger, double valueDouble, char valueCharacter, string valueString)
        : m_valueInteger(valueInteger)
        , m_valueDouble(valueDouble)
        , m_valueCharacter(valueCharacter)
        , m_valueString(valueString)
    {}
    bool operator<(TestObject const& testObject) const
    {
        return m_valueInteger < testObject.m_valueInteger;
    }
    bool operator>(TestObject const& testObject) const
    {
        return m_valueInteger > testObject.m_valueInteger;
    }
    bool operator==(TestObject const& testObject) const
    {
        return m_valueInteger == testObject.m_valueInteger;
    }

    friend ostream& operator<<(ostream & out, TestObject const& testObject);
    friend istream& operator>>(istream & in, TestObject& testObject);

    int m_valueInteger;
    double m_valueDouble;
    char m_valueCharacter;
    string m_valueString;
};

ostream& operator<<(ostream & out, TestObject const& testObject)
{
    out << testObject.m_valueInteger << endl;
    out << testObject.m_valueDouble << endl;
    out << testObject.m_valueCharacter << endl;
    out << testObject.m_valueString.empty() << endl;
    if(!testObject.m_valueString.empty())
    {
        out << testObject.m_valueString;
    }
    return out;
}

istream& operator>>(istream & in, TestObject& testObject)
{
    bool isEmpty;
    in >> testObject.m_valueInteger;
    in >> testObject.m_valueDouble;
    in >> testObject.m_valueCharacter;
    in >> isEmpty;
    if(!isEmpty)
    {
        in >> testObject.m_valueString;
    }
    return in;
}

TEST(AlbaLargeSorterTest, ObjectsCanBeSavedAndLoadFromFile)
{
    ofstream outputTestFile(ALBA_LARGE_SORTER_TEST_FILE);
    outputTestFile<<TestObject(0, 0, '0', "")<<endl;
    outputTestFile<<TestObject(1, 1.1, 'a', "firstString")<<endl;
    outputTestFile<<TestObject(2000, 1.222, 'b', "secondString")<<endl;
    outputTestFile<<TestObject(333333, 3.3, 'c', "thirdString")<<endl;
    outputTestFile.close();

    ifstream inputTestFile(ALBA_LARGE_SORTER_TEST_FILE);
    TestObject testObject;

    inputTestFile>>testObject;
    EXPECT_EQ(0, testObject.m_valueInteger);
    EXPECT_DOUBLE_EQ(0, testObject.m_valueDouble);
    EXPECT_EQ('0', testObject.m_valueCharacter);
    EXPECT_EQ("", testObject.m_valueString);

    inputTestFile>>testObject;
    EXPECT_EQ(1, testObject.m_valueInteger);
    EXPECT_DOUBLE_EQ(1.1, testObject.m_valueDouble);
    EXPECT_EQ('a', testObject.m_valueCharacter);
    EXPECT_EQ("firstString", testObject.m_valueString);

    inputTestFile>>testObject;
    EXPECT_EQ(2000, testObject.m_valueInteger);
    EXPECT_DOUBLE_EQ(1.222, testObject.m_valueDouble);
    EXPECT_EQ('b', testObject.m_valueCharacter);
    EXPECT_EQ("secondString", testObject.m_valueString);

    inputTestFile>>testObject;
    EXPECT_EQ(333333, testObject.m_valueInteger);
    EXPECT_DOUBLE_EQ(3.3, testObject.m_valueDouble);
    EXPECT_EQ('c', testObject.m_valueCharacter);
    EXPECT_EQ("thirdString", testObject.m_valueString);

    inputTestFile.close();
}

TEST(AlbaLargeSorterTest, ConfigurationTest_SuccessfulWhenTheConfigurationIsValid)
{
    AlbaLargeSorterConfiguration configuration(ALBA_LARGE_SORTER_BLOCK_DIR, 100, 1000, 1, 100);
    EXPECT_TRUE(configuration.isConfigurationValid());
}

TEST(AlbaLargeSorterTest, ConfigurationTest_FailedWhenTheDirectoryDoesNotExist)
{
    AlbaLargeSorterConfiguration configuration("io23i4uoiyw4oiy5", 100, 1000, 1, 100);
    EXPECT_FALSE(configuration.isConfigurationValid());
}

TEST(AlbaLargeSorterTest, ConfigurationTest_FailedWhenDirectoryPathIsGiven)
{
    AlbaLargeSorterConfiguration configuration(ALBA_LARGE_SORTER_TEST_FILE, 100, 1000, 1, 100);
    EXPECT_FALSE(configuration.isConfigurationValid());
}

TEST(AlbaLargeSorterTest, ConfigurationTest_FailedWhenMiminumIsZero)
{
    AlbaLargeSorterConfiguration configuration(ALBA_LARGE_SORTER_TEST_FILE, 0, 1000, 1, 100);
    EXPECT_FALSE(configuration.isConfigurationValid());
}

TEST(AlbaLargeSorterTest, ConfigurationTest_FailedWhenMiminumIsGreaterThanMaximum)
{
    AlbaLargeSorterConfiguration configuration(ALBA_LARGE_SORTER_TEST_FILE, 100, 99, 1, 100);
    EXPECT_FALSE(configuration.isConfigurationValid());
}

TEST(AlbaLargeSorterTest, CacheTest_ObjectsCanBeAdded)
{
    DataBlockCache<int> cache;
    cache.addBlock(1, 10);
    cache.addBlock(2, 20);
    cache.addBlock(3, 30);
    cache.addBlock(4, 40);
    cache.addBlock(5, 50);
    EXPECT_EQ(5u, cache.getContainerReference().size());
}

TEST(AlbaLargeSorterTest, CacheTest_ObjectsCanNotBeDuplicated)
{
    DataBlockCache<int> cache;
    cache.addBlock(1, 10);
    cache.addBlock(2, 20);
    cache.addBlock(3, 30);
    cache.addBlock(4, 40);
    cache.addBlock(5, 50);
    cache.addBlock(4, 40);
    cache.addBlock(3, 30);
    cache.addBlock(3, 30);
    cache.addBlock(3, 30);
    EXPECT_EQ(5u, cache.getContainerReference().size());
}

TEST(AlbaLargeSorterTest, CacheTest_ObjectsCanBeDeleted)
{
    DataBlockCache<int> cache;
    cache.addBlock(1, 10);
    cache.addBlock(2, 20);
    cache.addBlock(3, 30);
    cache.addBlock(4, 40);
    cache.addBlock(5, 50);
    cache.deleteBlock(1);
    cache.deleteBlock(2);
    cache.deleteBlock(3);
    cache.deleteBlock(4);
    cache.deleteBlock(5);
    EXPECT_TRUE(cache.getContainerReference().empty());
}

TEST(AlbaLargeSorterTest, CacheTest_CacheIsUnchangedByDeletionOfNonExistingObjects)
{
    DataBlockCache<int> cache;
    cache.addBlock(1, 10);
    cache.addBlock(2, 20);
    cache.addBlock(3, 30);
    cache.addBlock(4, 40);
    cache.addBlock(5, 50);
    cache.deleteBlock(6);
    cache.deleteBlock(7);
    cache.deleteBlock(7);
    cache.deleteBlock(7);
    cache.deleteBlock(8);
    EXPECT_EQ(5u, cache.getContainerReference().size());
}

TEST(AlbaLargeSorterTest, CacheTest_EarliestObjectsCanBePop)
{
    DataBlockCache<int> cache;
    cache.addBlock(1, 10);
    cache.addBlock(2, 20);
    cache.addBlock(3, 30);
    cache.addBlock(4, 40);
    cache.addBlock(5, 50);
    EXPECT_EQ(10, cache.popTheEarliestAddedBlock());
    EXPECT_EQ(20, cache.popTheEarliestAddedBlock());
    EXPECT_EQ(30, cache.popTheEarliestAddedBlock());
    EXPECT_EQ(40, cache.popTheEarliestAddedBlock());
    EXPECT_EQ(50, cache.popTheEarliestAddedBlock());
    EXPECT_TRUE(cache.getContainerReference().empty());
}

TEST(AlbaLargeSorterTest, CacheTest_CacheCanBeCleared)
{
    DataBlockCache<int> cache;
    cache.addBlock(1, 10);
    cache.addBlock(2, 20);
    cache.addBlock(3, 30);
    cache.addBlock(4, 40);
    cache.addBlock(5, 50);
    cache.clear();
    EXPECT_TRUE(cache.getContainerReference().empty());
}

TEST(AlbaLargeSorterTest, CacheTest_ContainerReferenceCanFetched)
{
    DataBlockCache<int> cache;
    cache.addBlock(1, 10);
    cache.addBlock(2, 20);
    cache.addBlock(3, 30);
    cache.addBlock(4, 40);
    cache.addBlock(5, 50);
    DataBlockCache<int>::BlockCacheContainer & container(cache.getContainerReference());
    ASSERT_EQ(5u, container.size());
    EXPECT_EQ(50, container[0].m_blockInformation);
    EXPECT_EQ(40, container[1].m_blockInformation);
    EXPECT_EQ(30, container[2].m_blockInformation);
    EXPECT_EQ(20, container[3].m_blockInformation);
    EXPECT_EQ(10, container[4].m_blockInformation);
}

TEST(AlbaLargeSorterTest, FileHandlerTest_FileAreWrittenAtTheEndAgainAfterRelease)
{
    AlbaLocalPathHandler(ALBA_LARGE_SORTER_TEST_FILE).deleteFile();

    DataBlockFileHandler<int> fileHandler;
    fileHandler.openFileIfNeeded(ALBA_LARGE_SORTER_TEST_FILE);
    ASSERT_TRUE(fileHandler.isFileStreamOpened());
    fileHandler.getFileDumpStreamReference()<<1<<endl;
    fileHandler.getFileDumpStreamReference()<<2<<endl;
    fileHandler.releaseFileStream();
    fileHandler.openFileIfNeeded(ALBA_LARGE_SORTER_TEST_FILE);
    ASSERT_TRUE(fileHandler.isFileStreamOpened());
    fileHandler.getFileDumpStreamReference()<<3<<endl;
    fileHandler.getFileDumpStreamReference()<<4<<endl;
    fileHandler.releaseFileStream();

    int valueFromFile;
    ifstream inputTestFile(ALBA_LARGE_SORTER_TEST_FILE);
    inputTestFile>>valueFromFile;
    EXPECT_EQ(1, valueFromFile);
    inputTestFile>>valueFromFile;
    EXPECT_EQ(2, valueFromFile);
    inputTestFile>>valueFromFile;
    EXPECT_EQ(3, valueFromFile);
    inputTestFile>>valueFromFile;
    EXPECT_EQ(4, valueFromFile);
}

TEST(AlbaLargeSorterTest, SorterIsInitiallyEmpty)
{
    AlbaLargeSorter<int> largeSorter(AlbaLargeSorterConfiguration(ALBA_LARGE_SORTER_BLOCK_DIR, 100, 1000, 1000, 100));
    EXPECT_TRUE(largeSorter.isEmpty());
}

TEST(AlbaLargeSorterTest, SorterIsNotEmptyWhenElementIsNotAdded)
{
    AlbaLargeSorter<int> largeSorter(AlbaLargeSorterConfiguration(ALBA_LARGE_SORTER_BLOCK_DIR, 100, 1000, 1000, 100));
    largeSorter.add(1);
    EXPECT_FALSE(largeSorter.isEmpty());
}

TEST(AlbaLargeSorterTest, PrimitiveDataTypesAreFoundWhenAdded)
{
    AlbaLargeSorter<int> largeSorter(AlbaLargeSorterConfiguration(ALBA_LARGE_SORTER_BLOCK_DIR, 100, 1000, 1000, 100));
    for(int inputValue=0; inputValue<100; inputValue++)
    {
        largeSorter.add(inputValue);
    }

    int expectedValue=0;
    largeSorter.sortThenDoFunctionThenReleaseAllObjects([&expectedValue](int const& actualValue)
    {
        EXPECT_EQ(expectedValue++, actualValue);
    });
    EXPECT_EQ(100, expectedValue);
}

TEST(AlbaLargeSorterTest, PrimitiveDataTypesAreSortedWhenAdded)
{
    AlbaLargeSorter<int> largeSorter(AlbaLargeSorterConfiguration(ALBA_LARGE_SORTER_BLOCK_DIR, 10, 100, 100, 100));
    largeSorter.add(8);
    largeSorter.add(4);
    largeSorter.add(2);
    largeSorter.add(9);
    largeSorter.add(7);
    largeSorter.add(3);
    largeSorter.add(5);
    largeSorter.add(1);
    largeSorter.add(6);
    largeSorter.add(0);

    int expectedValue=0;
    largeSorter.sortThenDoFunctionThenReleaseAllObjects([&expectedValue](int const& actualValue)
    {
        EXPECT_EQ(expectedValue++, actualValue);
    });
    EXPECT_EQ(10, expectedValue);
}

TEST(AlbaLargeSorterTest, PrimitiveDataTypesForBlocksAreCreatedWhenBlocksWhenMemoryIsLimited)
{
    AlbaLargeSorter<int> largeSorter(AlbaLargeSorterConfiguration(ALBA_LARGE_SORTER_BLOCK_DIR, 3, 10, 0, 100));
    for(int inputValue=0; inputValue<10; inputValue++)
    {
        largeSorter.add(inputValue);
    }

    int integerInFile;
    ifstream inputTestFile0(string(ALBA_LARGE_SORTER_BLOCK_DIR) + R"(\BLOCK_1.txt)");
    ifstream inputTestFile1(string(ALBA_LARGE_SORTER_BLOCK_DIR) + R"(\BLOCK_2.txt)");
    ifstream inputTestFile2(string(ALBA_LARGE_SORTER_BLOCK_DIR) + R"(\BLOCK_3.txt)");
    ifstream inputTestFile3(string(ALBA_LARGE_SORTER_BLOCK_DIR) + R"(\BLOCK_4.txt)");
    ASSERT_TRUE(inputTestFile0.is_open());
    inputTestFile0>>integerInFile;
    EXPECT_EQ(1, integerInFile);
    inputTestFile0>>integerInFile;
    EXPECT_EQ(0, integerInFile);
    inputTestFile0>>integerInFile;
    EXPECT_EQ(2, integerInFile);
    ASSERT_TRUE(inputTestFile1.is_open());
    inputTestFile1>>integerInFile;
    EXPECT_EQ(4, integerInFile);
    inputTestFile1>>integerInFile;
    EXPECT_EQ(3, integerInFile);
    inputTestFile1>>integerInFile;
    EXPECT_EQ(5, integerInFile);
    ASSERT_TRUE(inputTestFile2.is_open());
    inputTestFile2>>integerInFile;
    EXPECT_EQ(8, integerInFile);
    inputTestFile2>>integerInFile;
    EXPECT_EQ(7, integerInFile);
    inputTestFile2>>integerInFile;
    EXPECT_EQ(6, integerInFile);
    ASSERT_TRUE(inputTestFile3.is_open());
    inputTestFile3>>integerInFile;
    EXPECT_EQ(9, integerInFile);
    int expectedValue=0;
    largeSorter.sortThenDoFunctionThenReleaseAllObjects([&expectedValue](int const& actualValue)
    {        EXPECT_EQ(expectedValue++, actualValue);
    });
    EXPECT_EQ(10, expectedValue);
}
TEST(AlbaLargeSorterTest, FilesForBlocksAreDeletedAfterFileForBlocksAreCreated)
{
    AlbaLocalPathHandler directoryPathHandler(ALBA_LARGE_SORTER_BLOCK_DIR);
    set<string> listOfFiles;
    set<string> listOfDirectories;
    directoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    for(string const& filePath : listOfFiles)
    {
        AlbaLocalPathHandler(filePath).deleteFile();
    }
    listOfFiles.clear();
    listOfDirectories.clear();

    AlbaLargeSorter<int> largeSorter(AlbaLargeSorterConfiguration(ALBA_LARGE_SORTER_BLOCK_DIR, 3, 10, 0, 200));

    for(int inputValue=0; inputValue<200; inputValue++)
    {
        largeSorter.add(inputValue);    }

    int expectedValue=0;
    largeSorter.sortThenDoFunctionThenReleaseAllObjects([&expectedValue](int const& actualValue)    {
        EXPECT_EQ(expectedValue++, actualValue);
    });
    EXPECT_EQ(200, expectedValue);
    directoryPathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectories);
    EXPECT_TRUE(listOfFiles.empty());
    EXPECT_TRUE(listOfDirectories.empty());
}

TEST(AlbaLargeSorterTest, PrimitiveDataTypesAreSortedWhenBlocksAreCreated)
{
    AlbaLargeSorter<int> largeSorter(AlbaLargeSorterConfiguration(ALBA_LARGE_SORTER_BLOCK_DIR, 3, 10, 0, 100));
    largeSorter.add(8);
    largeSorter.add(4);
    largeSorter.add(2);
    largeSorter.add(9);
    largeSorter.add(7);
    largeSorter.add(3);
    largeSorter.add(5);
    largeSorter.add(1);
    largeSorter.add(6);
    largeSorter.add(0);

    int expectedValue=0;
    largeSorter.sortThenDoFunctionThenReleaseAllObjects([&expectedValue](int const& actualValue)
    {
        EXPECT_EQ(expectedValue++, actualValue);
    });
    EXPECT_EQ(10, expectedValue);
}

TEST(AlbaLargeSorterTest, ObjectsAreSortedWhenBlocksAreCreated)
{
    AlbaLargeSorter<TestObject> largeSorter(AlbaLargeSorterConfiguration(ALBA_LARGE_SORTER_BLOCK_DIR, 3, 10, 0, 100));
    largeSorter.add(TestObject(4, 4.04, 'd', "fourthString"));
    largeSorter.add(TestObject(5, 5.05, 'e', "fifthString"));
    largeSorter.add(TestObject(8, 8.08, 'h', "eighthString"));
    largeSorter.add(TestObject(2, 2.02, 'b', "secondString"));    largeSorter.add(TestObject(13, 13.13, 'm', "thirteenthString"));
    largeSorter.add(TestObject(7, 7.07, 'g', "seventhString"));
    largeSorter.add(TestObject(6, 6.06, 'f', "sixthString"));
    largeSorter.add(TestObject(9, 9.09, 'i', "ninthString"));    largeSorter.add(TestObject(1, 1.01, 'a', "firstString"));
    largeSorter.add(TestObject(14, 14.14, 'n', "fourteenthString"));
    largeSorter.add(TestObject(12, 12.12, 'l', "twelvethString"));
    largeSorter.add(TestObject(10, 10.10, 'j', "tenthString"));
    largeSorter.add(TestObject(15, 15.15, 'o', "fifteenthString"));
    largeSorter.add(TestObject(3, 3.03, 'c', "thirdString"));
    largeSorter.add(TestObject(11, 11.11, 'k', "eleventhString"));

    int expectedValue=1;
    largeSorter.sortThenDoFunctionThenReleaseAllObjects([&expectedValue](TestObject const& testObject)
    {
        switch(expectedValue)
        {
        case 1: EXPECT_EQ(1, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(1.01, testObject.m_valueDouble); EXPECT_EQ('a', testObject.m_valueCharacter); EXPECT_EQ("firstString", testObject.m_valueString); break;
        case 2: EXPECT_EQ(2, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(2.02, testObject.m_valueDouble); EXPECT_EQ('b', testObject.m_valueCharacter); EXPECT_EQ("secondString", testObject.m_valueString); break;
        case 3: EXPECT_EQ(3, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(3.03, testObject.m_valueDouble); EXPECT_EQ('c', testObject.m_valueCharacter); EXPECT_EQ("thirdString", testObject.m_valueString); break;
        case 4: EXPECT_EQ(4, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(4.04, testObject.m_valueDouble); EXPECT_EQ('d', testObject.m_valueCharacter); EXPECT_EQ("fourthString", testObject.m_valueString); break;
        case 5: EXPECT_EQ(5, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(5.05, testObject.m_valueDouble); EXPECT_EQ('e', testObject.m_valueCharacter); EXPECT_EQ("fifthString", testObject.m_valueString); break;
        case 6: EXPECT_EQ(6, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(6.06, testObject.m_valueDouble); EXPECT_EQ('f', testObject.m_valueCharacter); EXPECT_EQ("sixthString", testObject.m_valueString); break;
        case 7: EXPECT_EQ(7, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(7.07, testObject.m_valueDouble); EXPECT_EQ('g', testObject.m_valueCharacter); EXPECT_EQ("seventhString", testObject.m_valueString); break;
        case 8: EXPECT_EQ(8, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(8.08, testObject.m_valueDouble); EXPECT_EQ('h', testObject.m_valueCharacter); EXPECT_EQ("eighthString", testObject.m_valueString); break;
        case 9: EXPECT_EQ(9, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(9.09, testObject.m_valueDouble); EXPECT_EQ('i', testObject.m_valueCharacter); EXPECT_EQ("ninthString", testObject.m_valueString); break;
        case 10: EXPECT_EQ(10, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(10.10, testObject.m_valueDouble); EXPECT_EQ('j', testObject.m_valueCharacter); EXPECT_EQ("tenthString", testObject.m_valueString); break;
        case 11: EXPECT_EQ(11, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(11.11, testObject.m_valueDouble); EXPECT_EQ('k', testObject.m_valueCharacter); EXPECT_EQ("eleventhString", testObject.m_valueString); break;
        case 12: EXPECT_EQ(12, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(12.12, testObject.m_valueDouble); EXPECT_EQ('l', testObject.m_valueCharacter); EXPECT_EQ("twelvethString", testObject.m_valueString); break;
        case 13: EXPECT_EQ(13, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(13.13, testObject.m_valueDouble); EXPECT_EQ('m', testObject.m_valueCharacter); EXPECT_EQ("thirteenthString", testObject.m_valueString); break;
        case 14: EXPECT_EQ(14, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(14.14, testObject.m_valueDouble); EXPECT_EQ('n', testObject.m_valueCharacter); EXPECT_EQ("fourteenthString", testObject.m_valueString); break;
        case 15: EXPECT_EQ(15, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(15.15, testObject.m_valueDouble); EXPECT_EQ('o', testObject.m_valueCharacter); EXPECT_EQ("fifteenthString", testObject.m_valueString); break;
        default: break;
        }
        expectedValue++;
    });
    EXPECT_EQ(16, expectedValue);
}

TEST(AlbaLargeSorterTest, ObjectsAreStableSortedWhenDuplicateValuesAreExisting)
{
    AlbaLargeSorter<TestObject> largeSorter(AlbaLargeSorterConfiguration(ALBA_LARGE_SORTER_BLOCK_DIR, 3, 10, 0, 100));
    largeSorter.add(TestObject(1, 1.01, 'a', "firstString"));
    largeSorter.add(TestObject(2, 5.05, 'e', "fifthString"));
    largeSorter.add(TestObject(3, 8.08, 'h', "eighthString"));    largeSorter.add(TestObject(2, 6.06, 'f', "sixthString"));
    largeSorter.add(TestObject(1, 2.02, 'b', "secondString"));
    largeSorter.add(TestObject(3, 9.09, 'i', "ninthString"));
    largeSorter.add(TestObject(2, 7.07, 'g', "seventhString"));    largeSorter.add(TestObject(3, 10.10, 'j', "tenthString"));
    largeSorter.add(TestObject(1, 3.03, 'c', "thirdString"));
    largeSorter.add(TestObject(3, 11.11, 'k', "eleventhString"));
    largeSorter.add(TestObject(3, 12.12, 'l', "twelvethString"));
    largeSorter.add(TestObject(4, 15.15, 'o', "fifteenthString"));
    largeSorter.add(TestObject(3, 13.13, 'm', "thirteenthString"));
    largeSorter.add(TestObject(1, 4.04, 'd', "fourthString"));
    largeSorter.add(TestObject(3, 14.14, 'n', "fourteenthString"));

    int expectedValue=1;
    largeSorter.sortThenDoFunctionThenReleaseAllObjects([&expectedValue](TestObject const& testObject)
    {
        switch(expectedValue)
        {
        case 1: EXPECT_EQ(1, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(3.03, testObject.m_valueDouble); EXPECT_EQ('c', testObject.m_valueCharacter); EXPECT_EQ("thirdString", testObject.m_valueString); break;
        case 2: EXPECT_EQ(1, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(1.01, testObject.m_valueDouble); EXPECT_EQ('a', testObject.m_valueCharacter); EXPECT_EQ("firstString", testObject.m_valueString); break;
        case 3: EXPECT_EQ(1, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(2.02, testObject.m_valueDouble); EXPECT_EQ('b', testObject.m_valueCharacter); EXPECT_EQ("secondString", testObject.m_valueString); break;
        case 4: EXPECT_EQ(1, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(4.04, testObject.m_valueDouble); EXPECT_EQ('d', testObject.m_valueCharacter); EXPECT_EQ("fourthString", testObject.m_valueString); break;
        case 5: EXPECT_EQ(2, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(5.05, testObject.m_valueDouble); EXPECT_EQ('e', testObject.m_valueCharacter); EXPECT_EQ("fifthString", testObject.m_valueString); break;
        case 6: EXPECT_EQ(2, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(6.06, testObject.m_valueDouble); EXPECT_EQ('f', testObject.m_valueCharacter); EXPECT_EQ("sixthString", testObject.m_valueString); break;
        case 7: EXPECT_EQ(2, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(7.07, testObject.m_valueDouble); EXPECT_EQ('g', testObject.m_valueCharacter); EXPECT_EQ("seventhString", testObject.m_valueString); break;
        case 8: EXPECT_EQ(3, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(10.10, testObject.m_valueDouble); EXPECT_EQ('j', testObject.m_valueCharacter); EXPECT_EQ("tenthString", testObject.m_valueString); break;
        case 9: EXPECT_EQ(3, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(9.09, testObject.m_valueDouble); EXPECT_EQ('i', testObject.m_valueCharacter); EXPECT_EQ("ninthString", testObject.m_valueString); break;
        case 10: EXPECT_EQ(3, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(11.11, testObject.m_valueDouble); EXPECT_EQ('k', testObject.m_valueCharacter); EXPECT_EQ("eleventhString", testObject.m_valueString); break;
        case 11: EXPECT_EQ(3, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(8.08, testObject.m_valueDouble); EXPECT_EQ('h', testObject.m_valueCharacter); EXPECT_EQ("eighthString", testObject.m_valueString); break;
        case 12: EXPECT_EQ(3, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(12.12, testObject.m_valueDouble); EXPECT_EQ('l', testObject.m_valueCharacter); EXPECT_EQ("twelvethString", testObject.m_valueString); break;
        case 13: EXPECT_EQ(3, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(13.13, testObject.m_valueDouble); EXPECT_EQ('m', testObject.m_valueCharacter); EXPECT_EQ("thirteenthString", testObject.m_valueString); break;
        case 14: EXPECT_EQ(3, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(14.14, testObject.m_valueDouble); EXPECT_EQ('n', testObject.m_valueCharacter); EXPECT_EQ("fourteenthString", testObject.m_valueString); break;        case 15: EXPECT_EQ(4, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(15.15, testObject.m_valueDouble); EXPECT_EQ('o', testObject.m_valueCharacter); EXPECT_EQ("fifteenthString", testObject.m_valueString); break;
        default: break;
        }
        expectedValue++;
    });
    EXPECT_EQ(16, expectedValue);
}

TEST(AlbaLargeSorterTest, ObjectsAreSortedWhenUsingRandomShuffle)
{
    vector<TestObject> objectsToShuffle;
    objectsToShuffle.emplace_back(1, 1.01, 'a', "firstString");
    objectsToShuffle.emplace_back(2, 2.02, 'b', "secondString");
    objectsToShuffle.emplace_back(3, 3.03, 'c', "thirdString");    objectsToShuffle.emplace_back(4, 4.04, 'd', "fourthString");
    objectsToShuffle.emplace_back(5, 5.05, 'e', "fifthString");
    objectsToShuffle.emplace_back(6, 6.06, 'f', "sixthString");
    objectsToShuffle.emplace_back(7, 7.07, 'g', "seventhString");    objectsToShuffle.emplace_back(8, 8.08, 'h', "eighthString");
    objectsToShuffle.emplace_back(9, 9.09, 'i', "ninthString");
    objectsToShuffle.emplace_back(10, 10.10, 'j', "tenthString");
    objectsToShuffle.emplace_back(11, 11.11, 'k', "eleventhString");
    objectsToShuffle.emplace_back(12, 12.12, 'l', "twelvethString");
    objectsToShuffle.emplace_back(13, 13.13, 'm', "thirteenthString");
    objectsToShuffle.emplace_back(14, 14.14, 'n', "fourteenthString");
    objectsToShuffle.emplace_back(15, 15.15, 'o', "fifteenthString");
    random_shuffle(objectsToShuffle.begin(), objectsToShuffle.end());
    AlbaLargeSorter<TestObject> largeSorter(AlbaLargeSorterConfiguration(ALBA_LARGE_SORTER_BLOCK_DIR, 3, 10, 0, 100));

    for(TestObject const& testObject : objectsToShuffle)
    {
        largeSorter.add(testObject);
    }

    int expectedValue=1;
    largeSorter.sortThenDoFunctionThenReleaseAllObjects([&expectedValue](TestObject const& testObject)
    {
        switch(expectedValue)
        {
        case 1: EXPECT_EQ(1, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(1.01, testObject.m_valueDouble); EXPECT_EQ('a', testObject.m_valueCharacter); EXPECT_EQ("firstString", testObject.m_valueString); break;
        case 2: EXPECT_EQ(2, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(2.02, testObject.m_valueDouble); EXPECT_EQ('b', testObject.m_valueCharacter); EXPECT_EQ("secondString", testObject.m_valueString); break;
        case 3: EXPECT_EQ(3, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(3.03, testObject.m_valueDouble); EXPECT_EQ('c', testObject.m_valueCharacter); EXPECT_EQ("thirdString", testObject.m_valueString); break;
        case 4: EXPECT_EQ(4, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(4.04, testObject.m_valueDouble); EXPECT_EQ('d', testObject.m_valueCharacter); EXPECT_EQ("fourthString", testObject.m_valueString); break;
        case 5: EXPECT_EQ(5, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(5.05, testObject.m_valueDouble); EXPECT_EQ('e', testObject.m_valueCharacter); EXPECT_EQ("fifthString", testObject.m_valueString); break;
        case 6: EXPECT_EQ(6, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(6.06, testObject.m_valueDouble); EXPECT_EQ('f', testObject.m_valueCharacter); EXPECT_EQ("sixthString", testObject.m_valueString); break;
        case 7: EXPECT_EQ(7, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(7.07, testObject.m_valueDouble); EXPECT_EQ('g', testObject.m_valueCharacter); EXPECT_EQ("seventhString", testObject.m_valueString); break;
        case 8: EXPECT_EQ(8, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(8.08, testObject.m_valueDouble); EXPECT_EQ('h', testObject.m_valueCharacter); EXPECT_EQ("eighthString", testObject.m_valueString); break;
        case 9: EXPECT_EQ(9, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(9.09, testObject.m_valueDouble); EXPECT_EQ('i', testObject.m_valueCharacter); EXPECT_EQ("ninthString", testObject.m_valueString); break;
        case 10: EXPECT_EQ(10, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(10.10, testObject.m_valueDouble); EXPECT_EQ('j', testObject.m_valueCharacter); EXPECT_EQ("tenthString", testObject.m_valueString); break;
        case 11: EXPECT_EQ(11, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(11.11, testObject.m_valueDouble); EXPECT_EQ('k', testObject.m_valueCharacter); EXPECT_EQ("eleventhString", testObject.m_valueString); break;
        case 12: EXPECT_EQ(12, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(12.12, testObject.m_valueDouble); EXPECT_EQ('l', testObject.m_valueCharacter); EXPECT_EQ("twelvethString", testObject.m_valueString); break;
        case 13: EXPECT_EQ(13, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(13.13, testObject.m_valueDouble); EXPECT_EQ('m', testObject.m_valueCharacter); EXPECT_EQ("thirteenthString", testObject.m_valueString); break;
        case 14: EXPECT_EQ(14, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(14.14, testObject.m_valueDouble); EXPECT_EQ('n', testObject.m_valueCharacter); EXPECT_EQ("fourteenthString", testObject.m_valueString); break;
        case 15: EXPECT_EQ(15, testObject.m_valueInteger); EXPECT_DOUBLE_EQ(15.15, testObject.m_valueDouble); EXPECT_EQ('o', testObject.m_valueCharacter); EXPECT_EQ("fifteenthString", testObject.m_valueString); break;
        default: break;
        }
        expectedValue++;
    });
    EXPECT_EQ(16, expectedValue);
}

TEST(AlbaLargeSorterTest, DISABLED_FileStreamAreLimitedByMaximumFileStreams){
    AlbaLargeSorter<int> largeSorter(AlbaLargeSorterConfiguration(ALBA_LARGE_SORTER_BLOCK_DIR, 0, 1, 0, 200));
    vector<int> integersToShuffle;
    for(int inputValue=0; inputValue<1000; inputValue++)    {
        integersToShuffle.emplace_back(inputValue);
    }
    random_shuffle(integersToShuffle.begin(), integersToShuffle.end());
    for(int value : integersToShuffle)
    {
        largeSorter.add(value);
    }

    int expectedValue=0;
    largeSorter.sortThenDoFunctionThenReleaseAllObjects([&expectedValue](int const& actualValue)
    {
        EXPECT_EQ(expectedValue++, actualValue);
    });
    EXPECT_EQ(1000, expectedValue);
}
