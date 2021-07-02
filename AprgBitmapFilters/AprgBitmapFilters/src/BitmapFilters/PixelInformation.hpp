#pragma once

#include <TwoDimensions/Circle.hpp>

namespace alba
{

namespace AprgBitmap
{

class PixelInformation
{
public:
    PixelInformation();

    bool isPenPixel() const;

    void setAsPenPoint(bool const isPenPixel);

private:
    bool m_isPenPixel;
};

}

}
