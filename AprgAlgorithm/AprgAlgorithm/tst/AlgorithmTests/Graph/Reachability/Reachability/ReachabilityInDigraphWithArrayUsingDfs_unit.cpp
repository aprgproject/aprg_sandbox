#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/Reachability/Reachability/ReachabilityInDigraphWithArrayUsingDfs.hpp>
#include <AlgorithmTests/Graph/Reachability/Utilities/CommonTestsWithReachability.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithReachability;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = DirectedGraphWithListOfEdges<int>;
using ReachabilityForTest = ReachabilityInDigraphWithArrayUsingDfs<int, 13>;
}  // namespace

TEST(ReachabilityInDigraphWithArrayUsingDfsTest, IsReachableWorksWhenEmpty) {
    testIsReachableWhenEmptyWithVertexAsInt<ReachabilityForTest, GraphForTest>();
}

TEST(ReachabilityInDigraphWithArrayUsingDfsTest, IsReachableWorksWhenNotEmpty) {
    testIsReachableWhenNotEmptyWithVertexAsInt<ReachabilityForTest, GraphForTest>();
}

}  // namespace algorithm

}  // namespace alba
