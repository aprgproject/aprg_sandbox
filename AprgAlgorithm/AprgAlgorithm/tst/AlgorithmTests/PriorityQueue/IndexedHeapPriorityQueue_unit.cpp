#include <Algorithm/PriorityQueue/IndexedHeapPriorityQueue.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::IndexedHeapPriorityQueueConstants;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using IndexedMaxPriorityQueueForTest =
    IndexedHeapPriorityQueue<char, less, 2>;  // less leads to Max Priority Queue same as in c++ standard
}

TEST(IndexedHeapPriorityQueueTest, IsEmptyWorks) {
    IndexedMaxPriorityQueueForTest indexedPQ1;
    IndexedMaxPriorityQueueForTest indexedPQ2;
    indexedPQ2.insert(0, 'A');

    EXPECT_TRUE(indexedPQ1.isEmpty());
    EXPECT_FALSE(indexedPQ2.isEmpty());
}

TEST(IndexedHeapPriorityQueueTest, ContainsWorks) {
    IndexedMaxPriorityQueueForTest indexedPQ;
    indexedPQ.insert(2, 'C');

    EXPECT_FALSE(indexedPQ.contains(0));
    EXPECT_FALSE(indexedPQ.contains(3));
    EXPECT_TRUE(indexedPQ.contains(2));
}

TEST(IndexedHeapPriorityQueueTest, GetSizeWorks) {
    IndexedMaxPriorityQueueForTest indexedPQ1;
    IndexedMaxPriorityQueueForTest indexedPQ2;
    indexedPQ2.insert(1, 'B');
    indexedPQ2.insert(2, 'C');
    indexedPQ2.insert(4, 'E');

    EXPECT_EQ(0, indexedPQ1.getSize());
    EXPECT_EQ(3, indexedPQ2.getSize());
}

TEST(IndexedHeapPriorityQueueTest, GetObjectsWorks) {
    IndexedMaxPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1, 'B');
    indexedPQ.insert(2, 'C');
    indexedPQ.insert(4, 'E');

    IndexedMaxPriorityQueueForTest::Objects const& expectedObjects{'\0', 'B', 'C', '\0', 'E'};
    EXPECT_EQ(expectedObjects, indexedPQ.getObjects());
}

TEST(IndexedHeapPriorityQueueTest, GetTreeIndexToObjectIndexWorks) {
    IndexedMaxPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1, 'B');
    indexedPQ.insert(2, 'C');
    indexedPQ.insert(4, 'E');

    IndexedMaxPriorityQueueForTest::Indexes const& expectedTreeIndexToObjectIndex{
        VALUE_FOR_UNUSED_INDEX, 4, 1, 2, VALUE_FOR_UNUSED_INDEX};
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPQ.getTreeIndexToObjectIndex());
}

TEST(IndexedHeapPriorityQueueTest, GetObjectIndexToTreeIndexWorks) {
    IndexedMaxPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1, 'B');
    indexedPQ.insert(2, 'C');
    indexedPQ.insert(4, 'E');

    IndexedMaxPriorityQueueForTest::Indexes const& expectedObjectIndexToTreeIndex{
        VALUE_FOR_UNUSED_INDEX, 2, 3, VALUE_FOR_UNUSED_INDEX, 1};
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPQ.getObjectIndexToTreeIndex());
}

TEST(IndexedHeapPriorityQueueTest, GetIndexOfTopObjectWorks) {
    IndexedMaxPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1, 'B');
    indexedPQ.insert(2, 'C');
    indexedPQ.insert(4, 'E');

    EXPECT_EQ(4, indexedPQ.getIndexOfTopObject());
}

TEST(IndexedHeapPriorityQueueTest, GetTopObjectWorks) {
    IndexedMaxPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1, 'B');
    indexedPQ.insert(2, 'C');
    indexedPQ.insert(4, 'E');

    EXPECT_EQ('E', indexedPQ.getTopObject());
}

TEST(IndexedHeapPriorityQueueTest, GetObjectAtWorks) {
    IndexedMaxPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1, 'B');
    indexedPQ.insert(2, 'C');
    indexedPQ.insert(4, 'E');

    EXPECT_EQ('\0', indexedPQ.getObjectAt(0));
    EXPECT_EQ('B', indexedPQ.getObjectAt(1));
    EXPECT_EQ('C', indexedPQ.getObjectAt(2));
    EXPECT_EQ('\0', indexedPQ.getObjectAt(3));
    EXPECT_EQ('E', indexedPQ.getObjectAt(4));
}

