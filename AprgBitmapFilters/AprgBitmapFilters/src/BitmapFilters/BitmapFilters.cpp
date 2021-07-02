#include "BitmapFilters.hpp"

#include <BitmapFilters/AnimizeColor.hpp>
#include <BitmapFilters/ColorStatistics.hpp>
#include <BitmapFilters/ColorUtilities.hpp>
#include <BitmapFilters/Utilities.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <Optional/AlbaOptional.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>#include <TwoDimensions/TwoDimensionsHelper.hpp>

using namespace alba::AprgBitmap::ColorUtilities;
using namespace alba::TwoDimensions;
using namespace std;

namespace alba
{

namespace AprgBitmap
{

BitmapFilters::BitmapFilters(string const& path)
    : m_backgroundColor(0xFFFFFF)
    , m_bitmap(path)
{}

bool BitmapFilters::isSimilar(unsigned int const color1, unsigned int const color2, unsigned int const similarityColorLimit) const //RGB algo
{
    bool isRedDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)extractRed(color1)-(int)extractRed(color2))>(int)similarityColorLimit);
    bool isGreenDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)extractGreen(color1)-(int)extractGreen(color2))>(int)similarityColorLimit);
    bool isBlueDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)extractBlue(color1)-(int)extractBlue(color2))>(int)similarityColorLimit);
    return  !(isRedDifferenceBeyondLimit || isGreenDifferenceBeyondLimit || isBlueDifferenceBeyondLimit);
}

/*
bool BitmapFilters::isSimilar(unsigned int const color1, unsigned int const color2) const//Pythagorean algo
{
    double colorDifferenceAcrossDifferentColors(mathHelper::getSquareRootOfXSquaredPlusYSquaredPlusZSquared<double>((double)getRed(color1)-(double)getRed(color2), (double)getGreen(color1)-(double)getGreen(color2), (double)getBlue(color1)-(double)getBlue(color2)));
    return colorDifferenceAcrossDifferentColors < m_similarityColorLimit;
}
*/

bool BitmapFilters::isNotBackgroundColor(unsigned int const color) const
{
    return color != m_backgroundColor;
}

BitmapSnippet BitmapFilters::getWholeBitmapSnippet() const
{
    return m_bitmap.getSnippetReadFromFileWholeBitmap();
}

BitmapSnippet BitmapFilters::getBlankSnippet(unsigned int const backgroundColor) const
{
    return m_bitmap.createColorFilledSnippetWithSizeOfWholeBitmap(backgroundColor);
}

BitmapSnippet BitmapFilters::getBlankSnippetWithBackground() const
{
    return getBlankSnippet(m_backgroundColor);
}

unsigned int BitmapFilters::getLabelColor(unsigned int const label) const
{
    unsigned int digits = mathHelper::getNumberOfIntegerDigits(label);
    double newValue = (static_cast<double>(1)/label) * pow(10, digits+8);
    return static_cast<unsigned int>(newValue) % 0xFFFFFF;
}

AlbaOptional<Circle> BitmapFilters::getPossiblePenCircle(
        BitmapSnippet const& inputSnippet,
        BitmapXY const& centerPoint,
        unsigned int const similarityColorLimit,
        double const acceptablePenPercentage)
{
    AlbaOptional<Circle> result;
    unsigned int const centerColor(inputSnippet.getColorAt(centerPoint));
    unsigned int similarPixelsCount(0);
    unsigned int totalPixelCount(0);
    double initialRadius=0.25;
    double interval=0.25;
    double previousRadius=initialRadius;
    for(double currentRadius=initialRadius+interval; currentRadius<=10; currentRadius+=interval)
    {
        Circle circle(convertBitmapXYToPoint(centerPoint), currentRadius);
        twoDimensionsHelper::traverseCircleAreaBetweenTwoRadius(
                    convertBitmapXYToPoint(centerPoint),
                    previousRadius,
                    currentRadius,
                    1,
                    [&](Point const& point)
        {
            BitmapXY pointInCircle(floor(point.getX()), floor(point.getY()));
            if(inputSnippet.isPositionInsideTheSnippet(pointInCircle))
            {
                unsigned int const currentColor(inputSnippet.getColorAt(pointInCircle));
                if(isSimilar(centerColor, currentColor, similarityColorLimit))
                {
                    similarPixelsCount++;
                }
                totalPixelCount++;
            }
        });
        double calculatedPenPercentage = (double)similarPixelsCount/totalPixelCount;
        if(calculatedPenPercentage >= acceptablePenPercentage)
        {
            result.setReference(circle);
        }
        else
        {
            break;
        }
        previousRadius = currentRadius;
    }
    return result;
}

