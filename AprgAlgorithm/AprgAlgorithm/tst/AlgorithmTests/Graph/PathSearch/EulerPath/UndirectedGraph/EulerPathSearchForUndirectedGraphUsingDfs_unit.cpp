#include <Algorithm/Graph/PathSearch/EulerPath/UndirectedGraph/EulerPathSearchForUndirectedGraphUsingDfs.hpp>
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
using PathSearchForTest = EulerPathSearchForUndirectedGraphUsingDfs<VertexForTest>;
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, HasEulerCycleWorksOnGraphWithAllEvenDegreesVertices)
{
    testHasEulerCycleWorksOnGraphWithAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, HasEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices)
{
    testHasEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, HasEulerPathWorksOnGraphWithOneOddDegreeVertices)
{
    testHasEulerPathWorksOnGraphWithOneOddDegreeVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, HasEulerPathWorksOnGraphWithTwoOddDegreesVertices)
{
    testHasEulerPathWorksOnGraphWithTwoOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, HasEulerPathWorksOnGraphWithThreeOddDegreesVertices)
{
    testHasEulerPathWorksOnGraphWithThreeOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, GetEulerCycleWorksOnGraphWithAllEvenDegreesVertices)
{
    testGetEulerCycleWorksOnGraphWithAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, GetEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices)
{
    testGetEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, GetEulerPathWorksOnGraphWithTwoOddDegreesVertices)
{
    testGetEulerPathWorksOnGraphWithTwoOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, GetEulerPathWorksOnGraphWithThreeOddDegreesVertices)
{
    testGetEulerPathWorksOnGraphWithThreeOddDegreesVertices<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, GetEulerCycleAndPathWorksOnExample1)
{
    testGetEulerCycleAndPathWorksOnExample1<PathSearchForTest, GraphForTest>();
}

TEST(EulerPathSearchForUndirectedGraphUsingDfsTest, GetEulerCycleAndPathWorksOnExample2)
{
    testGetEulerCycleAndPathWorksOnExample2<PathSearchForTest, GraphForTest>();
}


}

}