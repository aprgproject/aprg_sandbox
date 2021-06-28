#include "PixelInformationDatabase.hpp"

using namespace std;

namespace alba
{

PixelInformation::PixelInformation()
    : isPenPixel(false)
    , label(INITIAL_LABEL_VALUE)
{}

PixelInformationDatabase::PixelInformationDatabase()
{}

void PixelInformationDatabase::saveAsPenPoint(BitmapXY const& bitmapPoint)
{
    m_pixelsInformationMap[bitmapPoint].isPenPixel = true;
    m_penPixels.emplace(bitmapPoint);
}

void PixelInformationDatabase::saveAsPenPoints(BitmapXYs const& bitmapPoints)
{
    for(BitmapXY const& bitmapPoint : bitmapPoints)
    {
        saveAsPenPoint(bitmapPoint);
    }
}

void PixelInformationDatabase::clear()
{
    m_pixelsInformationMap.clear();
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

PixelInformationDatabase::PixelSet const & PixelInformationDatabase::getPenPixelsConstReference() const
{
    return m_penPixels;
}

TwoDimensions::Circles & PixelInformationDatabase::getPenCirclesReference()
{
    return m_penCircles;
}

TwoDimensions::Circles const & PixelInformationDatabase::getPenCirclesConstReference() const
{
    return m_penCircles;
}


}
