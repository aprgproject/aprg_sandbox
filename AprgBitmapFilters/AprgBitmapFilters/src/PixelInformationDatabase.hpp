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
    unsigned int label;
    static constexpr unsigned int INITIAL_LABEL_VALUE=0;
    static constexpr unsigned int INVALID_LABEL_VALUE=0x1FFFFFFF;
};

class PixelInformationDatabase
{
public:
    using PixelInformationMap = std::map<BitmapXY, PixelInformation>;

    PixelInformationDatabase();
    void saveAsPenPoints(BitmapXYs const& bitmapPoints);
    void clear();
    PixelInformation getPixelInformation(BitmapXY const& bitmapXY) const;
    PixelInformation & getPixelInformationReferenceAndCreateIfNeeded(BitmapXY const& bitmapXY);
private:
    PixelInformationMap m_pixelsInformationMap; // separate class
};

}
