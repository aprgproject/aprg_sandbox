#include "PixelInformation.hpp"

namespace alba
{

namespace AprgBitmap
{

PixelInformation::PixelInformation()
    : m_isPenPixel(false)
{}

bool PixelInformation::isPenPixel() const
{
    return m_isPenPixel;
}

void PixelInformation::setAsPenPoint(bool const isPenPixel)
{
    m_isPenPixel = isPenPixel;
}

}

}
