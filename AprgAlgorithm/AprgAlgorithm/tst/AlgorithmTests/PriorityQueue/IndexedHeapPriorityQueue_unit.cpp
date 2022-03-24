#include <Algorithm/PriorityQueue/IndexedHeapPriorityQueue.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::IndexedHeapPriorityQueueConstants;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using IndexedPriorityQueueForTest = IndexedHeapPriorityQueue<char, std::less, 2U>;
}

TEST(IndexedHeapPriorityQueueTest, IsEmptyWorks)
{
    IndexedPriorityQueueForTest indexedPQ1;
    IndexedPriorityQueueForTest indexedPQ2;
    indexedPQ2.insert(0U, 'A');

    EXPECT_TRUE(indexedPQ1.isEmpty());
    EXPECT_FALSE(indexedPQ2.isEmpty());
}

TEST(IndexedHeapPriorityQueueTest, ContainsWorks)
{
    IndexedPriorityQueueForTest indexedPQ;
    indexedPQ.insert(2U, 'C');

    EXPECT_FALSE(indexedPQ.contains(0U));
    EXPECT_FALSE(indexedPQ.contains(3U));
    EXPECT_TRUE(indexedPQ.contains(2U));
}

TEST(IndexedHeapPriorityQueueTest, GetSizeWorks)
{
    IndexedPriorityQueueForTest indexedPQ1;
    IndexedPriorityQueueForTest indexedPQ2;
    indexedPQ2.insert(1U, 'B');
    indexedPQ2.insert(2U, 'C');
    indexedPQ2.insert(4U, 'E');

    EXPECT_EQ(0U, indexedPQ1.getSize());
    EXPECT_EQ(3U, indexedPQ2.getSize());
}

TEST(IndexedHeapPriorityQueueTest, GetObjectsWorks)
{
    IndexedPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1U, 'B');
    indexedPQ.insert(2U, 'C');
    indexedPQ.insert(4U, 'E');

    IndexedPriorityQueueForTest::Objects const& expectedObjects{'\0', 'B', 'C', '\0', 'E'};
    EXPECT_EQ(expectedObjects, indexedPQ.getObjects());
}

TEST(IndexedHeapPriorityQueueTest, GetTreeIndexToObjectIndexWorks)
{
    IndexedPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1U, 'B');
    indexedPQ.insert(2U, 'C');
    indexedPQ.insert(4U, 'E');

    IndexedPriorityQueueForTest::Indexes const& expectedTreeIndexToObjectIndex{VALUE_FOR_UNUSED_INDEX, 4U, 1U, 2U, VALUE_FOR_UNUSED_INDEX};
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPQ.getTreeIndexToObjectIndex());
}

TEST(IndexedHeapPriorityQueueTest, GetObjectIndexToTreeIndexWorks)
{
    IndexedPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1U, 'B');
    indexedPQ.insert(2U, 'C');
    indexedPQ.insert(4U, 'E');

    IndexedPriorityQueueForTest::Indexes const& expectedObjectIndexToTreeIndex{VALUE_FOR_UNUSED_INDEX, 2U, 3U, VALUE_FOR_UNUSED_INDEX, 1U};
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPQ.getObjectIndexToTreeIndex());
}

TEST(IndexedHeapPriorityQueueTest, GetIndexOfTopObjectWorks)
{
    IndexedPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1U, 'B');
    indexedPQ.insert(2U, 'C');
    indexedPQ.insert(4U, 'E');

    EXPECT_EQ(4U, indexedPQ.getIndexOfTopObject());
}

TEST(IndexedHeapPriorityQueueTest, GetTopObjectWorks)
{
    IndexedPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1U, 'B');
    indexedPQ.insert(2U, 'C');
    indexedPQ.insert(4U, 'E');

    EXPECT_EQ('E', indexedPQ.getTopObject());
}

TEST(IndexedHeapPriorityQueueTest, GetObjectAtWorks)
{
    IndexedPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1U, 'B');
    indexedPQ.insert(2U, 'C');
    indexedPQ.insert(4U, 'E');

    EXPECT_EQ('\0', indexedPQ.getObjectAt(0U));
    EXPECT_EQ('B', indexedPQ.getObjectAt(1U));
    EXPECT_EQ('C', indexedPQ.getObjectAt(2U));
    EXPECT_EQ('\0', indexedPQ.getObjectAt(3U));
    EXPECT_EQ('E', indexedPQ.getObjectAt(4U));
}

