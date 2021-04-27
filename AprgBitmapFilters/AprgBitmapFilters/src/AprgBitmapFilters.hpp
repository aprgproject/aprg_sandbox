#pragma once

#include <AprgBitmap.hpp>
#include <AprgBitmapSnippet.hpp>
#include <PixelInformationDatabase.hpp>
#include <TwoDimensions/Point.hpp>
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

    void clearOutputCanvas();
    void copyInputCanvasToOutputCanvas();
    void copyOutputCanvasToInputCanvas();

    void determinePenPixels(double const penSearchRadius, unsigned int const similarityColorLimit);
    void getConnectedComponentsOneComponentAtATime();
    void getConnectedComponentsTwoPass();

    void saveOutputCanvasToCurrentBitmapFile() const;
    void saveOutputCanvasIntoDifferentFile(std::string const& filename);

    void setBackgroundColor(unsigned int const backgroundColor);
    void setBlankGapsUsingBlurToOutputCanvas(double const blurRadius);
    void setBlurredNonPenPixelsToOutputCanvas(double const blurRadius, unsigned int const similarityColorLimit);
    void setNonPenPixelsToOutputCanvas();
    void setPenPixelsToOutputCanvas();
    void setColoredPixelsForDifferentLabelsIntoOutputCanvas();

private:
    unsigned int analyzeFourConnectivityNeighborPointsForConnectedComponentsTwoPassAndReturnSmallestLabel(
            UnionFindForLabels & unionFindForLabels,            BitmapXY const & neighborPoint);
    unsigned int analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(
            BitmapXY const & neighborPoint);
    void updateUnionFindForLabels(UnionFindForLabels& unionFindForLabels, unsigned int const smallestLabel, unsigned int const neighbor1Label, unsigned int const neighbor2Label) const;    void analyzeFourConnectivityNeighborPointsForConnectedComponentsOneComponentAtATime(
            std::deque<BitmapXY> & pointsInQueue,
            BitmapXY const & poppedPoint,
            unsigned int const currentLabel);
    void analyzeNeighborPointForConnectedComponentsOneComponentAtATime(
            std::deque<BitmapXY> & pointsInQueue,
            BitmapXY const & neighborPoint,
            unsigned int const currentLabel);
    TwoDimensions::Point convertBitmapXYToPoint(BitmapXY const& bitmapPosition) const;
    BitmapXY convertPointToBitmapXY(TwoDimensions::Point const& pointPosition) const;

    unsigned int getBlurredColor(AprgBitmapSnippet const& canvas, BitmapXY const& centerXY, double const blurRadius, BlurCondition const& isIncludedInBlur) const;
    double getBlurWeight(double const distanceFromCenter, double const blurRadius) const;

    void setLabelToColorMapForStableRun(std::map<unsigned int, unsigned int>& labelToColorMap) const;

    unsigned int m_backgroundColor;
    AprgBitmap m_bitmap;    AprgBitmapSnippet m_inputCanvas;
    AprgBitmapSnippet m_outputCanvas;
    PixelInformationDatabase m_pixelInformationDatabase;
};
}
