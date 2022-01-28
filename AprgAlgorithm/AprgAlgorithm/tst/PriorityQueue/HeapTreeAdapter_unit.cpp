#include <PriorityQueue/HeapTreeAdapter.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using ContainerForTest = std::vector<char>;
using AdapterForTest = HeapTreeAdapter<ContainerForTest, 2U, std::less>;
}

TEST(HeapTreeAdapterTest, GetObjectConstReferenceOnTreeWorks)
{
    ContainerForTest objects{'H', 'E', 'A', 'P', 'O', 'B', 'J', 'E', 'C', 'T', 'S'};
    AdapterForTest adapter(objects);

    EXPECT_EQ('H', adapter.getObjectConstReferenceOnTree(1U));
    EXPECT_EQ('E', adapter.getObjectConstReferenceOnTree(2U));
    EXPECT_EQ('A', adapter.getObjectConstReferenceOnTree(3U));
    EXPECT_EQ('P', adapter.getObjectConstReferenceOnTree(4U));
    EXPECT_EQ('S', adapter.getObjectConstReferenceOnTree(objects.size()));
}

TEST(HeapTreeAdapterTest, GetObjectReferenceOnTreeWorks)
{
    ContainerForTest objects{'H', 'E', 'A', 'P', 'O', 'B', 'J', 'E', 'C', 'T', 'S'};
    AdapterForTest adapter(objects);

    char & characterAtTopOfTree(adapter.getObjectReferenceOnTree(1U));

    characterAtTopOfTree = 'Z';

    ContainerForTest objectsToExpect{'Z', 'E', 'A', 'P', 'O', 'B', 'J', 'E', 'C', 'T', 'S'};
    EXPECT_EQ(objectsToExpect, objects);
}

TEST(HeapTreeAdapterTest, SwimWorks)
{
    ContainerForTest objects{'H', 'E', 'A', 'P', 'O', 'B', 'J', 'E', 'C', 'T', 'S'};
    AdapterForTest adapter(objects);

    adapter.swim(objects.size());

    ContainerForTest objectsToExpect{'S', 'H', 'A', 'P', 'E', 'B', 'J', 'E', 'C', 'T', 'O'};
    EXPECT_EQ(objectsToExpect, objects);
}

TEST(HeapTreeAdapterTest, SinkWorks)
{
    ContainerForTest objects{'A', 'D', 'A', 'P', 'T', 'E', 'R', 'F', 'O', 'R', 'H', 'E', 'A', 'P'};
    AdapterForTest adapter(objects);

    adapter.sink(1U);

    ContainerForTest objectsToExpect{'D', 'T', 'A', 'P', 'R', 'E', 'R', 'F', 'O', 'A', 'H', 'E', 'A', 'P'};
    EXPECT_EQ(objectsToExpect, objects);
}

}