void BitmapFilters::determinePenPixels(
        BitmapSnippet const& inputSnippet,
        double const penSearchRadius,
        unsigned int const similarityColorLimit)
{
    inputSnippet.traverse([&](BitmapXY const& centerXY, unsigned int const centerColor)
    {
        Circle circle(convertBitmapXYToPoint(centerXY), penSearchRadius);
        BitmapXYs bitmapPointsWithSimilarColors;
        BitmapXYs bitmapPointsWithDisimilarColors;
        circle.traverseArea(1, [&](Point const& point)
        {
            BitmapXY pointInCircle(convertPointToBitmapXY(point));
            if(inputSnippet.isPositionInsideTheSnippet(pointInCircle))
            {
                unsigned int const currentColor(inputSnippet.getColorAt(pointInCircle));
                if(isSimilar(centerColor, currentColor, similarityColorLimit))
                {
                    bitmapPointsWithSimilarColors.emplace_back(pointInCircle);
                }
                else
                {
                    bitmapPointsWithDisimilarColors.emplace_back(pointInCircle);
                }
            }
        });
        if(bitmapPointsWithSimilarColors.size() > bitmapPointsWithDisimilarColors.size())
        {
            m_pixelInformationDatabase.saveAsPenPoints(bitmapPointsWithDisimilarColors);
        }
        else
        {
            m_pixelInformationDatabase.saveAsPenPoints(bitmapPointsWithSimilarColors);
        }
    });
}

void BitmapFilters::determinePenCirclesFromPenPixels(
        BitmapSnippet const& inputSnippet,
        unsigned int const similarityColorLimit,
        double const acceptablePenPercentage)
{
    PixelInformationDatabase::PixelSet penPixels(m_pixelInformationDatabase.getPenPixelsConstReference());
    for(BitmapXY const& penPoint : penPixels)
    {
        AlbaOptional<Circle> penCircleOptional(getPossiblePenCircle(inputSnippet, penPoint, similarityColorLimit, acceptablePenPercentage));
        if(penCircleOptional.hasContent())
        {
            Circle const& penCircle(penCircleOptional.getConstReference());
            penCircle.traverseArea(1, [&](Point const& penCirclePoint)
            {
                BitmapXY pointInPenCircle(convertPointToBitmapXY(penCirclePoint));
                if(inputSnippet.isPositionInsideTheSnippet(pointInPenCircle))
                {
                    PixelInformation & pixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(pointInPenCircle));
                    if(pixelInfo.isPenPixel() && isThisPenCircleBetter(penCirclePoint, penCircle, pixelInfo.getPenCircle()))
                    {
                        pixelInfo.setPenCircle(penCircle);
                    }
                }
            });
        }
    }
    savePenCirclesInPenPixels();
}

void BitmapFilters::determineConnectedComponentsByOneComponentAtATime(
        BitmapSnippet const& inputSnippet)
{
    unsigned int currentLabel=1;
    deque<BitmapXY> pointsInDeque;
    inputSnippet.traverse([&](BitmapXY const& currentPoint, unsigned int const currentPointColor)
    {
        PixelInformation & currentPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(currentPoint));
        if(isNotBackgroundColor(currentPointColor) && currentPixelInfo.isInitialLabel())
        {
            currentPixelInfo.setLabel(currentLabel);
            pointsInDeque.push_front(currentPoint);
            while(!pointsInDeque.empty())
            {
                BitmapXY poppedPoint(pointsInDeque.back());
                pointsInDeque.pop_back();
                analyzeFourConnectivityNeighborPointsForConnectedComponentsOneComponentAtATime(inputSnippet, pointsInDeque, poppedPoint, currentLabel);
            }
            currentLabel++;
        }
    });
}

void BitmapFilters::determineConnectedComponentsUsingTwoPass(
        BitmapSnippet const& inputSnippet)
{
    UnionFindForLabels unionFindForLabels;
    determineConnectedComponentsUsingTwoPassInFirstPass(inputSnippet, unionFindForLabels);
    determineConnectedComponentsUsingTwoPassInSecondPass(inputSnippet, unionFindForLabels);
}

