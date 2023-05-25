#include <Algorithm/Graph/PathSearch/EulerPaths/UndirectedGraph/EulerPathSearchForUndirectedGraphUsingDfs.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <AlgorithmTests/Graph/PathSearch/EulerPaths/UndirectedGraph/Utilities/CommonTestsWithEulerPathForUndirectedGraph.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithEulerPathForUndirectedGraph;

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = EulerPathSearchForUndirectedGraphUsingDfs<VertexForTest>;
}  // namespace

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, HasEulerCycleWorksOnGraphWithAllEvenDegreesVertices) {
    testHasEulerCycleWorksOnGraphWithAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, HasEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices) {
    testHasEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, HasEulerPathWorksOnGraphWithOneOddDegreeVertices) {
    testHasEulerPathWorksOnGraphWithOneOddDegreeVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, HasEulerPathWorksOnGraphWithTwoOddDegreesVertices) {
    testHasEulerPathWorksOnGraphWithTwoOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, HasEulerPathWorksOnGraphWithThreeOddDegreesVertices) {
    testHasEulerPathWorksOnGraphWithThreeOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, GetEulerCycleWorksOnEmptyGraph) {
    testGetEulerCycleWorksOnEmptyGraph<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, GetEulerCycleWorksOnGraphWithAllEvenDegreesVertices) {
    testGetEulerCycleWorksOnGraphWithAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, GetEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices) {
    testGetEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, GetEulerPathWorksOnEmptyGraph) {
    testGetEulerPathWorksOnEmptyGraph<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, GetEulerPathWorksOnGraphWithTwoOddDegreesVertices) {
    testGetEulerPathWorksOnGraphWithTwoOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, GetEulerPathWorksOnGraphWithThreeOddDegreesVertices) {
    testGetEulerPathWorksOnGraphWithThreeOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, GetEulerCycleAndPathWorksOnExample1) {
    testGetEulerCycleAndPathWorksOnExample1<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, GetEulerCycleAndPathWorksOnExample2) {
    testGetEulerCycleAndPathWorksOnExample2<PathSearchForTest, GraphForTest>();
}

}  // namespace algorithm

}  // namespace alba
