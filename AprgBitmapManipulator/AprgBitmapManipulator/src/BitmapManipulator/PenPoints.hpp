#pragma once

#include <Bitmap/CommonTypes.hpp>

#include <set>

namespace alba {

namespace AprgBitmap {

class PenPoints {
public:
    using PenPointsSet = std::set<BitmapXY>;

    bool isPenPoint(BitmapXY const& penPoint) const;
    PenPointsSet const& getPenPoints() const;

    void addAsPenPoint(BitmapXY const& penPoint);
    void addAsPenPoints(BitmapXYs const& bitmapPoints);
    void removePenPoint(BitmapXY const& penPoint);
    void clear();

private:
    PenPointsSet m_penPoints;
};

}  // namespace AprgBitmap

}  // namespace alba
