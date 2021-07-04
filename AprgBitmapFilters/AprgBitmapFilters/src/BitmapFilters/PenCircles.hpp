#pragma once

#include <Bitmap/CommonTypes.hpp>

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

    bool isPenCircle(BitmapXY const& point) const;
    PointToPenCircleDetailsMap const& getPenCircles() const;
    PointToPenCircleDetailsMap & getPenCirclesReference();

    void addAsPenCircle(
            BitmapXY const& point,
            double const radius,
            unsigned int const color);
    void removePenCircle(BitmapXY const& point);
    void clear();

private:
    PointToPenCircleDetailsMap m_penCircles;
};

}
}
