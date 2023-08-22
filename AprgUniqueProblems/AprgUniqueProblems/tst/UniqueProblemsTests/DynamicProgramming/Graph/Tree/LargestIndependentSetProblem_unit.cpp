#include <UniqueProblems/DynamicProgramming/Graph/Tree/LargestIndependentSetProblem.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
namespace {
using SetOfVertices = LargestIndependentSetProblem::SetOfVertices;
}

TEST(LargestIndependentSetProblemTest, GetMaximumCountWorksOnExample1) {
    LargestIndependentSetProblem::Graph graph;
    graph.connect(10, 20);
    graph.connect(10, 30);
    graph.connect(20, 40);
    graph.connect(20, 50);
    graph.connect(30, 60);
    graph.connect(50, 70);
    graph.connect(50, 80);
    LargestIndependentSetProblem queryForTest(graph, 10);

    EXPECT_EQ(5, queryForTest.getMaximumCountUsingNaiveRecursion());
    EXPECT_EQ(5, queryForTest.getMaximumCountUsingMemoizationDP());
    EXPECT_EQ((SetOfVertices{10, 40, 60, 70, 80}), queryForTest.getMaximumSetUsingMemoizationDP());
}

TEST(LargestIndependentSetProblemTest, GetMaximumCountWorksOnExample2) {
    LargestIndependentSetProblem::Graph graph;
    graph.connect(1, 2);
    graph.connect(1, 4);
    graph.connect(1, 5);
    graph.connect(2, 6);
    graph.connect(4, 3);
    graph.connect(4, 7);
    graph.connect(7, 8);
    LargestIndependentSetProblem queryForTest(graph, 1);

    EXPECT_EQ(4, queryForTest.getMaximumCountUsingNaiveRecursion());
    EXPECT_EQ(4, queryForTest.getMaximumCountUsingMemoizationDP());
    EXPECT_EQ((SetOfVertices{1, 3, 6, 7}), queryForTest.getMaximumSetUsingMemoizationDP());
}

}  // namespace alba
