#include "PixelInformationDatabase.hpp"

using namespace std;

namespace alba
{


PixelInformation::PixelInformation()
    : type(PixelType::Unknown)
    , label(INITIAL_LABEL_VALUE)
{}

PixelInformationDatabase::PixelInformationDatabase()
{}

void PixelInformationDatabase::saveAsPenPoints(BitmapXYs const& bitmapPoints)
{
    for(BitmapXY const& bitmapPoint : bitmapPoints)
    {
        m_pixelsInformationMap[bitmapPoint].type = PixelType::Pen;
    }
}

PixelInformation PixelInformationDatabase::getPixelInformation(BitmapXY const& bitmapXY) const
{
    if(m_pixelsInformationMap.find(bitmapXY) != m_pixelsInformationMap.cend())
    {
        return m_pixelsInformationMap.at(bitmapXY);
    }
    return PixelInformation();
}

PixelInformation & PixelInformationDatabase::getPixelInformationReferenceAndCreateIfNeeded(BitmapXY const& bitmapXY)
{
    return m_pixelsInformationMap[bitmapXY];
}

void PixelInformationDatabase::clear()
{
    m_pixelsInformationMap.clear();
}

}
