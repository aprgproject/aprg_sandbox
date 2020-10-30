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
    AprgBitmapSnippet getSnippetReadFromFile(BitmapXY const topLeftCorner, BitmapXY const bottomRightCorner) const;
    AprgBitmapSnippet getSnippetReadFromFile(BitmapXY const center, unsigned int const numberOfBytesToRead) const;
    void setSnippetWriteToFile(AprgBitmapSnippet const& snippet) const;
    void saveCornersForCenterAndNumberOfBytes(BitmapXY & topLeftCorner, BitmapXY & bottomRightCorner, BitmapXY const center, unsigned int const numberOfBytes) const;

private:
    AprgBitmapConfiguration m_configuration;
};

}
