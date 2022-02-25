#include <Algorithm/Graph/GraphUtilities.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithAdjacencyMatrix.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using SampleGraphWithMax13 = UndirectedGraphWithAdjacencyMatrix<13>;
}

TEST(GraphUtilitiesTest, GetDegreeAtWorks)
{
    SampleGraphWithMax13 graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ(2U, getDegreeAt(graph, 0U));
    EXPECT_EQ(1U, getDegreeAt(graph, 1U));
    EXPECT_EQ(1U, getDegreeAt(graph, 2U));
}

TEST(GraphUtilitiesTest, GetMaxDegreeAtWorks)
{
    SampleGraphWithMax13 graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ(2U, getMaxDegree(graph));
}

TEST(GraphUtilitiesTest, GetAverageDegreeWorks)
{
    SampleGraphWithMax13 graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 3U);

    EXPECT_EQ(1.5, getAverageDegree(graph));
}

TEST(GraphUtilitiesTest, GetNumberOfSelfLoopsWorks)
{
    SampleGraphWithMax13 graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 3U);
    graph.connect(1U, 1U);
    graph.connect(2U, 2U);

    EXPECT_EQ(2U, getNumberOfSelfLoops(graph));
}


}

}
