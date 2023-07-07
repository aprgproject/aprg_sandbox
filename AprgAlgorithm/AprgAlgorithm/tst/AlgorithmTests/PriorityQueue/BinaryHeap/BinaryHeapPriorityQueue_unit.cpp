#include <Algorithm/PriorityQueue/BinaryHeap/BinaryHeapPriorityQueue.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
namespace algorithm {

namespace {
using MaxPriorityQueueForTest =
    BinaryHeapPriorityQueue<char, less>;  // less leads to Max Priority Queue same as in c++ standard
}

TEST(BinaryHeapPriorityQueueTest, IsEmptyWorks) {
    MaxPriorityQueueForTest queue1;
    MaxPriorityQueueForTest queue2;
    queue2.insert('A');
    EXPECT_TRUE(queue1.isEmpty());
    EXPECT_FALSE(queue2.isEmpty());
}

TEST(BinaryHeapPriorityQueueTest, GetSizeWorks) {
    MaxPriorityQueueForTest queue1;
    MaxPriorityQueueForTest queue2;
    queue2.insert('P');    queue2.insert('Q');
    queue2.insert('E');

    EXPECT_EQ(0, queue1.getSize());
    EXPECT_EQ(3, queue2.getSize());
}

TEST(BinaryHeapPriorityQueueTest, GetObjectsWorks) {
    MaxPriorityQueueForTest queue;
    queue.insert('P');
    queue.insert('Q');    queue.insert('E');

    MaxPriorityQueueForTest::Objects const& objectsToVerify(queue.getObjects());
    MaxPriorityQueueForTest::Objects const objectsToExpect{'Q', 'P', 'E'};
    EXPECT_EQ(objectsToExpect, objectsToVerify);
}

TEST(BinaryHeapPriorityQueueTest, GetTopWorks) {
    MaxPriorityQueueForTest queue;
    queue.insert('P');
    queue.insert('Q');    queue.insert('E');

    EXPECT_EQ('Q', queue.getTop());
}

TEST(BinaryHeapPriorityQueueTest, InsertWorksOnExample1) {
    MaxPriorityQueueForTest queue;

    queue.insert('P');    queue.insert('Q');
    queue.insert('E');

    MaxPriorityQueueForTest::Objects const& objectsToVerify(queue.getObjects());    MaxPriorityQueueForTest::Objects const objectsToExpect{'Q', 'P', 'E'};
    EXPECT_EQ(objectsToExpect, objectsToVerify);
}

TEST(BinaryHeapPriorityQueueTest, InsertWorksOnExample2) {
    MaxPriorityQueueForTest queue;

    queue.insert('S');    queue.insert('P');
    queue.insert('R');
    queue.insert('N');
    queue.insert('T');    queue.insert('O');
    queue.insert('A');
    queue.insert('E');
    queue.insert('I');
    queue.insert('G');
    queue.insert('H');

    MaxPriorityQueueForTest::Objects const& objectsToVerify(queue.getObjects());
    MaxPriorityQueueForTest::Objects const objectsToExpect{'T', 'S', 'R', 'N', 'P', 'O', 'A', 'E', 'I', 'G', 'H'};
    EXPECT_EQ(objectsToExpect, objectsToVerify);
}

TEST(BinaryHeapPriorityQueueTest, DeleteAndGetTopObjectWorksOnExample1) {
    MaxPriorityQueueForTest queue;
    queue.insert('P');
    queue.insert('Q');    queue.insert('E');

    char objectToVerify(queue.deleteAndGetTopObject());
    EXPECT_EQ('Q', objectToVerify);
    MaxPriorityQueueForTest::Objects const& objectsToVerify(queue.getObjects());
    MaxPriorityQueueForTest::Objects const objectsToExpect{'P', 'E'};
    EXPECT_EQ(objectsToExpect, objectsToVerify);
}

TEST(BinaryHeapPriorityQueueTest, DeleteAndGetTopObjectWorksOnExample2) {
    MaxPriorityQueueForTest queue;
    queue.insert('S');
    queue.insert('P');    queue.insert('R');
    queue.insert('N');
    queue.insert('T');
    queue.insert('O');    queue.insert('A');
    queue.insert('E');
    queue.insert('I');
    queue.insert('G');
    queue.insert('H');

    char objectToVerify(queue.deleteAndGetTopObject());

    EXPECT_EQ('T', objectToVerify);
    MaxPriorityQueueForTest::Objects const& objectsToVerify(queue.getObjects());
    MaxPriorityQueueForTest::Objects const objectsToExpect{'S', 'P', 'R', 'N', 'H', 'O', 'A', 'E', 'I', 'G'};
    EXPECT_EQ(objectsToExpect, objectsToVerify);
}

}  // namespace algorithm

}  // namespace alba
