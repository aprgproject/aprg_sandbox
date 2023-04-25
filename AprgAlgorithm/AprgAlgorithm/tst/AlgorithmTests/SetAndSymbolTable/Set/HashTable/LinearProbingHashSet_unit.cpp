#include <Algorithm/HashFunctions/ForPrimitiveTypes/UnsignedIntegerBasedHashFunction.hpp>
#include <Algorithm/SetAndSymbolTable/Set/HashTable/LinearProbingHashSet.hpp>
#include <AlgorithmTests/SetAndSymbolTable/Set/Utilities/CommonTestsWithSet.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSet;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using HashFunctionForTest = UnsignedIntegerBasedHashFunction<unsigned int, unsigned int>;
using SetForTest = LinearProbingHashSet<unsigned int, HashFunctionForTest>;
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

    EXPECT_EQ(1U, setObject.getHashTableSize());

    setObject.put(8U);
    setObject.put(9U);
    EXPECT_EQ(4U, setObject.getHashTableSize());

    setObject.put(5U);
    EXPECT_EQ(8U, setObject.getHashTableSize());

    setObject.put(4U);
    setObject.put(7U);
    EXPECT_EQ(16U, setObject.getHashTableSize());

    setObject.put(3U);
    EXPECT_EQ(16U, setObject.getHashTableSize());
}

TEST(LinearProbingHashSetTest, DeleteBasedOnKeyWorksWithHalvingHashTableSize) {
    SetForTest setObject;
    setObject.put(8U);
    setObject.put(9U);
    setObject.put(5U);
    setObject.put(4U);
    setObject.put(7U);
    setObject.put(3U);

    EXPECT_EQ(16U, setObject.getHashTableSize());

    setObject.deleteBasedOnKey(3U);
    setObject.deleteBasedOnKey(4U);
    setObject.deleteBasedOnKey(5U);
    setObject.deleteBasedOnKey(7U);
    EXPECT_EQ(8U, setObject.getHashTableSize());

    setObject.deleteBasedOnKey(8U);
    EXPECT_EQ(4U, setObject.getHashTableSize());

    setObject.deleteBasedOnKey(9U);
    EXPECT_EQ(4U, setObject.getHashTableSize());
}

}  // namespace algorithm

}  // namespace alba
