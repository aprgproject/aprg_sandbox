#include <Container/AlbaXY.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(AlbaXYTest, DefaultValuesAreZero)
{
    AlbaXY<int> xy;    EXPECT_EQ(0, xy.getX());
    EXPECT_EQ(0, xy.getY());
}
TEST(AlbaXYTest, ValuesAreSetAtConstruction)
{
    AlbaXY<int> xy(-5,5);
    EXPECT_EQ(-5, xy.getX());
    EXPECT_EQ(5, xy.getY());
}

TEST(AlbaXYTest,  ValuesCanBeSetAfterConstruction)
{
    AlbaXY<int> xy(-5,5);
    xy.setXAndY(10,10);
    EXPECT_EQ(AlbaXY<int>(10,10), xy);

    xy.setX(23);
    xy.setY(45);
    EXPECT_EQ(AlbaXY<int>(23,45), xy);
}

TEST(AlbaXYTest, XYCanBeCompared)
{
    AlbaXY<int> xy(-5,5);
    EXPECT_NE(AlbaXY<int>(-5,-5), xy);
    EXPECT_EQ(AlbaXY<int>(-5,5), xy);
    EXPECT_NE(AlbaXY<int>(5,-5), xy);
    EXPECT_NE(AlbaXY<int>(5,5), xy);
}

TEST(AlbaXYTest, XTimesYCanBeComputed)
{
    AlbaXY<int> xy(-5,5);
    EXPECT_EQ(-25, xy.getXTimesY());
}

TEST(AlbaXYTest, DisplayableStringIsNotEmpty)
{
    AlbaXY<int> xy(-5,5);
    EXPECT_FALSE(xy.getDisplayableString().empty());
}

TEST(AlbaXYTest, XYSaveTopLeftCorner)
{
    AlbaXY<int> xy;
    xy.saveMinimumXAndY(AlbaXY<int>(-5,5));
    xy.saveMinimumXAndY(AlbaXY<int>(5,-5));
    xy.saveMinimumXAndY(AlbaXY<int>(-5,-5));
    xy.saveMinimumXAndY(AlbaXY<int>(5,5));

    EXPECT_EQ(AlbaXY<int>(-5,-5), xy);
}

TEST(AlbaXYTest, XYSaveBottomRightCorner)
{
    AlbaXY<int> xy;
    xy.saveMaximumXAndY(AlbaXY<int>(-5,5));
    xy.saveMaximumXAndY(AlbaXY<int>(5,-5));
    xy.saveMaximumXAndY(AlbaXY<int>(-5,-5));
    xy.saveMaximumXAndY(AlbaXY<int>(5,5));

    EXPECT_EQ(AlbaXY<int>(5,5), xy);
}

}