#pragma once

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithReachability
{

template <typename ReachabilityType, typename GraphType>
void testIsReachableWhenEmptyWithVertexAsUnsignedInt()
{
    GraphType graph;    ReachabilityType reachabilityIn0(graph, 0U);

    //Reachability in 0
    EXPECT_FALSE(reachabilityIn0.isReachable(1U));    EXPECT_FALSE(reachabilityIn0.isReachable(2U));
    EXPECT_FALSE(reachabilityIn0.isReachable(3U));
    EXPECT_FALSE(reachabilityIn0.isReachable(4U));
    EXPECT_FALSE(reachabilityIn0.isReachable(5U));
    EXPECT_FALSE(reachabilityIn0.isReachable(6U));
    EXPECT_FALSE(reachabilityIn0.isReachable(7U));
    EXPECT_FALSE(reachabilityIn0.isReachable(8U));
    EXPECT_FALSE(reachabilityIn0.isReachable(9U));
    EXPECT_FALSE(reachabilityIn0.isReachable(10U));
    EXPECT_FALSE(reachabilityIn0.isReachable(11U));
    EXPECT_FALSE(reachabilityIn0.isReachable(12U));
}

template <typename ReachabilityType, typename GraphType>
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
    ReachabilityType reachabilityIn0(graph, 0U);
    ReachabilityType reachabilityIn6(graph, 6U);
    ReachabilityType reachabilityIn9(graph, 9U);

    //Reachability in 0
    EXPECT_TRUE(reachabilityIn0.isReachable(1U));
    EXPECT_TRUE(reachabilityIn0.isReachable(2U));
    EXPECT_TRUE(reachabilityIn0.isReachable(3U));
    EXPECT_TRUE(reachabilityIn0.isReachable(4U));
    EXPECT_TRUE(reachabilityIn0.isReachable(5U));
    EXPECT_FALSE(reachabilityIn0.isReachable(6U));
    EXPECT_FALSE(reachabilityIn0.isReachable(7U));
    EXPECT_FALSE(reachabilityIn0.isReachable(8U));
    EXPECT_FALSE(reachabilityIn0.isReachable(9U));
    EXPECT_FALSE(reachabilityIn0.isReachable(10U));
    EXPECT_FALSE(reachabilityIn0.isReachable(11U));
    EXPECT_FALSE(reachabilityIn0.isReachable(12U));

    //Reachability in 6
    EXPECT_TRUE(reachabilityIn6.isReachable(1U));
    EXPECT_TRUE(reachabilityIn6.isReachable(2U));
    EXPECT_TRUE(reachabilityIn6.isReachable(3U));
    EXPECT_TRUE(reachabilityIn6.isReachable(4U));
    EXPECT_TRUE(reachabilityIn6.isReachable(5U));
    EXPECT_TRUE(reachabilityIn6.isReachable(6U));
    EXPECT_FALSE(reachabilityIn6.isReachable(7U));
    EXPECT_TRUE(reachabilityIn6.isReachable(8U));
    EXPECT_TRUE(reachabilityIn6.isReachable(9U));
    EXPECT_TRUE(reachabilityIn6.isReachable(10U));
    EXPECT_TRUE(reachabilityIn6.isReachable(11U));
    EXPECT_TRUE(reachabilityIn6.isReachable(12U));

    //Reachability in 9
    EXPECT_TRUE(reachabilityIn9.isReachable(1U));
    EXPECT_TRUE(reachabilityIn9.isReachable(2U));
    EXPECT_TRUE(reachabilityIn9.isReachable(3U));
    EXPECT_TRUE(reachabilityIn9.isReachable(4U));
    EXPECT_TRUE(reachabilityIn9.isReachable(5U));
    EXPECT_FALSE(reachabilityIn9.isReachable(6U));
    EXPECT_FALSE(reachabilityIn9.isReachable(7U));
    EXPECT_FALSE(reachabilityIn9.isReachable(8U));
    EXPECT_TRUE(reachabilityIn9.isReachable(9U));
    EXPECT_TRUE(reachabilityIn9.isReachable(10U));
    EXPECT_TRUE(reachabilityIn9.isReachable(11U));
    EXPECT_TRUE(reachabilityIn9.isReachable(12U));

}

}

}

}
