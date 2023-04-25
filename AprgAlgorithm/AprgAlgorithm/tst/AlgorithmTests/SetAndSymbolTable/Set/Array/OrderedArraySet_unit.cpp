#include <Algorithm/SetAndSymbolTable/Set/Array/OrderedArraySet.hpp>
#include <AlgorithmTests/SetAndSymbolTable/Set/Utilities/CommonTestsWithSet.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSet;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using SetForTest = OrderedArraySet<unsigned int>;
}

TEST(OrderedArraySetTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithUnsignedIntAndChar<SetForTest>(); }

TEST(OrderedArraySetTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SetForTest>(); }

TEST(OrderedArraySetTest, DoesContainWorks) { testDoesContainWithUnsignedIntAndChar<SetForTest>(); }

TEST(OrderedArraySetTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithUnsignedIntAndChar<SetForTest>(); }

TEST(OrderedArraySetTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SetForTest>(); }

TEST(OrderedArraySetTest, GetWorks) { testGetWithUnsignedIntAndChar<SetForTest>(); }

TEST(OrderedArraySetTest, GetRankWorks) { testGetRankWithUnsignedIntAndChar<SetForTest>(); }

TEST(OrderedArraySetTest, GetMinimumWorks) { testGetMinimumWithUnsignedIntAndChar<SetForTest>(); }

TEST(OrderedArraySetTest, GetMaximumWorks) { testGetMaximumWithUnsignedIntAndChar<SetForTest>(); }

TEST(OrderedArraySetTest, SelectAtWorks) { testSelectAtWithUnsignedIntAndChar<SetForTest>(); }

TEST(OrderedArraySetTest, GetFloorWorks) { testGetFloorWithUnsignedIntAndChar<SetForTest>(); }

TEST(OrderedArraySetTest, GetCeilingWorks) { testGetCeilingWithUnsignedIntAndChar<SetForTest>(); }

TEST(OrderedArraySetTest, PutWorks) { testPutWithUnsignedIntAndChar<SetForTest>(); }

TEST(OrderedArraySetTest, DeleteBasedOnKeyWorks) { testDeleteBasedOnKeyWithUnsignedIntAndChar<SetForTest>(); }

TEST(OrderedArraySetTest, DeleteMinimumWorks) { testDeleteMinimumWithUnsignedIntAndChar<SetForTest>(); }

TEST(OrderedArraySetTest, DeleteMaximumWorks) { testDeleteMaximumWithUnsignedIntAndChar<SetForTest>(); }

TEST(OrderedArraySetTest, GetKeys) { testGetKeysWithUnsignedIntAndChar<SetForTest>(); }

TEST(OrderedArraySetTest, GetKeysInRangeWorks) { testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SetForTest>(); }

}  // namespace algorithm

}  // namespace alba
