#pragma once

#include <Bitmap/CommonTypes.hpp>

#include <map>
#include <set>

namespace alba {

namespace AprgBitmap {

class PenCircles {
public:
    struct PenCircleDetails {
        PenCircleDetails();
        PenCircleDetails(double const radiusParameter, uint32_t const colorParameter);
        double radius;
        uint32_t color;
    };
    using PointToPenCircleDetailsMap = std::map<BitmapXY, PenCircleDetails>;
    using PointAndPenCircleDetailsPair = std::pair<BitmapXY, PenCircleDetails>;
    using PointAndPenCircleDetailsPairs = std::vector<PointAndPenCircleDetailsPair>;
    using CircleCenterConnection = std::pair<BitmapXY, BitmapXY>;
    using CircleCenterConnections = std::set<CircleCenterConnection>;

    bool isPenCircle(BitmapXY const& point) const;

    PenCircleDetails getPenCircleDetails(BitmapXY const& point) const;
    PointToPenCircleDetailsMap const& getPenCircles() const;
    CircleCenterConnections const& getCenterConnections() const;
    PointAndPenCircleDetailsPairs getNearestPenCirclesToAPoint(
        BitmapXY const& point, unsigned int const distance) const;

    PointToPenCircleDetailsMap& getPenCirclesReference();

    void addAsPenCircle(BitmapXY const& point, double const radius, uint32_t const color);
    void removePenCircleAt(BitmapXY const& circleCenter);
    void connectCircles(BitmapXY const& circle1Center, BitmapXY const& circle2Center);
    void clear();

private:
    PointToPenCircleDetailsMap m_penCircles;
    CircleCenterConnections m_centerConnections;
};

}  // namespace AprgBitmap

}  // namespace alba
