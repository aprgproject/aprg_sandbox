#include "LabelForPoints.hpp"

#include <BitmapManipulator/ColorUtilities.hpp>
#include <Common/Math/Helpers/DigitRelatedHelpers.hpp>

#include <cmath>

using namespace alba::AprgBitmap::ColorUtilities;
using namespace alba::mathHelper;

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

uint32_t getLabelColor(unsigned int const label)
{
    unsigned int digits = getNumberOfBase10Digits(label);
    double newValue = (static_cast<double>(1)/label) * pow(10, digits+8);
    return getColorValueOnly(static_cast<uint32_t>(newValue) % 0xFFFFFF);
}

unsigned int LabelForPoints::getLabel(BitmapXY const& point) const
{
    unsigned int label(INITIAL_LABEL_VALUE);
    PixelsToLabelsMap::const_iterator it = m_pixelsTolabelsMap.find(point);
    if(it != m_pixelsTolabelsMap.cend())
    {
        label = it->second;
    }
    return label;
}

LabelForPoints::PixelsToLabelsMap const& LabelForPoints::getPixelsToLabels() const
{
    return m_pixelsTolabelsMap;
}

void LabelForPoints::setLabel(
        BitmapXY const& point,
        unsigned int const label)
{
    m_pixelsTolabelsMap[point]=label;
}

}

}
