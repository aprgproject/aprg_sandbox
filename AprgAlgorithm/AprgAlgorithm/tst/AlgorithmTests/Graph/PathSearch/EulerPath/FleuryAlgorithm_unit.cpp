#include <Algorithm/Graph/PathSearch/EulerPath/FleuryAlgorithm.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <AlgorithmTests/Graph/PathSearch/EulerPath/Utilities/CommonTestsWithEulerPath.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithEulerPath;

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

}

}
