#pragma once

#include <Bitmap/BitmapSnippet.hpp>
#include <BitmapFilters/PenCircles.hpp>
#include <BitmapTraversal/BitmapSnippetTraversal.hpp>

namespace alba
{

namespace AprgBitmap
{

class PenCirclesDrawer
{
public:
    struct ColorDetails
    {
        ColorDetails();
        double totalRed;
        double totalGreen;
        double totalBlue;
        double totalWeight;
        bool isEmpty() const;
        unsigned int getColor() const;
        void addColor(unsigned int const color, double const weight);
        void clear();
    };
    using PointToColorMap = std::map<BitmapXY, unsigned int>;
    using PointColorPair = std::pair<BitmapXY, unsigned int>;
    using PointToColorDetailsMap = std::map<BitmapXY, ColorDetails>;
    using PointColorDetailsPair = std::pair<BitmapXY, ColorDetails>;

    PenCirclesDrawer(
            PenCircles const& penCircles,
            BitmapSnippet & snippet);

    void draw();
    void drawUsingCirclesWithoutOverlay();
    void drawUsingCirclesWithOverlay();
    void drawUsingConnectedCircles();

private:
    bool isToBeConnected(
            PenCircles::PointPenCircleDetailsPair const& pair1,
            PenCircles::PointPenCircleDetailsPair const& pair2) const;
    void writeDrawnPointsInSnippet();
    void writeCirclesWithoutOverlay();
    void writeCirclesWithOverlay();
    void connectCirclesIfNeeded();
    void putCirclesWithoutOverlay();
    void putCirclesWithOverlay();
    void putCircleConnectionsAndRemoveProcessedCircles();
    BitmapSnippet & m_snippet;
    BitmapSnippetTraversal m_snippetTraversal;
    PenCircles m_penCircles;
    PointToColorMap m_drawnPoints;
};

}

}
