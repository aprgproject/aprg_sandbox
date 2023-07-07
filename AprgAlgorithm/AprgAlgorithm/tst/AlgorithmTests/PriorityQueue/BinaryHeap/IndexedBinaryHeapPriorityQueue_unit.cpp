#include <Algorithm/PriorityQueue/BinaryHeap/IndexedBinaryHeapPriorityQueue.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::IndexedBinaryHeapPriorityQueueConstants;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
// less leads to Max Priority Queue same as in c++ standard
using IndexedPqForTest = IndexedBinaryHeapPriorityQueue<char, less, 2>;
auto UNUSED = VALUE_FOR_UNUSED_INDEX;
}  // namespace

TEST(IndexedBinaryHeapPriorityQueueTest, IsEmptyWorks) {
    IndexedPqForTest indexedPQ1;
    IndexedPqForTest indexedPQ2;
    indexedPQ2.insert(0, 'A');

    EXPECT_TRUE(indexedPQ1.isEmpty());
    EXPECT_FALSE(indexedPQ2.isEmpty());
}

TEST(IndexedBinaryHeapPriorityQueueTest, ContainsWorks) {
    IndexedPqForTest indexedPq;
    indexedPq.insert(2, 'C');

    EXPECT_FALSE(indexedPq.contains(0));
    EXPECT_FALSE(indexedPq.contains(3));
    EXPECT_TRUE(indexedPq.contains(2));
}

TEST(IndexedBinaryHeapPriorityQueueTest, GetSizeWorks) {
    IndexedPqForTest indexedPQ1;
    IndexedPqForTest indexedPQ2;
    indexedPQ2.insert(1, 'B');
    indexedPQ2.insert(2, 'C');
    indexedPQ2.insert(4, 'E');
    indexedPQ2.insert(5, 'F');
    indexedPQ2.insert(6, 'G');

    EXPECT_EQ(0, indexedPQ1.getSize());
    EXPECT_EQ(5, indexedPQ2.getSize());
}

TEST(IndexedBinaryHeapPriorityQueueTest, GetObjectsWorks) {
    IndexedPqForTest indexedPq;
    indexedPq.insert(6, 'G');
    indexedPq.insert(5, 'F');
    indexedPq.insert(4, 'E');
    indexedPq.insert(2, 'C');
    indexedPq.insert(1, 'B');

    IndexedPqForTest::Objects const& expectedObjects{'\0', 'B', 'C', '\0', 'E', 'F', 'G'};
    EXPECT_EQ(expectedObjects, indexedPq.getObjects());
}

TEST(IndexedBinaryHeapPriorityQueueTest, GetTreeIndexToObjectIndexWorks) {
    IndexedPqForTest indexedPq;
    indexedPq.insert(6, 'G');
    indexedPq.insert(5, 'F');
    indexedPq.insert(4, 'E');
    indexedPq.insert(2, 'C');
    indexedPq.insert(1, 'B');

    IndexedPqForTest::Indexes const& expectedTreeIndexToObjectIndex{UNUSED, 6, 5, 4, 2, 1, UNUSED};
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPq.getTreeIndexToObjectIndex());
}

TEST(IndexedBinaryHeapPriorityQueueTest, GetObjectIndexToTreeIndexWorks) {
    IndexedPqForTest indexedPq;
    indexedPq.insert(6, 'G');
    indexedPq.insert(5, 'F');
    indexedPq.insert(4, 'E');
    indexedPq.insert(2, 'C');
    indexedPq.insert(1, 'B');

    IndexedPqForTest::Indexes const& expectedObjectIndexToTreeIndex{UNUSED, 5, 4, UNUSED, 3, 2, 1};
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPq.getObjectIndexToTreeIndex());
}

TEST(IndexedBinaryHeapPriorityQueueTest, GetIndexOfTopObjectWorks) {
    IndexedPqForTest indexedPq;
    indexedPq.insert(6, 'G');
    indexedPq.insert(5, 'F');
    indexedPq.insert(4, 'E');
    indexedPq.insert(2, 'C');
    indexedPq.insert(1, 'B');

    EXPECT_EQ(6, indexedPq.getIndexOfTopObject());
}

TEST(IndexedBinaryHeapPriorityQueueTest, GetTopObjectWorks) {
    IndexedPqForTest indexedPq;
    indexedPq.insert(6, 'G');
    indexedPq.insert(5, 'F');
    indexedPq.insert(4, 'E');
    indexedPq.insert(2, 'C');
    indexedPq.insert(1, 'B');

    EXPECT_EQ('G', indexedPq.getTopObject());
}

