#include <AprgUniqueProblems/DynamicProgramming/Graph/Tree/VertexCoverProblem.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using SetOfVertices = VertexCoverProblem::SetOfVertices;
}

TEST(VertexCoverProblemTest, GetMinimumCountWorksOnExample1) {
    VertexCoverProblem::Graph graph;
    graph.connect(10U, 20U);
    graph.connect(10U, 30U);
    graph.connect(20U, 40U);
    graph.connect(20U, 50U);
    graph.connect(30U, 60U);
    graph.connect(50U, 70U);
    graph.connect(50U, 80U);
    VertexCoverProblem queryForTest(graph, 10U);

    EXPECT_EQ(3U, queryForTest.getMinimumCountUsingNaiveRecursion());
    EXPECT_EQ(3U, queryForTest.getMinimumCountUsingMemoizationDP());
    EXPECT_EQ((SetOfVertices{20U, 30U, 50U}), queryForTest.getMinimumSetUsingMemoizationDP());
}

TEST(VertexCoverProblemTest, GetMinimumCountWorksOnExample2) {
    VertexCoverProblem::Graph graph;
    graph.connect(1U, 2U);
    graph.connect(1U, 4U);
    graph.connect(1U, 5U);
    graph.connect(2U, 6U);
    graph.connect(4U, 3U);
    graph.connect(4U, 7U);
    graph.connect(7U, 8U);
    VertexCoverProblem queryForTest(graph, 1U);

    EXPECT_EQ(4U, queryForTest.getMinimumCountUsingNaiveRecursion());
    EXPECT_EQ(4U, queryForTest.getMinimumCountUsingMemoizationDP());
    EXPECT_EQ((SetOfVertices{1U, 2U, 4U, 7U}), queryForTest.getMinimumSetUsingMemoizationDP());
}

}  // namespace alba
