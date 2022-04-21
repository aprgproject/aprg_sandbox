#pragma once

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithTransitiveClosure
{

template <typename TransitiveClosureType, typename GraphType>
void testIsReachableWhenEmptyWithVertexAsUnsignedInt()
{
    GraphType graph;    TransitiveClosureType transitiveClosure(graph);

    //Reachability in 0
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 1U));    EXPECT_FALSE(transitiveClosure.isReachable(0U, 2U));
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 3U));
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 4U));
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 5U));
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 6U));
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 7U));
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 8U));
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 9U));
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 10U));
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 11U));
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 12U));
}

template <typename TransitiveClosureType, typename GraphType>
void testIsReachableWhenNotEmptyWithVertexAsUnsignedInt()
{
    GraphType graph;    graph.connect(0U, 1U);
    graph.connect(0U, 5U);
    graph.connect(2U, 0U);
    graph.connect(2U, 3U);    graph.connect(3U, 2U);
    graph.connect(3U, 5U);
    graph.connect(4U, 2U);
    graph.connect(4U, 3U);
    graph.connect(5U, 4U);
    graph.connect(6U, 0U);
    graph.connect(6U, 4U);
    graph.connect(6U, 8U);
    graph.connect(6U, 9U);
    graph.connect(7U, 6U);
    graph.connect(7U, 9U);
    graph.connect(8U, 6U);
    graph.connect(9U, 10U);
    graph.connect(9U, 11U);
    graph.connect(10U, 12U);
    graph.connect(11U, 4U);
    graph.connect(11U, 12U);
    graph.connect(12U, 9U);
    TransitiveClosureType transitiveClosure(graph);

    //Reachability in 0
    EXPECT_TRUE(transitiveClosure.isReachable(0U, 1U));
    EXPECT_TRUE(transitiveClosure.isReachable(0U, 2U));
    EXPECT_TRUE(transitiveClosure.isReachable(0U, 3U));
    EXPECT_TRUE(transitiveClosure.isReachable(0U, 4U));
    EXPECT_TRUE(transitiveClosure.isReachable(0U, 5U));
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 6U));
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 7U));
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 8U));
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 9U));
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 10U));
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 11U));
    EXPECT_FALSE(transitiveClosure.isReachable(0U, 12U));

    //Reachability in 6
    EXPECT_TRUE(transitiveClosure.isReachable(6U, 1U));
    EXPECT_TRUE(transitiveClosure.isReachable(6U, 2U));
    EXPECT_TRUE(transitiveClosure.isReachable(6U, 3U));
    EXPECT_TRUE(transitiveClosure.isReachable(6U, 4U));
    EXPECT_TRUE(transitiveClosure.isReachable(6U, 5U));
    EXPECT_TRUE(transitiveClosure.isReachable(6U, 6U));
    EXPECT_FALSE(transitiveClosure.isReachable(6U, 7U));
    EXPECT_TRUE(transitiveClosure.isReachable(6U, 8U));
    EXPECT_TRUE(transitiveClosure.isReachable(6U, 9U));
    EXPECT_TRUE(transitiveClosure.isReachable(6U, 10U));
    EXPECT_TRUE(transitiveClosure.isReachable(6U, 11U));
    EXPECT_TRUE(transitiveClosure.isReachable(6U, 12U));

    //Reachability in 9
    EXPECT_TRUE(transitiveClosure.isReachable(9U, 1U));
    EXPECT_TRUE(transitiveClosure.isReachable(9U, 2U));
    EXPECT_TRUE(transitiveClosure.isReachable(9U, 3U));
    EXPECT_TRUE(transitiveClosure.isReachable(9U, 4U));
    EXPECT_TRUE(transitiveClosure.isReachable(9U, 5U));
    EXPECT_FALSE(transitiveClosure.isReachable(9U, 6U));
    EXPECT_FALSE(transitiveClosure.isReachable(9U, 7U));
    EXPECT_FALSE(transitiveClosure.isReachable(9U, 8U));
    EXPECT_TRUE(transitiveClosure.isReachable(9U, 9U));
    EXPECT_TRUE(transitiveClosure.isReachable(9U, 10U));
    EXPECT_TRUE(transitiveClosure.isReachable(9U, 11U));
    EXPECT_TRUE(transitiveClosure.isReachable(9U, 12U));

}

}

}

}
