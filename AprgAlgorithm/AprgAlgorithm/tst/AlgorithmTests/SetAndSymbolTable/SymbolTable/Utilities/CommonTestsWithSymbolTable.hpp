#pragma once

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba {

namespace algorithm {

namespace CommonTestsWithSymbolTable {

template <typename SymbolTable>
void testIsEmptyWhenEmptyWithUnsignedIntAndChar() {
    SymbolTable symbolTable;

    EXPECT_TRUE(symbolTable.isEmpty());
}

template <typename SymbolTable>
void testIsEmptyWhenNotEmptyWithUnsignedIntAndChar() {
    SymbolTable symbolTable;
    symbolTable.put(5, 'E');

    EXPECT_FALSE(symbolTable.isEmpty());
}

template <typename SymbolTable>
void testDoesContainWithUnsignedIntAndChar() {
    SymbolTable symbolTable;
    symbolTable.put(5, 'E');

    EXPECT_FALSE(symbolTable.doesContain(4));
    EXPECT_TRUE(symbolTable.doesContain(5));
}

template <typename SymbolTable>
void testGetSizeWhenEmptyWithUnsignedIntAndChar() {
    SymbolTable symbolTable;

    EXPECT_EQ(0, symbolTable.getSize());
}

template <typename SymbolTable>
void testGetSizeWhenNotEmptyWithUnsignedIntAndChar() {
    SymbolTable symbolTable;
    symbolTable.put(7, 'G');
    symbolTable.put(5, 'E');
    symbolTable.put(6, 'F');

    EXPECT_EQ(3, symbolTable.getSize());
}

template <typename SymbolTable>
void testGetWithUnsignedIntAndChar() {
    SymbolTable symbolTable;
    symbolTable.put(7, 'G');
    symbolTable.put(5, 'E');
    symbolTable.put(6, 'F');

    EXPECT_EQ('E', symbolTable.get(5));
    EXPECT_EQ('F', symbolTable.get(6));
    EXPECT_EQ('G', symbolTable.get(7));
    EXPECT_EQ('\0', symbolTable.get(8));
}

template <typename SymbolTable>
void testGetRankWithUnsignedIntAndChar() {
    SymbolTable symbolTable;
    symbolTable.put(8, 'H');
    symbolTable.put(5, 'E');
    symbolTable.put(4, 'D');
    symbolTable.put(7, 'G');

    EXPECT_EQ(0, symbolTable.getRank(3));
    EXPECT_EQ(0, symbolTable.getRank(4));
    EXPECT_EQ(1, symbolTable.getRank(5));
    EXPECT_EQ(2, symbolTable.getRank(6));
    EXPECT_EQ(2, symbolTable.getRank(7));
    EXPECT_EQ(3, symbolTable.getRank(8));
    EXPECT_EQ(4, symbolTable.getRank(9));
}

template <typename SymbolTable>
void testGetMinimumWithUnsignedIntAndChar() {
    SymbolTable symbolTable;
    symbolTable.put(8, 'H');
    symbolTable.put(5, 'E');
    symbolTable.put(4, 'D');
    symbolTable.put(7, 'G');

    EXPECT_EQ(4, symbolTable.getMinimum());
}

template <typename SymbolTable>
void testGetMaximumWithUnsignedIntAndChar() {
    SymbolTable symbolTable;
    symbolTable.put(8, 'H');
    symbolTable.put(5, 'E');
    symbolTable.put(4, 'D');
    symbolTable.put(7, 'G');

    EXPECT_EQ(8, symbolTable.getMaximum());
}

template <typename SymbolTable>
void testSelectAtWithUnsignedIntAndChar() {
    SymbolTable symbolTable;
    symbolTable.put(8, 'H');
    symbolTable.put(5, 'E');
    symbolTable.put(4, 'D');
    symbolTable.put(7, 'G');

    EXPECT_EQ(4, symbolTable.selectAt(0));
    EXPECT_EQ(5, symbolTable.selectAt(1));
    EXPECT_EQ(7, symbolTable.selectAt(2));
    EXPECT_EQ(8, symbolTable.selectAt(3));
}

template <typename SymbolTable>
void testGetFloorWithUnsignedIntAndChar() {
    SymbolTable symbolTable;
    symbolTable.put(8, 'H');
    symbolTable.put(5, 'E');
    symbolTable.put(4, 'D');
    symbolTable.put(7, 'G');

    EXPECT_EQ(0, symbolTable.getFloor(3));
    EXPECT_EQ(4, symbolTable.getFloor(4));
    EXPECT_EQ(5, symbolTable.getFloor(5));
    EXPECT_EQ(5, symbolTable.getFloor(6));
    EXPECT_EQ(7, symbolTable.getFloor(7));
    EXPECT_EQ(8, symbolTable.getFloor(8));
    EXPECT_EQ(8, symbolTable.getFloor(9));
}

template <typename SymbolTable>
void testGetCeilingWithUnsignedIntAndChar() {
    SymbolTable symbolTable;
    symbolTable.put(8, 'H');
    symbolTable.put(5, 'E');
    symbolTable.put(4, 'D');
    symbolTable.put(7, 'G');

    EXPECT_EQ(4, symbolTable.getCeiling(3));
    EXPECT_EQ(4, symbolTable.getCeiling(4));
    EXPECT_EQ(5, symbolTable.getCeiling(5));
    EXPECT_EQ(7, symbolTable.getCeiling(6));
    EXPECT_EQ(7, symbolTable.getCeiling(7));
    EXPECT_EQ(8, symbolTable.getCeiling(8));
    EXPECT_EQ(0, symbolTable.getCeiling(9));
}

template <typename SymbolTable>
void testPutWithUnsignedIntAndChar() {
    SymbolTable symbolTable;
    symbolTable.put(7, 'G');
    symbolTable.put(5, 'E');
    symbolTable.put(6, 'F');

    ASSERT_EQ(3, symbolTable.getSize());
    EXPECT_EQ('E', symbolTable.get(5));
    EXPECT_EQ('F', symbolTable.get(6));
    EXPECT_EQ('G', symbolTable.get(7));
}

template <typename SymbolTable>
void testDeleteBasedOnKeyWithUnsignedIntAndChar() {
    SymbolTable symbolTable;
    symbolTable.put(7, 'G');
    symbolTable.put(5, 'E');
    symbolTable.put(6, 'F');

    symbolTable.deleteBasedOnKey(5);
    ASSERT_EQ(2, symbolTable.getSize());
    EXPECT_EQ('F', symbolTable.get(6));
    EXPECT_EQ('G', symbolTable.get(7));

    symbolTable.deleteBasedOnKey(6);
    ASSERT_EQ(1, symbolTable.getSize());
    EXPECT_EQ('G', symbolTable.get(7));

    symbolTable.deleteBasedOnKey(7);
    EXPECT_TRUE(symbolTable.isEmpty());
}

template <typename SymbolTable>
void testDeleteMinimumWithUnsignedIntAndChar() {
    SymbolTable symbolTable;
    symbolTable.put(7, 'G');
    symbolTable.put(5, 'E');
    symbolTable.put(6, 'F');

    symbolTable.deleteMinimum();
    ASSERT_EQ(2, symbolTable.getSize());
    EXPECT_EQ('F', symbolTable.get(6));
    EXPECT_EQ('G', symbolTable.get(7));
}

template <typename SymbolTable>
void testDeleteMaximumWithUnsignedIntAndChar() {
    SymbolTable symbolTable;
    symbolTable.put(7, 'G');
    symbolTable.put(5, 'E');
    symbolTable.put(6, 'F');

    symbolTable.deleteMaximum();
    ASSERT_EQ(2, symbolTable.getSize());
    EXPECT_EQ('E', symbolTable.get(5));
    EXPECT_EQ('F', symbolTable.get(6));
}

template <typename SymbolTable>
void testGetKeysWithUnsignedIntAndChar() {
    using Keys = typename SymbolTable::Keys;
    SymbolTable symbolTable;
    symbolTable.put(8, 'H');
    symbolTable.put(9, 'I');
    symbolTable.put(5, 'E');
    symbolTable.put(4, 'D');
    symbolTable.put(7, 'G');
    symbolTable.put(3, 'C');

    Keys keysToVerify(symbolTable.getKeys());

    Keys expectedKeys{3, 4, 5, 7, 8, 9};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

template <typename SymbolTable>
void testGetKeysInRangeInclusiveWithUnsignedIntAndChar() {
    using Keys = typename SymbolTable::Keys;
    SymbolTable symbolTable;
    symbolTable.put(8, 'H');
    symbolTable.put(9, 'I');
    symbolTable.put(5, 'E');
    symbolTable.put(4, 'D');
    symbolTable.put(7, 'G');
    symbolTable.put(3, 'C');

    Keys keysToVerify(symbolTable.getKeysInRangeInclusive(5, 8));

    Keys expectedKeys{5, 7, 8};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

}  // namespace CommonTestsWithSymbolTable

}  // namespace algorithm

}  // namespace alba
