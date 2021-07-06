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
    PenCirclesDrawer(
            PenCircles const& penCircles,
            BitmapSnippet & snippet);

    void drawCircles();
    void drawCircleConnections();

private:
    PenCircles m_penCircles;
    BitmapSnippet & m_snippet;
    BitmapSnippetTraversal m_snippetTraversal;
};

}

}
