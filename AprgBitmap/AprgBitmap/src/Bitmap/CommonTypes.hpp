#pragma once

#include <Common/Container/AlbaXY.hpp>
#include <Common/Memory/AlbaMemoryBuffer.hpp>

#include <vector>

namespace alba
{

namespace AprgBitmap
{

using BitmapSignedXY = AlbaXY<int>;
using BitmapXY = AlbaXY<unsigned int>;
using BitmapDoubleXY = AlbaXY<double>;
using BitmapXYs = std::vector<BitmapXY>;
using BitmapSignedXYs = std::vector<BitmapSignedXY>;
using Colors = std::vector<uint32_t>;
using PixelData = AlbaMemoryBuffer;
}

}
