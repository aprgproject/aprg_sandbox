#pragma once

#include <Bitmap/BitmapSnippet.hpp>
#include <BitmapManipulator/PenCircles.hpp>
#include <BitmapManipulator/Traversal/BitmapSnippetTraversal.hpp>

namespace alba {

namespace AprgBitmap {

class PenCirclesDrawer {
public:
    struct ColorDetails {
        ColorDetails();
        double totalRed;
        double totalGreen;
        double totalBlue;
        double totalWeight;
        bool isEmpty() const;
        uint32_t getColor() const;
        void addColor(uint32_t const color, double const weight);
        void clear();
    };
    using PointToColorMap = std::map<BitmapXY, uint32_t>;
    using PointAndColorPair = std::pair<BitmapXY, uint32_t>;
    using PointToColorDetailsMap = std::map<BitmapXY, ColorDetails>;
    using PointAndColorDetailsPair = std::pair<BitmapXY, ColorDetails>;

    PenCirclesDrawer(PenCircles const& penCircles, BitmapSnippet& snippet);

    void draw();
    void drawUsingCirclesWithoutOverlay();
    void drawUsingCirclesWithOverlay();
    void drawUsingConnectedCircles();

private:
    bool isToBeConnected(
        PenCircles::PointAndPenCircleDetailsPair const& pair1,
        PenCircles::PointAndPenCircleDetailsPair const& pair2) const;
    void writeDrawnPointsInSnippet();
    void writeCirclesWithoutOverlay();
    void writeCirclesWithOverlay();
    void connectCirclesIfNeeded();
    void putCirclesWithoutOverlay();
    void putCirclesWithOverlay();
    void putCircleConnectionsAndRemoveProcessedCircles();
    BitmapSnippet& m_snippet;
    BitmapSnippetTraversal m_snippetTraversal;
    PenCircles m_penCircles;
    PointToColorMap m_drawnPoints;
};

}  // namespace AprgBitmap

}  // namespace alba
