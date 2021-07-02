#pragma once

#include <Container/AlbaXY.hpp>
#include <Memory/AlbaMemoryBuffer.hpp>

#include <vector>

namespace alba
{

namespace AprgBitmap
{

using BitmapSignedXY = AlbaXY<int>;
using BitmapXY = AlbaXY<unsigned int>;
using BitmapDoubleXY = AlbaXY<double>;using BitmapXYs = std::vector<BitmapXY>;
using Colors = std::vector<unsigned int>;
using PixelData = AlbaMemoryBuffer;

}

}