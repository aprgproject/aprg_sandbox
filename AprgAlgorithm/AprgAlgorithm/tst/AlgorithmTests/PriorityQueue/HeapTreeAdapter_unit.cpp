#include <Algorithm/PriorityQueue/HeapTreeAdapter.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ContainerForTest = vector<char>;
using AdapterForTest = HeapTreeAdapter<ContainerForTest, 2, less>;
}  // namespace

TEST(HeapTreeAdapterTest, GetObjectConstReferenceOnTreeWorks) {
    ContainerForTest objects{'H', 'E', 'A', 'P', 'O', 'B', 'J', 'E', 'C', 'T', 'S'};
    AdapterForTest adapter(objects);

    EXPECT_EQ('H', adapter.getObjectOnTree(1));
    EXPECT_EQ('E', adapter.getObjectOnTree(2));
    EXPECT_EQ('A', adapter.getObjectOnTree(3));
    EXPECT_EQ('P', adapter.getObjectOnTree(4));
    EXPECT_EQ('S', adapter.getObjectOnTree(objects.size()));
}

TEST(HeapTreeAdapterTest, GetObjectReferenceOnTreeWorks) {
    ContainerForTest objects{'H', 'E', 'A', 'P', 'O', 'B', 'J', 'E', 'C', 'T', 'S'};
    AdapterForTest adapter(objects);

    char& characterAtTopOfTree(adapter.getObjectReferenceOnTree(1));

    characterAtTopOfTree = 'Z';

    ContainerForTest objectsToExpect{'Z', 'E', 'A', 'P', 'O', 'B', 'J', 'E', 'C', 'T', 'S'};
    EXPECT_EQ(objectsToExpect, objects);
}

TEST(HeapTreeAdapterTest, SwimWorks) {
    ContainerForTest objects{'H', 'E', 'A', 'P', 'O', 'B', 'J', 'E', 'C', 'T', 'S'};
    AdapterForTest adapter(objects);

    adapter.swim(objects.size());

    ContainerForTest objectsToExpect{'S', 'H', 'A', 'P', 'E', 'B', 'J', 'E', 'C', 'T', 'O'};
    EXPECT_EQ(objectsToExpect, objects);
}

TEST(HeapTreeAdapterTest, SinkWorksOnExample1) {
    ContainerForTest objects{'A', 'D', 'A', 'P', 'T', 'E', 'R', 'F', 'O', 'R', 'H', 'E', 'A', 'P'};
    AdapterForTest adapter(objects);

    adapter.sink(1);

    ContainerForTest objectsToExpect{'D', 'T', 'A', 'P', 'R', 'E', 'R', 'F', 'O', 'A', 'H', 'E', 'A', 'P'};
    EXPECT_EQ(objectsToExpect, objects);
}

TEST(HeapTreeAdapterTest, SinkWorksOnExample2) {
    ContainerForTest objects{'A', 'B'};
    AdapterForTest adapter(objects);

    adapter.sink(1);

    ContainerForTest objectsToExpect{'B', 'A'};
    EXPECT_EQ(objectsToExpect, objects);
}

}  // namespace algorithm

}  // namespace alba
