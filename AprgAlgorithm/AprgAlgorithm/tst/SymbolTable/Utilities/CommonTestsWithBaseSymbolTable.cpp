#include <SymbolTable/Utilities/CommonTestsWithBaseSymbolTable.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba
{

namespace CommonTestsWithBaseSymbolTable
{

void performIsEmptyTestWhenEmpty(BaseSymbolTableForUnsignedInt & symbolTable)
{
    EXPECT_TRUE(symbolTable.isEmpty());
}

void performIsEmptyTestWhenNotEmpty(BaseSymbolTableForUnsignedInt & symbolTable)
{
    symbolTable.put(5U, 'E');

    EXPECT_FALSE(symbolTable.isEmpty());
}

void performDoesContainTest(BaseSymbolTableForUnsignedInt & symbolTable)
{
    symbolTable.put(5U, 'E');

    EXPECT_FALSE(symbolTable.doesContain(4U));
    EXPECT_TRUE(symbolTable.doesContain(5U));
}

void performGetSizeTestWhenEmpty(BaseSymbolTableForUnsignedInt & symbolTable)
{
    EXPECT_EQ(0U, symbolTable.getSize());}

void performGetSizeTestWhenNotEmpty(BaseSymbolTableForUnsignedInt & symbolTable)
{
    symbolTable.put(7U, 'G');    symbolTable.put(5U, 'E');
    symbolTable.put(6U, 'F');

    EXPECT_EQ(3U, symbolTable.getSize());
}

void performGetTest(BaseSymbolTableForUnsignedInt & symbolTable)
{
    symbolTable.put(7U, 'G');
    symbolTable.put(5U, 'E');
    symbolTable.put(6U, 'F');

    EXPECT_EQ('E', symbolTable.get(5U));
    EXPECT_EQ('F', symbolTable.get(6U));
    EXPECT_EQ('G', symbolTable.get(7U));
    EXPECT_EQ('\0', symbolTable.get(8U));
}

void performGetRankTest(BaseSymbolTableForUnsignedInt & symbolTable)
{
    symbolTable.put(8U, 'H');
    symbolTable.put(5U, 'E');
    symbolTable.put(4U, 'D');
    symbolTable.put(7U, 'G');

    EXPECT_EQ(0U, symbolTable.getRank(3U));
    EXPECT_EQ(0U, symbolTable.getRank(4U));
    EXPECT_EQ(1U, symbolTable.getRank(5U));
    EXPECT_EQ(2U, symbolTable.getRank(6U));
    EXPECT_EQ(2U, symbolTable.getRank(7U));
    EXPECT_EQ(3U, symbolTable.getRank(8U));
    EXPECT_EQ(4U, symbolTable.getRank(9U));
}

void performGetMinimumTest(BaseSymbolTableForUnsignedInt & symbolTable)
{
    symbolTable.put(8U, 'H');
    symbolTable.put(5U, 'E');
    symbolTable.put(4U, 'D');
    symbolTable.put(7U, 'G');

    EXPECT_EQ(4U, symbolTable.getMinimum());
}

void performGetMaximumTest(BaseSymbolTableForUnsignedInt & symbolTable)
{
    symbolTable.put(8U, 'H');
    symbolTable.put(5U, 'E');
    symbolTable.put(4U, 'D');
    symbolTable.put(7U, 'G');

    EXPECT_EQ(8U, symbolTable.getMaximum());
}

void performSelectAtTest(BaseSymbolTableForUnsignedInt & symbolTable)
{
    symbolTable.put(8U, 'H');
    symbolTable.put(5U, 'E');
    symbolTable.put(4U, 'D');
    symbolTable.put(7U, 'G');

    EXPECT_EQ(4U, symbolTable.selectAt(0U));
    EXPECT_EQ(5U, symbolTable.selectAt(1U));
    EXPECT_EQ(7U, symbolTable.selectAt(2U));
    EXPECT_EQ(8U, symbolTable.selectAt(3U));
}

void performGetFloorTest(BaseSymbolTableForUnsignedInt & symbolTable)
{
    symbolTable.put(8U, 'H');
    symbolTable.put(5U, 'E');
    symbolTable.put(4U, 'D');
    symbolTable.put(7U, 'G');

    EXPECT_EQ(0U, symbolTable.getFloor(3U));
    EXPECT_EQ(4U, symbolTable.getFloor(4U));
    EXPECT_EQ(5U, symbolTable.getFloor(5U));
    EXPECT_EQ(5U, symbolTable.getFloor(6U));
    EXPECT_EQ(7U, symbolTable.getFloor(7U));
    EXPECT_EQ(8U, symbolTable.getFloor(8U));
    EXPECT_EQ(8U, symbolTable.getFloor(9U));
}

void performGetCeilingTest(BaseSymbolTableForUnsignedInt & symbolTable)
{
    symbolTable.put(8U, 'H');
    symbolTable.put(5U, 'E');
    symbolTable.put(4U, 'D');
    symbolTable.put(7U, 'G');

    EXPECT_EQ(4U, symbolTable.getCeiling(3U));
    EXPECT_EQ(4U, symbolTable.getCeiling(4U));
    EXPECT_EQ(5U, symbolTable.getCeiling(5U));
    EXPECT_EQ(7U, symbolTable.getCeiling(6U));
    EXPECT_EQ(7U, symbolTable.getCeiling(7U));
    EXPECT_EQ(8U, symbolTable.getCeiling(8U));
    EXPECT_EQ(0U, symbolTable.getCeiling(9U));
}

void performPutTest(BaseSymbolTableForUnsignedInt & symbolTable)
{
    symbolTable.put(7U, 'G');
    symbolTable.put(5U, 'E');
    symbolTable.put(6U, 'F');

    ASSERT_EQ(3U, symbolTable.getSize());
    EXPECT_EQ('E', symbolTable.get(5U));
    EXPECT_EQ('F', symbolTable.get(6U));
    EXPECT_EQ('G', symbolTable.get(7U));
}

void performDeleteBasedOnKeyTest(BaseSymbolTableForUnsignedInt & symbolTable)
{
    symbolTable.put(7U, 'G');
    symbolTable.put(5U, 'E');
    symbolTable.put(6U, 'F');

    symbolTable.deleteBasedOnKey(5U);
    ASSERT_EQ(2U, symbolTable.getSize());
    EXPECT_EQ('F', symbolTable.get(6U));
    EXPECT_EQ('G', symbolTable.get(7U));

    symbolTable.deleteBasedOnKey(6U);
    ASSERT_EQ(1U, symbolTable.getSize());
    EXPECT_EQ('G', symbolTable.get(7U));

    symbolTable.deleteBasedOnKey(7U);
    EXPECT_TRUE(symbolTable.isEmpty());
}

void performDeleteMinimumTest(BaseSymbolTableForUnsignedInt & symbolTable)
{
    symbolTable.put(7U, 'G');
    symbolTable.put(5U, 'E');
    symbolTable.put(6U, 'F');

    symbolTable.deleteMinimum();
    ASSERT_EQ(2U, symbolTable.getSize());
    EXPECT_EQ('F', symbolTable.get(6U));
    EXPECT_EQ('G', symbolTable.get(7U));
}

void performDeleteMaximumTest(BaseSymbolTableForUnsignedInt & symbolTable)
{
    symbolTable.put(7U, 'G');
    symbolTable.put(5U, 'E');
    symbolTable.put(6U, 'F');

    symbolTable.deleteMaximum();
    ASSERT_EQ(2U, symbolTable.getSize());
    EXPECT_EQ('E', symbolTable.get(5U));
    EXPECT_EQ('F', symbolTable.get(6U));
}

void performGetKeysTest(BaseSymbolTableForUnsignedInt & symbolTable)
{
    symbolTable.put(8U, 'H');
    symbolTable.put(9U, 'I');
    symbolTable.put(5U, 'E');
    symbolTable.put(4U, 'D');
    symbolTable.put(7U, 'G');
    symbolTable.put(3U, 'C');

    vector<unsigned int> keysToVerify(symbolTable.getKeys());

    vector<unsigned int> expectedKeys{3U, 4U, 5U, 7U, 8U, 9U};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

void performGetKeysInRangeInclusiveTest(BaseSymbolTableForUnsignedInt & symbolTable)
{
    symbolTable.put(8U, 'H');
    symbolTable.put(9U, 'I');
    symbolTable.put(5U, 'E');
    symbolTable.put(4U, 'D');
    symbolTable.put(7U, 'G');
    symbolTable.put(3U, 'C');

    vector<unsigned int> keysToVerify(symbolTable.getKeysInRangeInclusive(5U, 8U));

    vector<unsigned int> expectedKeys{5U, 7U, 8U};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

}

}
