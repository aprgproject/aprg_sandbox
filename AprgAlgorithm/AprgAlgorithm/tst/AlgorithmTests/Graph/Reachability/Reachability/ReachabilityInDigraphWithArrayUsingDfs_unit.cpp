#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/Reachability/Reachability/ReachabilityInDigraphWithArrayUsingDfs.hpp>
#include <AlgorithmTests/Graph/Reachability/Utilities/CommonTestsWithReachability.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithReachability;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = DirectedGraphWithListOfEdges<unsigned int>;
using ReachabilityForTest = ReachabilityInDigraphWithArrayUsingDfs<unsigned int, 13U>;
}  // namespace

TEST(ReachabilityInDigraphWithArrayUsingDfsTest, IsReachableWorksWhenEmpty) {
    testIsReachableWhenEmptyWithVertexAsUnsignedInt<ReachabilityForTest, GraphForTest>();
}

TEST(ReachabilityInDigraphWithArrayUsingDfsTest, IsReachableWorksWhenNotEmpty) {
    testIsReachableWhenNotEmptyWithVertexAsUnsignedInt<ReachabilityForTest, GraphForTest>();
}

}  // namespace algorithm

}  // namespace alba
