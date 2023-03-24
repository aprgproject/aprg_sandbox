#include <AprgUniqueProblems/DynamicProgramming/Graph/Tree/LargestIndependentSetProblem.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

namespace
{
using SetOfVertices=LargestIndependentSetProblem::SetOfVertices;
}

TEST(LargestIndependentSetProblemTest, GetMaximumCountWorksOnExample1)
{
    LargestIndependentSetProblem::Graph graph;
    graph.connect(10U, 20U);
    graph.connect(10U, 30U);
    graph.connect(20U, 40U);
    graph.connect(20U, 50U);
    graph.connect(30U, 60U);
    graph.connect(50U, 70U);
    graph.connect(50U, 80U);
    LargestIndependentSetProblem queryForTest(graph, 10U);

    EXPECT_EQ(5U, queryForTest.getMaximumCountUsingNaiveRecursion());
    EXPECT_EQ(5U, queryForTest.getMaximumCountUsingMemoizationDP());
    EXPECT_EQ((SetOfVertices{10U, 40U, 60U, 70U, 80U}), queryForTest.getMaximumSetUsingMemoizationDP());
}

TEST(LargestIndependentSetProblemTest, GetMaximumCountWorksOnExample2)
{
    LargestIndependentSetProblem::Graph graph;
    graph.connect(1U, 2U);
    graph.connect(1U, 4U);
    graph.connect(1U, 5U);
    graph.connect(2U, 6U);
    graph.connect(4U, 3U);
    graph.connect(4U, 7U);
    graph.connect(7U, 8U);
    LargestIndependentSetProblem queryForTest(graph, 1U);

    EXPECT_EQ(4U, queryForTest.getMaximumCountUsingNaiveRecursion());
    EXPECT_EQ(4U, queryForTest.getMaximumCountUsingMemoizationDP());
    EXPECT_EQ((SetOfVertices{1U, 3U, 6U, 7U}), queryForTest.getMaximumSetUsingMemoizationDP());
}

}
