#include <Algorithm/SetAndSymbolTable/Set/LinkedList/UnorderedLinkedListSet.hpp>
#include <AlgorithmTests/SetAndSymbolTable/Set/Utilities/CommonTestsWithSet.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSet;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using SetForTest = UnorderedLinkedListSet<unsigned int>;
}

TEST(UnorderedLinkedListSetTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithUnsignedIntAndChar<SetForTest>(); }

TEST(UnorderedLinkedListSetTest, IsEmptyWorksWhenNotEmpty) {
    testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(UnorderedLinkedListSetTest, DoesContainWorks) { testDoesContainWithUnsignedIntAndChar<SetForTest>(); }

TEST(UnorderedLinkedListSetTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithUnsignedIntAndChar<SetForTest>(); }

TEST(UnorderedLinkedListSetTest, GetSizeWorksWhenNotEmpty) {
    testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(UnorderedLinkedListSetTest, GetWorks) { testGetWithUnsignedIntAndChar<SetForTest>(); }

TEST(UnorderedLinkedListSetTest, GetRankWorks) { testGetRankWithUnsignedIntAndChar<SetForTest>(); }

TEST(UnorderedLinkedListSetTest, GetMinimumWorks) { testGetMinimumWithUnsignedIntAndChar<SetForTest>(); }

TEST(UnorderedLinkedListSetTest, GetMaximumWorks) { testGetMaximumWithUnsignedIntAndChar<SetForTest>(); }

TEST(UnorderedLinkedListSetTest, SelectAtWorks) { testSelectAtWithUnsignedIntAndChar<SetForTest>(); }

TEST(UnorderedLinkedListSetTest, GetFloorWorks) { testGetFloorWithUnsignedIntAndChar<SetForTest>(); }

TEST(UnorderedLinkedListSetTest, GetCeilingWorks) { testGetCeilingWithUnsignedIntAndChar<SetForTest>(); }

TEST(UnorderedLinkedListSetTest, PutWorks) { testPutWithUnsignedIntAndChar<SetForTest>(); }

TEST(UnorderedLinkedListSetTest, DeleteBasedOnKeyWorks) { testDeleteBasedOnKeyWithUnsignedIntAndChar<SetForTest>(); }

TEST(UnorderedLinkedListSetTest, DeleteMinimumWorks) { testDeleteMinimumWithUnsignedIntAndChar<SetForTest>(); }

TEST(UnorderedLinkedListSetTest, DeleteMaximumWorks) { testDeleteMaximumWithUnsignedIntAndChar<SetForTest>(); }

TEST(UnorderedLinkedListSetTest, GetKeys) { testGetKeysWithUnsignedIntAndChar<SetForTest>(); }

TEST(UnorderedLinkedListSetTest, GetKeysInRangeWorks) {
    testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SetForTest>();
}

}  // namespace algorithm

}  // namespace alba
