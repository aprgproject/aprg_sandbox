#include <Container/AlbaXYZ.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(AlbaXYZTest, DefaultValuesAreZero)
{
    AlbaXYZ<int> xyz;
    EXPECT_EQ(0, xyz.getX());
    EXPECT_EQ(0, xyz.getY());
}

TEST(AlbaXYZTest, ValuesAreSetAtConstruction)
{
    AlbaXYZ<int> xyz(-5,5,10);
    EXPECT_EQ(-5, xyz.getX());
    EXPECT_EQ(5, xyz.getY());
    EXPECT_EQ(5, xyz.getZ());
}

TEST(AlbaXYZTest,  ValuesCanBeSetAfterConstruction)
{
    AlbaXYZ<int> xyz(-5,5,10);
    xyz.setXAndYAndZ(10,20,30);
    EXPECT_EQ(AlbaXYZ<int>(10,20,30), xyz);

    xyz.setX(23);
    xyz.setY(45);
    xyz.setZ(68);
    EXPECT_EQ(AlbaXYZ<int>(23,45,68), xyz);
}

TEST(AlbaXYZTest, XYZCanBeCompared)
{
    AlbaXYZ<int> xyz(-5,5,10);
    EXPECT_NE(AlbaXYZ<int>(-5,-5,10), xyz);
    EXPECT_NE(AlbaXYZ<int>(-5,5,20), xyz);
    EXPECT_EQ(AlbaXYZ<int>(-5,5,10), xyz);
    EXPECT_NE(AlbaXYZ<int>(5,-5,10), xyz);
    EXPECT_NE(AlbaXYZ<int>(5,5,10), xyz);
}

TEST(AlbaXYZTest, XTimesYCanBeComputed)
{
    AlbaXYZ<int> xyz(-5,5,10);
    EXPECT_EQ(-250, xyz.getXTimesYTimesZ());
}

TEST(AlbaXYZTest, DisplayableStringIsNotEmpty)
{
    AlbaXYZ<int> xyz(-5,5,10);
    EXPECT_FALSE(xyz.getDisplayableString().empty());
}

TEST(AlbaXYZTest, XYZMinimumCanBeSaved)
{
    AlbaXYZ<int> xyz;
    xyz.saveMinimumXAndYAndZ(AlbaXYZ<int>(-5,5,10));
    xyz.saveMinimumXAndYAndZ(AlbaXYZ<int>(5,-5,10));
    xyz.saveMinimumXAndYAndZ(AlbaXYZ<int>(-5,-5,-10));
    xyz.saveMinimumXAndYAndZ(AlbaXYZ<int>(5,5,-10));

    EXPECT_EQ(AlbaXYZ<int>(-5,-5,-10), xyz);
}

TEST(AlbaXYZTest, XYZMaximumCanBeSaved)
{
    AlbaXYZ<int> xyz;
    xyz.saveMaximumXAndYAndZ(AlbaXYZ<int>(-5,5,-10));
    xyz.saveMaximumXAndYAndZ(AlbaXYZ<int>(5,-5,-10));
    xyz.saveMaximumXAndYAndZ(AlbaXYZ<int>(-5,-5,10));
    xyz.saveMaximumXAndYAndZ(AlbaXYZ<int>(5,5,10));

    EXPECT_EQ(AlbaXYZ<int>(5,5,10), xyz);
}

}
