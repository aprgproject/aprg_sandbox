#pragma once

#include <File/AlbaFileReader.hpp>

#include <fstream>

namespace alba
{

class AprgBitmap
{
public:
    AprgBitmap(std::string const& path);
    void loadBitmap();

private:
    std::ifstream m_inputStream;
    AlbaFileReader m_fileReader;
    std::string m_signature;
    unsigned long m_fileSize;
    unsigned int m_rasterDataAddress;
    unsigned int m_cols;
    unsigned int m_rows;
    unsigned int m_bitsPerPixel;
    unsigned long m_numberOfBytesInRasterData;
    unsigned int m_pixelsInAMeterInXDirection;
    unsigned int m_pixelsInAMeterInYDirection;
    unsigned long m_numberOfColors;
    unsigned int m_defaultColor;
    unsigned int m_rasterPadSize;
};

}