TEST(IndexedBinaryHeapPriorityQueueTest, GetObjectAtWorks) {
    IndexedPqForTest indexedPq;
    indexedPq.insert(6, 'G');
    indexedPq.insert(5, 'F');
    indexedPq.insert(4, 'E');
    indexedPq.insert(2, 'C');
    indexedPq.insert(1, 'B');

    EXPECT_EQ('\0', indexedPq.getObjectAt(0));
    EXPECT_EQ('B', indexedPq.getObjectAt(1));
    EXPECT_EQ('C', indexedPq.getObjectAt(2));
    EXPECT_EQ('\0', indexedPq.getObjectAt(3));
    EXPECT_EQ('E', indexedPq.getObjectAt(4));
    EXPECT_EQ('F', indexedPq.getObjectAt(5));
    EXPECT_EQ('G', indexedPq.getObjectAt(6));
}

TEST(IndexedBinaryHeapPriorityQueueTest, SetNumberOfItemsWorks) {
    IndexedPqForTest indexedPq;

    indexedPq.setNumberOfItems(7);

    EXPECT_EQ('\0', indexedPq.getObjectAt(0));
    EXPECT_EQ('\0', indexedPq.getObjectAt(1));
    EXPECT_EQ('\0', indexedPq.getObjectAt(2));
    EXPECT_EQ('\0', indexedPq.getObjectAt(3));
    EXPECT_EQ('\0', indexedPq.getObjectAt(4));
    EXPECT_EQ('\0', indexedPq.getObjectAt(5));
    EXPECT_EQ('\0', indexedPq.getObjectAt(6));
}

TEST(IndexedBinaryHeapPriorityQueueTest, InsertWorks) {
    IndexedPqForTest indexedPq;

    indexedPq.insert(6, 'G');
    indexedPq.insert(5, 'F');
    indexedPq.insert(4, 'E');
    indexedPq.insert(2, 'C');
    indexedPq.insert(1, 'B');

    IndexedPqForTest::Objects const& expectedObjects{'\0', 'B', 'C', '\0', 'E', 'F', 'G'};
    IndexedPqForTest::Indexes const& expectedTreeIndexToObjectIndex{UNUSED, 6, 5, 4, 2, 1, UNUSED};
    IndexedPqForTest::Indexes const& expectedObjectIndexToTreeIndex{UNUSED, 5, 4, UNUSED, 3, 2, 1};
    EXPECT_EQ(expectedObjects, indexedPq.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPq.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPq.getObjectIndexToTreeIndex());
}

TEST(IndexedBinaryHeapPriorityQueueTest, DeleteAndGetTopObjectWorksWhenEmpty) {
    IndexedPqForTest indexedPq;

    EXPECT_EQ('\0', indexedPq.deleteAndGetTopObject());

    EXPECT_TRUE(indexedPq.getObjects().empty());
    EXPECT_TRUE(indexedPq.getTreeIndexToObjectIndex().empty());
    EXPECT_TRUE(indexedPq.getObjectIndexToTreeIndex().empty());
}

TEST(IndexedBinaryHeapPriorityQueueTest, DeleteAndGetTopObjectWorksWhenNotEmpty) {
    IndexedPqForTest indexedPq;
    indexedPq.insert(6, 'G');
    indexedPq.insert(5, 'F');
    indexedPq.insert(4, 'E');
    indexedPq.insert(2, 'C');
    indexedPq.insert(1, 'B');

    EXPECT_EQ('G', indexedPq.deleteAndGetTopObject());

    IndexedPqForTest::Objects const& expectedObjects{'\0', 'B', 'C', '\0', 'E', 'F', '\0'};
    IndexedPqForTest::Indexes const& expectedTreeIndexToObjectIndex{UNUSED, 5, 2, 4, 1, UNUSED, UNUSED};
    IndexedPqForTest::Indexes const& expectedObjectIndexToTreeIndex{UNUSED, 4, 2, UNUSED, 3, 1, UNUSED};
    EXPECT_EQ(expectedObjects, indexedPq.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPq.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPq.getObjectIndexToTreeIndex());
}

TEST(IndexedBinaryHeapPriorityQueueTest, DeleteObjectAtWorksWhenEmpty) {
    IndexedPqForTest indexedPq;

    indexedPq.deleteObjectAt(2);

    EXPECT_TRUE(indexedPq.getObjects().empty());
    EXPECT_TRUE(indexedPq.getTreeIndexToObjectIndex().empty());
    EXPECT_TRUE(indexedPq.getObjectIndexToTreeIndex().empty());
}

