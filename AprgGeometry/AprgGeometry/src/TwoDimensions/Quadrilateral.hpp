#pragma once

#include <TwoDimensions/Polygon.hpp>

#include <functional>

namespace alba
{

namespace TwoDimensions
{

using QuadrilateralPolygonParent = Polygon<4>;

class Quadrilateral : public QuadrilateralPolygonParent
{
public:
    struct StartEndOfXAndY
    {
        StartEndOfXAndY(
                double const xStartParameter,
                double const xEndParameter,
                double const yParameter);
        double xStart;
        double xEnd;
        double y;
    };
    using TraverseOperation = std::function<void(Point const&)>;
    using GroupOfPoints = std::vector<Points>;
    using ListOfStartEndOfXAndY = std::vector<StartEndOfXAndY>;

    Quadrilateral();
    Quadrilateral(Point const& first, Point const& second, Point const& third, Point const& fourth);

    void traverseArea(
            double const interval,
            TraverseOperation const& traverseOperation) const;

    std::string getDisplayableString() const;

private:
    GroupOfPoints getGroupOfPointsBasedOnYValue() const;
    ListOfStartEndOfXAndY getStartEndForXs(
            GroupOfPoints const& groupOfPointsBasedOnYValue,
            double const interval) const;
    ListOfStartEndOfXAndY getStartEndForXsFor1Points(
            Points const& points) const;
    ListOfStartEndOfXAndY getStartEndForXsFor2Points(
            Points const& points1,
            Points const& points2,
            double const interval) const;
    ListOfStartEndOfXAndY getStartEndForXsFor3Points(
            Points const& points1,
            Points const& points2,
            Points const& points3,
            double const interval) const;
    ListOfStartEndOfXAndY getStartEndForXsFor4Points(
            Points const& points1,
            Points const& points2,
            Points const& points3,
            Points const& points4,
            double const interval) const;
};

std::ostream & operator<<(std::ostream & out, Quadrilateral const& quadrilateral);

}
}