void BitmapFilters::drawPenPixels(
        BitmapSnippet const& inputSnippet,
        BitmapSnippet & outputSnippet)
{
    inputSnippet.traverse([&](BitmapXY const& bitmapPoint, unsigned int const color)
    {
        PixelInformation const& pixelInfo(m_pixelInformationDatabase.getPixelInformation(bitmapPoint));
        if(pixelInfo.isPenPixel())
        {
            outputSnippet.setPixelAt(bitmapPoint, color);
        }
    });
}

void BitmapFilters::drawNonPenPixels(
        BitmapSnippet const& inputSnippet,
        BitmapSnippet & outputSnippet)
{
    inputSnippet.traverse([&](BitmapXY const& bitmapPoint, unsigned int const color)
    {
        PixelInformation const& pixelInfo(m_pixelInformationDatabase.getPixelInformation(bitmapPoint));
        if(!pixelInfo.isPenPixel())
        {
            outputSnippet.setPixelAt(bitmapPoint, color);
        }
    });
}

void BitmapFilters::drawBlurredNonPenPixels(
        BitmapSnippet & snippet,
        double const blurRadius,
        unsigned int const similarityColorLimit)
{
    BitmapSnippet tempSnippet(snippet);
    tempSnippet.traverse([&](BitmapXY const& bitmapPoint, unsigned int const)
    {
        PixelInformation const& pixelInfo(m_pixelInformationDatabase.getPixelInformation(bitmapPoint));
        if(!pixelInfo.isPenPixel())
        {
            snippet.setPixelAt(bitmapPoint, getBlurredColor(
                                   tempSnippet, bitmapPoint, blurRadius,[&](
                                   unsigned int centerColor, unsigned int currentColor, BitmapXY pointInCircle)
            {
                PixelInformation const& pointInCirclePixelInfo(m_pixelInformationDatabase.getPixelInformation(pointInCircle));
                return isSimilar(centerColor, currentColor, similarityColorLimit)
                        && currentColor!=m_backgroundColor
                        && !pointInCirclePixelInfo.isPenPixel();
            }));
        }
    });
}

void BitmapFilters::drawToFillGapsUsingBlur(
        BitmapSnippet & snippet,
        double const blurRadius)
{
    unsigned int numberOfPixelsWithChangedColor(1);
    while(numberOfPixelsWithChangedColor!=0)
    {
        numberOfPixelsWithChangedColor=0;
        BitmapSnippet tempSnippet(snippet);
        snippet.traverse([&](BitmapXY const& bitmapPoint, unsigned int const color)
        {
            unsigned int newColor(color);
            if(m_backgroundColor == color)
            {
                newColor = getBlurredColor(snippet, bitmapPoint, blurRadius, [&](unsigned int , unsigned int currentColor, BitmapXY )
                {
                    return m_backgroundColor!=currentColor;
                });
                if(m_backgroundColor != newColor)
                {
                    numberOfPixelsWithChangedColor++;
                }
            }
            tempSnippet.setPixelAt(bitmapPoint, newColor);
        });
        snippet=tempSnippet;
    }
}

void BitmapFilters::drawPenCircles(
        BitmapSnippet const& inputSnippet,
        BitmapSnippet & outputSnippet)
{
    Circles const & penCircles(m_pixelInformationDatabase.getPenCirclesConstReference());

    for(Circle const& penCircle : penCircles)
    {
        BitmapXY centerPoint(convertPointToBitmapXY(penCircle.getCenter()));
        unsigned int const centerColor(inputSnippet.getColorAt(centerPoint));
        penCircle.traverseArea(1, [&](Point const& point)
        {
            BitmapXY pointInCircle(convertPointToBitmapXY(point));
            if(inputSnippet.isPositionInsideTheSnippet(pointInCircle))
            {
                //PixelInformation & pixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(pointInCircle));
                //pixelInfo.temporaryColors.emplace_back(centerColor);
                outputSnippet.setPixelAt(pointInCircle, centerColor);
            }
        });
    }
    /*    outputSnippet.traverse([&](BitmapXY const& bitmapPoint, unsigned int const)
    {
        PixelInformation & pixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(bitmapPoint));
        vector<unsigned int> & tempColors(pixelInfo.temporaryColors);
        if(!tempColors.empty())
        {
            unsigned int redSum(0), greenSum(0), blueSum(0);
            double maxColorIntensity(0);
            unsigned int savedColorWithMaxIntensity(0);
            for(unsigned int tempColor: tempColors)
            {
                redSum += extractRed(tempColor);
                greenSum += extractGreen(tempColor);
                blueSum += extractBlue(tempColor);
                double currentColorIntensity = calculateColorIntensityDecimal(tempColor);
                if(maxColorIntensity<currentColorIntensity)
                {
                    savedColorWithMaxIntensity = tempColor;
                }
            }
            //unsigned int colorOfCircle = combineRgbToColor(redSum/tempColors.size(), greenSum/tempColors.size(), blueSum/tempColors.size());
            unsigned int colorOfCircle = savedColorWithMaxIntensity;
            HueSaturationLightnessData hslData = convertColorToHueSaturationLightnessData(colorOfCircle);
            //hslData.saturationLightnessDecimal = 1.1*hslData.saturationLightnessDecimal;
            //hslData.saturationLightnessDecimal = hslData.saturationLightnessDecimal > 1 ? 1 : hslData.lightnessDecimal;
//            if(hslData.lightnessDecimal>0.5)
//            {
//                hslData.lightnessDecimal = 1.05*hslData.lightnessDecimal;
//            }
//            else
//            {
//                hslData.lightnessDecimal = 0.95*hslData.lightnessDecimal;
//            }

            hslData.lightnessDecimal = hslData.lightnessDecimal > 1 ? 1 : hslData.lightnessDecimal;
            outputSnippet.setPixelAt(bitmapPoint, convertHueSaturationLightnessDataToColor(hslData));
            tempColors.clear();
        }
    });*/
}

