#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/Reachability/Reachability/ReachabilityInDigraphWithSetUsingDfs.hpp>
#include <AlgorithmTests/Graph/Reachability/Utilities/CommonTestsWithReachability.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithReachability;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = DirectedGraphWithListOfEdges<int>;
using ReachabilityForTest = ReachabilityInDigraphWithSetUsingDfs<int>;
}  // namespace

TEST(ReachabilityInDigraphWithSetUsingDfsTest, IsReachableWorksWhenEmpty) {
    testIsReachableWhenEmptyWithVertexAsInt<ReachabilityForTest, GraphForTest>();
}

TEST(ReachabilityInDigraphWithSetUsingDfsTest, IsReachableWorksWhenNotEmpty) {
    testIsReachableWhenNotEmptyWithVertexAsInt<ReachabilityForTest, GraphForTest>();
}

}  // namespace algorithm

}  // namespace alba