TEST(IndexedHeapPriorityQueueTest, SetNumberOfItemsWorks)
{
    IndexedPriorityQueueForTest indexedPQ;

    indexedPQ.setNumberOfItems(5);

    EXPECT_EQ('\0', indexedPQ.getObjectAt(0U));
    EXPECT_EQ('\0', indexedPQ.getObjectAt(1U));
    EXPECT_EQ('\0', indexedPQ.getObjectAt(2U));
    EXPECT_EQ('\0', indexedPQ.getObjectAt(3U));
    EXPECT_EQ('\0', indexedPQ.getObjectAt(4U));
}

TEST(IndexedHeapPriorityQueueTest, InsertWorks)
{
    IndexedPriorityQueueForTest indexedPQ;

    indexedPQ.insert(1U, 'B');
    indexedPQ.insert(2U, 'C');
    indexedPQ.insert(4U, 'E');

    IndexedPriorityQueueForTest::Objects const& expectedObjects{'\0', 'B', 'C', '\0', 'E'};
    IndexedPriorityQueueForTest::Indexes const& expectedTreeIndexToObjectIndex{VALUE_FOR_UNUSED_INDEX, 4U, 1U, 2U, VALUE_FOR_UNUSED_INDEX};
    IndexedPriorityQueueForTest::Indexes const& expectedObjectIndexToTreeIndex{VALUE_FOR_UNUSED_INDEX, 2U, 3U, VALUE_FOR_UNUSED_INDEX, 1U};
    EXPECT_EQ(expectedObjects, indexedPQ.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPQ.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPQ.getObjectIndexToTreeIndex());
}

TEST(IndexedHeapPriorityQueueTest, DeleteAndGetTopObjectWorksWhenEmpty)
{
    IndexedPriorityQueueForTest indexedPQ;

    EXPECT_EQ('\0', indexedPQ.deleteAndGetTopObject());

    EXPECT_TRUE(indexedPQ.getObjects().empty());
    EXPECT_TRUE(indexedPQ.getTreeIndexToObjectIndex().empty());
    EXPECT_TRUE(indexedPQ.getObjectIndexToTreeIndex().empty());
}

TEST(IndexedHeapPriorityQueueTest, DeleteAndGetTopObjectWorksWhenNotEmpty)
{
    IndexedPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1U, 'B');
    indexedPQ.insert(2U, 'C');
    indexedPQ.insert(4U, 'E');

    EXPECT_EQ('E', indexedPQ.deleteAndGetTopObject());

    IndexedPriorityQueueForTest::Objects const& expectedObjects{'\0', 'B', 'C', '\0', '\0'};
    IndexedPriorityQueueForTest::Indexes const& expectedTreeIndexToObjectIndex{VALUE_FOR_UNUSED_INDEX, 2U, 1U, VALUE_FOR_UNUSED_INDEX, VALUE_FOR_UNUSED_INDEX};
    IndexedPriorityQueueForTest::Indexes const& expectedObjectIndexToTreeIndex{VALUE_FOR_UNUSED_INDEX, 2U, 1U, VALUE_FOR_UNUSED_INDEX, VALUE_FOR_UNUSED_INDEX};
    EXPECT_EQ(expectedObjects, indexedPQ.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPQ.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPQ.getObjectIndexToTreeIndex());
}

TEST(IndexedHeapPriorityQueueTest, DeleteObjectAtWorksWhenEmpty)
{
    IndexedPriorityQueueForTest indexedPQ;

    indexedPQ.deleteObjectAt(2U);

    EXPECT_TRUE(indexedPQ.getObjects().empty());
    EXPECT_TRUE(indexedPQ.getTreeIndexToObjectIndex().empty());
    EXPECT_TRUE(indexedPQ.getObjectIndexToTreeIndex().empty());
}

