#include <Algorithm/HashFunctions/ForPrimitiveTypes/UnsignedIntegerBasedHashFunction.hpp>
#include <Algorithm/SetAndSymbolTable/Set/HashTable/SeparateChainingHashSet.hpp>
#include <AlgorithmTests/SetAndSymbolTable/Set/Utilities/CommonTestsWithSet.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSet;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using HashFunctionForTest = UnsignedIntegerBasedHashFunction<unsigned int, unsigned int>;
using SetForTest = SeparateChainingHashSet<unsigned int, HashFunctionForTest, 2U>;
}

TEST(SeparateChainingHashSetTest, IsEmptyWorksWhenEmpty)
{
    testIsEmptyWhenEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, IsEmptyWorksWhenNotEmpty)
{
    testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, DoesContainWorks)
{
    testDoesContainWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, GetSizeWorksWhenEmpty)
{
    testGetSizeWhenEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, GetSizeWorksWhenNotEmpty)
{
    testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, GetWorks)
{
    testGetWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, GetRankWorks)
{
    testGetRankWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, GetMinimumWorks)
{
    testGetMinimumWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, GetMaximumWorks)
{
    testGetMaximumWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, SelectAtWorks)
{
    testSelectAtWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, GetFloorWorks)
{
    testGetFloorWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, GetCeilingWorks)
{
    testGetCeilingWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, PutWorks)
{
    testPutWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, DeleteBasedOnKeyWorks)
{
    testDeleteBasedOnKeyWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, DeleteMinimumWorks)
{
    testDeleteMinimumWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, DeleteMaximumWorks)
{
    testDeleteMaximumWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, GetKeys)
{
    testGetKeysWithUnsignedIntAndChar<SetForTest>();
}

TEST(SeparateChainingHashSetTest, GetKeysInRangeWorks)
{
    testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SetForTest>();
}

}

}
