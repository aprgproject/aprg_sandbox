#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/EulerPath/DirectedGraph/HierholzerAlgorithm.hpp>
#include <AlgorithmTests/Graph/PathSearch/EulerPath/DirectedGraph/Utilities/CommonTestsWithEulerPathForDirectedGraph.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithEulerPathForDirectedGraph;

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = HierholzerAlgorithm<VertexForTest>;
}

TEST(HierholzerAlgorithmTest, HasEulerCycleWorksOnGraphWithAllInDegreesEqualsOutDegrees)
{
    testHasEulerCycleWorksOnGraphWithAllInDegreesEqualsOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmTest, HasEulerCycleWorksOnGraphWithAllInDegreesNotEqualToOutDegrees)
{
    testHasEulerCycleWorksOnGraphWithAllInDegreesNotEqualToOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmTest, HasEulerPathWorksOnGraphWithAllInDegreesEqualsOutDegrees)
{
    testHasEulerPathWorksOnGraphWithAllInDegreesEqualsOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmTest, HasEulerPathWorksOnGraphWithOneLesserAndGreaterInAndOutDegrees)
{
    testHasEulerPathWorksOnGraphWithOneLesserAndGreaterInAndOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmTest, HasEulerPathWorksOnGraphWithMoreThanOneLesserAndGreaterInAndOutDegrees)
{
    testHasEulerPathWorksOnGraphWithMoreThanOneLesserAndGreaterInAndOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmTest, GetEulerCycleWorksOnGraphWithAllInDegreesEqualsOutDegrees)
{
    testGetEulerCycleWorksOnGraphWithAllInDegreesEqualsOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmTest, GetEulerCycleWorksOnGraphWithAllInDegreesNotEqualToOutDegrees)
{
    testGetEulerCycleWorksOnGraphWithAllInDegreesNotEqualToOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmTest, GetEulerPathWorksOnGraphWithOneLesserAndGreaterInAndOutDegrees)
{
    testGetEulerPathWorksOnGraphWithOneLesserAndGreaterInAndOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmTest, GetEulerPathWorksOnGraphWithMoreThanOneLesserAndGreaterInAndOutDegrees)
{
    testGetEulerPathWorksOnGraphWithMoreThanOneLesserAndGreaterInAndOutDegrees<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmTest, GetEulerCycleAndPathWorksOnExample1)
{
    testGetEulerCycleAndPathWorksOnExample1<PathSearchForTest, GraphForTest>();
}

}

}
