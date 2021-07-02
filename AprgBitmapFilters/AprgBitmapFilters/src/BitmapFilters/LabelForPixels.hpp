#pragma once

#include <Bitmap/CommonTypes.hpp>

#include <map>

namespace alba
{

namespace AprgBitmap
{

constexpr unsigned int INITIAL_LABEL_VALUE=0;
constexpr unsigned int INVALID_LABEL_VALUE=0x1FFFFFFF;

bool isInitialLabel(unsigned int const label);
bool isInvalidLabel(unsigned int const label);
bool isInitialOrInvalidLabel(unsigned int const label);

class LabelForPixels
{
public:
    using PixelsToLabelsMap=std::map<BitmapXY, unsigned int>;
    unsigned int getLabel(BitmapXY const& point) const;
    void setLabel(
            BitmapXY const& point,
            unsigned int const label);

private:
    PixelsToLabelsMap m_pixelsTolabelsMap;
};

}

}
