#pragma once

#include <Bitmap/CommonTypes.hpp>

#include <set>
#include <map>

namespace alba
{

namespace AprgBitmap
{

class PenCircles
{
public:
    struct PenCircleDetails
    {
        PenCircleDetails();
        PenCircleDetails(
                double const radiusParameter,
                unsigned int const colorParameter);
        double radius;
        unsigned int color;
    };
    using PointToPenCircleDetailsMap = std::map<BitmapXY, PenCircleDetails>;
    using PointPenCircleDetailsPair = std::pair<BitmapXY, PenCircleDetails>;
    using PointPenCircleDetailsPairs = std::vector<PointPenCircleDetailsPair>;
    using CircleCenterConnection = std::pair<BitmapXY, BitmapXY>;
    using CircleCenterConnections = std::set<CircleCenterConnection>;

    bool isPenCircle(BitmapXY const& point) const;

    PenCircleDetails getPenCircleDetails(BitmapXY const& point) const;
    PointToPenCircleDetailsMap const& getPenCircles() const;
    CircleCenterConnections const& getCenterConnections() const;
    PointPenCircleDetailsPairs getNearestPenCirclesToAPoint(
            BitmapXY const& point,
            unsigned int const distance) const;

    PointToPenCircleDetailsMap & getPenCirclesReference();

    void addAsPenCircle(
            BitmapXY const& point,
            double const radius,
            unsigned int const color);
    void removePenCircleAt(
            BitmapXY const& circleCenter);
    void connectCircles(
            BitmapXY const& circle1Center,
            BitmapXY const& circle2Center);
    void clear();

private:
    PointToPenCircleDetailsMap m_penCircles;
    CircleCenterConnections m_centerConnections;
};

}

}
