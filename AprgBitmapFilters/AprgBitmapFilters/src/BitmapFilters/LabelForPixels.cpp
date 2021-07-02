#include "LabelForPixels.hpp"

#include <Math/AlbaMathHelper.hpp>

#include <cmath>

namespace alba
{
namespace AprgBitmap
{
bool isInitialLabel(unsigned int const label)
{
    return label==INITIAL_LABEL_VALUE;
}

bool isInvalidLabel(unsigned int const label)
{
    return label==INVALID_LABEL_VALUE;
}

bool isInitialOrInvalidLabel(unsigned int const label)
{
    return isInitialLabel(label) || isInvalidLabel(label);
}

unsigned int getLabelColor(unsigned int const label)
{
    unsigned int digits = mathHelper::getNumberOfIntegerDigits(label);
    double newValue = (static_cast<double>(1)/label) * pow(10, digits+8);
    return static_cast<unsigned int>(newValue) % 0xFFFFFF;
}

unsigned int LabelForPixels::getLabel(BitmapXY const& point) const
{
    unsigned int label(INITIAL_LABEL_VALUE);    PixelsToLabelsMap::const_iterator it = m_pixelsTolabelsMap.find(point);
    if(it != m_pixelsTolabelsMap.cend())
    {
        label = it->second;    }
    return label;
}

void LabelForPixels::setLabel(
        BitmapXY const& point,
        unsigned int const label)
{
    m_pixelsTolabelsMap[point]=label;
}

}

}
