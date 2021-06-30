#pragma once

#include <AprgBitmap.hpp>
#include <AprgBitmapSnippet.hpp>
#include <PixelInformationDatabase.hpp>
#include <TwoDimensions/Point.hpp>
#include <TwoDimensions/Circle.hpp>
#include <UnionFind/UnionFind.hpp>

#include <functional>
#include <deque>

namespace alba
{

class AprgBitmapFilters
{
public:
    using BlurCondition = std::function<bool(unsigned int,unsigned int,BitmapXY)>;
    using UnionFindForLabels = UnionFindUsingMap<unsigned int>;

    AprgBitmapFilters(std::string const& path);

    bool isSimilar(unsigned int const color1, unsigned int const color2, unsigned int const similarityColorLimit) const;
    bool isNotBackgroundColor(unsigned int const color) const;

    AprgBitmapSnippet getWholeBitmapSnippet() const;
    AprgBitmapSnippet getBlankSnippet(unsigned int const backgroundColor) const;
    AprgBitmapSnippet getBlankSnippetWithBackground() const;
    unsigned int getLabelColor(unsigned int const label) const;

    AlbaOptional<TwoDimensions::Circle> getPossiblePenCircle(
            AprgBitmapSnippet const& inputSnippet,
            BitmapXY const& centerPoint,
            unsigned int const similarityColorLimit,
            double const acceptablePenPercentage);

    void determinePenPixels(
            AprgBitmapSnippet const& inputSnippet,
            double const penSearchRadius,
            unsigned int const similarityColorLimit);
    void determinePenCirclesFromPenPixels(
            AprgBitmapSnippet const& inputSnippet,
            unsigned int const similarityColorLimit,
            double const acceptablePenPercentage);
    void determineConnectedComponentsByOneComponentAtATime(
            AprgBitmapSnippet const& inputSnippet);
    void determineConnectedComponentsUsingTwoPass(
            AprgBitmapSnippet const& inputSnippet);

    void drawPenPixels(
            AprgBitmapSnippet const& inputSnippet,
            AprgBitmapSnippet & outputSnippet);
    void drawNonPenPixels(
            AprgBitmapSnippet const& inputSnippet,
            AprgBitmapSnippet & outputSnippet);
    void drawBlurredNonPenPixels(
            AprgBitmapSnippet & snippet,
            double const blurRadius,
            unsigned int const similarityColorLimit);
    void drawToFillGapsUsingBlur(
            AprgBitmapSnippet & snippet,
            double const blurRadius);
    void drawPenCircles(
            AprgBitmapSnippet const& inputSnippet,
            AprgBitmapSnippet & outputSnippet);
    void drawAnimeColor(
            AprgBitmapSnippet & snippet);
    void drawNewColorForLabels(            AprgBitmapSnippet & snippet);

    void saveOutputCanvasIntoCurrentBitmapFile(
            AprgBitmapSnippet const& snippet) const;    void saveOutputCanvasIntoFileInTheSameDirectory(
            AprgBitmapSnippet const& snippet,
            std::string const& filename);
    void saveOutputCanvasIntoFileWithFullFilePath(
            AprgBitmapSnippet const& snippet,
            std::string const& fullFilePath);

    void setBackgroundColor(unsigned int const backgroundColor);
    void gatherAndSaveColorDataAndStatistics();

private:
    void savePenCirclesInPenPixels();
    unsigned int analyzeFourConnectivityNeighborPointsForConnectedComponentsTwoPassAndReturnSmallestLabel(
            AprgBitmapSnippet const& inputSnippet,
            UnionFindForLabels & unionFindForLabels,            BitmapXY const & neighborPoint);
    unsigned int analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(
            AprgBitmapSnippet const& inputSnippet,
            BitmapXY const & neighborPoint);    void updateUnionFindForLabels(
            UnionFindForLabels& unionFindForLabels,
            unsigned int const smallestLabel,
            unsigned int const neighbor1Label,
            unsigned int const neighbor2Label) const;
    void analyzeFourConnectivityNeighborPointsForConnectedComponentsOneComponentAtATime(
            AprgBitmapSnippet const& inputSnippet,
            std::deque<BitmapXY> & pointsInQueue,
            BitmapXY const & poppedPoint,
            unsigned int const currentLabel);
    void analyzeNeighborPointForConnectedComponentsOneComponentAtATime(
            AprgBitmapSnippet const& inputSnippet,
            std::deque<BitmapXY> & pointsInQueue,
            BitmapXY const & neighborPoint,
            unsigned int const currentLabel);
    void determineConnectedComponentsUsingTwoPassInFirstPass(
            AprgBitmapSnippet const& inputSnippet,
            UnionFindForLabels & unionFindForLabels);
    void determineConnectedComponentsUsingTwoPassInSecondPass(
            AprgBitmapSnippet const& inputSnippet,
            UnionFindForLabels const& unionFindForLabels);
    TwoDimensions::Point convertBitmapXYToPoint(BitmapXY const& bitmapPosition) const;
    BitmapXY convertPointToBitmapXY(TwoDimensions::Point const& pointPosition) const;

    unsigned int getBlurredColor(AprgBitmapSnippet const& canvas, BitmapXY const& centerXY, double const blurRadius, BlurCondition const& isIncludedInBlur) const;
    double getBlurWeight(double const distanceFromCenter, double const blurRadius) const;

    unsigned int m_backgroundColor;
    AprgBitmap m_bitmap;
    PixelInformationDatabase m_pixelInformationDatabase;
};

}