void BitmapFilters::drawAnimeColor(
        BitmapSnippet & snippet)
{
    AnimizeColor animizeColor;
    animizeColor.gatherStatistics(m_bitmap.getConfiguration().getPath());
    animizeColor.calculateNewValues();
    snippet.traverse([&](BitmapXY const& position, unsigned int const color)
    {
        unsigned int newColor = animizeColor.getNewColor(color);
        snippet.setPixelAt(position, newColor);
    });
}

void BitmapFilters::drawNewColorForLabels(
        BitmapSnippet & snippet)
{
    snippet.traverse([&](BitmapXY const& bitmapPoint, unsigned int const)
    {
        PixelInformation const& pixelInfo(m_pixelInformationDatabase.getPixelInformation(bitmapPoint));
        if(!pixelInfo.isInitialOrInvalidLabel())
        {
            snippet.setPixelAt(bitmapPoint, getLabelColor(pixelInfo.getLabel()));
        }
    });
}

void BitmapFilters::saveOutputCanvasIntoCurrentBitmapFile(
        BitmapSnippet const& snippet) const
{
    m_bitmap.setSnippetWriteToFile(snippet);
}

void BitmapFilters::saveOutputCanvasIntoFileInTheSameDirectory(
        BitmapSnippet const& snippet,
        string const& filename)
{
    AlbaLocalPathHandler originalBitmapPathHandler(m_bitmap.getConfiguration().getPath());
    saveOutputCanvasIntoFileWithFullFilePath(snippet, originalBitmapPathHandler.getDirectory()+filename);
}

void BitmapFilters::saveOutputCanvasIntoFileWithFullFilePath(
        BitmapSnippet const& snippet,
        string const& fullFilePath)
{
    AlbaLocalPathHandler originalBitmapPathHandler(m_bitmap.getConfiguration().getPath());
    AlbaLocalPathHandler newFilePathHandler(fullFilePath);
    originalBitmapPathHandler.copyToNewFile(newFilePathHandler.getFullPath());
    Bitmap newBitmap(newFilePathHandler.getFullPath());
    newBitmap.setSnippetWriteToFile(snippet);
}

void BitmapFilters::setBackgroundColor(unsigned int const backgroundColor)
{
    m_backgroundColor = backgroundColor;
}

void BitmapFilters::gatherAndSaveColorDataAndStatistics()
{
    gatherAndSaveColorStatistics(m_bitmap.getConfiguration().getPath());
}

bool BitmapFilters::isThisPenCircleBetter(
        Point const& penPoint,
        Circle const& circleToCheck,
        Circle const& circleToCompare) const
{
    bool isBetter(false);
    if(circleToCheck.getRadius() == circleToCompare.getRadius())
    {
        isBetter = twoDimensionsHelper::getDistance(penPoint, circleToCheck.getCenter())
                < twoDimensionsHelper::getDistance(penPoint, circleToCompare.getCenter());
    }
    else
    {
        isBetter = circleToCheck.getRadius() > circleToCompare.getRadius();
    }
    return isBetter;
}

