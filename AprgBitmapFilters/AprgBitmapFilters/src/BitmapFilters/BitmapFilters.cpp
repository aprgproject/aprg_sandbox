#include "BitmapFilters.hpp"

#include <BitmapFilters/AnimizeColor.hpp>
#include <BitmapFilters/ColorStatistics.hpp>
#include <BitmapFilters/ColorUtilities.hpp>
#include <BitmapFilters/Utilities.hpp>
#include <BitmapTraversal/BitmapSnippetTraversal.hpp>
#include <BitmapTraversal/OutwardCircleTraversal.hpp>
#include <Optional/AlbaOptional.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <TwoDimensions/TwoDimensionsHelper.hpp>

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
    BitmapSnippetTraversal snippetTraversal(inputSnippet);
    OutwardCircleTraversal outwardTraversal(5);
    OutwardCircleTraversal::RadiusToCoordinates const& radiusToCoordinates(
                outwardTraversal.getRadiusToCoordinates());
    double currentRadius(0);
    double previousRadius(0);
    for(OutwardCircleTraversal::RadiusCoordinatesPair const& pair : radiusToCoordinates)
    {
        currentRadius=pair.first;
        snippetTraversal.traverse(centerPoint, pair, [&](BitmapXY const& pointInCircle)
        {
            unsigned int const currentColor(inputSnippet.getColorAt(pointInCircle));
            if(isSimilar(centerColor, currentColor, similarityColorLimit))
            {
                similarPixelsCount++;
            }
            totalPixelCount++;
        });
        if(previousRadius != currentRadius)
        {
            double calculatedPenPercentage = (double)similarPixelsCount/totalPixelCount;
            if(calculatedPenPercentage < acceptablePenPercentage)
            {
                Circle penCircle(convertBitmapXYToPoint(centerPoint), previousRadius);
                result.setReference(penCircle);
                break;
            }
            previousRadius = currentRadius;
        }
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
        BitmapSnippetTraversal snippetTraversal(inputSnippet);
        snippetTraversal.traverse(circle, [&](BitmapXY const& pointInCircle)
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
        });
        if(bitmapPointsWithSimilarColors.size() > bitmapPointsWithDisimilarColors.size())
        {
            m_penPoints.addAsPenPoints(bitmapPointsWithDisimilarColors);
        }
        else
        {
            m_penPoints.addAsPenPoints(bitmapPointsWithSimilarColors);
        }
    });
}

void BitmapFilters::determinePenCirclesFromPenPixels(
        BitmapSnippet const& inputSnippet,
        unsigned int const similarityColorLimit,
        double const acceptablePenPercentage)
{
    map<BitmapXY, Circle> penPixelsToPenCircles;
    determinePenPixelsToPenCircles(penPixelsToPenCircles, inputSnippet, similarityColorLimit, acceptablePenPercentage);
    savePenCircles(penPixelsToPenCircles);
}

