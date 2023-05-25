#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/Reachability/TransitiveClosure/TransitiveClosureWithMap.hpp>
#include <AlgorithmTests/Graph/Reachability/Utilities/CommonTestsWithTransitiveClosure.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithTransitiveClosure;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = DirectedGraphWithListOfEdges<int>;
using ReachabilityForTest = TransitiveClosureWithMap<int>;
}  // namespace

TEST(TransitiveClosureWithMapTest, IsReachableWorksWhenEmpty) {
    testIsReachableWhenEmptyWithVertexAsInt<ReachabilityForTest, GraphForTest>();
}

TEST(TransitiveClosureWithMapTest, IsReachableWorksWhenNotEmpty) {
    testIsReachableWhenNotEmptyWithVertexAsInt<ReachabilityForTest, GraphForTest>();
}

}  // namespace algorithm

}  // namespace alba