void BitmapFilters::savePenCirclesInPenPixels()
{
    PixelInformationDatabase::PixelSet penPixels(m_pixelInformationDatabase.getPenPixelsConstReference());
    std::set<Circle> setOfPenCircles;
    for(BitmapXY const& penPoint : penPixels)
    {
        PixelInformation const& pixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(penPoint));
        setOfPenCircles.emplace(pixelInfo.getPenCircle());
    }
    Circles & penCircles(m_pixelInformationDatabase.getPenCirclesReference());
    copy(setOfPenCircles.cbegin(), setOfPenCircles.cend(), back_inserter(penCircles));
}

unsigned int BitmapFilters::analyzeFourConnectivityNeighborPointsForConnectedComponentsTwoPassAndReturnSmallestLabel(
        BitmapSnippet const& inputSnippet,
        UnionFindForLabels & unionFindForLabels,
        BitmapXY const & neighborPoint)
{
    //4-connectivity
    unsigned int smallestLabel = PixelInformation::INVALID_LABEL_VALUE;
    BitmapXY neighbor1(neighborPoint.getX()-1, neighborPoint.getY());
    BitmapXY neighbor2(neighborPoint.getX(), neighborPoint.getY()-1);
    unsigned int neighbor1Label = analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(inputSnippet, neighbor1);
    unsigned int neighbor2Label = analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(inputSnippet, neighbor2);
    smallestLabel = min(smallestLabel, neighbor1Label);
    smallestLabel = min(smallestLabel, neighbor2Label);
    updateUnionFindForLabels(unionFindForLabels, smallestLabel, neighbor1Label, neighbor2Label);
    return smallestLabel;
}

unsigned int BitmapFilters::analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(
        BitmapSnippet const& inputSnippet,
        BitmapXY const & neighborPoint)
{
    unsigned int labelResult = PixelInformation::INVALID_LABEL_VALUE;
    if(inputSnippet.isPositionInsideTheSnippet(neighborPoint))
    {
        unsigned int neighborPointColor = inputSnippet.getColorAt(neighborPoint);
        PixelInformation & neighborPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(neighborPoint));
        if(isNotBackgroundColor(neighborPointColor) && !neighborPixelInfo.isInitialLabel())
        {
            labelResult = neighborPixelInfo.getLabel();
        }
    }
    return labelResult;
}

void BitmapFilters::updateUnionFindForLabels(
        UnionFindForLabels& unionFindForLabels,
        unsigned int const smallestLabel,
        unsigned int const neighbor1Label,
        unsigned int const neighbor2Label) const
{
    if(smallestLabel != PixelInformation::INVALID_LABEL_VALUE && neighbor1Label != PixelInformation::INVALID_LABEL_VALUE)
    {
        unionFindForLabels.connect(smallestLabel, neighbor1Label);
    }
    if(smallestLabel != PixelInformation::INVALID_LABEL_VALUE && neighbor2Label != PixelInformation::INVALID_LABEL_VALUE)
    {
        unionFindForLabels.connect(smallestLabel, neighbor2Label);
    }
}

void BitmapFilters::analyzeFourConnectivityNeighborPointsForConnectedComponentsOneComponentAtATime(
        BitmapSnippet const& inputSnippet,
        deque<BitmapXY> & pointsInDeque,
        BitmapXY const & poppedPoint,
        unsigned int const currentLabel)
{
    //4-connectivity
    BitmapXY neighbor1(poppedPoint.getX()-1, poppedPoint.getY());
    BitmapXY neighbor2(poppedPoint.getX(), poppedPoint.getY()-1);
    BitmapXY neighbor3(poppedPoint.getX()+1, poppedPoint.getY());
    BitmapXY neighbor4(poppedPoint.getX(), poppedPoint.getY()+1);
    analyzeNeighborPointForConnectedComponentsOneComponentAtATime(inputSnippet, pointsInDeque, neighbor1, currentLabel);
    analyzeNeighborPointForConnectedComponentsOneComponentAtATime(inputSnippet, pointsInDeque, neighbor2, currentLabel);
    analyzeNeighborPointForConnectedComponentsOneComponentAtATime(inputSnippet, pointsInDeque, neighbor3, currentLabel);
    analyzeNeighborPointForConnectedComponentsOneComponentAtATime(inputSnippet, pointsInDeque, neighbor4, currentLabel);
}

