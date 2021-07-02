#include "LabelForPixels.hpp"

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

unsigned int LabelForPixels::getLabel(BitmapXY const& point) const
{
    unsigned int label(INITIAL_LABEL_VALUE);
    PixelsToLabelsMap::const_iterator it = m_pixelsTolabelsMap.find(point);
    if(it != m_pixelsTolabelsMap.cend())
    {
        label = it->second;
    }
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
