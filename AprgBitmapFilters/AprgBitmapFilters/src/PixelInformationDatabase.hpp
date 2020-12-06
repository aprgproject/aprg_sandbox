#pragma once

#include <CommonTypes.hpp>

#include <map>

namespace alba
{

enum class PixelType
{
    Pen,
    Unknown
};

struct PixelInformation
{
    PixelInformation();
    PixelType type;
};

class PixelInformationDatabase
{
public:
    using PixelInformationMap = std::map<BitmapXY, PixelInformation>;

    PixelInformationDatabase();
    void saveAsPenPoints(BitmapXYs const& bitmapPoints);
    void clear();
    PixelInformation getPixelInformation(BitmapXY const& bitmapXY) const;
private:
    PixelInformationMap m_pixelsInformationMap; // separate class};

}