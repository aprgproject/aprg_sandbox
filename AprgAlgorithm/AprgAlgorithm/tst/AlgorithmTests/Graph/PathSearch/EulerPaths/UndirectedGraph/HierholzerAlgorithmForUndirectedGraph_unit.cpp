#include <Algorithm/Graph/PathSearch/EulerPaths/UndirectedGraph/HierholzerAlgorithmForUndirectedGraph.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <AlgorithmTests/Graph/PathSearch/EulerPaths/UndirectedGraph/Utilities/CommonTestsWithEulerPathForUndirectedGraph.hpp>

#include <gtest/gtest.h>
using namespace alba::algorithm::CommonTestsWithEulerPathForUndirectedGraph;

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = HierholzerAlgorithmForUndirectedGraph<VertexForTest>;
}

TEST(HierholzerAlgorithmForUndirectedGraphTest, HasEulerCycleWorksOnGraphWithAllEvenDegreesVertices)
{
    testHasEulerCycleWorksOnGraphWithAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForUndirectedGraphTest, HasEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices)
{
    testHasEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForUndirectedGraphTest, HasEulerPathWorksOnGraphWithOneOddDegreeVertices)
{
    testHasEulerPathWorksOnGraphWithOneOddDegreeVertices<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForUndirectedGraphTest, HasEulerPathWorksOnGraphWithTwoOddDegreesVertices)
{
    testHasEulerPathWorksOnGraphWithTwoOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForUndirectedGraphTest, HasEulerPathWorksOnGraphWithThreeOddDegreesVertices)
{
    testHasEulerPathWorksOnGraphWithThreeOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForUndirectedGraphTest, GetEulerCycleWorksOnEmptyGraph)
{
    testGetEulerCycleWorksOnEmptyGraph<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForUndirectedGraphTest, GetEulerCycleWorksOnGraphWithAllEvenDegreesVertices)
{
    testGetEulerCycleWorksOnGraphWithAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForUndirectedGraphTest, GetEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices)
{
    testGetEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForUndirectedGraphTest, GetEulerPathWorksOnEmptyGraph)
{
    testGetEulerPathWorksOnEmptyGraph<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForUndirectedGraphTest, GetEulerPathWorksOnGraphWithTwoOddDegreesVertices)
{
    testGetEulerPathWorksOnGraphWithTwoOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForUndirectedGraphTest, GetEulerPathWorksOnGraphWithThreeOddDegreesVertices)
{
    testGetEulerPathWorksOnGraphWithThreeOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForUndirectedGraphTest, GetEulerCycleAndPathWorksOnExample1)
{
    testGetEulerCycleAndPathWorksOnExample1<PathSearchForTest, GraphForTest>();
}

TEST(HierholzerAlgorithmForUndirectedGraphTest, GetEulerCycleAndPathWorksOnExample2)
{
    testGetEulerCycleAndPathWorksOnExample2<PathSearchForTest, GraphForTest>();
}

}

}
