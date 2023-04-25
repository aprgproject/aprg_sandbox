#include <Algorithm/HashFunctions/ForPrimitiveTypes/UnsignedIntegerBasedHashFunction.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/HashTable/LinearProbingHashSymbolTable.hpp>
#include <AlgorithmTests/SetAndSymbolTable/SymbolTable/Utilities/CommonTestsWithSymbolTable.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSymbolTable;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using HashFunctionForTest = UnsignedIntegerBasedHashFunction<unsigned int, unsigned int>;
using SymbolTableForTest = LinearProbingHashSymbolTable<unsigned int, char, HashFunctionForTest>;
}  // namespace

TEST(LinearProbingHashSymbolTableTest, IsEmptyWorksWhenEmpty) {
    testIsEmptyWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(LinearProbingHashSymbolTableTest, IsEmptyWorksWhenNotEmpty) {
    testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(LinearProbingHashSymbolTableTest, DoesContainWorks) {
    testDoesContainWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(LinearProbingHashSymbolTableTest, GetSizeWorksWhenEmpty) {
    testGetSizeWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(LinearProbingHashSymbolTableTest, GetSizeWorksWhenNotEmpty) {
    testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(LinearProbingHashSymbolTableTest, GetWorks) { testGetWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(LinearProbingHashSymbolTableTest, GetRankWorks) { testGetRankWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(LinearProbingHashSymbolTableTest, GetMinimumWorks) { testGetMinimumWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(LinearProbingHashSymbolTableTest, GetMaximumWorks) { testGetMaximumWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(LinearProbingHashSymbolTableTest, SelectAtWorks) { testSelectAtWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(LinearProbingHashSymbolTableTest, GetFloorWorks) { testGetFloorWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(LinearProbingHashSymbolTableTest, GetCeilingWorks) { testGetCeilingWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(LinearProbingHashSymbolTableTest, PutWorks) { testPutWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(LinearProbingHashSymbolTableTest, DeleteBasedOnKeyWorks) {
    testDeleteBasedOnKeyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(LinearProbingHashSymbolTableTest, DeleteMinimumWorks) {
    testDeleteMinimumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(LinearProbingHashSymbolTableTest, DeleteMaximumWorks) {
    testDeleteMaximumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(LinearProbingHashSymbolTableTest, GetKeys) { testGetKeysWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(LinearProbingHashSymbolTableTest, GetKeysInRangeWorks) {
    testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(LinearProbingHashSymbolTableTest, PutWorksWithDoublingHashTableSize) {
    SymbolTableForTest symbolTable;

    EXPECT_EQ(1U, symbolTable.getHashTableSize());

    symbolTable.put(8U, 'H');
    symbolTable.put(9U, 'I');
    EXPECT_EQ(4U, symbolTable.getHashTableSize());

    symbolTable.put(5U, 'E');
    EXPECT_EQ(8U, symbolTable.getHashTableSize());

    symbolTable.put(4U, 'D');
    symbolTable.put(7U, 'G');
    EXPECT_EQ(16U, symbolTable.getHashTableSize());

    symbolTable.put(3U, 'C');
    EXPECT_EQ(16U, symbolTable.getHashTableSize());
}

TEST(LinearProbingHashSymbolTableTest, DeleteBasedOnKeyWorksWithHalvingHashTableSize) {
    SymbolTableForTest symbolTable;
    symbolTable.put(8U, 'H');
    symbolTable.put(9U, 'I');
    symbolTable.put(5U, 'E');
    symbolTable.put(4U, 'D');
    symbolTable.put(7U, 'G');
    symbolTable.put(3U, 'C');

    EXPECT_EQ(16U, symbolTable.getHashTableSize());

    symbolTable.deleteBasedOnKey(3U);
    symbolTable.deleteBasedOnKey(4U);
    symbolTable.deleteBasedOnKey(5U);
    symbolTable.deleteBasedOnKey(7U);
    EXPECT_EQ(8U, symbolTable.getHashTableSize());

    symbolTable.deleteBasedOnKey(8U);
    EXPECT_EQ(4U, symbolTable.getHashTableSize());

    symbolTable.deleteBasedOnKey(9U);
    EXPECT_EQ(4U, symbolTable.getHashTableSize());
}

}  // namespace algorithm

}  // namespace alba
