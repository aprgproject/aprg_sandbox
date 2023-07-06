#include <Algorithm/HashFunctions/PrimitiveTypes/IntegerHashFunction.hpp>
#include <Algorithm/SetAndSymbolTable/Set/HashTable/SeparateChainingHashSet.hpp>
#include <AlgorithmTests/SetAndSymbolTable/Set/Utilities/CommonTestsWithSet.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSet;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using HashValue = uint32_t;
constexpr HashValue HASH_TABLE_SIZE = 2;
using HashFunctionForTest = IntegerHashFunction<int, HashValue, HASH_TABLE_SIZE>;
using SetForTest = SeparateChainingHashSet<int, HashFunctionForTest, HASH_TABLE_SIZE>;
}  // namespace

TEST(SeparateChainingHashSetTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithUnsignedIntAndChar<SetForTest>(); }

TEST(SeparateChainingHashSetTest, IsEmptyWorksWhenNotEmpty) {
    testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, DoesContainWorks) { testDoesContainWithUnsignedIntAndChar<SetForTest>(); }

TEST(SeparateChainingHashSetTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithUnsignedIntAndChar<SetForTest>(); }

TEST(SeparateChainingHashSetTest, GetSizeWorksWhenNotEmpty) {
    testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, GetWorks) { testGetWithUnsignedIntAndChar<SetForTest>(); }

TEST(SeparateChainingHashSetTest, GetRankWorks) { testGetRankWithUnsignedIntAndChar<SetForTest>(); }

TEST(SeparateChainingHashSetTest, GetMinimumWorks) { testGetMinimumWithUnsignedIntAndChar<SetForTest>(); }

TEST(SeparateChainingHashSetTest, GetMaximumWorks) { testGetMaximumWithUnsignedIntAndChar<SetForTest>(); }

TEST(SeparateChainingHashSetTest, SelectAtWorks) { testSelectAtWithUnsignedIntAndChar<SetForTest>(); }

TEST(SeparateChainingHashSetTest, GetFloorWorks) { testGetFloorWithUnsignedIntAndChar<SetForTest>(); }

TEST(SeparateChainingHashSetTest, GetCeilingWorks) { testGetCeilingWithUnsignedIntAndChar<SetForTest>(); }

TEST(SeparateChainingHashSetTest, PutWorks) { testPutWithUnsignedIntAndChar<SetForTest>(); }

TEST(SeparateChainingHashSetTest, DeleteBasedOnKeyWorks) { testDeleteBasedOnKeyWithUnsignedIntAndChar<SetForTest>(); }

TEST(SeparateChainingHashSetTest, DeleteMinimumWorks) { testDeleteMinimumWithUnsignedIntAndChar<SetForTest>(); }

TEST(SeparateChainingHashSetTest, DeleteMaximumWorks) { testDeleteMaximumWithUnsignedIntAndChar<SetForTest>(); }

TEST(SeparateChainingHashSetTest, GetKeys) { testGetKeysWithUnsignedIntAndChar<SetForTest>(); }

TEST(SeparateChainingHashSetTest, GetKeysInRangeWorks) {
    testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SetForTest>();
}

}  // namespace algorithm

}  // namespace alba
