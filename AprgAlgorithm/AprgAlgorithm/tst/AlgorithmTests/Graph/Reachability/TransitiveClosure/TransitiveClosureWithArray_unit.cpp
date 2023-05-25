#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/Reachability/TransitiveClosure/TransitiveClosureWithArray.hpp>
#include <AlgorithmTests/Graph/Reachability/Utilities/CommonTestsWithTransitiveClosure.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithTransitiveClosure;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = DirectedGraphWithListOfEdges<int>;
using ReachabilityForTest = TransitiveClosureWithArray<int, 13>;
}  // namespace

TEST(TransitiveClosureWithArrayTest, IsReachableWorksWhenEmpty) {
    testIsReachableWhenEmptyWithVertexAsInt<ReachabilityForTest, GraphForTest>();
}

TEST(TransitiveClosureWithArrayTest, IsReachableWorksWhenNotEmpty) {
    testIsReachableWhenNotEmptyWithVertexAsInt<ReachabilityForTest, GraphForTest>();
}

}  // namespace algorithm

}  // namespace alba
