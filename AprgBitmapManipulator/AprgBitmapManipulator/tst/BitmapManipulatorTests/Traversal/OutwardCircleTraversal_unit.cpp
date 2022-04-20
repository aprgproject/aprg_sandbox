#include <BitmapFilters/Traversal/OutwardCircleTraversal.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace AprgBitmap
{

using Coordinate=OutwardCircleTraversal::Coordinate;
using RadiusToCoordinates=OutwardCircleTraversal::RadiusToCoordinates;
using ExpectedRadiusToCoordinates=vector<OutwardCircleTraversal::RadiusAndCoordinatesPair>;

TEST(OutwardCircleTraversalTest, ConstructedRadiusToCoordinatesAreCorrectForZeroRadius)
{
    OutwardCircleTraversal traversal(0);
    RadiusToCoordinates const& radiusToCoordinates(traversal.getRadiusToCoordinates());

    ExpectedRadiusToCoordinates expectation;
    expectation.emplace_back(0, Coordinate(0,0));
    RadiusToCoordinates::const_iterator itInVerify=radiusToCoordinates.cbegin();
    ExpectedRadiusToCoordinates::const_iterator itInExpect=expectation.cbegin();
    ASSERT_EQ(expectation.size(), radiusToCoordinates.size());
    for(;itInExpect!=expectation.cend() && itInVerify!=radiusToCoordinates.cend();)
    {
        EXPECT_DOUBLE_EQ(itInExpect->first, itInVerify->first);
        EXPECT_EQ(itInExpect->second.coordinate1, itInVerify->second.coordinate1);
        EXPECT_EQ(itInExpect->second.coordinate2, itInVerify->second.coordinate2);
        itInExpect++;
        itInVerify++;
    }
}

TEST(OutwardCircleTraversalTest, ConstructedRadiusToCoordinatesAreCorrectForRadiusWith5)
{
    OutwardCircleTraversal traversal(5);
    OutwardCircleTraversal::RadiusToCoordinates const& radiusToCoordinates(traversal.getRadiusToCoordinates());

    ExpectedRadiusToCoordinates expectation;
    expectation.emplace_back(0, Coordinate(0,0));
    expectation.emplace_back(1, Coordinate(0,1));
    expectation.emplace_back(1.4142135623730951, Coordinate(1,1));
    expectation.emplace_back(2, Coordinate(0,2));
    expectation.emplace_back(2.2360679774997898, Coordinate(1,2));
    expectation.emplace_back(2.8284271247461903, Coordinate(2,2));
    expectation.emplace_back(3, Coordinate(0,3));
    expectation.emplace_back(3.1622776601683795, Coordinate(1,3));
    expectation.emplace_back(3.6055512754639891, Coordinate(2,3));
    expectation.emplace_back(4, Coordinate(0,4));
    expectation.emplace_back(4.1231056256176606, Coordinate(1,4));
    expectation.emplace_back(4.2426406871192848, Coordinate(3,3));
    expectation.emplace_back(4.4721359549995796, Coordinate(2,4));
    expectation.emplace_back(5, Coordinate(0,5));
    expectation.emplace_back(5, Coordinate(3,4));
    expectation.emplace_back(5.0990195135927845, Coordinate(1,5));
    expectation.emplace_back(5.3851648071345037, Coordinate(2,5));
    expectation.emplace_back(5.6568542494923806, Coordinate(4,4));
    expectation.emplace_back(5.8309518948453007, Coordinate(3,5));
    expectation.emplace_back(6.4031242374328485, Coordinate(4,5));
    expectation.emplace_back(7.0710678118654755, Coordinate(5,5));
    RadiusToCoordinates::const_iterator itInVerify=radiusToCoordinates.cbegin();
    ExpectedRadiusToCoordinates::const_iterator itInExpect=expectation.cbegin();
    ASSERT_EQ(expectation.size(), radiusToCoordinates.size());
    for(;itInExpect!=expectation.cend() && itInVerify!=radiusToCoordinates.cend();)
    {
        EXPECT_DOUBLE_EQ(itInExpect->first, itInVerify->first);
        EXPECT_EQ(itInExpect->second.coordinate1, itInVerify->second.coordinate1);
        EXPECT_EQ(itInExpect->second.coordinate2, itInVerify->second.coordinate2);
        itInExpect++;
        itInVerify++;
    }
}

}

}
