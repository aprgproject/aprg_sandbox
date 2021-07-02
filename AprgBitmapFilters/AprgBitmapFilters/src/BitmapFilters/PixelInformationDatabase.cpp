#include "PixelInformationDatabase.hpp"

using namespace std;

namespace alba
{

namespace AprgBitmap
{

PixelInformationDatabase::PixelInformationDatabase()
{}

TwoDimensions::Circles & PixelInformationDatabase::getPenCirclesReference()
{
    return m_penCircles;
}

TwoDimensions::Circles const & PixelInformationDatabase::getPenCirclesConstReference() const
{
    return m_penCircles;
}

}

}
