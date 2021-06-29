#include "PixelInformation.hpp"

namespace alba
{

PixelInformation::PixelInformation()
    : m_isPenPixel(false)
    , m_label(INITIAL_LABEL_VALUE)
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

unsigned int PixelInformation::getLabel() const
{
    return m_label;
}

void PixelInformation::setAsPenPoint(bool const isPenPixel)
{
    m_isPenPixel = isPenPixel;
}

void PixelInformation::setLabel(unsigned int const label)
{
    m_label=label;
}

}
