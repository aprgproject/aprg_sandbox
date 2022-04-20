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
    penPoints.addAsPenPoint(BitmapXY(4155U, 6416U));

    EXPECT_FALSE(penPoints.isPenPoint(BitmapXY(256U, 552U)));
    EXPECT_TRUE(penPoints.isPenPoint(BitmapXY(4155U, 6416U)));
}

TEST(PenPointsTest, GetPenPointsWorks)
{
    PenPoints penPoints;
    penPoints.addAsPenPoint(BitmapXY(4155U, 6416U));

    PenPoints::PenPointsSet const& penPointsToVerify(penPoints.getPenPoints());

    ASSERT_EQ(1U, penPointsToVerify.size());
    BitmapXY const& pointToVerify(*penPointsToVerify.cbegin());
    EXPECT_EQ(BitmapXY(4155U, 6416U), pointToVerify);
}

TEST(PenPointsTest, AddAsPenPointWorks)
{
    PenPoints penPoints;

    penPoints.addAsPenPoint(BitmapXY(4155U, 6416U));

    PenPoints::PenPointsSet const& penPointsToVerify(penPoints.getPenPoints());
    ASSERT_EQ(1U, penPointsToVerify.size());
    BitmapXY const& pointToVerify(*penPointsToVerify.cbegin());
    EXPECT_EQ(BitmapXY(4155U, 6416U), pointToVerify);
}

TEST(PenPointsTest, AddAsPenPointsWorks)
{
    PenPoints penPoints;

    penPoints.addAsPenPoints({BitmapXY(4155U, 6416U), BitmapXY(4156U, 256U)});

    PenPoints::PenPointsSet const& penPointsToVerify(penPoints.getPenPoints());
    ASSERT_EQ(2U, penPointsToVerify.size());
    PenPoints::PenPointsSet::const_iterator itToVerify=penPointsToVerify.cbegin();
    BitmapXY const& pointToVerify1(*itToVerify++);
    BitmapXY const& pointToVerify2(*itToVerify++);
    EXPECT_EQ(BitmapXY(4155U, 6416U), pointToVerify1);
    EXPECT_EQ(BitmapXY(4156U, 256U), pointToVerify2);
}

TEST(PenPointsTest, RemovePenPointWorks)
{
    PenPoints penPoints;
    penPoints.addAsPenPoint(BitmapXY(4155U, 6416U));

    penPoints.removePenPoint(BitmapXY(4155U, 6416U));

    PenPoints::PenPointsSet const& penPointsToVerify(penPoints.getPenPoints());
    ASSERT_TRUE(penPointsToVerify.empty());
}

TEST(PenPointsTest, ClearWorks)
{
    PenPoints penPoints;
    penPoints.addAsPenPoint(BitmapXY(4155U, 6416U));

    penPoints.clear();

    PenPoints::PenPointsSet const& penPointsToVerify(penPoints.getPenPoints());
    ASSERT_TRUE(penPointsToVerify.empty());
}

}

}