TEST(IndexedHeapPriorityQueueTest, SetNumberOfItemsWorks) {
    IndexedMaxPriorityQueueForTest indexedPQ;

    indexedPQ.setNumberOfItems(5);

    EXPECT_EQ('\0', indexedPQ.getObjectAt(0));
    EXPECT_EQ('\0', indexedPQ.getObjectAt(1));
    EXPECT_EQ('\0', indexedPQ.getObjectAt(2));
    EXPECT_EQ('\0', indexedPQ.getObjectAt(3));
    EXPECT_EQ('\0', indexedPQ.getObjectAt(4));
}

TEST(IndexedHeapPriorityQueueTest, InsertWorks) {
    IndexedMaxPriorityQueueForTest indexedPQ;

    indexedPQ.insert(1, 'B');
    indexedPQ.insert(2, 'C');
    indexedPQ.insert(4, 'E');

    IndexedMaxPriorityQueueForTest::Objects const& expectedObjects{'\0', 'B', 'C', '\0', 'E'};
    IndexedMaxPriorityQueueForTest::Indexes const& expectedTreeIndexToObjectIndex{
        VALUE_FOR_UNUSED_INDEX, 4, 1, 2, VALUE_FOR_UNUSED_INDEX};
    IndexedMaxPriorityQueueForTest::Indexes const& expectedObjectIndexToTreeIndex{
        VALUE_FOR_UNUSED_INDEX, 2, 3, VALUE_FOR_UNUSED_INDEX, 1};
    EXPECT_EQ(expectedObjects, indexedPQ.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPQ.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPQ.getObjectIndexToTreeIndex());
}

TEST(IndexedHeapPriorityQueueTest, DeleteAndGetTopObjectWorksWhenEmpty) {
    IndexedMaxPriorityQueueForTest indexedPQ;

    EXPECT_EQ('\0', indexedPQ.deleteAndGetTopObject());

    EXPECT_TRUE(indexedPQ.getObjects().empty());
    EXPECT_TRUE(indexedPQ.getTreeIndexToObjectIndex().empty());
    EXPECT_TRUE(indexedPQ.getObjectIndexToTreeIndex().empty());
}

TEST(IndexedHeapPriorityQueueTest, DeleteAndGetTopObjectWorksWhenNotEmpty) {
    IndexedMaxPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1, 'B');
    indexedPQ.insert(2, 'C');
    indexedPQ.insert(4, 'E');

    EXPECT_EQ('E', indexedPQ.deleteAndGetTopObject());

    IndexedMaxPriorityQueueForTest::Objects const& expectedObjects{'\0', 'B', 'C', '\0', '\0'};
    IndexedMaxPriorityQueueForTest::Indexes const& expectedTreeIndexToObjectIndex{
        VALUE_FOR_UNUSED_INDEX, 2, 1, VALUE_FOR_UNUSED_INDEX, VALUE_FOR_UNUSED_INDEX};
    IndexedMaxPriorityQueueForTest::Indexes const& expectedObjectIndexToTreeIndex{
        VALUE_FOR_UNUSED_INDEX, 2, 1, VALUE_FOR_UNUSED_INDEX, VALUE_FOR_UNUSED_INDEX};
    EXPECT_EQ(expectedObjects, indexedPQ.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPQ.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPQ.getObjectIndexToTreeIndex());
}

TEST(IndexedHeapPriorityQueueTest, DeleteObjectAtWorksWhenEmpty) {
    IndexedMaxPriorityQueueForTest indexedPQ;

    indexedPQ.deleteObjectAt(2);

    EXPECT_TRUE(indexedPQ.getObjects().empty());
    EXPECT_TRUE(indexedPQ.getTreeIndexToObjectIndex().empty());
    EXPECT_TRUE(indexedPQ.getObjectIndexToTreeIndex().empty());
}

TEST(IndexedHeapPriorityQueueTest, DeleteObjectAtWorksWhenObjectExists) {
    IndexedMaxPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1, 'B');
    indexedPQ.insert(2, 'C');
    indexedPQ.insert(4, 'E');

    indexedPQ.deleteObjectAt(2);

    IndexedMaxPriorityQueueForTest::Objects const& expectedObjects{'\0', 'B', '\0', '\0', 'E'};
    IndexedMaxPriorityQueueForTest::Indexes const& expectedTreeIndexToObjectIndex{
        VALUE_FOR_UNUSED_INDEX, 4, 1, VALUE_FOR_UNUSED_INDEX, VALUE_FOR_UNUSED_INDEX};
    IndexedMaxPriorityQueueForTest::Indexes const& expectedObjectIndexToTreeIndex{
        VALUE_FOR_UNUSED_INDEX, 2, VALUE_FOR_UNUSED_INDEX, VALUE_FOR_UNUSED_INDEX, 1};
    EXPECT_EQ(expectedObjects, indexedPQ.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPQ.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPQ.getObjectIndexToTreeIndex());
}

