#pragma once

#include <Bitmap/CommonTypes.hpp>
#include <BitmapFilters/PixelInformation.hpp>
#include <TwoDimensions/Circle.hpp>

#include <map>
#include <set>

namespace alba
{

namespace AprgBitmap
{

class PixelInformationDatabase
{
public:
    using PixelInformationMap = std::map<BitmapXY, PixelInformation>;
    using PixelSet = std::set<BitmapXY>;

    PixelInformationDatabase();
    TwoDimensions::Circles & getPenCirclesReference();
    TwoDimensions::Circles const & getPenCirclesConstReference() const;
private:
    PixelInformationMap m_pixelsInformationMap;
    PixelSet m_penPoints;
    TwoDimensions::Circles m_penCircles;

};
}

}