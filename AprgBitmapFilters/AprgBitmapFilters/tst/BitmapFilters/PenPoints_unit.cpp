#include <BitmapFilters/PenPoints.hpp>

#include <gtest/gtest.h>

using namespace alba::AprgBitmap;
using namespace std;

namespace alba
{

namespace AprgBitmap
{

TEST(PenPointsTest, IsPenPointWorks)
{
    PenPoints penPoints;
    penPoints.addAsPenPoint(BitmapXY(4155u, 6416u));

    EXPECT_FALSE(penPoints.isPenPoint(BitmapXY(256u, 552u)));
    EXPECT_TRUE(penPoints.isPenPoint(BitmapXY(4155u, 6416u)));
}

TEST(PenPointsTest, GetPenPointsWorks)
{
    PenPoints penPoints;
    penPoints.addAsPenPoint(BitmapXY(4155u, 6416u));

    PenPoints::PenPointsSet const& penPointsToVerify(penPoints.getPenPoints());

    ASSERT_EQ(1u, penPointsToVerify.size());
    BitmapXY const& pointToVerify(*penPointsToVerify.cbegin());
    EXPECT_EQ(BitmapXY(4155u, 6416u), pointToVerify);
}

TEST(PenPointsTest, AddAsPenPointWorks)
{
    PenPoints penPoints;

    penPoints.addAsPenPoint(BitmapXY(4155u, 6416u));

    PenPoints::PenPointsSet const& penPointsToVerify(penPoints.getPenPoints());
    ASSERT_EQ(1u, penPointsToVerify.size());
    BitmapXY const& pointToVerify(*penPointsToVerify.cbegin());
    EXPECT_EQ(BitmapXY(4155u, 6416u), pointToVerify);
}

TEST(PenPointsTest, AddAsPenPointsWorks)
{
    PenPoints penPoints;

    penPoints.addAsPenPoints({BitmapXY(4155u, 6416u), BitmapXY(4156u, 256u)});

    PenPoints::PenPointsSet const& penPointsToVerify(penPoints.getPenPoints());
    ASSERT_EQ(2u, penPointsToVerify.size());
    PenPoints::PenPointsSet::const_iterator itToVerify=penPointsToVerify.cbegin();
    BitmapXY const& pointToVerify1(*itToVerify++);
    BitmapXY const& pointToVerify2(*itToVerify++);
    EXPECT_EQ(BitmapXY(4155u, 6416u), pointToVerify1);
    EXPECT_EQ(BitmapXY(4156u, 256u), pointToVerify2);
}

TEST(PenPointsTest, RemovePenPointWorks)
{
    PenPoints penPoints;
    penPoints.addAsPenPoint(BitmapXY(4155u, 6416u));

    penPoints.removePenPoint(BitmapXY(4155u, 6416u));

    PenPoints::PenPointsSet const& penPointsToVerify(penPoints.getPenPoints());
    ASSERT_TRUE(penPointsToVerify.empty());
}

TEST(PenPointsTest, ClearWorks)
{
    PenPoints penPoints;
    penPoints.addAsPenPoint(BitmapXY(4155u, 6416u));

    penPoints.clear();

    PenPoints::PenPointsSet const& penPointsToVerify(penPoints.getPenPoints());
    ASSERT_TRUE(penPointsToVerify.empty());
}

}

}
