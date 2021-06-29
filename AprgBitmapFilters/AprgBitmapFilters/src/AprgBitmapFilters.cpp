#include "AprgBitmapFilters.hpp"

#include <AnimizeColor.hpp>
#include <AprgColorStatistics.hpp>
#include <AprgColorUtilities.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <Optional/AlbaOptional.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <Randomizer/AlbaRandomizer.hpp>
#include <TwoDimensions/TwoDimensionsHelper.hpp>

using namespace alba::ColorUtilities;
using namespace alba::TwoDimensions;
using namespace std;

namespace alba
{

AprgBitmapFilters::AprgBitmapFilters(string const& path)
    : m_backgroundColor(0xFFFFFF)
    , m_bitmap(path)
    , m_inputCanvas(m_bitmap.getSnippetReadFromFileWholeBitmap())
    , m_outputCanvas(m_bitmap.createColorFilledSnippetWithSizeOfWholeBitmap(m_backgroundColor))
{}

bool AprgBitmapFilters::isSimilar(unsigned int const color1, unsigned int const color2, unsigned int const similarityColorLimit) const //RGB algo
{
    bool isRedDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)extractRed(color1)-(int)extractRed(color2))>(int)similarityColorLimit);
    bool isGreenDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)extractGreen(color1)-(int)extractGreen(color2))>(int)similarityColorLimit);
    bool isBlueDifferenceBeyondLimit(mathHelper::getAbsoluteValue<int>((int)extractBlue(color1)-(int)extractBlue(color2))>(int)similarityColorLimit);
    return  !(isRedDifferenceBeyondLimit || isGreenDifferenceBeyondLimit || isBlueDifferenceBeyondLimit);
}

/*
bool AprgBitmapFilters::isSimilar(unsigned int const color1, unsigned int const color2) const//Pythagorean algo
{
    double colorDifferenceAcrossDifferentColors(mathHelper::getSquareRootOfXSquaredPlusYSquaredPlusZSquared<double>((double)getRed(color1)-(double)getRed(color2), (double)getGreen(color1)-(double)getGreen(color2), (double)getBlue(color1)-(double)getBlue(color2)));
    return colorDifferenceAcrossDifferentColors < m_similarityColorLimit;
}
*/

bool AprgBitmapFilters::isNotBackgroundColor(unsigned int const color) const
{
    return color != m_backgroundColor;
}

void AprgBitmapFilters::clearOutputCanvas()
{
    unsigned char backgroundColorByte = static_cast<unsigned char>(m_backgroundColor);
    m_outputCanvas = m_bitmap.createColorFilledSnippetWithSizeOfWholeBitmap(backgroundColorByte);
}

void AprgBitmapFilters::copyInputCanvasToOutputCanvas()
{
    m_outputCanvas = m_inputCanvas;
}

void AprgBitmapFilters::copyOutputCanvasToInputCanvas()
{
    m_inputCanvas = m_outputCanvas;
}

