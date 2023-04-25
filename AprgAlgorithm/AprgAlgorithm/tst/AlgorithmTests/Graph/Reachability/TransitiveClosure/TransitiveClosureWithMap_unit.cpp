#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/Reachability/TransitiveClosure/TransitiveClosureWithMap.hpp>
#include <AlgorithmTests/Graph/Reachability/Utilities/CommonTestsWithTransitiveClosure.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithTransitiveClosure;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = DirectedGraphWithListOfEdges<unsigned int>;
using ReachabilityForTest = TransitiveClosureWithMap<unsigned int>;
}  // namespace

TEST(TransitiveClosureWithMapTest, IsReachableWorksWhenEmpty) {
    testIsReachableWhenEmptyWithVertexAsUnsignedInt<ReachabilityForTest, GraphForTest>();
}

TEST(TransitiveClosureWithMapTest, IsReachableWorksWhenNotEmpty) {
    testIsReachableWhenNotEmptyWithVertexAsUnsignedInt<ReachabilityForTest, GraphForTest>();
}

}  // namespace algorithm

}  // namespace alba
