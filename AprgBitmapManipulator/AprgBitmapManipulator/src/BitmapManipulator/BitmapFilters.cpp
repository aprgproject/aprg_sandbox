#include "BitmapFilters.hpp"

#include <BitmapFilters/ColorStatistics.hpp>
#include <BitmapFilters/ColorUtilities.hpp>
#include <BitmapFilters/PenCirclesDrawer.hpp>
#include <BitmapFilters/Utilities.hpp>
#include <BitmapFilters/Traversal/OutwardCircleTraversal.hpp>
#include <BitmapFilters/Traversal/OutwardSnakeLikeTraversal.hpp>
#include <Common/Math/AlbaMathHelper.hpp>
#include <Common/Optional/AlbaOptional.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Geometry/TwoDimensions/TwoDimensionsHelper.hpp>

using namespace alba::AprgBitmap::ColorUtilities;
using namespace alba::mathHelper;
using namespace alba::TwoDimensions;
using namespace std;

namespace alba
{

namespace AprgBitmap
{

constexpr unsigned int MAX_PEN_CIRCLE_RADIUS_COORDINATE=5;

BitmapFilters::BitmapFilters(string const& path)
    : m_backgroundColor(0xFFFFFF)
    , m_bitmap(path)
{}

bool BitmapFilters::isBackgroundColor(uint32_t const color) const
{
    return getColorValueOnly(color) == m_backgroundColor;
}

bool BitmapFilters::isNotBackgroundColor(uint32_t const color) const
{
    return getColorValueOnly(color) != m_backgroundColor;
}

BitmapSnippet BitmapFilters::getWholeBitmapSnippet() const
{
    return m_bitmap.getSnippetReadFromFileWholeBitmap();
}

BitmapSnippet BitmapFilters::getBlankSnippet(uint8_t const backgroundColorByte) const
{
    return m_bitmap.createColorFilledSnippetWithSizeOfWholeBitmap(backgroundColorByte);
}

BitmapSnippet BitmapFilters::getBlankSnippetWithBackground() const
{
    return getBlankSnippet(static_cast<uint8_t>(m_backgroundColor & 0xFF));
}

BitmapSnippet BitmapFilters::getBlankSnippetWithColor(
        uint32_t const color) const
{
    return getBlankSnippet(static_cast<uint8_t>(color & 0xFF));
}

AlbaOptional<Circle> BitmapFilters::getPossiblePenCircle(
        BitmapSnippet const& inputSnippet,
        BitmapXY const& centerPoint,
        uint32_t const similarityColorLimit,
        double const acceptablePenPercentage)
{
    AlbaOptional<Circle> result;
    uint32_t const centerColor(inputSnippet.getColorAt(centerPoint));
    unsigned int similarPixelsCount(0);
    unsigned int totalPixelCount(0);
    BitmapSnippetTraversal snippetTraversal(inputSnippet);
    OutwardCircleTraversal outwardTraversal(MAX_PEN_CIRCLE_RADIUS_COORDINATE);
    OutwardCircleTraversal::RadiusToCoordinates const& radiusToCoordinates(
                outwardTraversal.getRadiusToCoordinates());
    double currentRadius(0);
    double previousRadius(0);
    for(auto const& radiusAndCoordinatePair : radiusToCoordinates)
    {
        currentRadius=radiusAndCoordinatePair.first;
        snippetTraversal.traverseCoordinatesCombinations(
                    centerPoint,
                    radiusAndCoordinatePair.second.coordinate1,
                    radiusAndCoordinatePair.second.coordinate2,
                    [&](BitmapXY const& pointInCircle)
        {
            uint32_t const currentColor(inputSnippet.getColorAt(pointInCircle));
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
                result.setConstReference(penCircle);
                break;
            }
            previousRadius = currentRadius;
        }
    }
    if(!result.hasContent())
    {
        Circle penCircle(convertBitmapXYToPoint(centerPoint), currentRadius);
        result.setConstReference(penCircle);
    }
    return result;
}

void BitmapFilters::determinePenPoints(
        PenPoints & penPoints,
        BitmapSnippet const& inputSnippet,
        double const penSearchRadius,
        uint32_t const similarityColorLimit)
{
    inputSnippet.traverse([&](BitmapXY const& centerXY, uint32_t const centerColor)
    {
        Circle circle(convertBitmapXYToPoint(centerXY), penSearchRadius);
        BitmapXYs bitmapPointsWithSimilarColors;
        BitmapXYs bitmapPointsWithDisimilarColors;
        BitmapSnippetTraversal snippetTraversal(inputSnippet);
        snippetTraversal.traverseCircleArea(circle, [&](BitmapXY const& pointInCircle)
        {
            uint32_t const currentColor(inputSnippet.getColorAt(pointInCircle));
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
            penPoints.addAsPenPoints(bitmapPointsWithDisimilarColors);
        }
        else
        {
            penPoints.addAsPenPoints(bitmapPointsWithSimilarColors);
        }
    });
}

void BitmapFilters::determinePenCirclesFromPenPoints(
        PenCircles & penCircles,
        PenPoints const& penPoints,
        BitmapSnippet const& inputSnippet,
        uint32_t const similarityColorLimit,
        double const acceptablePenPercentage)
{
    map<BitmapXY, Circle> penPointsToPenCircles;
    determinePenPointsToPenCircles(penPointsToPenCircles, penPoints, inputSnippet, similarityColorLimit, acceptablePenPercentage);
    for(auto const& penPointAndPenCirclePair : penPointsToPenCircles)
    {
        penCircles.addAsPenCircle(
                    penPointAndPenCirclePair.first,
                    penPointAndPenCirclePair.second.getRadius(),
                    inputSnippet.getColorAt(penPointAndPenCirclePair.first));
    }
}

void BitmapFilters::determineConnectedComponentsByOneComponentAtATime(
        BitmapSnippet const& inputSnippet)
{
    unsigned int currentLabel=1;
    deque<BitmapXY> pointsInDeque;
    inputSnippet.traverse([&](BitmapXY const& currentPoint, uint32_t const currentPointColor)
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

void BitmapFilters::drawPenPoints(
        PenPoints const& penPoints,
        BitmapSnippet const& inputSnippet,
        BitmapSnippet & outputSnippet)
{
    inputSnippet.traverse([&](BitmapXY const& bitmapPoint, uint32_t const color)
    {
        bool isPenPoint(penPoints.isPenPoint(bitmapPoint));
        if(isPenPoint)
        {
            outputSnippet.setPixelAt(bitmapPoint, color);
        }
    });
}

void BitmapFilters::drawNonPenPoints(
        PenPoints const& penPoints,
        BitmapSnippet const& inputSnippet,
        BitmapSnippet & outputSnippet)
{
    inputSnippet.traverse([&](BitmapXY const& bitmapPoint, uint32_t const color)
    {
        bool isPenPoint(penPoints.isPenPoint(bitmapPoint));
        if(!isPenPoint)
        {
            outputSnippet.setPixelAt(bitmapPoint, color);
        }
    });
}

void BitmapFilters::drawBlurredNonPenPoints(
        PenPoints const& penPoints,
        BitmapSnippet const& inputSnippet,
        BitmapSnippet & outputSnippet,
        double const blurRadius,
        uint32_t const similarityColorLimit)
{
    inputSnippet.traverse([&](BitmapXY const& bitmapPoint, uint32_t const)
    {
        bool isPenPoint(penPoints.isPenPoint(bitmapPoint));
        if(!isPenPoint)
        {
            outputSnippet.setPixelAt(
                        bitmapPoint, getBlurredColorUsingACircle(
                            inputSnippet, bitmapPoint, blurRadius,
                            [&](uint32_t const centerColor, uint32_t const currentColor, BitmapXY const& pointInCircle)
            {
                bool isPointInCircleAPenPoint(penPoints.isPenPoint(pointInCircle));
                return isSimilar(centerColor, currentColor, similarityColorLimit)
                        && isNotBackgroundColor(currentColor)
                        && !isPointInCircleAPenPoint;
            }));
        }
    });
}

void BitmapFilters::drawPenCircles(
        PenCircles const& penCircles,
        BitmapSnippet & snippet)
{
    PenCirclesDrawer drawer(penCircles, snippet);
    drawer.draw();
}

void BitmapFilters::drawPenCirclesOnly(
        PenCircles const& penCircles,
        BitmapSnippet & snippet)
{
    for(auto const& pointAndPenCircleDetailsPair : penCircles.getPenCircles())
    {
        BitmapXY const& centerPoint(pointAndPenCircleDetailsPair.first);
        BitmapSnippetTraversal snippetTraversal(snippet);
        Circle penCircle(convertBitmapXYToPoint(centerPoint), pointAndPenCircleDetailsPair.second.radius);
        snippetTraversal.traverseCircleArea(penCircle, [&](BitmapXY const& pointInPenCircle)
        {
            snippet.setPixelAt(pointInPenCircle, pointAndPenCircleDetailsPair.second.color);
        });
    }
}

void BitmapFilters::drawWithBlurringDisimilarColors(
        BitmapSnippet & snippet,
        unsigned int const numberOfPasses,
        uint32_t const similarityColorLimit)
{
    PointToColorMap disimilarPointsToNewColors;

    for(unsigned int i=0; i<numberOfPasses; i++)
    {
        disimilarPointsToNewColors.clear();
        collectDisimilarPointsToNewColors(disimilarPointsToNewColors, snippet, similarityColorLimit);
        for(auto const& disimilarPointAndNewColorPair : disimilarPointsToNewColors)
        {
            snippet.setPixelAt(disimilarPointAndNewColorPair.first, disimilarPointAndNewColorPair.second);
        }
    }
}

void BitmapFilters::drawBlurredColorsUsingCircles(
        BitmapSnippet & snippet,
        double const blurRadius,
        uint32_t const similarityColorLimit)
{
    BitmapSnippet tempSnippet(snippet);
    tempSnippet.traverse([&](BitmapXY const& bitmapPoint, uint32_t const)
    {
        snippet.setPixelAt(
                    bitmapPoint, getBlurredColorUsingACircle(
                        tempSnippet, bitmapPoint, blurRadius,
                        [&](uint32_t const centerColor, uint32_t const currentColor, BitmapXY const& )
        {
            return isSimilar(centerColor, currentColor, similarityColorLimit)
                    && isNotBackgroundColor(currentColor);
        }));
    });
}

void BitmapFilters::drawWithBlurUsingSnakeLikeTraversal(
        BitmapSnippet & snippet,
        uint32_t const similarityColorLimit)
{
    BitmapXY const topLeft(snippet.getTopLeftCorner());
    BitmapXY const bottomRight(snippet.getBottomRightCorner());
    BitmapXY const middle((topLeft.getX()+bottomRight.getX())/2, (topLeft.getY()+bottomRight.getY())/2);

    BitmapXYs pointsToBlur;
    OutwardSnakeLikeTraversal traversal(
                middle, OutwardSnakeLikeTraversal::Direction::Up, topLeft.getX(), bottomRight.getX(), topLeft.getY(), bottomRight.getY());
    while(!traversal.isTraversalFinished())
    {
        BitmapXY centerPoint(traversal.getNextPoint());
        drawToBlurForCenterPoint(snippet, pointsToBlur, centerPoint, similarityColorLimit);
        while(!pointsToBlur.empty())
        {
            BitmapXYs newPointsToBlur;
            for(BitmapXY const& pointToBlur : pointsToBlur)
            {
                drawToBlurForCenterPoint(snippet, newPointsToBlur, pointToBlur, similarityColorLimit);
            }
            pointsToBlur = newPointsToBlur;
        }
    }
}

void BitmapFilters::drawToFillGapsUsingBlur(
        BitmapSnippet & snippet,
        double const blurRadius)
{
    BitmapXYs backgroundPoints;
    snippet.traverse([&](BitmapXY const& bitmapPoint, uint32_t const color)
    {
        if(isBackgroundColor(color))
        {
            backgroundPoints.emplace_back(bitmapPoint);
        }
    });
    unsigned int previousNumberOfPoints=0;
    while(previousNumberOfPoints != backgroundPoints.size() && !backgroundPoints.empty())
    {
        previousNumberOfPoints=backgroundPoints.size();
        BitmapXYs newBackgroundPoints;
        BitmapSnippet tempSnippet(snippet);
        for(BitmapXY const& backgroundPoint : backgroundPoints)
        {
            uint32_t newColor = getBlurredColorUsingACircle(
                        snippet, backgroundPoint, blurRadius,
                        [&](uint32_t const, uint32_t const currentColor, BitmapXY const& )
            {
                return isNotBackgroundColor(currentColor);
            });
            if(isBackgroundColor(newColor))
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

void BitmapFilters::drawAnimeColor(
        BitmapSnippet & snippet,
        AnimizeColor const& animizeColor)
{
    snippet.traverse([&](BitmapXY const& position, uint32_t const color)
    {
        snippet.setPixelAt(position, animizeColor.getNewColor(color));
    });
}

void BitmapFilters::drawNewColorForLabels(
        BitmapSnippet & snippet)
{
    snippet.traverse([&](BitmapXY const& bitmapPoint, uint32_t const)
    {
        unsigned int pixelLabel = m_labelForPixels.getLabel(bitmapPoint);
        if(!isInitialOrInvalidLabel(pixelLabel))
        {
            snippet.setPixelAt(bitmapPoint, getLabelColor(pixelLabel));
        }
    });
}

void BitmapFilters::saveSnippetIntoCurrentBitmapFile(
        BitmapSnippet const& snippet) const
{
    m_bitmap.setSnippetWriteToFile(snippet);
}

void BitmapFilters::saveSnippetIntoFileInTheSameDirectory(
        BitmapSnippet const& snippet,
        string const& filename)
{
    AlbaLocalPathHandler originalBitmapPathHandler(m_bitmap.getConfiguration().getPath());
    saveSnippetIntoFileWithFullFilePath(snippet, originalBitmapPathHandler.getDirectory()+filename);
}

void BitmapFilters::saveSnippetIntoFileWithFullFilePath(
        BitmapSnippet const& snippet,
        string const& fullFilePath)
{
    AlbaLocalPathHandler originalBitmapPathHandler(m_bitmap.getConfiguration().getPath());
    AlbaLocalPathHandler newFilePathHandler(fullFilePath);
    originalBitmapPathHandler.copyToNewFile(newFilePathHandler.getFullPath());
    Bitmap newBitmap(newFilePathHandler.getFullPath());
    newBitmap.setSnippetWriteToFile(snippet);
}

void BitmapFilters::setBackgroundColor(uint32_t const backgroundColor)
{
    m_backgroundColor = backgroundColor;
}

void BitmapFilters::gatherAndSaveColorDataAndStatistics()
{
    gatherAndSaveColorStatistics(m_bitmap.getConfiguration().getPath());
}

void BitmapFilters::collectDisimilarPointsToNewColors(
        PointToColorMap & disimilarPointsToNewColors,
        BitmapSnippet const& inputSnippet,
        uint32_t const similarityColorLimit)
{
    BitmapSnippetTraversal snippetTraversal(inputSnippet);
    inputSnippet.traverse([&](BitmapXY const& point, uint32_t const pointColor)
    {
        double redTotal(0);
        double greenTotal(0);
        double blueTotal(0);
        unsigned int neighborCount(0);
        unsigned int disimilarNeighborCount(0);
        snippetTraversal.traverse8WayConnectivity(point, [&](BitmapXY const& neighborPoint)
        {
            uint32_t neighborPointColor = inputSnippet.getColorAt(neighborPoint);
            redTotal += extractRed(neighborPointColor);
            greenTotal += extractGreen(neighborPointColor);
            blueTotal += extractBlue(neighborPointColor);
            neighborCount++;
            if(!isSimilar(pointColor, neighborPointColor, similarityColorLimit))
            {
                disimilarNeighborCount++;
            }
        });
        uint32_t newColor = combineRgbToColor(
                    static_cast<uint8_t>(round(redTotal/neighborCount)),
                    static_cast<uint8_t>(round(greenTotal/neighborCount)),
                    static_cast<uint8_t>(round(blueTotal/neighborCount)));

        if(disimilarNeighborCount>0)
        {
            disimilarPointsToNewColors[point]=newColor;
        }
    });
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

unsigned int BitmapFilters::analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(
        BitmapSnippet const& inputSnippet,
        BitmapXY const & neighborPoint)
{
    unsigned int labelResult = INVALID_LABEL_VALUE;
    if(inputSnippet.isPositionInsideTheSnippet(neighborPoint))
    {
        uint32_t neighborPointColor = inputSnippet.getColorAt(neighborPoint);
        unsigned int neighborPointLabel = m_labelForPixels.getLabel(neighborPoint);
        if(isNotBackgroundColor(neighborPointColor) && !isInitialLabel(neighborPointLabel))
        {
            labelResult = neighborPointLabel;
        }
    }
    return labelResult;
}

void BitmapFilters::analyzeNeighborPointForConnectedComponentsOneComponentAtATime(
        BitmapSnippet const& inputSnippet,
        deque<BitmapXY> & pointsInDeque,
        BitmapXY const & neighborPoint,
        unsigned int const currentLabel)
{
    if(inputSnippet.isPositionInsideTheSnippet(neighborPoint))
    {
        uint32_t neighborPointColor = inputSnippet.getColorAt(neighborPoint);
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
    inputSnippet.traverse([&](BitmapXY const& currentPoint, uint32_t const currentPointColor)
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
    inputSnippet.traverse([&](BitmapXY const& currentPoint, uint32_t const currentPointColor)
    {
        unsigned int pixelLabel=m_labelForPixels.getLabel(currentPoint);
        if(isNotBackgroundColor(currentPointColor) && !isInitialLabel(pixelLabel))
        {
            unsigned int smallestLabel = unionFindForLabels.getRoot(pixelLabel);
            m_labelForPixels.setLabel(currentPoint, smallestLabel);
        }
    });
}

void BitmapFilters::determinePenPointsToPenCircles(
        PenPointToPenCircleMap & penPointsToPenCircles,
        PenPoints const& penPoints,
        BitmapSnippet const& inputSnippet,
        uint32_t const similarityColorLimit,
        double const acceptablePenPercentage)
{
    PenPoints::PenPointsSet const& penPointsSet(penPoints.getPenPoints());
    for(BitmapXY const& penPoint : penPointsSet)
    {
        AlbaOptional<Circle> penCircleOptional(getPossiblePenCircle(inputSnippet, penPoint, similarityColorLimit, acceptablePenPercentage));
        if(penCircleOptional.hasContent())
        {
            Circle const& possiblePenCircle(penCircleOptional.getConstReference());
            BitmapSnippetTraversal snippetTraversal(inputSnippet);
            snippetTraversal.traverseCircleArea(possiblePenCircle, [&](BitmapXY const& pointInPossibleCircle)
            {
                bool isPointInCircleAPenPoint(penPoints.isPenPoint(pointInPossibleCircle));
                if(isPointInCircleAPenPoint
                        && isThisPenCircleBetter(pointInPossibleCircle, possiblePenCircle, penPointsToPenCircles[pointInPossibleCircle]))
                {
                    penPointsToPenCircles[pointInPossibleCircle] = possiblePenCircle;
                }
            });
        }
    }
}

void BitmapFilters::drawToBlurForCenterPoint(
        BitmapSnippet & snippet,
        BitmapXYs & pointsToBlur,
        BitmapXY const& centerPoint,
        uint32_t const similarityColorLimit)
{
    if(snippet.isPositionInsideTheSnippet(centerPoint))
    {
        uint32_t const centerColor(snippet.getColorAt(centerPoint));
        BitmapSnippetTraversal snippetTraversal(snippet);
        snippetTraversal.traverse8WayConnectivity(centerPoint, [&](BitmapXY const& pointInPossibleCircle)
        {
            drawToBlurForNonCenterPoint(snippet, pointsToBlur, pointInPossibleCircle, centerColor, similarityColorLimit);
        });
    }
}

void BitmapFilters::drawToBlurForNonCenterPoint(
        BitmapSnippet & snippet,
        BitmapXYs & pointsToBlur,
        BitmapXY const& point,
        uint32_t const centerColor,
        uint32_t const similarityColorLimit)
{
    uint32_t colorToCompare(snippet.getColorAt(point));
    uint32_t newColor(getBlurredColor(centerColor, colorToCompare, similarityColorLimit));
    snippet.setPixelAt(point, newColor);
    if(!isSimilar(colorToCompare, newColor, similarityColorLimit))
    {
        pointsToBlur.emplace_back(point);
    }
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

uint32_t BitmapFilters::getBlurredColor(
        uint32_t const centerColor,
        uint32_t const colorToCompare,
        uint32_t const similarityColorLimit) const
{
    uint8_t red = getBlurredColorPart(extractRed(centerColor), extractRed(colorToCompare), similarityColorLimit);
    uint8_t green = getBlurredColorPart(extractGreen(centerColor), extractGreen(colorToCompare), similarityColorLimit);
    uint8_t blue = getBlurredColorPart(extractBlue(centerColor), extractBlue(colorToCompare), similarityColorLimit);
    return combineRgbToColor(red, green, blue);
}

uint8_t BitmapFilters::getBlurredColorPart(
        uint8_t const centerColorPart,
        uint8_t const colorToComparePart,
        uint32_t const similarityColorLimit) const
{
    uint8_t blurredColorPart(colorToComparePart);
    uint32_t positiveDelta(getPositiveDelta<uint32_t>(centerColorPart, colorToComparePart));
    if(positiveDelta > similarityColorLimit)
    {
        if(centerColorPart > colorToComparePart)
        {
            blurredColorPart = centerColorPart-similarityColorLimit;
        }
        else
        {
            blurredColorPart = centerColorPart+similarityColorLimit;
        }
    }
    return blurredColorPart;
}

uint32_t BitmapFilters::getBlurredColorUsingACircle(
        BitmapSnippet const& snippet,
        BitmapXY const& centerXY,
        double const blurRadius,
        BlurCondition const& isIncludedInBlur) const
{
    uint32_t const centerColor(snippet.getColorAt(centerXY));
    double totalBlurredColorRed(0);
    double totalBlurredColorGreen(0);
    double totalBlurredColorBlue(0);
    double totalBlurWeight(0);
    bool isChanged(false);
    Circle circle(convertBitmapXYToPoint(centerXY), blurRadius);
    BitmapSnippetTraversal snippetTraversal(snippet);
    snippetTraversal.traverseCircleArea(circle, [&](BitmapXY const& pointInCircle)
    {
        uint32_t const currentColor(snippet.getColorAt(pointInCircle));
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
    uint32_t blurredColor(m_backgroundColor);
    if(isChanged)
    {
        blurredColor = combineRgbToColor(
                    static_cast<uint8_t>(totalBlurredColorRed/totalBlurWeight),
                    static_cast<uint8_t>(totalBlurredColorGreen/totalBlurWeight),
                    static_cast<uint8_t>(totalBlurredColorBlue/totalBlurWeight));
    }
    return blurredColor;
}

double BitmapFilters::getBlurWeight(double const distanceFromCenter, double const blurRadius) const
{
    return (blurRadius-distanceFromCenter+1)/(blurRadius+1);
}

}

}