void AprgBitmapFilters::determinePenPixels(double const penSearchRadius, unsigned int const similarityColorLimit)
{
    m_inputCanvas.traverse([&](BitmapXY const& centerXY, unsigned int const centerColor)
    {
        Circle circle(convertBitmapXYToPoint(centerXY), penSearchRadius);
        BitmapXYs bitmapPointsWithSimilarColors;
        BitmapXYs bitmapPointsWithDisimilarColors;
        circle.traverseArea(1, [&](Point const& point)
        {
            BitmapXY pointInCircle(convertPointToBitmapXY(point));
            if(m_inputCanvas.isPositionInsideTheSnippet(pointInCircle))
            {
                unsigned int const currentColor(m_inputCanvas.getColorAt(pointInCircle));
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

void AprgBitmapFilters::retainMaxRadiusPenCircles(
        Circles & penCircles,
        map<Point, Circles> const& penPointToPenCircles)
{
    penCircles.clear();
    for(auto it=penPointToPenCircles.cbegin(); it!=penPointToPenCircles.cend(); it++)
    {
        Circles const& penCirclesInOnePoint(it->second);
        Circles::const_iterator circleWithMaxRadiusIt = max_element(
                    penCirclesInOnePoint.cbegin(),
                    penCirclesInOnePoint.cend(),
                    [](Circle const& circle1, Circle const& circle2)
        {
            return circle1.getRadius() < circle2.getRadius();
        });
        penCircles.emplace_back(*circleWithMaxRadiusIt);
    }
}

void AprgBitmapFilters::determinePenCircles(
        unsigned int const similarityColorLimit,
        double const acceptablePenPercentage)
{
    PixelInformationDatabase::PixelSet penPixels(m_pixelInformationDatabase.getPenPixelsConstReference());
    Circles & penCircles(m_pixelInformationDatabase.getPenCirclesReference());

    map<Point, Circles> penPointToPenCircles;
    for(BitmapXY const centerPoint : penPixels)
    {
        AlbaOptional<Circle> penCircleOptional(getPossiblePenCircle(centerPoint, similarityColorLimit, acceptablePenPercentage));
        if(penCircleOptional.hasContent())
        {
            Circle penCircle(penCircleOptional.getConstReference());
            penCircles.emplace_back(penCircle);
            penCircle.traverseArea(1, [&](Point const& point)
            {
                penPointToPenCircles[point].emplace_back(penCircle);
            });
        }
    }
    retainMaxRadiusPenCircles(penCircles, penPointToPenCircles);
}

void AprgBitmapFilters::drawPenCirclesToOutputCanvas()
{
    Circles const & penCircles(m_pixelInformationDatabase.getPenCirclesConstReference());

    for(Circle const& penCircle : penCircles)
    {
        BitmapXY centerPoint(convertPointToBitmapXY(penCircle.getCenter()));
        unsigned int const centerColor(m_inputCanvas.getColorAt(centerPoint));
        penCircle.traverseArea(1, [&](Point const& point)
        {
            BitmapXY pointInCircle(convertPointToBitmapXY(point));
            if(m_inputCanvas.isPositionInsideTheSnippet(pointInCircle))
            {
                //PixelInformation & pixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(pointInCircle));
                //pixelInfo.temporaryColors.emplace_back(centerColor);
                m_outputCanvas.setPixelAt(pointInCircle, centerColor);
            }
        });
    }
    /*    m_outputCanvas.traverse([&](BitmapXY const& bitmapPoint, unsigned int const)
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
            m_outputCanvas.setPixelAt(bitmapPoint, convertHueSaturationLightnessDataToColor(hslData));
            tempColors.clear();
        }
    });*/
}

void AprgBitmapFilters::drawBlankGapsUsingBlurInOutputCanvas(double const blurRadius)
{
    unsigned int numberOfPixelsWithChangedColor(1);
    while(numberOfPixelsWithChangedColor!=0)
    {
        numberOfPixelsWithChangedColor=0;
        AprgBitmapSnippet canvas2(m_outputCanvas);
        m_outputCanvas.traverse([&](BitmapXY const& bitmapPoint, unsigned int const color)
        {
            unsigned int newColor(color);
            if(m_backgroundColor == color)
            {
                newColor = getBlurredColor(m_outputCanvas, bitmapPoint, blurRadius, [&](unsigned int , unsigned int currentColor, BitmapXY )
                {
                    return m_backgroundColor!=currentColor;
                });
                if(m_backgroundColor != newColor)
                {
                    numberOfPixelsWithChangedColor++;
                }
            }
            canvas2.setPixelAt(bitmapPoint, newColor);
        });
        m_outputCanvas=canvas2;
    }
}

void AprgBitmapFilters::drawBlurredNonPenPixelsToOutputCanvas(double const blurRadius, unsigned int const similarityColorLimit)
{
    m_inputCanvas.traverse([&](BitmapXY const& bitmapPoint, unsigned int const)
    {
        PixelInformation const& pixelInfo(m_pixelInformationDatabase.getPixelInformation(bitmapPoint));
        if(!pixelInfo.isPenPixel)
        {
            m_outputCanvas.setPixelAt(bitmapPoint, getBlurredColor(m_inputCanvas, bitmapPoint, blurRadius,[&](unsigned int centerColor, unsigned int currentColor, BitmapXY pointInCircle)
            {
                PixelInformation const& pointInCirclePixelInfo(m_pixelInformationDatabase.getPixelInformation(pointInCircle));
                return isSimilar(centerColor, currentColor, similarityColorLimit) && currentColor!=m_backgroundColor && !pointInCirclePixelInfo.isPenPixel;
            }));
        }
    });
}

void AprgBitmapFilters::drawNonPenPixelsToOutputCanvas()
{
    m_inputCanvas.traverse([&](BitmapXY const& bitmapPoint, unsigned int const color)
    {
        PixelInformation const& pixelInfo(m_pixelInformationDatabase.getPixelInformation(bitmapPoint));
        if(!pixelInfo.isPenPixel)
        {
            m_outputCanvas.setPixelAt(bitmapPoint, color);
        }
    });
}

void AprgBitmapFilters::drawPenPixelsToOutputCanvas()
{
    m_inputCanvas.traverse([&](BitmapXY const& bitmapPoint, unsigned int const color)
    {
        PixelInformation const& pixelInfo(m_pixelInformationDatabase.getPixelInformation(bitmapPoint));
        if(pixelInfo.isPenPixel)
        {
            m_outputCanvas.setPixelAt(bitmapPoint, color);
        }
    });
}

void AprgBitmapFilters::getConnectedComponentsOneComponentAtATime()
{
    unsigned int currentLabel=1;
    deque<BitmapXY> pointsInDeque;
    m_inputCanvas.traverse([&](BitmapXY const& currentPoint, unsigned int const currentPointColor)
    {
        PixelInformation & currentPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(currentPoint));
        if(isNotBackgroundColor(currentPointColor) && currentPixelInfo.label==PixelInformation::INITIAL_LABEL_VALUE)
        {
            currentPixelInfo.label = currentLabel;
            pointsInDeque.push_front(currentPoint);
            while(!pointsInDeque.empty())
            {
                BitmapXY poppedPoint(pointsInDeque.back());
                pointsInDeque.pop_back();
                analyzeFourConnectivityNeighborPointsForConnectedComponentsOneComponentAtATime(pointsInDeque, poppedPoint, currentLabel);
            }
            currentLabel++;
        }
    });
}

AlbaOptional<Circle> AprgBitmapFilters::getPossiblePenCircle(
        BitmapXY const& centerPoint,
        unsigned int const similarityColorLimit,
        double const acceptablePenPercentage)
{
    AlbaOptional<Circle> result;
    unsigned int const centerColor(m_inputCanvas.getColorAt(centerPoint));
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
            if(m_inputCanvas.isPositionInsideTheSnippet(pointInCircle))
            {
                unsigned int const currentColor(m_inputCanvas.getColorAt(pointInCircle));
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

void AprgBitmapFilters::getConnectedComponentsTwoPass()
{
    unsigned int currentLabel=1;
    UnionFindForLabels unionFindForLabels;
    m_inputCanvas.traverse([&](BitmapXY const& currentPoint, unsigned int const currentPointColor)
    {
        if(isNotBackgroundColor(currentPointColor))
        {
            PixelInformation & currentPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(currentPoint));
            unsigned int smallestNeighborLabel = analyzeFourConnectivityNeighborPointsForConnectedComponentsTwoPassAndReturnSmallestLabel(
                        unionFindForLabels,
                        currentPoint);
            if(smallestNeighborLabel != PixelInformation::INVALID_LABEL_VALUE)
            {
                currentPixelInfo.label = smallestNeighborLabel;
            }
            else
            {
                currentPixelInfo.label = currentLabel;
                currentLabel++;
            }
        }
    });
    m_inputCanvas.traverse([&](BitmapXY const& currentPoint, unsigned int const currentPointColor)
    {
        PixelInformation & currentPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(currentPoint));
        if(isNotBackgroundColor(currentPointColor) && currentPixelInfo.label!=PixelInformation::INITIAL_LABEL_VALUE)
        {
            unsigned int smallestLabel = unionFindForLabels.getRoot(currentPixelInfo.label);
            currentPixelInfo.label = smallestLabel;
        }
    });
}

void AprgBitmapFilters::saveOutputCanvasIntoCurrentBitmapFile() const
{
    m_bitmap.setSnippetWriteToFile(m_outputCanvas);
}

void AprgBitmapFilters::saveOutputCanvasIntoFileInTheSameDirectory(string const& filename)
{
    AlbaLocalPathHandler originalBitmapPathHandler(m_bitmap.getConfiguration().getPath());
    saveOutputCanvasIntoFileWithFullFilePath(originalBitmapPathHandler.getDirectory()+filename);
}

void AprgBitmapFilters::saveOutputCanvasIntoFileWithFullFilePath(string const& fullFilePath)
{
    AlbaLocalPathHandler originalBitmapPathHandler(m_bitmap.getConfiguration().getPath());
    AlbaLocalPathHandler newFilePathHandler(fullFilePath);
    originalBitmapPathHandler.copyToNewFile(newFilePathHandler.getFullPath());
    AprgBitmap newBitmap(newFilePathHandler.getFullPath());
    newBitmap.setSnippetWriteToFile(m_outputCanvas);
}

void AprgBitmapFilters::setBackgroundColor(unsigned int const backgroundColor)
{
    m_backgroundColor = backgroundColor;
}

void AprgBitmapFilters::gatherAndSaveColorDataAndStatistics()
{
    gatherAndSaveColorStatistics(m_bitmap.getConfiguration().getPath());
}

void AprgBitmapFilters::drawToAnimeColorToOutputCanvas()
{
    AnimizeColor animizeColor;
    animizeColor.gatherStatistics(m_bitmap.getConfiguration().getPath());
    animizeColor.calculateNewValues();
    m_inputCanvas.traverse([&](BitmapXY const& position, unsigned int const color)
    {
        unsigned int newColor = animizeColor.getNewColor(color);
        m_outputCanvas.setPixelAt(position, newColor);
    });
}

unsigned int AprgBitmapFilters::analyzeFourConnectivityNeighborPointsForConnectedComponentsTwoPassAndReturnSmallestLabel(
        UnionFindForLabels & unionFindForLabels,
        BitmapXY const & neighborPoint)
{
    //4-connectivity
    unsigned int smallestLabel = PixelInformation::INVALID_LABEL_VALUE;
    BitmapXY neighbor1(neighborPoint.getX()-1, neighborPoint.getY());
    BitmapXY neighbor2(neighborPoint.getX(), neighborPoint.getY()-1);
    unsigned int neighbor1Label = analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(neighbor1);
    unsigned int neighbor2Label = analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(neighbor2);
    smallestLabel = min(smallestLabel, neighbor1Label);
    smallestLabel = min(smallestLabel, neighbor2Label);
    updateUnionFindForLabels(unionFindForLabels, smallestLabel, neighbor1Label, neighbor2Label);
    return smallestLabel;
}

unsigned int AprgBitmapFilters::analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(
        BitmapXY const & neighborPoint)
{
    unsigned int labelResult = PixelInformation::INVALID_LABEL_VALUE;
    if(m_inputCanvas.isPositionInsideTheSnippet(neighborPoint))
    {
        unsigned int neighborPointColor = m_inputCanvas.getColorAt(neighborPoint);
        PixelInformation & neighborPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(neighborPoint));
        if(isNotBackgroundColor(neighborPointColor) && neighborPixelInfo.label!=PixelInformation::INITIAL_LABEL_VALUE)
        {
            labelResult = neighborPixelInfo.label;
        }
    }
    return labelResult;
}

void AprgBitmapFilters::updateUnionFindForLabels(
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

void AprgBitmapFilters::analyzeFourConnectivityNeighborPointsForConnectedComponentsOneComponentAtATime(
        deque<BitmapXY> & pointsInDeque,
        BitmapXY const & poppedPoint,
        unsigned int const currentLabel)
{
    //4-connectivity
    BitmapXY neighbor1(poppedPoint.getX()-1, poppedPoint.getY());
    BitmapXY neighbor2(poppedPoint.getX(), poppedPoint.getY()-1);
    BitmapXY neighbor3(poppedPoint.getX()+1, poppedPoint.getY());
    BitmapXY neighbor4(poppedPoint.getX(), poppedPoint.getY()+1);
    analyzeNeighborPointForConnectedComponentsOneComponentAtATime(pointsInDeque, neighbor1, currentLabel);
    analyzeNeighborPointForConnectedComponentsOneComponentAtATime(pointsInDeque, neighbor2, currentLabel);
    analyzeNeighborPointForConnectedComponentsOneComponentAtATime(pointsInDeque, neighbor3, currentLabel);
    analyzeNeighborPointForConnectedComponentsOneComponentAtATime(pointsInDeque, neighbor4, currentLabel);
}

void AprgBitmapFilters::analyzeNeighborPointForConnectedComponentsOneComponentAtATime(
        deque<BitmapXY> & pointsInDeque,
        BitmapXY const & neighborPoint,
        unsigned int const currentLabel)
{
    if(m_inputCanvas.isPositionInsideTheSnippet(neighborPoint))
    {
        unsigned int neighborPointColor = m_inputCanvas.getColorAt(neighborPoint);
        PixelInformation & neighborPixelInfo(m_pixelInformationDatabase.getPixelInformationReferenceAndCreateIfNeeded(neighborPoint));
        if(isNotBackgroundColor(neighborPointColor) && neighborPixelInfo.label==PixelInformation::INITIAL_LABEL_VALUE)
        {
            neighborPixelInfo.label = currentLabel;
            pointsInDeque.push_front(neighborPoint);
        }
    }
}

Point AprgBitmapFilters::convertBitmapXYToPoint(BitmapXY const& bitmapPosition) const
{
    return Point(bitmapPosition.getX(), bitmapPosition.getY());
}

BitmapXY AprgBitmapFilters::convertPointToBitmapXY(Point const& pointPosition) const
{
    return BitmapXY(round(pointPosition.getX()), round(pointPosition.getY()));
}

unsigned int AprgBitmapFilters::getBlurredColor(AprgBitmapSnippet const& canvas, BitmapXY const& centerXY, double const blurRadius, BlurCondition const& isIncludedInBlur) const
{
    unsigned int const centerColor(canvas.getColorAt(centerXY));
    double totalBlurredColorRed(0);
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

double AprgBitmapFilters::getBlurWeight(double const distanceFromCenter, double const blurRadius) const
{
    return (blurRadius-distanceFromCenter+1)/(blurRadius+1);
}

}
