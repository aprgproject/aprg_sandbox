#include <Common/Container/AlbaXYZ.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using IntXYZ = AlbaXYZ<int>;
}

TEST(AlbaXYZTest, DefaultValuesAreZero) {
    IntXYZ xyz;

    EXPECT_EQ(0, xyz.getX());
    EXPECT_EQ(0, xyz.getY());
    EXPECT_EQ(0, xyz.getZ());
}

TEST(AlbaXYZTest, ValuesAreSetAtConstruction) {
    IntXYZ xyz(-5, 5, 10);

    EXPECT_EQ(-5, xyz.getX());
    EXPECT_EQ(5, xyz.getY());
    EXPECT_EQ(10, xyz.getZ());
}

TEST(AlbaXYZTest, EqualityOperatorWorks) {
    IntXYZ xyz(-5, 5, 10);

    EXPECT_FALSE(IntXYZ(-5, -5, 10) == xyz);
    EXPECT_FALSE(IntXYZ(-5, 5, 20) == xyz);
    EXPECT_TRUE(IntXYZ(-5, 5, 10) == xyz);
    EXPECT_FALSE(IntXYZ(5, -5, 10) == xyz);
    EXPECT_FALSE(IntXYZ(5, 5, 10) == xyz);
}

TEST(AlbaXYZTest, NonEqualityOperatorWorks) {
    IntXYZ xyz(-5, 5, 10);

    EXPECT_TRUE(IntXYZ(-5, -5, 10) != xyz);
    EXPECT_TRUE(IntXYZ(-5, 5, 20) != xyz);
    EXPECT_FALSE(IntXYZ(-5, 5, 10) != xyz);
    EXPECT_TRUE(IntXYZ(5, -5, 10) != xyz);
    EXPECT_TRUE(IntXYZ(5, 5, 10) != xyz);
}

TEST(AlbaXYZTest, LessThanOperatorWorks) {
    IntXYZ xyz(-5, 5, 10);

    EXPECT_FALSE(IntXYZ(-5, 5, 10) < xyz);
    EXPECT_TRUE(IntXYZ(-6, 5, 10) < xyz);
    EXPECT_FALSE(IntXYZ(-4, 5, 10) < xyz);
    EXPECT_TRUE(IntXYZ(-5, 4, 10) < xyz);
    EXPECT_FALSE(IntXYZ(-5, 6, 10) < xyz);
    EXPECT_TRUE(IntXYZ(-5, 5, 9) < xyz);
    EXPECT_FALSE(IntXYZ(-5, 5, 11) < xyz);
}

TEST(AlbaXYZTest, PlusUnaryOperatorWorks) { EXPECT_EQ(IntXYZ(1, 2, 3), +IntXYZ(1, 2, 3)); }

TEST(AlbaXYZTest, MinusUnaryOperatorWorks) { EXPECT_EQ(IntXYZ(-1, -2, -3), -IntXYZ(1, 2, 3)); }

TEST(AlbaXYZTest, PlusBinaryOperatorWorks) { EXPECT_EQ(IntXYZ(5, -3, -3), (IntXYZ(1, 2, 3) + IntXYZ(4, -5, -6))); }

TEST(AlbaXYZTest, MinusBinaryOperatorWorks) { EXPECT_EQ(IntXYZ(-3, 7, 9), (IntXYZ(1, 2, 3) - IntXYZ(4, -5, -6))); }

TEST(AlbaXYZTest, MultiplyBinaryOperatorWorks) { EXPECT_EQ(IntXYZ(35, -70, 105), (IntXYZ(5, -10, 15) * 7)); }

TEST(AlbaXYZTest, DivideBinaryOperatorWorks) { EXPECT_EQ(IntXYZ(1, -2, 3), (IntXYZ(5, -10, 15) / 5)); }

TEST(AlbaXYZTest, PlusAssignmentOperatorWorks) {
    IntXYZ xyzToTest(1, 2, 3);

    xyzToTest += IntXYZ(4, -5, -6);

    EXPECT_EQ(IntXYZ(5, -3, -3), xyzToTest);
}

TEST(AlbaXYZTest, MinusAssignmentOperatorWorks) {
    IntXYZ xyzToTest(1, 2, 3);

    xyzToTest -= IntXYZ(4, -5, -6);

    EXPECT_EQ(IntXYZ(-3, 7, 9), xyzToTest);
}

TEST(AlbaXYZTest, IsEmptyWorks) {
    EXPECT_TRUE(IntXYZ().isEmpty());
    EXPECT_FALSE(IntXYZ(-5, 5, 10).isEmpty());
}

TEST(AlbaXYZTest, GetXWorks) {
    IntXYZ xyz(-5, 5, 10);

    EXPECT_EQ(-5, xyz.getX());
}

TEST(AlbaXYZTest, GetYWorks) {
    IntXYZ xyz(-5, 5, 10);

    EXPECT_EQ(5, xyz.getY());
}

TEST(AlbaXYZTest, GetZWorks) {
    IntXYZ xyz(-5, 5, 10);

    EXPECT_EQ(10, xyz.getZ());
}

TEST(AlbaXYZTest, GetXTimesYTimesZWorks) {
    IntXYZ xyz(-5, 5, 10);

    EXPECT_EQ(-250, xyz.getXTimesYTimesZ());
}

TEST(AlbaXYZTest, SetXWorks) {
    IntXYZ xyz(-5, 5, 10);

    xyz.setX(23);

    EXPECT_EQ(IntXYZ(23, 5, 10), xyz);
}

TEST(AlbaXYZTest, SetYWorks) {
    IntXYZ xyz(-5, 5, 10);

    xyz.setY(45);

    EXPECT_EQ(IntXYZ(-5, 45, 10), xyz);
}

TEST(AlbaXYZTest, SetZWorks) {
    IntXYZ xyz(-5, 5, 10);

    xyz.setZ(68);

    EXPECT_EQ(IntXYZ(-5, 5, 68), xyz);
}

TEST(AlbaXYZTest, SetXAndYAndZWorks) {
    IntXYZ xyz(-5, 5, 10);

    xyz.setXAndYAndZ(10, 20, 30);

    EXPECT_EQ(IntXYZ(10, 20, 30), xyz);
}

TEST(AlbaXYZTest, SaveMinimumXAndYAndZWorks) {
    IntXYZ xyz;

    xyz.saveMinimumXAndYAndZ(IntXYZ(-5, 5, 10));
    xyz.saveMinimumXAndYAndZ(IntXYZ(5, -5, 10));
    xyz.saveMinimumXAndYAndZ(IntXYZ(-5, -5, -10));
    xyz.saveMinimumXAndYAndZ(IntXYZ(5, 5, -10));

    EXPECT_EQ(IntXYZ(-5, -5, -10), xyz);
}

TEST(AlbaXYZTest, SaveMaximumXAndYAndZWorks) {
    IntXYZ xyz;

    xyz.saveMaximumXAndYAndZ(IntXYZ(-5, 5, -10));
    xyz.saveMaximumXAndYAndZ(IntXYZ(5, -5, -10));
    xyz.saveMaximumXAndYAndZ(IntXYZ(-5, -5, 10));
    xyz.saveMaximumXAndYAndZ(IntXYZ(5, 5, 10));

    EXPECT_EQ(IntXYZ(5, 5, 10), xyz);
}

TEST(AlbaXYZTest, OutputStreamOperatorWorks) {
    stringstream ss;
    IntXYZ xyz(-5, 5, 10);

    ss << xyz;

    EXPECT_EQ("(-5,5,10)", ss.str());
}

}  // namespace alba