void BitmapFilters::determineConnectedComponentsByOneComponentAtATime(
        BitmapSnippet const& inputSnippet)
{
    unsigned int currentLabel=1;
    deque<BitmapXY> pointsInDeque;
    inputSnippet.traverse([&](BitmapXY const& currentPoint, unsigned int const currentPointColor)
    {
        unsigned int pixelLabel=m_labelForPixels.getLabel(currentPoint);
        if(isNotBackgroundColor(currentPointColor) && isInitialLabel(pixelLabel))
        {
            m_labelForPixels.setLabel(currentPoint, currentLabel);
            pointsInDeque.push_front(currentPoint);
            while(!pointsInDeque.empty())
            {
                BitmapXY poppedPoint(pointsInDeque.back());
                pointsInDeque.pop_back();
                analyzeFourConnectivityNeighborPointsForConnectedComponentsOneComponentAtATime(
                            inputSnippet, pointsInDeque, poppedPoint, currentLabel);
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
        bool isPenPoint(m_penPoints.isPenPoint(bitmapPoint));
        if(isPenPoint)
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
        bool isPenPoint(m_penPoints.isPenPoint(bitmapPoint));
        if(!isPenPoint)
        {
            outputSnippet.setPixelAt(bitmapPoint, color);
        }
    });
}

void BitmapFilters::drawBlurredNonPenPixels(
        BitmapSnippet const& inputSnippet,
        BitmapSnippet & outputSnippet,
        double const blurRadius,
        unsigned int const similarityColorLimit)
{
    inputSnippet.traverse([&](BitmapXY const& bitmapPoint, unsigned int const)
    {
        bool isPenPoint(m_penPoints.isPenPoint(bitmapPoint));
        if(!isPenPoint)
        {
            outputSnippet.setPixelAt(
                        bitmapPoint, getBlurredColor(
                            inputSnippet, bitmapPoint, blurRadius,[&](
                            unsigned int centerColor, unsigned int currentColor, BitmapXY pointInCircle)
            {
                bool isPointInCircleAPenPoint(m_penPoints.isPenPoint(pointInCircle));
                return isSimilar(centerColor, currentColor, similarityColorLimit)
                        && currentColor!=m_backgroundColor
                        && !isPointInCircleAPenPoint;
            }));
        }
    });
}

void BitmapFilters::drawToFillGapsUsingBlur(
        BitmapSnippet & snippet,
        double const blurRadius)
{
    BitmapXYs backgroundPoints;
    snippet.traverse([&](BitmapXY const& bitmapPoint, unsigned int const color)
    {
        if(m_backgroundColor == color)
        {
            backgroundPoints.emplace_back(bitmapPoint);
        }
    });
    while(!backgroundPoints.empty())
    {
        BitmapXYs newBackgroundPoints;
        BitmapSnippet tempSnippet(snippet);
        for(BitmapXY const& backgroundPoint : backgroundPoints)
        {
            unsigned int newColor = getBlurredColor(
                        snippet, backgroundPoint, blurRadius, [&](unsigned int , unsigned int currentColor, BitmapXY )
            {
                return m_backgroundColor!=currentColor;
            });
            if(m_backgroundColor == newColor)
            {
                newBackgroundPoints.emplace_back(backgroundPoint);
            }
            else
            {
                tempSnippet.setPixelAt(backgroundPoint, newColor);
            }
        }
        backgroundPoints = newBackgroundPoints;
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
        BitmapSnippetTraversal snippetTraversal(inputSnippet);
        snippetTraversal.traverse(penCircle, [&](BitmapXY const& pointInPenCircle)
        {
            outputSnippet.setPixelAt(pointInPenCircle, centerColor);
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
        unsigned int pixelLabel=m_labelForPixels.getLabel(bitmapPoint);
        if(!isInitialOrInvalidLabel(pixelLabel))
        {
            snippet.setPixelAt(bitmapPoint, getLabelColor(pixelLabel));
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
        BitmapXY const& penBitmapXY,
        Circle const& circleToCheck,
        Circle const& circleToCompare) const
{
    bool isBetter(false);
    if(circleToCheck.getRadius() == circleToCompare.getRadius())
    {
        Point penPoint(convertBitmapXYToPoint(penBitmapXY));
        isBetter = twoDimensionsHelper::getDistance(penPoint, circleToCheck.getCenter())
                < twoDimensionsHelper::getDistance(penPoint, circleToCompare.getCenter());
    }
    else
    {
        isBetter = circleToCheck.getRadius() > circleToCompare.getRadius();
    }
    return isBetter;
}

void BitmapFilters::determinePenPixelsToPenCircles(
        PenPixelToPenCircleMap & penPixelsToPenCircles,
        BitmapSnippet const& inputSnippet,
        unsigned int const similarityColorLimit,
        double const acceptablePenPercentage)
{
    PenPoints::PenPointsSet const& penPoints(m_penPoints.getPenPoints());
    for(BitmapXY const& penPoint : penPoints)
    {
        AlbaOptional<Circle> penCircleOptional(getPossiblePenCircle(inputSnippet, penPoint, similarityColorLimit, acceptablePenPercentage));
        if(penCircleOptional.hasContent())
        {
            Circle const& possiblePenCircle(penCircleOptional.getConstReference());
            BitmapSnippetTraversal snippetTraversal(inputSnippet);
            snippetTraversal.traverse(possiblePenCircle, [&](BitmapXY const& pointInPossibleCircle)
            {
                bool isPointInCircleAPenPoint(m_penPoints.isPenPoint(pointInPossibleCircle));
                if(isPointInCircleAPenPoint
                        && isThisPenCircleBetter(pointInPossibleCircle, possiblePenCircle, penPixelsToPenCircles[pointInPossibleCircle]))
                {
                    penPixelsToPenCircles[pointInPossibleCircle] = possiblePenCircle;
                }
            });
        }
    }
}

void BitmapFilters::savePenCircles(PenPixelToPenCircleMap const& penPixelsToPenCircles)
{
    std::set<Circle> setOfPenCircles;
    for(PenPixelPenCirclePair const& penPixelNewPenCirclePair : penPixelsToPenCircles)
    {
        setOfPenCircles.emplace(penPixelNewPenCirclePair.second);
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
    unsigned int smallestLabel = INVALID_LABEL_VALUE;
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
    unsigned int labelResult = INVALID_LABEL_VALUE;
    if(inputSnippet.isPositionInsideTheSnippet(neighborPoint))
    {
        unsigned int neighborPointColor = inputSnippet.getColorAt(neighborPoint);
        unsigned int neighborPointLabel=m_labelForPixels.getLabel(neighborPoint);
        if(isNotBackgroundColor(neighborPointColor) && !isInitialLabel(neighborPointLabel))
        {
            labelResult = neighborPointLabel;
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
    if(!isInvalidLabel(smallestLabel) && !isInvalidLabel(neighbor1Label))
    {
        unionFindForLabels.connect(smallestLabel, neighbor1Label);
    }
    if(!isInvalidLabel(smallestLabel) && !isInvalidLabel(neighbor2Label))
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
        unsigned int neighborPointLabel=m_labelForPixels.getLabel(neighborPoint);
        if(isNotBackgroundColor(neighborPointColor) && isInitialLabel(neighborPointLabel))
        {
            m_labelForPixels.setLabel(neighborPoint, currentLabel);
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
            unsigned int smallestNeighborLabel =
                    analyzeFourConnectivityNeighborPointsForConnectedComponentsTwoPassAndReturnSmallestLabel(
                        inputSnippet,
                        unionFindForLabels,
                        currentPoint);
            if(!isInvalidLabel(smallestNeighborLabel))
            {
                m_labelForPixels.setLabel(currentPoint, smallestNeighborLabel);
            }
            else
            {
                m_labelForPixels.setLabel(currentPoint, currentLabel);
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
        unsigned int pixelLabel=m_labelForPixels.getLabel(currentPoint);
        if(isNotBackgroundColor(currentPointColor) && !isInitialLabel(pixelLabel))
        {
            unsigned int smallestLabel = unionFindForLabels.getRoot(pixelLabel);
            m_labelForPixels.setLabel(currentPoint, smallestLabel);
        }
    });
}

unsigned int BitmapFilters::getBlurredColor(
        BitmapSnippet const& snippet,
        BitmapXY const& centerXY,
        double const blurRadius,
        BlurCondition const& isIncludedInBlur) const
{
    unsigned int const centerColor(snippet.getColorAt(centerXY));
    double totalBlurredColorRed(0);
    double totalBlurredColorGreen(0);
    double totalBlurredColorBlue(0);
    double totalBlurWeight(0);
    bool isChanged(false);
    Circle circle(convertBitmapXYToPoint(centerXY), blurRadius);
    BitmapSnippetTraversal snippetTraversal(snippet);
    snippetTraversal.traverse(circle, [&](BitmapXY const& pointInCircle)
    {
        unsigned int const currentColor(snippet.getColorAt(pointInCircle));
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