TEST(IndexedHeapPriorityQueueTest, DeleteObjectAtWorksWhenObjectDoesNotExist) {
    IndexedMaxPriorityQueueForTest indexedPQ;
    indexedPQ.insert(1, 'B');
    indexedPQ.insert(2, 'C');
    indexedPQ.insert(4, 'E');

    indexedPQ.deleteObjectAt(0);

    IndexedMaxPriorityQueueForTest::Objects const& expectedObjects{'\0', 'B', 'C', '\0', 'E'};
    IndexedMaxPriorityQueueForTest::Indexes const& expectedTreeIndexToObjectIndex{
        VALUE_FOR_UNUSED_INDEX, 4, 1, 2, VALUE_FOR_UNUSED_INDEX};
    IndexedMaxPriorityQueueForTest::Indexes const& expectedObjectIndexToTreeIndex{
        VALUE_FOR_UNUSED_INDEX, 2, 3, VALUE_FOR_UNUSED_INDEX, 1};
    EXPECT_EQ(expectedObjects, indexedPQ.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPQ.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPQ.getObjectIndexToTreeIndex());
}

TEST(IndexedHeapPriorityQueueTest, ChangeWorksWhenEmpty) {
    IndexedMaxPriorityQueueForTest indexedPQ;

    indexedPQ.change(2, 'c');

    IndexedMaxPriorityQueueForTest::Objects const& expectedObjects{'\0', '\0', 'c'};
    IndexedMaxPriorityQueueForTest::Indexes const& expectedTreeIndexToObjectIndex{
        VALUE_FOR_UNUSED_INDEX, 2, VALUE_FOR_UNUSED_INDEX};
    IndexedMaxPriorityQueueForTest::Indexes const& expectedObjectIndexToTreeIndex{
        VALUE_FOR_UNUSED_INDEX, VALUE_FOR_UNUSED_INDEX, 1};
    EXPECT_EQ(expectedObjects, indexedPQ.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPQ.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPQ.getObjectIndexToTreeIndex());
}

TEST(IndexedHeapPriorityQueueTest, ChangeWorksWhenObjectExists) {
    IndexedMaxPriorityQueueForTest indexedPQ;
    indexedPQ.insert(2, 'C');

    indexedPQ.change(2, 'c');

    IndexedMaxPriorityQueueForTest::Objects const& expectedObjects{'\0', '\0', 'c'};
    IndexedMaxPriorityQueueForTest::Indexes const& expectedTreeIndexToObjectIndex{
        VALUE_FOR_UNUSED_INDEX, 2, VALUE_FOR_UNUSED_INDEX};
    IndexedMaxPriorityQueueForTest::Indexes const& expectedObjectIndexToTreeIndex{
        VALUE_FOR_UNUSED_INDEX, VALUE_FOR_UNUSED_INDEX, 1};
    EXPECT_EQ(expectedObjects, indexedPQ.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPQ.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPQ.getObjectIndexToTreeIndex());
}

TEST(IndexedHeapPriorityQueueTest, ChangeWorksWhenObjectDoesNotExist) {
    IndexedMaxPriorityQueueForTest indexedPQ;
    indexedPQ.insert(3, 'D');

    indexedPQ.change(2, 'c');

    IndexedMaxPriorityQueueForTest::Objects const& expectedObjects{'\0', '\0', 'c', 'D'};
    IndexedMaxPriorityQueueForTest::Indexes const& expectedTreeIndexToObjectIndex{
        VALUE_FOR_UNUSED_INDEX, 2, 3, VALUE_FOR_UNUSED_INDEX};
    IndexedMaxPriorityQueueForTest::Indexes const& expectedObjectIndexToTreeIndex{
        VALUE_FOR_UNUSED_INDEX, VALUE_FOR_UNUSED_INDEX, 1, 2};
    EXPECT_EQ(expectedObjects, indexedPQ.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPQ.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPQ.getObjectIndexToTreeIndex());
}

}  // namespace algorithm

}  // namespace alba
