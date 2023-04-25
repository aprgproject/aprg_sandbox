#include <Geometry/ThreeDimensions/Constructs/Ellipsoid.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace ThreeDimensions {

TEST(EllipsoidTest, EmptyEllipsoid) {
    Ellipsoid ellipsoid;

    EXPECT_EQ(Point(0, 0, 0), ellipsoid.getCenter());
    EXPECT_DOUBLE_EQ(0, ellipsoid.getAValue());
    EXPECT_DOUBLE_EQ(0, ellipsoid.getBValue());
    EXPECT_DOUBLE_EQ(0, ellipsoid.getCValue());
}

TEST(EllipsoidTest, EllipsoidAtOriginWithRadius) {
    Ellipsoid ellipsoid(Point(0, 0, 0), 10, 11, 12);

    EXPECT_EQ(Point(0, 0, 0), ellipsoid.getCenter());
    EXPECT_DOUBLE_EQ(10, ellipsoid.getAValue());
    EXPECT_DOUBLE_EQ(11, ellipsoid.getBValue());
    EXPECT_DOUBLE_EQ(12, ellipsoid.getCValue());
    EXPECT_DOUBLE_EQ(-9.818135054134796, ellipsoid.calculateXFromYAndZ(1, 2, -1));
    EXPECT_DOUBLE_EQ(-9.8318642970474102, ellipsoid.calculateYFromXAndZ(3, 4, -1));
    EXPECT_DOUBLE_EQ(-8.0719901383356785, ellipsoid.calculateZFromXAndY(5, 6, -1));
}

TEST(EllipsoidTest, EllipsoidNotAtOriginWithRadius) {
    Ellipsoid ellipsoid(Point(1, 2, 3), 10, 11, 12);

    EXPECT_EQ(Point(1, 2, 3), ellipsoid.getCenter());
    EXPECT_DOUBLE_EQ(10, ellipsoid.getAValue());
    EXPECT_DOUBLE_EQ(11, ellipsoid.getBValue());
    EXPECT_DOUBLE_EQ(12, ellipsoid.getCValue());
    EXPECT_DOUBLE_EQ(-8.9236641052871111, ellipsoid.calculateXFromYAndZ(1, 2, -1));
    EXPECT_DOUBLE_EQ(-8.738702073445479, ellipsoid.calculateYFromXAndZ(3, 4, -1));
    EXPECT_DOUBLE_EQ(-7.095478081099003, ellipsoid.calculateZFromXAndY(5, 6, -1));
}

TEST(EllipsoidTest, IsInsideWorks) {
    Ellipsoid ellipsoid(Point(1, 2, 3), 10, 11, 12);

    EXPECT_TRUE(ellipsoid.isInside(Point(0, 0, 0)));
}

}  // namespace ThreeDimensions

}  // namespace alba
