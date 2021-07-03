#pragma once

#include <Bitmap/Bitmap.hpp>
#include <Bitmap/BitmapSnippet.hpp>
#include <BitmapFilters/LabelForPoints.hpp>
#include <BitmapFilters/PenCircles.hpp>
#include <BitmapFilters/PenPoints.hpp>
#include <TwoDimensions/Point.hpp>
#include <TwoDimensions/Circle.hpp>
#include <UnionFind/UnionFind.hpp>

#include <functional>
#include <deque>

namespace alba
{

namespace AprgBitmap
{

class BitmapFilters
{
public:
    using BlurCondition = std::function<bool(unsigned int,unsigned int,BitmapXY)>;
    using UnionFindForLabels = UnionFindUsingMap<unsigned int>;
    using PenPointToPenCircleMap=std::map<BitmapXY, TwoDimensions::Circle>;
    using PenPointPenCirclePair=std::pair<BitmapXY, TwoDimensions::Circle>;

    BitmapFilters(std::string const& path);

    bool isSimilar(unsigned int const color1, unsigned int const color2, unsigned int const similarityColorLimit) const;
    bool isNotBackgroundColor(unsigned int const color) const;

    BitmapSnippet getWholeBitmapSnippet() const;
    BitmapSnippet getBlankSnippet(unsigned int const backgroundColor) const;
    BitmapSnippet getBlankSnippetWithBackground() const;

    AlbaOptional<TwoDimensions::Circle> getPossiblePenCircle(
            BitmapSnippet const& inputSnippet,
            BitmapXY const& centerPoint,
            unsigned int const similarityColorLimit,
            double const acceptablePenPercentage);

    void determinePenPoints(
            BitmapSnippet const& inputSnippet,
            double const penSearchRadius,
            unsigned int const similarityColorLimit);
    void determinePenCirclesFromPenPoints(
            BitmapSnippet const& inputSnippet,
            unsigned int const similarityColorLimit,
            double const acceptablePenPercentage);
    void determineConnectedComponentsByOneComponentAtATime(
            BitmapSnippet const& inputSnippet);
    void determineConnectedComponentsUsingTwoPass(
            BitmapSnippet const& inputSnippet);

    void drawPenPoints(
            BitmapSnippet const& inputSnippet,
            BitmapSnippet & outputSnippet);
    void drawNonPenPoints(
            BitmapSnippet const& inputSnippet,
            BitmapSnippet & outputSnippet);
    void drawBlurredNonPenPoints(
            BitmapSnippet const& inputSnippet,
            BitmapSnippet & outputSnippet,
            double const blurRadius,
            unsigned int const similarityColorLimit);
    void drawBlurredColors(
            BitmapSnippet & snippet,
            double const blurRadius,
            unsigned int const similarityColorLimit);
    void drawToFillGapsUsingBlur(
            BitmapSnippet & snippet,
            double const blurRadius);    void drawPenCircles(
            BitmapSnippet const& inputSnippet,
            BitmapSnippet & outputSnippet);
    void drawWithBlurredOutDisimilarColors(
            BitmapSnippet & snippet,
            unsigned int const similarityColorLimit);
    void drawAnimeColor(
            BitmapSnippet & snippet);
    void drawNewColorForLabels(            BitmapSnippet & snippet);

    void saveOutputCanvasIntoCurrentBitmapFile(
            BitmapSnippet const& snippet) const;
    void saveOutputCanvasIntoFileInTheSameDirectory(
            BitmapSnippet const& snippet,
            std::string const& filename);
    void saveOutputCanvasIntoFileWithFullFilePath(
            BitmapSnippet const& snippet,
            std::string const& fullFilePath);

    void setBackgroundColor(unsigned int const backgroundColor);
    void gatherAndSaveColorDataAndStatistics();


private:
    void drawBlurredDisimilarColorsForCenterPoint(
            BitmapSnippet & snippet,
            BitmapXY const& point,
            unsigned int const similarityColorLimit);
    void drawBlurredDisimilarColorsForNonCenterPoint(
            BitmapSnippet & snippet,
            BitmapXY const& point,
            unsigned int const centerColor,
            unsigned int const similarityColorLimit);
    bool isThisPenCircleBetter(
            BitmapXY const& penBitmapXY,
            TwoDimensions::Circle const& circleToCheck,            TwoDimensions::Circle const& circleToCompare) const;
    void determinePenPointsToPenCircles(
            PenPointToPenCircleMap & penPointsToPenCircles,
            BitmapSnippet const& inputSnippet,
            unsigned int const similarityColorLimit,
            double const acceptablePenPercentage);
    void savePenCircles(PenPointToPenCircleMap const& penPointsToPenCircles);
    unsigned int analyzeFourConnectivityNeighborPointsForConnectedComponentsTwoPassAndReturnSmallestLabel(
            BitmapSnippet const& inputSnippet,
            UnionFindForLabels & unionFindForLabels,
            BitmapXY const & neighborPoint);
    unsigned int analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(
            BitmapSnippet const& inputSnippet,
            BitmapXY const & neighborPoint);
    void updateUnionFindForLabels(
            UnionFindForLabels& unionFindForLabels,
            unsigned int const smallestLabel,
            unsigned int const neighbor1Label,
            unsigned int const neighbor2Label) const;
    void analyzeFourConnectivityNeighborPointsForConnectedComponentsOneComponentAtATime(
            BitmapSnippet const& inputSnippet,
            std::deque<BitmapXY> & pointsInQueue,
            BitmapXY const & poppedPoint,
            unsigned int const currentLabel);
    void analyzeNeighborPointForConnectedComponentsOneComponentAtATime(
            BitmapSnippet const& inputSnippet,
            std::deque<BitmapXY> & pointsInQueue,
            BitmapXY const & neighborPoint,
            unsigned int const currentLabel);
    void determineConnectedComponentsUsingTwoPassInFirstPass(
            BitmapSnippet const& inputSnippet,
            UnionFindForLabels & unionFindForLabels);
    void determineConnectedComponentsUsingTwoPassInSecondPass(
            BitmapSnippet const& inputSnippet,
            UnionFindForLabels const& unionFindForLabels);

    unsigned int getBlurredColor(
            unsigned int const centerColor,
            unsigned int const colorToCompare,
            unsigned int const similarityColorLimit) const;
    unsigned char getBlurredColorPart(
            unsigned char const centerColorPart,
            unsigned char const colorToComparePart,
            unsigned int const similarityColorLimit) const;
    unsigned int getBlurredColor(
            BitmapSnippet const& snippet,
            BitmapXY const& centerXY,
            double const blurRadius,            BlurCondition const& isIncludedInBlur) const;
    double getBlurWeight(double const distanceFromCenter, double const blurRadius) const;

    unsigned int m_backgroundColor;
    Bitmap m_bitmap;
    LabelForPoints m_labelForPixels;
    PenPoints m_penPoints;
    PenCircles m_penCircles;
};

}

}
