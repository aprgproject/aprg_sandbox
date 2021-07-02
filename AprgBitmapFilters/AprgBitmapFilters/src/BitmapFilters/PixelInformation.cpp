#include "PixelInformation.hpp"

namespace alba
{

namespace AprgBitmap
{

PixelInformation::PixelInformation()
    : m_label(INITIAL_LABEL_VALUE)
    , m_isPenPixel(false)
    , m_penCircle()
{}

bool PixelInformation::isPenPixel() const
{
    return m_isPenPixel;
}

bool PixelInformation::isInitialLabel() const
{
    return m_label==INITIAL_LABEL_VALUE;
}

bool PixelInformation::isInvalidLabel() const
{
    return m_label==INVALID_LABEL_VALUE;
}

bool PixelInformation::isInitialOrInvalidLabel() const
{
    return isInitialLabel() || isInvalidLabel();
}

unsigned int PixelInformation::getLabel() const
{
    return m_label;
}

TwoDimensions::Circle PixelInformation::getPenCircle() const
{
    return m_penCircle;
}

void PixelInformation::setAsPenPoint(bool const isPenPixel)
{
    m_isPenPixel = isPenPixel;
}

void PixelInformation::setLabel(unsigned int const label)
{
    m_label=label;
}

void PixelInformation::setPenCircle(TwoDimensions::Circle const& penCircle)
{
    m_penCircle=penCircle;
}

}

}
