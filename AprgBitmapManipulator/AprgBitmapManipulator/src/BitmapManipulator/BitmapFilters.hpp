#pragma once

#include <Algorithm/UnionFind/UnionFindUsingMap.hpp>
#include <Bitmap/Bitmap.hpp>
#include <Bitmap/BitmapSnippet.hpp>
#include <BitmapManipulator/AnimizeColor.hpp>
#include <BitmapManipulator/LabelForPoints.hpp>
#include <BitmapManipulator/PenCircles.hpp>
#include <BitmapManipulator/PenPoints.hpp>
#include <BitmapManipulator/Traversal/BitmapSnippetTraversal.hpp>
#include <Geometry/TwoDimensions/Circle.hpp>
#include <Geometry/TwoDimensions/Point.hpp>

#include <deque>
#include <functional>

namespace alba
{

namespace AprgBitmap
{

class BitmapFilters
{
public:
    using BlurCondition = std::function<bool(uint32_t const, uint32_t const, BitmapXY const&)>;
    using UnionFindForLabels = algorithm::UnionFindUsingMap<unsigned int>;
    using PointToColorMap = std::map<BitmapXY, uint32_t>;
    using PointAndColorPair = std::pair<BitmapXY, uint32_t>;
    using PenPointToPenCircleMap = std::map<BitmapXY, TwoDimensions::Circle>;
    using PenPointAndPenCirclePair = std::pair<BitmapXY, TwoDimensions::Circle>;

    BitmapFilters(std::string const& path);

    bool isBackgroundColor(uint32_t const color) const;
    bool isNotBackgroundColor(uint32_t const color) const;

    BitmapSnippet getWholeBitmapSnippet() const;
    BitmapSnippet getBlankSnippet(uint8_t const backgroundColorByte) const;
    BitmapSnippet getBlankSnippetWithBackground() const;
    BitmapSnippet getBlankSnippetWithColor(
            uint32_t const color) const;

    AlbaOptional<TwoDimensions::Circle> getPossiblePenCircle(
            BitmapSnippet const& inputSnippet,
            BitmapXY const& centerPoint,
            uint32_t const similarityColorLimit,
            double const acceptablePenPercentage);

    //determine functions
    void determinePenPoints(
            PenPoints & penPoints,
            BitmapSnippet const& inputSnippet,
            double const penSearchRadius,
            uint32_t const similarityColorLimit);
    void determinePenCirclesFromPenPoints(
            PenCircles & penCircles,
            PenPoints const& penPoints,
            BitmapSnippet const& inputSnippet,
            uint32_t const similarityColorLimit,
            double const acceptablePenPercentage);
    void determineConnectedComponentsByOneComponentAtATime(
            BitmapSnippet const& inputSnippet);
    void determineConnectedComponentsUsingTwoPass(
            BitmapSnippet const& inputSnippet);

    //draw pen and non pen functions
    void drawPenPoints(
            PenPoints const& penPoints,
            BitmapSnippet const& inputSnippet,
            BitmapSnippet & outputSnippet);
    void drawNonPenPoints(
            PenPoints const& penPoints,
            BitmapSnippet const& inputSnippet,
            BitmapSnippet & outputSnippet);
    void drawBlurredNonPenPoints(
            PenPoints const& penPoints,
            BitmapSnippet const& inputSnippet,
            BitmapSnippet & outputSnippet,
            double const blurRadius,
            uint32_t const similarityColorLimit);
    void drawPenCircles(
            PenCircles const& penCircles,
            BitmapSnippet & snippet);
    void drawPenCirclesOnly(
            PenCircles const& penCircles,
            BitmapSnippet & snippet);

    //draw blur functions
    void drawWithBlurringDisimilarColors(
            BitmapSnippet & snippet,
            unsigned int const numberOfPasses,
            uint32_t const similarityColorLimit);
    void drawBlurredColorsUsingCircles(
            BitmapSnippet & snippet,
            double const blurRadius,
            uint32_t const similarityColorLimit);
    void drawWithBlurUsingSnakeLikeTraversal(
            BitmapSnippet & snippet,
            uint32_t const similarityColorLimit);

