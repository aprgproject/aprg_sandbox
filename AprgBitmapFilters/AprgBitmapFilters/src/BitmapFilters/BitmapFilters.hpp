#pragma once

#include <Bitmap/Bitmap.hpp>
#include <Bitmap/BitmapSnippet.hpp>
#include <BitmapFilters/LabelForPixels.hpp>
#include <BitmapFilters/PixelInformationDatabase.hpp>
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
    using PenPixelToPenCircleMap=std::map<BitmapXY, TwoDimensions::Circle>;
    using PenPixelPenCirclePair=std::pair<BitmapXY, TwoDimensions::Circle>;

    BitmapFilters(std::string const& path);

    bool isSimilar(unsigned int const color1, unsigned int const color2, unsigned int const similarityColorLimit) const;
    bool isNotBackgroundColor(unsigned int const color) const;

    BitmapSnippet getWholeBitmapSnippet() const;
    BitmapSnippet getBlankSnippet(unsigned int const backgroundColor) const;
    BitmapSnippet getBlankSnippetWithBackground() const;
    unsigned int getLabelColor(unsigned int const label) const;

    AlbaOptional<TwoDimensions::Circle> getPossiblePenCircle(
            BitmapSnippet const& inputSnippet,
            BitmapXY const& centerPoint,
            unsigned int const similarityColorLimit,
            double const acceptablePenPercentage);

    void determinePenPixels(
            BitmapSnippet const& inputSnippet,
            double const penSearchRadius,
            unsigned int const similarityColorLimit);
    void determinePenCirclesFromPenPixels(
            BitmapSnippet const& inputSnippet,
            unsigned int const similarityColorLimit,
            double const acceptablePenPercentage);
    void determineConnectedComponentsByOneComponentAtATime(
            BitmapSnippet const& inputSnippet);
    void determineConnectedComponentsUsingTwoPass(
            BitmapSnippet const& inputSnippet);

    void drawPenPixels(
            BitmapSnippet const& inputSnippet,
            BitmapSnippet & outputSnippet);
    void drawNonPenPixels(
            BitmapSnippet const& inputSnippet,
            BitmapSnippet & outputSnippet);
    void drawBlurredNonPenPixels(
            BitmapSnippet const& inputSnippet,
            BitmapSnippet & outputSnippet,
            double const blurRadius,
            unsigned int const similarityColorLimit);
    void drawToFillGapsUsingBlur(
            BitmapSnippet & snippet,
            double const blurRadius);
    void drawPenCircles(
            BitmapSnippet const& inputSnippet,
            BitmapSnippet & outputSnippet);
    void drawAnimeColor(
            BitmapSnippet & snippet);
    void drawNewColorForLabels(
            BitmapSnippet & snippet);

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

    void drawBlurredColorToBackgroundPoints(double const blurRadius, BitmapSnippet& snippet, BitmapXYs backgroundPoints, BitmapXYs newBackgroundPoints);


private:
    bool isThisPenCircleBetter(
            BitmapXY const& penBitmapXY,
            TwoDimensions::Circle const& circleToCheck,
            TwoDimensions::Circle const& circleToCompare) const;
    void determinePenPixelsToPenCircles(
            PenPixelToPenCircleMap & penPixelsToPenCircles,
            BitmapSnippet const& inputSnippet,
            unsigned int const similarityColorLimit,
            double const acceptablePenPercentage);
    void savePenCircles(PenPixelToPenCircleMap const& penPixelsToPenCircles);
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
            BitmapSnippet const& snippet,
            BitmapXY const& centerXY,
            double const blurRadius,
            BlurCondition const& isIncludedInBlur) const;
    double getBlurWeight(double const distanceFromCenter, double const blurRadius) const;

    unsigned int m_backgroundColor;
    Bitmap m_bitmap;
    PixelInformationDatabase m_pixelInformationDatabase;
    LabelForPixels m_labelForPixels;
};

}

}
