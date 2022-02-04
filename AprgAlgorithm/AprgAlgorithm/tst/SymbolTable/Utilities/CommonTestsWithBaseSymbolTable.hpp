#pragma once

#include <SymbolTable/BaseSymbolTable.hpp>

namespace alba
{

namespace CommonTestsWithBaseSymbolTable
{

using BaseSymbolTableForUnsignedInt = BaseSymbolTable<unsigned int, char>;

void performIsEmptyTestWhenEmpty(BaseSymbolTableForUnsignedInt & symbolTable);
void performIsEmptyTestWhenNotEmpty(BaseSymbolTableForUnsignedInt & symbolTable);
void performDoesContainTest(BaseSymbolTableForUnsignedInt & symbolTable);
void performGetSizeTestWhenEmpty(BaseSymbolTableForUnsignedInt & symbolTable);
void performGetSizeTestWhenNotEmpty(BaseSymbolTableForUnsignedInt & symbolTable);
void performGetTest(BaseSymbolTableForUnsignedInt & symbolTable);
void performGetRankTest(BaseSymbolTableForUnsignedInt & symbolTable);
void performGetMinimumTest(BaseSymbolTableForUnsignedInt & symbolTable);
void performGetMaximumTest(BaseSymbolTableForUnsignedInt & symbolTable);
void performSelectAtTest(BaseSymbolTableForUnsignedInt & symbolTable);
void performGetFloorTest(BaseSymbolTableForUnsignedInt & symbolTable);
void performGetCeilingTest(BaseSymbolTableForUnsignedInt & symbolTable);
void performPutTest(BaseSymbolTableForUnsignedInt & symbolTable);
void performDeleteBasedOnKeyTest(BaseSymbolTableForUnsignedInt & symbolTable);
void performDeleteMinimumTest(BaseSymbolTableForUnsignedInt & symbolTable);
void performDeleteMaximumTest(BaseSymbolTableForUnsignedInt & symbolTable);
void performGetKeysTest(BaseSymbolTableForUnsignedInt & symbolTable);
void performGetKeysInRangeInclusiveTest(BaseSymbolTableForUnsignedInt & symbolTable);

}

}