TEST(IndexedBinaryHeapPriorityQueueTest, DeleteObjectAtWorksWhenObjectExists) {
    IndexedPqForTest indexedPq;
    indexedPq.insert(6, 'G');
    indexedPq.insert(5, 'F');
    indexedPq.insert(4, 'E');
    indexedPq.insert(2, 'C');
    indexedPq.insert(1, 'B');

    indexedPq.deleteObjectAt(2);

    IndexedPqForTest::Objects const& expectedObjects{'\0', 'B', '\0', '\0', 'E', 'F', 'G'};
    IndexedPqForTest::Indexes const& expectedTreeIndexToObjectIndex{UNUSED, 6, 5, 4, 1, UNUSED, UNUSED};
    IndexedPqForTest::Indexes const& expectedObjectIndexToTreeIndex{UNUSED, 4, UNUSED, UNUSED, 3, 2, 1};
    EXPECT_EQ(expectedObjects, indexedPq.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPq.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPq.getObjectIndexToTreeIndex());
}

TEST(IndexedBinaryHeapPriorityQueueTest, DeleteObjectAtWorksWhenObjectDoesNotExist) {
    IndexedPqForTest indexedPq;
    indexedPq.insert(6, 'G');
    indexedPq.insert(5, 'F');
    indexedPq.insert(4, 'E');
    indexedPq.insert(2, 'C');
    indexedPq.insert(1, 'B');

    indexedPq.deleteObjectAt(0);

    IndexedPqForTest::Objects const& expectedObjects{'\0', 'B', 'C', '\0', 'E', 'F', 'G'};
    IndexedPqForTest::Indexes const& expectedTreeIndexToObjectIndex{UNUSED, 6, 5, 4, 2, 1, UNUSED};
    IndexedPqForTest::Indexes const& expectedObjectIndexToTreeIndex{UNUSED, 5, 4, UNUSED, 3, 2, 1};
    EXPECT_EQ(expectedObjects, indexedPq.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPq.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPq.getObjectIndexToTreeIndex());
}

TEST(IndexedBinaryHeapPriorityQueueTest, ChangeWorksWhenEmpty) {
    IndexedPqForTest indexedPq;

    indexedPq.change(2, 'c');

    IndexedPqForTest::Objects const& expectedObjects{'\0', '\0', 'c'};
    IndexedPqForTest::Indexes const& expectedTreeIndexToObjectIndex{UNUSED, 2, UNUSED};
    IndexedPqForTest::Indexes const& expectedObjectIndexToTreeIndex{UNUSED, UNUSED, 1};
    EXPECT_EQ(expectedObjects, indexedPq.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPq.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPq.getObjectIndexToTreeIndex());
}

TEST(IndexedBinaryHeapPriorityQueueTest, ChangeWorksWhenObjectExists) {
    IndexedPqForTest indexedPq;
    indexedPq.insert(6, 'G');
    indexedPq.insert(5, 'F');
    indexedPq.insert(4, 'E');
    indexedPq.insert(2, 'C');
    indexedPq.insert(1, 'B');

    indexedPq.change(2, 'c');

    IndexedPqForTest::Objects const& expectedObjects{'\0', 'B', 'c', '\0', 'E', 'F', 'G'};
    IndexedPqForTest::Indexes const& expectedTreeIndexToObjectIndex{UNUSED, 2, 6, 4, 5, 1, UNUSED};
    IndexedPqForTest::Indexes const& expectedObjectIndexToTreeIndex{UNUSED, 5, 1, UNUSED, 3, 4, 2};
    EXPECT_EQ(expectedObjects, indexedPq.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPq.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPq.getObjectIndexToTreeIndex());
}

TEST(IndexedBinaryHeapPriorityQueueTest, ChangeWorksWhenObjectDoesNotExist) {
    IndexedPqForTest indexedPq;
    indexedPq.insert(6, 'G');
    indexedPq.insert(5, 'F');
    indexedPq.insert(4, 'E');
    indexedPq.insert(2, 'C');
    indexedPq.insert(1, 'B');

    indexedPq.change(7, 'H');

    IndexedPqForTest::Objects const& expectedObjects{'\0', 'B', 'C', '\0', 'E', 'F', 'G', 'H'};
    IndexedPqForTest::Indexes const& expectedTreeIndexToObjectIndex{UNUSED, 7, 5, 6, 2, 1, 4, UNUSED};
    IndexedPqForTest::Indexes const& expectedObjectIndexToTreeIndex{UNUSED, 5, 4, UNUSED, 6, 2, 3, 1};
    EXPECT_EQ(expectedObjects, indexedPq.getObjects());
    EXPECT_EQ(expectedTreeIndexToObjectIndex, indexedPq.getTreeIndexToObjectIndex());
    EXPECT_EQ(expectedObjectIndexToTreeIndex, indexedPq.getObjectIndexToTreeIndex());
}

}  // namespace algorithm

}  // namespace alba
