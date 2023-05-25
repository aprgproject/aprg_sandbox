#include <Algorithm/Bag/LinkedListBag.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using BagForTest = LinkedListBag<int>;
}

TEST(LinkedListBagTest, IsEmptyWorks) {
    BagForTest bag1;
    BagForTest bag2;
    bag2.add(10);

    EXPECT_TRUE(bag1.isEmpty());
    EXPECT_FALSE(bag2.isEmpty());
}

TEST(LinkedListBagTest, GetSizeWorks) {
    BagForTest bag1;
    BagForTest bag2;
    bag2.add(10);
    bag2.add(5);
    bag2.add(4);

    EXPECT_EQ(0, bag1.getSize());
    EXPECT_EQ(3, bag2.getSize());
}

TEST(LinkedListBagTest, TraverseWorks) {
    BagForTest bag;
    bag.add(1);
    bag.add(2);
    bag.add(3);

    int i = 0;
    bag.traverse([&](int const& object) {
        if (i == 0) {
            EXPECT_EQ(3, object);
        } else if (i == 1) {
            EXPECT_EQ(2, object);
        } else if (i == 2) {
            EXPECT_EQ(1, object);
        }
        i++;
    });
}

TEST(LinkedListBagTest, AddWorks) {
    BagForTest bag;

    bag.add(1);
    bag.add(2);
    bag.add(3);

    EXPECT_EQ(3, bag.getSize());
    int i = 0;
    bag.traverse([&](int const& object) {
        if (i == 0) {
            EXPECT_EQ(3, object);
        } else if (i == 1) {
            EXPECT_EQ(2, object);
        } else if (i == 2) {
            EXPECT_EQ(1, object);
        }
        i++;
    });
}

}  // namespace algorithm

}  // namespace alba
