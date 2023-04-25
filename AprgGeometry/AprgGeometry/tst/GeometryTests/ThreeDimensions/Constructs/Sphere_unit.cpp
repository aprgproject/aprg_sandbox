#include <Geometry/ThreeDimensions/Constructs/Sphere.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace ThreeDimensions {

TEST(SphereTest, EmptySphere) {
    Sphere sphere;

    EXPECT_EQ(Point(0, 0, 0), sphere.getCenter());
    EXPECT_DOUBLE_EQ(0, sphere.getRadius());
}

TEST(SphereTest, SphereAtOriginWithRadius) {
    Sphere sphere(Point(0, 0, 0), 10);

    EXPECT_EQ(Point(0, 0, 0), sphere.getCenter());
    EXPECT_DOUBLE_EQ(10, sphere.getRadius());
    EXPECT_EQ(optional<double>(-9.7467943448089631), sphere.calculateXFromYAndZ(1, 2, -1));
    EXPECT_EQ(optional<double>(-8.6602540378443873), sphere.calculateYFromXAndZ(3, 4, -1));
    EXPECT_EQ(optional<double>(-6.2449979983983983), sphere.calculateZFromXAndY(5, 6, -1));
}

TEST(SphereTest, SphereNotAtOriginWithRadius) {
    Sphere sphere(Point(1, 2, 3), 10);

    EXPECT_EQ(Point(1, 2, 3), sphere.getCenter());
    EXPECT_DOUBLE_EQ(10, sphere.getRadius());
    EXPECT_EQ(optional<double>(-8.8994949366116654), sphere.calculateXFromYAndZ(1, 2, -1));
    EXPECT_EQ(optional<double>(-7.7467943448089631), sphere.calculateYFromXAndZ(3, 4, -1));
    EXPECT_EQ(optional<double>(-5.2462112512353212), sphere.calculateZFromXAndY(5, 6, -1));
}

TEST(SphereTest, IsInsideWorks) {
    Sphere sphere(Point(1, 2, 3), 10);

    EXPECT_TRUE(sphere.isInside(Point(0, 0, 0)));
}

}  // namespace ThreeDimensions

}  // namespace alba
