#include <AprgUniqueProblems/DynamicProgramming/Graph/Tree/VertexCoverProblem.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using SetOfVertices = VertexCoverProblem::SetOfVertices;
}

TEST(VertexCoverProblemTest, GetMinimumCountWorksOnExample1) {
    VertexCoverProblem::Graph graph;
    graph.connect(10, 20);
    graph.connect(10, 30);
    graph.connect(20, 40);
    graph.connect(20, 50);
    graph.connect(30, 60);
    graph.connect(50, 70);
    graph.connect(50, 80);
    VertexCoverProblem queryForTest(graph, 10);

    EXPECT_EQ(3, queryForTest.getMinimumCountUsingNaiveRecursion());
    EXPECT_EQ(3, queryForTest.getMinimumCountUsingMemoizationDP());
    EXPECT_EQ((SetOfVertices{20, 30, 50}), queryForTest.getMinimumSetUsingMemoizationDP());
}

TEST(VertexCoverProblemTest, GetMinimumCountWorksOnExample2) {
    VertexCoverProblem::Graph graph;
    graph.connect(1, 2);
    graph.connect(1, 4);
    graph.connect(1, 5);
    graph.connect(2, 6);
    graph.connect(4, 3);
    graph.connect(4, 7);
    graph.connect(7, 8);
    VertexCoverProblem queryForTest(graph, 1);

    EXPECT_EQ(4, queryForTest.getMinimumCountUsingNaiveRecursion());
    EXPECT_EQ(4, queryForTest.getMinimumCountUsingMemoizationDP());
    EXPECT_EQ((SetOfVertices{1, 2, 4, 7}), queryForTest.getMinimumSetUsingMemoizationDP());
}

}  // namespace alba