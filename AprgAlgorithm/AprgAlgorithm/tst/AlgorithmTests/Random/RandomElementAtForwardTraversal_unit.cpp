#include <Algorithm/Random/RandomElementAtForwardTraversal.hpp>

#include <gtest/gtest.h>

#include <forward_list>
#include <vector>

using namespace std;

namespace alba {

namespace algorithm {

TEST(RandomElementAtForwardTraversalTest, GetRandomElementAtForwardTraversalWorksOnVector) {
    vector<int> values{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    RandomElementAtForwardTraversal<vector<int>> algorithm;

    EXPECT_NE(0, algorithm.getRandomElement(values));
}

TEST(RandomElementAtForwardTraversalTest, GetRandomElementAtForwardTraversalWorksOnForwardList) {
    forward_list<int> values{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    RandomElementAtForwardTraversal<forward_list<int>> algorithm;

    EXPECT_NE(0, algorithm.getRandomElement(values));
}

}  // namespace algorithm

}  // namespace alba
