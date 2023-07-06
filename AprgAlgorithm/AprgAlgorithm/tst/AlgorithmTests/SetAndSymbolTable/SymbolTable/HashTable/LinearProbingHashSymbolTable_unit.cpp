#include <Algorithm/HashFunctions/PrimitiveTypes/IntegerHashFunction.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/HashTable/LinearProbingHashSymbolTable.hpp>
#include <AlgorithmTests/SetAndSymbolTable/SymbolTable/Utilities/CommonTestsWithSymbolTable.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSymbolTable;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using HashValue = uint32_t;
constexpr HashValue HASH_TABLE_SIZE = 2;
using HashFunctionForTest = IntegerHashFunction<int, HashValue, HASH_TABLE_SIZE>;
using SymbolTableForTest = LinearProbingHashSymbolTable<int, char, HashFunctionForTest>;
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

    EXPECT_EQ(1, symbolTable.getHashTableSize());

    symbolTable.put(8, 'H');
    symbolTable.put(9, 'I');
    EXPECT_EQ(4, symbolTable.getHashTableSize());

    symbolTable.put(5, 'E');
    EXPECT_EQ(8, symbolTable.getHashTableSize());

    symbolTable.put(4, 'D');
    symbolTable.put(7, 'G');
    EXPECT_EQ(16, symbolTable.getHashTableSize());

    symbolTable.put(3, 'C');
    EXPECT_EQ(16, symbolTable.getHashTableSize());
}

TEST(LinearProbingHashSymbolTableTest, DeleteBasedOnKeyWorksWithHalvingHashTableSize) {
    SymbolTableForTest symbolTable;
    symbolTable.put(8, 'H');
    symbolTable.put(9, 'I');
    symbolTable.put(5, 'E');
    symbolTable.put(4, 'D');
    symbolTable.put(7, 'G');
    symbolTable.put(3, 'C');

    EXPECT_EQ(16, symbolTable.getHashTableSize());

    symbolTable.deleteBasedOnKey(3);
    symbolTable.deleteBasedOnKey(4);
    symbolTable.deleteBasedOnKey(5);
    symbolTable.deleteBasedOnKey(7);
    EXPECT_EQ(8, symbolTable.getHashTableSize());

    symbolTable.deleteBasedOnKey(8);
    EXPECT_EQ(4, symbolTable.getHashTableSize());

    symbolTable.deleteBasedOnKey(9);
    EXPECT_EQ(4, symbolTable.getHashTableSize());
}

}  // namespace algorithm

}  // namespace alba
