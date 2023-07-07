#include <Algorithm/Search/Interval/IntervalSearchTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {

using IntervalForTest = Interval<int>;
using SearchTreeForTest = IntervalSearchTree<int>;
}  // namespace

TEST(IntervalSearchTreeTest, PutWorks) {
    SearchTreeForTest search;
    search.put({17, 19});
    search.put({5, 8});
    search.put({21, 24});

    auto const& root(search.getRoot());
    EXPECT_EQ((IntervalForTest{17, 9}), root->key);
    EXPECT_EQ(3, root->sizeOfThisSubTree);
    EXPECT_EQ(RedBlackColor::Red, root->parentLinkColor);
    EXPECT_EQ(24, root->maxIntervalValueInSubtree);
    EXPECT_EQ((IntervalForTest{5, 8}), root->left->key);
    EXPECT_EQ(1, root->left->sizeOfThisSubTree);
    EXPECT_EQ(RedBlackColor::Black, root->left->parentLinkColor);
    EXPECT_EQ(8, root->left->maxIntervalValueInSubtree);
    EXPECT_EQ((IntervalForTest{21, 24}), root->right->key);
    EXPECT_EQ(1, root->right->sizeOfThisSubTree);
    EXPECT_EQ(RedBlackColor::Black, root->right->parentLinkColor);
    EXPECT_EQ(24, root->right->maxIntervalValueInSubtree);
}

TEST(IntervalSearchTreeTest, GetSupersetIntervalsOfWorksOnExample1) {
    SearchTreeForTest search;
    search.put({17, 19});
    search.put({5, 8});
    search.put({21, 24});
    search.put({4, 8});
    search.put({15, 18});
    search.put({7, 10});
    search.put({16, 22});

    auto const& intervalsToVerify(search.getIntersectingIntervalsOf({12, 14}));

    EXPECT_TRUE(intervalsToVerify.empty());
}

TEST(IntervalSearchTreeTest, GetSupersetIntervalsOfWorksOnExample2) {
    SearchTreeForTest search;
    search.put({17, 19});
    search.put({5, 8});
    search.put({21, 24});
    search.put({4, 8});
    search.put({15, 18});
    search.put({7, 10});
    search.put({16, 22});

    auto const& intervalsToVerify(search.getIntersectingIntervalsOf({23, 25}));

    SearchTreeForTest::Keys const& intervalsToExpect{{21, 24}};
    EXPECT_EQ(intervalsToExpect, intervalsToVerify);
}

TEST(IntervalSearchTreeTest, GetSupersetIntervalsOfWorksOnExample3) {
    SearchTreeForTest search;
    search.put({17, 19});
    search.put({5, 8});
    search.put({21, 24});
    search.put({4, 8});
    search.put({15, 18});
    search.put({7, 10});
    search.put({16, 22});

    auto const& intervalsToVerify(search.getIntersectingIntervalsOf({4, 25}));

    SearchTreeForTest::Keys const& intervalsToExpect{{15, 18}, {5, 8}, {4, 8}, {7, 10}, {17, 19}, {16, 22}, {21, 24}};
    EXPECT_EQ(intervalsToExpect, intervalsToVerify);
}

TEST(IntervalSearchTreeTest, MergeIntervalsWorksOnExample2) {
    SearchTreeForTest search;
    SearchTreeForTest::BooleanBinaryFunction mergeCondition = [](SearchTreeForTest::Key const& interval1,
                                                                 SearchTreeForTest::Key const& interval2) {
        return interval1.end + 1 >= interval2.start;
    };
    search.put({5, 8});
    search.put({8, 9});

    auto const& intervalsToVerify1(search.getIntersectingIntervalsOf({8, 8}));
    SearchTreeForTest::Keys const& intervalsToExpect1{{8, 9}, {5, 8}};
    EXPECT_EQ(intervalsToExpect1, intervalsToVerify1);

    search.mergeIntervals(mergeCondition);

    auto const& intervalsToVerify2(search.getIntersectingIntervalsOf({8, 8}));
    SearchTreeForTest::Keys const& intervalsToExpect2{{5, 9}};
    EXPECT_EQ(intervalsToExpect2, intervalsToVerify2);
}

}  // namespace algorithm

}  // namespace alba
