#include <Algorithm/Graph/PathSearch/EulerPath/UndirectedGraph/FleuryAlgorithm.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <AlgorithmTests/Graph/PathSearch/EulerPath/UndirectedGraph/Utilities/CommonTestsWithEulerPathForUndirectedGraph.hpp>

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
using PathSearchForTest = FleuryAlgorithm<VertexForTest>;
}

TEST(FleuryAlgorithmTest, HasEulerCycleWorksOnGraphWithAllEvenDegreesVertices)
{
    testHasEulerCycleWorksOnGraphWithAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(FleuryAlgorithmTest, HasEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices)
{
    testHasEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(FleuryAlgorithmTest, HasEulerPathWorksOnGraphWithOneOddDegreeVertices)
{
    testHasEulerPathWorksOnGraphWithOneOddDegreeVertices<PathSearchForTest, GraphForTest>();
}

TEST(FleuryAlgorithmTest, HasEulerPathWorksOnGraphWithTwoOddDegreesVertices)
{
    testHasEulerPathWorksOnGraphWithTwoOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(FleuryAlgorithmTest, HasEulerPathWorksOnGraphWithThreeOddDegreesVertices)
{
    testHasEulerPathWorksOnGraphWithThreeOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(FleuryAlgorithmTest, GetEulerCycleWorksOnGraphWithAllEvenDegreesVertices)
{
    testGetEulerCycleWorksOnGraphWithAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(FleuryAlgorithmTest, GetEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices)
{
    testGetEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(FleuryAlgorithmTest, GetEulerPathWorksOnGraphWithTwoOddDegreesVertices)
{
    testGetEulerPathWorksOnGraphWithTwoOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(FleuryAlgorithmTest, GetEulerPathWorksOnGraphWithThreeOddDegreesVertices)
{
    testGetEulerPathWorksOnGraphWithThreeOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(FleuryAlgorithmTest, GetEulerCycleAndPathWorksOnExample1)
{
    testGetEulerCycleAndPathWorksOnExample1<PathSearchForTest, GraphForTest>();
}

TEST(FleuryAlgorithmTest, GetEulerCycleAndPathWorksOnExample2)
{
    testGetEulerCycleAndPathWorksOnExample2<PathSearchForTest, GraphForTest>();
}

}

}