#include <Algorithm/HashFunctions/PrimitiveTypes/IntegerHashFunction.hpp>
#include <Algorithm/SetAndSymbolTable/Set/HashTable/LinearProbingHashSet.hpp>
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
using SetForTest = LinearProbingHashSet<int, HashFunctionForTest>;
}  // namespace

TEST(LinearProbingHashSetTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithUnsignedIntAndChar<SetForTest>(); }

TEST(LinearProbingHashSetTest, IsEmptyWorksWhenNotEmpty) {
    testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(LinearProbingHashSetTest, DoesContainWorks) { testDoesContainWithUnsignedIntAndChar<SetForTest>(); }

TEST(LinearProbingHashSetTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithUnsignedIntAndChar<SetForTest>(); }

TEST(LinearProbingHashSetTest, GetSizeWorksWhenNotEmpty) {
    testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(LinearProbingHashSetTest, GetWorks) { testGetWithUnsignedIntAndChar<SetForTest>(); }

TEST(LinearProbingHashSetTest, GetRankWorks) { testGetRankWithUnsignedIntAndChar<SetForTest>(); }

TEST(LinearProbingHashSetTest, GetMinimumWorks) { testGetMinimumWithUnsignedIntAndChar<SetForTest>(); }

TEST(LinearProbingHashSetTest, GetMaximumWorks) { testGetMaximumWithUnsignedIntAndChar<SetForTest>(); }

TEST(LinearProbingHashSetTest, SelectAtWorks) { testSelectAtWithUnsignedIntAndChar<SetForTest>(); }

TEST(LinearProbingHashSetTest, GetFloorWorks) { testGetFloorWithUnsignedIntAndChar<SetForTest>(); }

TEST(LinearProbingHashSetTest, GetCeilingWorks) { testGetCeilingWithUnsignedIntAndChar<SetForTest>(); }

TEST(LinearProbingHashSetTest, PutWorks) { testPutWithUnsignedIntAndChar<SetForTest>(); }

TEST(LinearProbingHashSetTest, DeleteBasedOnKeyWorks) { testDeleteBasedOnKeyWithUnsignedIntAndChar<SetForTest>(); }

TEST(LinearProbingHashSetTest, DeleteMinimumWorks) { testDeleteMinimumWithUnsignedIntAndChar<SetForTest>(); }

TEST(LinearProbingHashSetTest, DeleteMaximumWorks) { testDeleteMaximumWithUnsignedIntAndChar<SetForTest>(); }

TEST(LinearProbingHashSetTest, GetKeys) { testGetKeysWithUnsignedIntAndChar<SetForTest>(); }

TEST(LinearProbingHashSetTest, GetKeysInRangeWorks) { testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SetForTest>(); }

TEST(LinearProbingHashSetTest, PutWorksWithDoublingHashTableSize) {
    SetForTest setObject;

    EXPECT_EQ(1, setObject.getHashTableSize());

    setObject.put(8);
    setObject.put(9);
    EXPECT_EQ(4, setObject.getHashTableSize());

    setObject.put(5);
    EXPECT_EQ(8, setObject.getHashTableSize());

    setObject.put(4);
    setObject.put(7);
    EXPECT_EQ(16, setObject.getHashTableSize());

    setObject.put(3);
    EXPECT_EQ(16, setObject.getHashTableSize());
}

TEST(LinearProbingHashSetTest, DeleteBasedOnKeyWorksWithHalvingHashTableSize) {
    SetForTest setObject;
    setObject.put(8);
    setObject.put(9);
    setObject.put(5);
    setObject.put(4);
    setObject.put(7);
    setObject.put(3);

    EXPECT_EQ(16, setObject.getHashTableSize());

    setObject.deleteBasedOnKey(3);
    setObject.deleteBasedOnKey(4);
    setObject.deleteBasedOnKey(5);
    setObject.deleteBasedOnKey(7);
    EXPECT_EQ(8, setObject.getHashTableSize());

    setObject.deleteBasedOnKey(8);
    EXPECT_EQ(4, setObject.getHashTableSize());

    setObject.deleteBasedOnKey(9);
    EXPECT_EQ(4, setObject.getHashTableSize());
}

}  // namespace algorithm

}  // namespace alba
