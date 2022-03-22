#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/Reachability/TransitiveClosure/TransitiveClosureWithArray.hpp>
#include <AlgorithmTests/Graph/Reachability/Utilities/CommonTestsWithTransitiveClosure.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithTransitiveClosure;

namespace alba
{

namespace algorithm
{

namespace
{
using GraphForTest = DirectedGraphWithListOfEdges<unsigned int>;
using ReachabilityForTest = TransitiveClosureWithArray<unsigned int, 13>;
}

TEST(TransitiveClosureWithArrayTest, IsReachableWorksWhenEmpty)
{
    testIsReachableWhenEmptyWithVertexAsUnsignedInt<ReachabilityForTest, GraphForTest>();
}

TEST(TransitiveClosureWithArrayTest, IsReachableWorksWhenNotEmpty)
{
    testIsReachableWhenNotEmptyWithVertexAsUnsignedInt<ReachabilityForTest, GraphForTest>();
}

}

}
