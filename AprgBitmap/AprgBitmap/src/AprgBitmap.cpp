#include "AprgBitmap.hpp"

#include <PathHandlers/AlbaLocalPathHandler.hpp>

using namespace std;

namespace alba
{

AprgBitmap::AprgBitmap(string const& path)
    : m_inputStream(AlbaLocalPathHandler(path).getFullPath(), ios::binary)
    , m_fileReader(m_inputStream)
{}

void AprgBitmap::loadBitmap()
{
    m_fileReader.moveLocation(0);
    m_signature+=m_fileReader.getCharacter();
    m_signature+=m_fileReader.getCharacter();

    m_fileReader.moveLocation(2);
    m_fileSize = m_fileReader.getFourByteData<unsigned int>();

    m_fileReader.moveLocation(10);
    m_rasterPadSize = m_fileReader.getFourByteData<unsigned int>();

    m_fileReader.moveLocation(18);
    m_cols = m_fileReader.getFourByteData<unsigned int>();

    m_fileReader.moveLocation(22);
    m_rows = m_fileReader.getFourByteData<unsigned int>();

    m_fileReader.moveLocation(28);
    m_bitsPerPixel = m_fileReader.getFourByteData<unsigned int>();

    m_numberOfBytesInRasterData = m_cols*m_rows;

    m_fileReader.moveLocation(38);
    m_pixelsInAMeterInXDirection = m_fileReader.getFourByteData<unsigned int>();

    m_fileReader.moveLocation(42);
    m_pixelsInAMeterInYDirection = m_fileReader.getFourByteData<unsigned int>();

    m_fileReader.moveLocation(46);
    m_numberOfColors = m_fileReader.getFourByteData<unsigned int>();

    m_fileReader.moveLocation(54);
    m_defaultColor = (unsigned int) m_fileReader.getCharacter();

    //m_rasterPadSize =( 4-(rasterRound((double)nCols/8)%4) ) % 4;
}

}


