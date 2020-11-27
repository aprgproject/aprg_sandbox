#pragma once

#include <AprgBitmapConfiguration.hpp>
#include <AprgBitmapSnippet.hpp>

#include <CommonTypes.hpp>

#include <string>

namespace alba
{

class AprgBitmap
{
public:
    AprgBitmap(std::string const& path);

    AprgBitmapConfiguration getConfiguration() const;
    AprgBitmapSnippet getSnippetReadFromFileWithOutOfRangeCoordinates(int outOfRangeTop, int outOfRangeLeft, int outOfRangeBottom, int outOfRangeRight) const;
    AprgBitmapSnippet getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY const center, unsigned int const numberOfBytesToRead) const;
    AprgBitmapSnippet getSnippetReadFromFile(BitmapXY const topLeftCorner, BitmapXY const bottomRightCorner) const;
    void setSnippetWriteToFile(AprgBitmapSnippet const& snippet) const;
    BitmapXY getPointWithinTheBitmap(int const xCoordinate, int const yCoordinate) const;
    unsigned int getXCoordinateWithinTheBitmap(int const coordinate) const;
    unsigned int getYCoordinateWithinTheBitmap(int const coordinate) const;
    unsigned int getCoordinateWithinRange(int const coordinate, int maxLength) const;

private:
    void calculateNewCornersBasedOnCenterAndNumberOfBytes(BitmapXY & topLeftCorner, BitmapXY & bottomRightCorner, BitmapXY const center, unsigned int const numberOfBytes) const;
    void adjustToTargetLength(int & low, int & high, int const targetLength, unsigned int const maxLength) const;
    AprgBitmapConfiguration m_configuration;
};

}
