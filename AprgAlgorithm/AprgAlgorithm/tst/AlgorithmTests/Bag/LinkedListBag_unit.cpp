#include <Algorithm/Bag/LinkedListBag.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using BagForTest = LinkedListBag<unsigned int>;
}

TEST(LinkedListBagTest, IsEmptyWorks)
{
    BagForTest bag1;
    BagForTest bag2;
    bag2.add(10U);

    EXPECT_TRUE(bag1.isEmpty());
    EXPECT_FALSE(bag2.isEmpty());
}

TEST(LinkedListBagTest, GetSizeWorks)
{
    BagForTest bag1;
    BagForTest bag2;
    bag2.add(10U);
    bag2.add(5U);
    bag2.add(4U);

    EXPECT_EQ(0U, bag1.getSize());
    EXPECT_EQ(3U, bag2.getSize());
}

TEST(LinkedListBagTest, TraverseWorks)
{
    BagForTest bag;
    bag.add(1U);
    bag.add(2U);
    bag.add(3U);

    unsigned int i=0;
    bag.traverse([&](unsigned int const& object)
    {
        if(i==0)
        {
            EXPECT_EQ(3U, object);
        }
        else if(i==1)
        {
            EXPECT_EQ(2U, object);
        }
        else if(i==2)
        {
            EXPECT_EQ(1U, object);
        }
        i++;
    });
}

TEST(LinkedListBagTest, AddWorks)
{
    BagForTest bag;

    bag.add(1U);
    bag.add(2U);
    bag.add(3U);

    EXPECT_EQ(3U, bag.getSize());
    unsigned int i=0;
    bag.traverse([&](unsigned int const& object)
    {
        if(i==0)
        {
            EXPECT_EQ(3U, object);
        }
        else if(i==1)
        {
            EXPECT_EQ(2U, object);
        }
        else if(i==2)
        {
            EXPECT_EQ(1U, object);
        }
        i++;
    });
}

}

}
