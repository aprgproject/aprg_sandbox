#pragma once

#include <Container/AlbaXY.hpp>
#include <Memory/AlbaMemoryBuffer.hpp>

#include <vector>

namespace alba
{

using BitmapSignedXY = AlbaXY<int>;
using BitmapXY = AlbaXY<unsigned int>;
using Colors = std::vector<unsigned int>;
using PixelData = AlbaMemoryBuffer;

}