TEST(IndexedHeapPriorityQueueTest, DeleteObjectAtWorksWhenObjectExists)
{
    IndexedPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1U, 'B');
    indexedPQ.insert(2U, 'C');
    indexedPQ.insert(4U, 'E');

    indexedPQ.deleteObjectAt(2U);

    IndexedPriorityQueueForTest::Objects const& expectedObjects{'\0', 'B', '\0', '\0', 'E'};
    IndexedPriorityQueueForTest::Indexes const& expectedTreeIndexToObjectIndex{VALUE_FOR_UNUSED_INDEX, 4U, 1U, VALUE_FOR_UNUSED_INDEX, VALUE_FOR_UNUSED_INDEX};
    IndexedPriorityQueueForTest::Indexes const& expectedObjectIndexToTreeIndex{VALUE_FOR_UNUSED_INDEX, 2U, VALUE_FOR_UNUSED_INDEX, VALUE_FOR_UNUSED_INDEX, 1U};
    EXPECT_EQ(expectedObjects, indexedPQ.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPQ.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPQ.getObjectIndexToTreeIndex());
}

TEST(IndexedHeapPriorityQueueTest, DeleteObjectAtWorksWhenObjectDoesNotExist)
{
    IndexedPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1U, 'B');
    indexedPQ.insert(2U, 'C');
    indexedPQ.insert(4U, 'E');

    indexedPQ.deleteObjectAt(0U);

    IndexedPriorityQueueForTest::Objects const& expectedObjects{'\0', 'B', 'C', '\0', 'E'};
    IndexedPriorityQueueForTest::Indexes const& expectedTreeIndexToObjectIndex{VALUE_FOR_UNUSED_INDEX, 4U, 1U, 2U, VALUE_FOR_UNUSED_INDEX};
    IndexedPriorityQueueForTest::Indexes const& expectedObjectIndexToTreeIndex{VALUE_FOR_UNUSED_INDEX, 2U, 3U, VALUE_FOR_UNUSED_INDEX, 1U};
    EXPECT_EQ(expectedObjects, indexedPQ.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPQ.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPQ.getObjectIndexToTreeIndex());
}

TEST(IndexedHeapPriorityQueueTest, ChangeWorksWhenEmpty)
{
    IndexedPriorityQueueForTest indexedPQ;

    indexedPQ.change(2U, 'c');

    IndexedPriorityQueueForTest::Objects const& expectedObjects{'\0', '\0', 'c'};
    IndexedPriorityQueueForTest::Indexes const& expectedTreeIndexToObjectIndex{VALUE_FOR_UNUSED_INDEX, 2U, VALUE_FOR_UNUSED_INDEX};
    IndexedPriorityQueueForTest::Indexes const& expectedObjectIndexToTreeIndex{VALUE_FOR_UNUSED_INDEX, VALUE_FOR_UNUSED_INDEX, 1U};
    EXPECT_EQ(expectedObjects, indexedPQ.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPQ.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPQ.getObjectIndexToTreeIndex());
}

TEST(IndexedHeapPriorityQueueTest, ChangeWorksWhenObjectExists)
{
    IndexedPriorityQueueForTest indexedPQ;
    indexedPQ.insert(2U, 'C');

    indexedPQ.change(2U, 'c');

    IndexedPriorityQueueForTest::Objects const& expectedObjects{'\0', '\0', 'c'};
    IndexedPriorityQueueForTest::Indexes const& expectedTreeIndexToObjectIndex{VALUE_FOR_UNUSED_INDEX, 2U, VALUE_FOR_UNUSED_INDEX};
    IndexedPriorityQueueForTest::Indexes const& expectedObjectIndexToTreeIndex{VALUE_FOR_UNUSED_INDEX, VALUE_FOR_UNUSED_INDEX, 1U};
    EXPECT_EQ(expectedObjects, indexedPQ.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPQ.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPQ.getObjectIndexToTreeIndex());
}

TEST(IndexedHeapPriorityQueueTest, ChangeWorksWhenObjectDoesNotExist)
{
    IndexedPriorityQueueForTest indexedPQ;
    indexedPQ.insert(3U, 'D');

    indexedPQ.change(2U, 'c');

    IndexedPriorityQueueForTest::Objects const& expectedObjects{'\0', '\0', 'c', 'D'};
    IndexedPriorityQueueForTest::Indexes const& expectedTreeIndexToObjectIndex{VALUE_FOR_UNUSED_INDEX, 2U, 3U, VALUE_FOR_UNUSED_INDEX};
    IndexedPriorityQueueForTest::Indexes const& expectedObjectIndexToTreeIndex{VALUE_FOR_UNUSED_INDEX, VALUE_FOR_UNUSED_INDEX, 1U, 2U};
    EXPECT_EQ(expectedObjects, indexedPQ.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPQ.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPQ.getObjectIndexToTreeIndex());
}

}

}
