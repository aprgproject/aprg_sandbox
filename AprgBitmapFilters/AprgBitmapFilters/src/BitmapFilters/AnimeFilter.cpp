#include "AnimeFilter.hpp"

#include <BitmapFilters/AnimizeColor.hpp>
#include <BitmapFilters/Utilities.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>
#include <String/AlbaStringHelper.hpp>

#include <iostream>
#include <sstream>

using namespace std;

namespace alba
{

namespace AprgBitmap
{

void animize(string const& inputFile,
             string const& outputFile)
{
    AlbaLocalTimer localTimer;
    AlbaLocalPathHandler inputFilePathHandler(inputFile);
    AlbaLocalPathHandler outputFilePathHandler(outputFile);
    BitmapFilters bitmapFilter(inputFilePathHandler.getFullPath());
    BitmapSnippet tempSnippet(bitmapFilter.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilter.getBlankSnippetWithBackground());
    BitmapSnippet debugSnippet(bitmapFilter.getBlankSnippetWithBackground());
    PenPoints penPointsBeforeAnimeColor;
    PenPoints penPointsAfterAnimeColor;
    PenCircles penCirclesBeforeAnimeColor;
    PenCircles penCirclesAfterAnimeColor;

    localTimer.resetTimer();

    AnimizeColor animizeColor;
    animizeColor.gatherStatistics(inputFilePathHandler.getFullPath());
    animizeColor.calculateNewValues();
    doStuffsAfterSteps(localTimer, "Determining the new colors for animizing");

    bitmapFilter.determinePenPoints(penPointsBeforeAnimeColor, tempSnippet, 3, 0x06);
    bitmapFilter.drawPenPoints(penPointsBeforeAnimeColor, tempSnippet, debugSnippet);
    doStuffsAfterSteps(localTimer, bitmapFilter, debugSnippet, inputFile, "Determining pen points (before anime color)");

    bitmapFilter.determinePenCirclesFromPenPoints(penCirclesBeforeAnimeColor, penPointsBeforeAnimeColor, tempSnippet, 0x06, 0.90);
    debugSnippet=bitmapFilter.getBlankSnippetWithBackground();
    bitmapFilter.drawPenCircles(penCirclesBeforeAnimeColor, debugSnippet);
    doStuffsAfterSteps(localTimer, bitmapFilter, debugSnippet, inputFile, "Determining pen circles (before anime color)");

    bitmapFilter.drawAnimeColor(tempSnippet, animizeColor);
    doStuffsAfterSteps(localTimer, bitmapFilter, tempSnippet, inputFile, "Drawing to anime color");

    bitmapFilter.drawWithBlurringDisimilarColors(tempSnippet, 5, 0x02);
    doStuffsAfterSteps(localTimer, bitmapFilter, tempSnippet, inputFile, "Blur disimilar colors");

    bitmapFilter.determinePenPoints(penPointsAfterAnimeColor, tempSnippet, 3, 0x06); //detect pixelation
    debugSnippet=bitmapFilter.getBlankSnippetWithBackground();
    bitmapFilter.drawPenPoints(penPointsAfterAnimeColor, tempSnippet, debugSnippet);
    doStuffsAfterSteps(localTimer, bitmapFilter, debugSnippet, inputFile, "Determining pen points (after anime color)");

    bitmapFilter.determinePenCirclesFromPenPoints(penCirclesAfterAnimeColor, penPointsAfterAnimeColor, tempSnippet, 0x08, 0.70);
    debugSnippet=bitmapFilter.getBlankSnippetWithBackground();
    bitmapFilter.drawPenCircles(penCirclesAfterAnimeColor, debugSnippet);
    doStuffsAfterSteps(localTimer, bitmapFilter, debugSnippet, inputFile, "Determining pen circles (after anime color");

    bitmapFilter.drawNonPenPoints(penPointsAfterAnimeColor, tempSnippet, outputSnippet);
    doStuffsAfterSteps(localTimer, bitmapFilter, outputSnippet, inputFile, "Drawing non pen points");

    bitmapFilter.drawToFillGapsUsingBlur(outputSnippet, 2);
    doStuffsAfterSteps(localTimer, bitmapFilter, outputSnippet, inputFile, "Drawing to fill gaps");

    bitmapFilter.drawPenCircles(penCirclesAfterAnimeColor, outputSnippet);
    debugSnippet=bitmapFilter.getBlankSnippetWithBackground();
    bitmapFilter.drawPenCircles(penCirclesAfterAnimeColor, debugSnippet);
    doStuffsAfterSteps(localTimer, bitmapFilter, debugSnippet, inputFile, "Drawing pen circles (after anime color)");

    animeColorsInPenCircles(penCirclesBeforeAnimeColor, animizeColor);
    doStuffsAfterSteps(localTimer, "Convert pen circles (before anime color) to anime color");

    bitmapFilter.drawPenCircles(penCirclesBeforeAnimeColor, outputSnippet);
    debugSnippet=bitmapFilter.getBlankSnippetWithBackground();
    bitmapFilter.drawPenCircles(penCirclesBeforeAnimeColor, debugSnippet);
    doStuffsAfterSteps(localTimer, bitmapFilter, debugSnippet, inputFile, "Drawing pen circles (before anime color)");

    bitmapFilter.saveSnippetIntoFileWithFullFilePath(outputSnippet, outputFilePathHandler.getFullPath());
}

void doStuffsAfterSteps(
        AlbaLocalTimer & localTimer,
        string const& description)
{
    static unsigned int step=1;
    localTimer.stopTimer();
    cout << localTimer.getElapsedTimeDisplayableString()  << ": " << description<< endl;
    localTimer.resetTimer();
}

void doStuffsAfterSteps(
        AlbaLocalTimer & localTimer,
        BitmapFilters & bitmapFilter,
        BitmapSnippet const& snippet,
        string const& inputFilePath,
        string const& description)
{
    static unsigned int step=1;
    localTimer.stopTimer();
    bitmapFilter.saveSnippetIntoFileWithFullFilePath(snippet, getNewFilePath(inputFilePath, step++, description));
    cout << localTimer.getElapsedTimeDisplayableString()  << ": " << description<< endl;
    localTimer.resetTimer();
}

string getNewFilePath(
        string const& inputFilePath,
        unsigned int const step,
        string const& description)
{
    AlbaLocalPathHandler inputFilePathHandler(inputFilePath);
    stringstream ss;
    ss << inputFilePathHandler.getDirectory()
       << inputFilePathHandler.getFilenameOnly()
       << "_Step" << step
       << "_(" << stringHelper::getStringAndReplaceNonAlphanumericCharactersToUnderScore(description)
       << ")."
       << inputFilePathHandler.getExtension();
    return ss.str();
}

}

}
