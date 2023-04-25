#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/EulerPaths/DirectedGraph/HierholzerAlgorithmForDirectedGraph.hpp>
#include <AlgorithmTests/Graph/PathSearch/EulerPaths/DirectedGraph/Utilities/CommonTestsWithEulerPathForDirectedGraph.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithEulerPathForDirectedGraph;

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = unsigned int;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = HierholzerAlgorithmForDirectedGraph<VertexForTest>;
}  // namespace

TEST(HierholzerAlgorithmForDirectedGraphTest, HasEulerCycleWorksOnGraphWithAllInDegreesEqualsOutDegrees) {
    testHasEulerCycleWorksOnGraphWithAllInDegreesEqualsOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForDirectedGraphTest, HasEulerCycleWorksOnGraphWithAllInDegreesNotEqualToOutDegrees) {
    testHasEulerCycleWorksOnGraphWithAllInDegreesNotEqualToOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForDirectedGraphTest, HasEulerPathWorksOnGraphWithAllInDegreesEqualsOutDegrees) {
    testHasEulerPathWorksOnGraphWithAllInDegreesEqualsOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForDirectedGraphTest, HasEulerPathWorksOnGraphWithOneLesserAndGreaterInAndOutDegrees) {
    testHasEulerPathWorksOnGraphWithOneLesserAndGreaterInAndOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForDirectedGraphTest, HasEulerPathWorksOnGraphWithMoreThanOneLesserAndGreaterInAndOutDegrees) {
    testHasEulerPathWorksOnGraphWithMoreThanOneLesserAndGreaterInAndOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForDirectedGraphTest, GetEulerCycleWorksOnEmptyGraph) {
    testGetEulerCycleWorksOnEmptyGraph<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForDirectedGraphTest, GetEulerCycleWorksOnGraphWithAllInDegreesEqualsOutDegrees) {
    testGetEulerCycleWorksOnGraphWithAllInDegreesEqualsOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForDirectedGraphTest, GetEulerCycleWorksOnGraphWithAllInDegreesNotEqualToOutDegrees) {
    testGetEulerCycleWorksOnGraphWithAllInDegreesNotEqualToOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForDirectedGraphTest, GetEulerPathWorksOnEmptyGraph) {
    testGetEulerPathWorksOnEmptyGraph<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForDirectedGraphTest, GetEulerPathWorksOnGraphWithOneLesserAndGreaterInAndOutDegrees) {
    testGetEulerPathWorksOnGraphWithOneLesserAndGreaterInAndOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForDirectedGraphTest, GetEulerPathWorksOnGraphWithMoreThanOneLesserAndGreaterInAndOutDegrees) {
    testGetEulerPathWorksOnGraphWithMoreThanOneLesserAndGreaterInAndOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForDirectedGraphTest, GetEulerCycleAndPathWorksOnExample1) {
    testGetEulerCycleAndPathWorksOnExample1<PathSearchForTest, GraphForTest>();
}

}  // namespace algorithm

}  // namespace alba
