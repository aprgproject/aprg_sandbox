#include <Algorithm/SetAndSymbolTable/SymbolTable/LinkedList/UnorderedLinkedListSymbolTable.hpp>
#include <AlgorithmTests/SetAndSymbolTable/SymbolTable/Utilities/CommonTestsWithSymbolTable.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSymbolTable;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using SymbolTableForTest = UnorderedLinkedListSymbolTable<unsigned int, char>;
}

TEST(UnorderedLinkedListSymbolTableTest, IsEmptyWorksWhenEmpty) {
    testIsEmptyWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(UnorderedLinkedListSymbolTableTest, IsEmptyWorksWhenNotEmpty) {
    testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(UnorderedLinkedListSymbolTableTest, DoesContainWorks) {
    testDoesContainWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(UnorderedLinkedListSymbolTableTest, GetSizeWorksWhenEmpty) {
    testGetSizeWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(UnorderedLinkedListSymbolTableTest, GetSizeWorksWhenNotEmpty) {
    testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(UnorderedLinkedListSymbolTableTest, GetWorks) { testGetWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(UnorderedLinkedListSymbolTableTest, GetRankWorks) { testGetRankWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(UnorderedLinkedListSymbolTableTest, GetMinimumWorks) {
    testGetMinimumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(UnorderedLinkedListSymbolTableTest, GetMaximumWorks) {
    testGetMaximumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(UnorderedLinkedListSymbolTableTest, SelectAtWorks) { testSelectAtWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(UnorderedLinkedListSymbolTableTest, GetFloorWorks) { testGetFloorWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(UnorderedLinkedListSymbolTableTest, GetCeilingWorks) {
    testGetCeilingWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(UnorderedLinkedListSymbolTableTest, PutWorks) { testPutWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(UnorderedLinkedListSymbolTableTest, DeleteBasedOnKeyWorks) {
    testDeleteBasedOnKeyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(UnorderedLinkedListSymbolTableTest, DeleteMinimumWorks) {
    testDeleteMinimumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(UnorderedLinkedListSymbolTableTest, DeleteMaximumWorks) {
    testDeleteMaximumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(UnorderedLinkedListSymbolTableTest, GetKeys) { testGetKeysWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(UnorderedLinkedListSymbolTableTest, GetKeysInRangeWorks) {
    testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SymbolTableForTest>();
}

}  // namespace algorithm

}  // namespace alba