    //other draw functions
    void drawToFillGapsUsingBlur(
            BitmapSnippet & snippet,
            double const blurRadius);
    void drawAnimeColor(
            BitmapSnippet & snippet,
            AnimizeColor const& animizeColor);
    void drawNewColorForLabels(
            BitmapSnippet & snippet);

    void saveSnippetIntoCurrentBitmapFile(
            BitmapSnippet const& snippet) const;
    void saveSnippetIntoFileInTheSameDirectory(
            BitmapSnippet const& snippet,
            std::string const& filename);
    void saveSnippetIntoFileWithFullFilePath(
            BitmapSnippet const& snippet,
            std::string const& fullFilePath);

    void setBackgroundColor(uint32_t const backgroundColor);

    void gatherAndSaveColorDataAndStatistics();

private:
    void collectDisimilarPointsToNewColors(
            PointToColorMap & disimilarPointsToNewColors,
            BitmapSnippet const& inputSnippet,
            uint32_t const similarityColorLimit);
    unsigned int analyzeFourConnectivityNeighborPointsForConnectedComponentsTwoPassAndReturnSmallestLabel(
            BitmapSnippet const& inputSnippet,
            UnionFindForLabels & unionFindForLabels,
            BitmapXY const & neighborPoint);
    void analyzeFourConnectivityNeighborPointsForConnectedComponentsOneComponentAtATime(
            BitmapSnippet const& inputSnippet,
            std::deque<BitmapXY> & pointsInDeque,
            BitmapXY const & poppedPoint,
            unsigned int const currentLabel);
    unsigned int analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(
            BitmapSnippet const& inputSnippet,
            BitmapXY const & neighborPoint);
    void analyzeNeighborPointForConnectedComponentsOneComponentAtATime(
            BitmapSnippet const& inputSnippet,
            std::deque<BitmapXY> & pointsInDeque,
            BitmapXY const & neighborPoint,
            unsigned int const currentLabel);
    void determineConnectedComponentsUsingTwoPassInFirstPass(
            BitmapSnippet const& inputSnippet,
            UnionFindForLabels & unionFindForLabels);
    void determineConnectedComponentsUsingTwoPassInSecondPass(
            BitmapSnippet const& inputSnippet,
            UnionFindForLabels const& unionFindForLabels);
    void determinePenPointsToPenCircles(
            PenPointToPenCircleMap & penPointsToPenCircles,
            PenPoints const& penPoints,
            BitmapSnippet const& inputSnippet,
            uint32_t const similarityColorLimit,
            double const acceptablePenPercentage);
    void drawToBlurForCenterPoint(
            BitmapSnippet & snippet,
            BitmapXYs & pointsToBlur,
            BitmapXY const& point,
            uint32_t const similarityColorLimit);
    void drawToBlurForNonCenterPoint(
            BitmapSnippet & snippet,
            BitmapXYs & pointsToBlur,
            BitmapXY const& point,
            uint32_t const centerColor,
            uint32_t const similarityColorLimit);
    void updateUnionFindForLabels(
            UnionFindForLabels& unionFindForLabels,
            unsigned int const smallestLabel,
            unsigned int const neighbor1Label,
            unsigned int const neighbor2Label) const;

    bool isThisPenCircleBetter(
            BitmapXY const& penBitmapXY,
            TwoDimensions::Circle const& circleToCheck,
            TwoDimensions::Circle const& circleToCompare) const;
    uint32_t getBlurredColor(
            uint32_t const centerColor,
            uint32_t const colorToCompare,
            uint32_t const similarityColorLimit) const;
    uint8_t getBlurredColorPart(
            uint8_t const centerColorPart,
            uint8_t const colorToComparePart,
            uint32_t const similarityColorLimit) const;
    uint32_t getBlurredColorUsingACircle(
            BitmapSnippet const& snippet,
            BitmapXY const& centerXY,
            double const blurRadius,
            BlurCondition const& isIncludedInBlur) const;
    double getBlurWeight(double const distanceFromCenter, double const blurRadius) const;

    uint32_t m_backgroundColor;
    Bitmap m_bitmap;
    LabelForPoints m_labelForPixels;
};

}

}