void BitmapFilters::analyzeNeighborPointForConnectedComponentsOneComponentAtATime(
        BitmapSnippet const& inputSnippet,
        deque<BitmapXY> & pointsInDeque,
        BitmapXY const & neighborPoint,
        unsigned int const currentLabel)
{
    if(inputSnippet.isPositionInsideTheSnippet(neighborPoint))
    {
        unsigned int neighborPointColor = inputSnippet.getColorAt(neighborPoint);
        PixelInformation & neighborPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(neighborPoint));
        if(isNotBackgroundColor(neighborPointColor) && neighborPixelInfo.isInitialLabel())
        {
            neighborPixelInfo.setLabel(currentLabel);
            pointsInDeque.push_front(neighborPoint);
        }
    }
}

void BitmapFilters::determineConnectedComponentsUsingTwoPassInFirstPass(
        BitmapSnippet const& inputSnippet,
        UnionFindForLabels & unionFindForLabels)
{
    unsigned int currentLabel=1;
    inputSnippet.traverse([&](BitmapXY const& currentPoint, unsigned int const currentPointColor)
    {
        if(isNotBackgroundColor(currentPointColor))
        {
            PixelInformation & currentPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(currentPoint));
            unsigned int smallestNeighborLabel = analyzeFourConnectivityNeighborPointsForConnectedComponentsTwoPassAndReturnSmallestLabel(
                        inputSnippet,
                        unionFindForLabels,
                        currentPoint);
            if(smallestNeighborLabel != PixelInformation::INVALID_LABEL_VALUE)
            {
                currentPixelInfo.setLabel(smallestNeighborLabel);
            }
            else
            {
                currentPixelInfo.setLabel(currentLabel);
                currentLabel++;
            }
        }
    });
}

void BitmapFilters::determineConnectedComponentsUsingTwoPassInSecondPass(
        BitmapSnippet const& inputSnippet,
        UnionFindForLabels const& unionFindForLabels)
{
    inputSnippet.traverse([&](BitmapXY const& currentPoint, unsigned int const currentPointColor)
    {
        PixelInformation & currentPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(currentPoint));
        if(isNotBackgroundColor(currentPointColor) && !currentPixelInfo.isInitialLabel())
        {
            unsigned int smallestLabel = unionFindForLabels.getRoot(currentPixelInfo.getLabel());
            currentPixelInfo.setLabel(smallestLabel);
        }
    });
}

unsigned int BitmapFilters::getBlurredColor(BitmapSnippet const& canvas, BitmapXY const& centerXY, double const blurRadius, BlurCondition const& isIncludedInBlur) const
{
    unsigned int const centerColor(canvas.getColorAt(centerXY));    double totalBlurredColorRed(0);
    double totalBlurredColorGreen(0);
    double totalBlurredColorBlue(0);
    double totalBlurWeight(0);
    bool isChanged(false);
    Circle circle(convertBitmapXYToPoint(centerXY), blurRadius);
    circle.traverseArea(1, [&](Point const& point)
    {
        BitmapXY pointInCircle(convertPointToBitmapXY(point));
        if(canvas.isPositionInsideTheSnippet(pointInCircle))
        {
            unsigned int const currentColor(canvas.getColorAt(pointInCircle));
            if(isIncludedInBlur(centerColor, currentColor, pointInCircle))
            {
                isChanged=true;
                double distanceFromCenter(twoDimensionsHelper::getDistance(convertBitmapXYToPoint(centerXY), convertBitmapXYToPoint(pointInCircle)));
                double blurWeight(getBlurWeight(distanceFromCenter, blurRadius));
                totalBlurredColorRed+=blurWeight*extractRed(currentColor);
                totalBlurredColorGreen+=blurWeight*extractGreen(currentColor);
                totalBlurredColorBlue+=blurWeight*extractBlue(currentColor);
                totalBlurWeight+=blurWeight;
            }
        }
    });
    unsigned int blurredColor(m_backgroundColor);
    if(isChanged)
    {
        blurredColor = combineRgbToColor(
                    static_cast<unsigned char>(totalBlurredColorRed/totalBlurWeight),
                    static_cast<unsigned char>(totalBlurredColorGreen/totalBlurWeight),
                    static_cast<unsigned char>(totalBlurredColorBlue/totalBlurWeight));
    }
    return blurredColor;
}

double BitmapFilters::getBlurWeight(double const distanceFromCenter, double const blurRadius) const
{
    return (blurRadius-distanceFromCenter+1)/(blurRadius+1);
}

}

}
