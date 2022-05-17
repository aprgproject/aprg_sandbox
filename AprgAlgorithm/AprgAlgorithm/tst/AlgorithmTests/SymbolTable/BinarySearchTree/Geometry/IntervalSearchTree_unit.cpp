#include <Algorithm/SymbolTable/BinarySearchTree/Geometry/IntervalSearchTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{

using IntervalForTest = Interval<unsigned int>;
using SearchTreeForTest = IntervalSearchTree<unsigned int, unsigned int>;
}

TEST(IntervalSearchTreeTest, PutWorks)
{
    SearchTreeForTest search;
    search.put({17, 19}, {});
    search.put({5, 8}, {});
    search.put({21, 24}, {});

    auto const& root(search.getRoot());
    EXPECT_EQ((IntervalForTest{17, 9}), root->key);
    EXPECT_EQ(3U, root->numberOfNodesOnThisSubTree);
    EXPECT_EQ(BinarySearchTreeNode::Color::Red, root->parentLinkColor);
    EXPECT_EQ(24U, root->maxValueInSubtree);
    EXPECT_EQ((IntervalForTest{5, 8}), root->left->key);
    EXPECT_EQ(1U, root->left->numberOfNodesOnThisSubTree);
    EXPECT_EQ(BinarySearchTreeNode::Color::Black, root->left->parentLinkColor);
    EXPECT_EQ(8U, root->left->maxValueInSubtree);
    EXPECT_EQ((IntervalForTest{21, 24}), root->right->key);
    EXPECT_EQ(1U, root->right->numberOfNodesOnThisSubTree);
    EXPECT_EQ(BinarySearchTreeNode::Color::Black, root->right->parentLinkColor);
    EXPECT_EQ(24U, root->right->maxValueInSubtree);
}

TEST(IntervalSearchTreeTest, GetSupersetIntervalsOfWorksOnExample1)
{
    SearchTreeForTest search;
    search.put({17, 19}, {});
    search.put({5, 8}, {});
    search.put({21, 24}, {});
    search.put({4, 8}, {});
    search.put({15, 18}, {});
    search.put({7, 10}, {});
    search.put({16, 22}, {});

    auto const& intervalsToVerify(search.getIntersectingIntervalsOf({12, 14}));

    EXPECT_TRUE(intervalsToVerify.empty());
}

TEST(IntervalSearchTreeTest, GetSupersetIntervalsOfWorksOnExample2)
{
    SearchTreeForTest search;
    search.put({17, 19}, {});
    search.put({5, 8}, {});
    search.put({21, 24}, {});
    search.put({4, 8}, {});
    search.put({15, 18}, {});
    search.put({7, 10}, {});
    search.put({16, 22}, {});

    auto const& intervalsToVerify(search.getIntersectingIntervalsOf({23, 25}));

    SearchTreeForTest::Keys const& intervalsToExpect{{21, 24}};
    EXPECT_EQ(intervalsToExpect, intervalsToVerify);
}

TEST(IntervalSearchTreeTest, GetSupersetIntervalsOfWorksOnExample3)
{
    SearchTreeForTest search;
    search.put({17, 19}, {});
    search.put({5, 8}, {});
    search.put({21, 24}, {});
    search.put({4, 8}, {});
    search.put({15, 18}, {});
    search.put({7, 10}, {});
    search.put({16, 22}, {});

    auto const& intervalsToVerify(search.getIntersectingIntervalsOf({4, 25}));

    SearchTreeForTest::Keys const& intervalsToExpect{{15, 18}, {5, 8}, {4, 8}, {7, 10}, {17, 19}, {16, 22}, {21, 24}};
    EXPECT_EQ(intervalsToExpect, intervalsToVerify);
}

}

}
