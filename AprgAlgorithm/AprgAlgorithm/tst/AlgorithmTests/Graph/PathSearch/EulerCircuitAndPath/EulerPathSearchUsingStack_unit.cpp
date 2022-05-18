#include <Algorithm/Graph/PathSearch/EulerCircuitAndPath/EulerPathSearchUsingDfs.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <AlgorithmTests/Graph/PathSearch/EulerCircuitAndPath/Utilities/CommonTestsWithEulerCircuitAndPath.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithEulerCircuitAndPath;

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = EulerPathSearchUsingDfs<VertexForTest>;
}

TEST(EulerPathSearchUsingDfsTest, HasEulerCircuitWorksOnGraphWithAllEvenDegreesVertices)
{
    testHasEulerCircuitWorksOnGraphWithAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchUsingDfsTest, HasEulerCircuitWorksOnGraphWithNotAllEvenDegreesVertices)
{
    testHasEulerCircuitWorksOnGraphWithNotAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchUsingDfsTest, HasEulerPathWorksOnGraphWithTwoOddDegreesVertices)
{
    testHasEulerPathWorksOnGraphWithTwoOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchUsingDfsTest, HasEulerPathWorksOnGraphWithThreeOddDegreesVertices)
{
    testHasEulerPathWorksOnGraphWithThreeOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchUsingDfsTest, GetEulerCircuitWorksOnGraphWithAllEvenDegreesVertices)
{
    testGetEulerCircuitWorksOnGraphWithAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchUsingDfsTest, GetEulerCircuitWorksOnGraphWithNotAllEvenDegreesVertices)
{
    testGetEulerCircuitWorksOnGraphWithNotAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchUsingDfsTest, GetEulerPathWorksOnGraphWithTwoOddDegreesVertices)
{
    testGetEulerPathWorksOnGraphWithTwoOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchUsingDfsTest, GetEulerPathWorksOnGraphWithThreeOddDegreesVertices)
{
    testGetEulerPathWorksOnGraphWithThreeOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

}

}
