#include <Algorithm/Graph/PathSearch/EulerCircuitAndPath/FleuryAlgorithm.hpp>
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
using PathSearchForTest = FleuryAlgorithm<VertexForTest>;
}
TEST(FleuryAlgorithmTest, HasEulerCircuitWorksOnGraphWithAllEvenDegreesVertices)
{
    testHasEulerCircuitWorksOnGraphWithAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(FleuryAlgorithmTest, HasEulerCircuitWorksOnGraphWithNotAllEvenDegreesVertices)
{
    testHasEulerCircuitWorksOnGraphWithNotAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(FleuryAlgorithmTest, HasEulerPathWorksOnGraphWithTwoOddDegreesVertices)
{
    testHasEulerPathWorksOnGraphWithTwoOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(FleuryAlgorithmTest, HasEulerPathWorksOnGraphWithThreeOddDegreesVertices)
{
    testHasEulerPathWorksOnGraphWithThreeOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(FleuryAlgorithmTest, GetEulerCircuitWorksOnGraphWithAllEvenDegreesVertices)
{
    testGetEulerCircuitWorksOnGraphWithAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(FleuryAlgorithmTest, GetEulerCircuitWorksOnGraphWithNotAllEvenDegreesVertices)
{
    testGetEulerCircuitWorksOnGraphWithNotAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(FleuryAlgorithmTest, GetEulerPathWorksOnGraphWithTwoOddDegreesVertices)
{
    testGetEulerPathWorksOnGraphWithTwoOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(FleuryAlgorithmTest, GetEulerPathWorksOnGraphWithThreeOddDegreesVertices)
{
    testGetEulerPathWorksOnGraphWithThreeOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

}
}