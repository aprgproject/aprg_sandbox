#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/HamiltonianPaths/Common/Utilities.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
}  // namespace

TEST(HamiltonianPathUtilitiesTest, HasHamiltonianPathBecauseItsCompleteWorks) {
    UndirectedGraphForTest nonCompleteGraph;
    nonCompleteGraph.connect(0, 1);
    nonCompleteGraph.connect(0, 2);
    UndirectedGraphForTest completeGraph;
    completeGraph.connect(0, 1);
    completeGraph.connect(0, 2);
    completeGraph.connect(1, 2);

    EXPECT_FALSE(hasHamiltonianPathBecauseItsComplete(nonCompleteGraph));
    EXPECT_TRUE(hasHamiltonianPathBecauseItsComplete(completeGraph));
}

TEST(HamiltonianPathUtilitiesTest, HasHamiltonianPathBecauseOfDiracTheoremWorks) {
    UndirectedGraphForTest graphWithNoPath;  // Has min degree of 1 but half or number of vertices is 2
    graphWithNoPath.connect(0, 1);
    graphWithNoPath.connect(0, 2);
    graphWithNoPath.connect(0, 3);
    UndirectedGraphForTest graphWithPathButNotSatisfied;
    graphWithPathButNotSatisfied.connect(1, 2);
    graphWithPathButNotSatisfied.connect(2, 3);
    graphWithPathButNotSatisfied.connect(3, 4);
    graphWithPathButNotSatisfied.connect(4, 5);
    graphWithPathButNotSatisfied.connect(5, 1);
    UndirectedGraphForTest graphWithPathAndSatisfied;
    graphWithNoPath.connect(0, 1);
    graphWithNoPath.connect(0, 2);

    EXPECT_FALSE(hasHamiltonianPathBecauseOfDiracTheorem(graphWithNoPath));
    EXPECT_FALSE(hasHamiltonianPathBecauseOfDiracTheorem(graphWithPathButNotSatisfied));
    EXPECT_TRUE(hasHamiltonianPathBecauseOfDiracTheorem(graphWithPathAndSatisfied));
}

TEST(HamiltonianPathUtilitiesTest, HasHamiltonianPathBecauseOfOreTheoremWorks) {
    UndirectedGraphForTest graphWithNoPath;
    graphWithNoPath.connect(1, 2);
    graphWithNoPath.connect(1, 4);
    graphWithNoPath.connect(2, 3);
    graphWithNoPath.connect(2, 5);
    graphWithNoPath.connect(3, 5);
    graphWithNoPath.connect(4, 5);
    UndirectedGraphForTest graphWithPathButNotSatisfied;
    graphWithPathButNotSatisfied.connect(1, 2);
    graphWithPathButNotSatisfied.connect(2, 3);
    graphWithPathButNotSatisfied.connect(3, 4);
    graphWithPathButNotSatisfied.connect(4, 5);
    graphWithPathButNotSatisfied.connect(5, 1);
    UndirectedGraphForTest graphWithPathAndSatisfied;
    graphWithPathAndSatisfied.connect(1, 2);
    graphWithPathAndSatisfied.connect(2, 3);
    graphWithPathAndSatisfied.connect(3, 4);
    graphWithPathAndSatisfied.connect(4, 1);

    EXPECT_FALSE(hasHamiltonianPathBecauseOfOreTheorem(graphWithNoPath));
    EXPECT_FALSE(hasHamiltonianPathBecauseOfOreTheorem(graphWithPathButNotSatisfied));
    EXPECT_TRUE(hasHamiltonianPathBecauseOfOreTheorem(graphWithPathAndSatisfied));
}

}  // namespace algorithm

}  // namespace alba
