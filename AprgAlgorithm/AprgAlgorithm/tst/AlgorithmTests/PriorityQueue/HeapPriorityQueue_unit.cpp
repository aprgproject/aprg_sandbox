#include <Algorithm/PriorityQueue/HeapPriorityQueue.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using PriorityQueueForTest = HeapPriorityQueue<char, std::less>;
}

TEST(HeapPriorityQueueTest, IsEmptyWorks)
{
    PriorityQueueForTest queue1;
    PriorityQueueForTest queue2;
    queue2.insert('A');

    EXPECT_TRUE(queue1.isEmpty());
    EXPECT_FALSE(queue2.isEmpty());
}

TEST(HeapPriorityQueueTest, GetSizeWorks)
{
    PriorityQueueForTest queue1;
    PriorityQueueForTest queue2;
    queue2.insert('P');
    queue2.insert('Q');
    queue2.insert('E');

    EXPECT_EQ(0U, queue1.getSize());
    EXPECT_EQ(3U, queue2.getSize());
}

TEST(HeapPriorityQueueTest, GetObjectsWorks)
{
    PriorityQueueForTest queue;
    queue.insert('P');
    queue.insert('Q');
    queue.insert('E');

    PriorityQueueForTest::Objects const& objectsToVerify(queue.getObjects());

    PriorityQueueForTest::Objects const objectsToExpect{'Q', 'P', 'E'};
    EXPECT_EQ(objectsToExpect, objectsToVerify);
}

TEST(HeapPriorityQueueTest, InsertWorksOnExample1)
{
    PriorityQueueForTest queue;

    queue.insert('P');
    queue.insert('Q');
    queue.insert('E');

    PriorityQueueForTest::Objects const& objectsToVerify(queue.getObjects());
    PriorityQueueForTest::Objects const objectsToExpect{'Q', 'P', 'E'};
    EXPECT_EQ(objectsToExpect, objectsToVerify);
}

TEST(HeapPriorityQueueTest, InsertWorksOnExample2)
{
    PriorityQueueForTest queue;

    queue.insert('S');
    queue.insert('P');
    queue.insert('R');
    queue.insert('N');
    queue.insert('T');
    queue.insert('O');
    queue.insert('A');
    queue.insert('E');
    queue.insert('I');
    queue.insert('G');
    queue.insert('H');

    PriorityQueueForTest::Objects const& objectsToVerify(queue.getObjects());
    PriorityQueueForTest::Objects const objectsToExpect
    {'T', 'S', 'R', 'N', 'P', 'O', 'A', 'E', 'I', 'G', 'H'};
    EXPECT_EQ(objectsToExpect, objectsToVerify);
}

TEST(HeapPriorityQueueTest, DeleteAndGetTopObjectWorksOnExample1)
{
    PriorityQueueForTest queue;
    queue.insert('P');
    queue.insert('Q');
    queue.insert('E');

    char objectToVerify(queue.deleteAndGetTopObject());

    EXPECT_EQ('Q', objectToVerify);
    PriorityQueueForTest::Objects const& objectsToVerify(queue.getObjects());
    PriorityQueueForTest::Objects const objectsToExpect
    {'E', 'P'};
    EXPECT_EQ(objectsToExpect, objectsToVerify);
}

TEST(HeapPriorityQueueTest, DeleteAndGetTopObjectWorksOnExample2)
{
    PriorityQueueForTest queue;
    queue.insert('S');
    queue.insert('P');
    queue.insert('R');
    queue.insert('N');
    queue.insert('T');
    queue.insert('O');
    queue.insert('A');
    queue.insert('E');
    queue.insert('I');
    queue.insert('G');
    queue.insert('H');

    char objectToVerify(queue.deleteAndGetTopObject());

    EXPECT_EQ('T', objectToVerify);
    PriorityQueueForTest::Objects const& objectsToVerify(queue.getObjects());
    PriorityQueueForTest::Objects const objectsToExpect
    {'S', 'P', 'R', 'N', 'H', 'O', 'A', 'E', 'I', 'G'};
    EXPECT_EQ(objectsToExpect, objectsToVerify);
}

}

}
