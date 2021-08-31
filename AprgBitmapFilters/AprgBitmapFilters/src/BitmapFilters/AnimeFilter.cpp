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
    BitmapFilters bitmapFilters(inputFilePathHandler.getFullPath());
    BitmapSnippet tempSnippet(bitmapFilters.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilters.getBlankSnippetWithBackground());
    BitmapSnippet debugSnippet(bitmapFilters.getBlankSnippetWithBackground());
    PenPoints penPointsBeforeAnimeColor;
    PenPoints penPointsAfterAnimeColor;
    PenCircles penCirclesBeforeAnimeColor;
    PenCircles penCirclesAfterAnimeColor;

    localTimer.resetTimer();

    AnimizeColor animizeColor;
    animizeColor.gatherStatistics(inputFilePathHandler.getFullPath());
    animizeColor.calculateNewValues();
    doStuffsAfterSteps(localTimer, "Determining the new colors for animizing");

    bitmapFilters.determinePenPoints(penPointsBeforeAnimeColor, tempSnippet, 3, 0x08);
    bitmapFilters.drawPenPoints(penPointsBeforeAnimeColor, tempSnippet, debugSnippet);
    doStuffsAfterSteps(localTimer, bitmapFilters, debugSnippet, inputFile, "Determining pen points (before anime color)");

    bitmapFilters.determinePenCirclesFromPenPoints(penCirclesBeforeAnimeColor, penPointsBeforeAnimeColor, tempSnippet, 0x06, 0.90);
    debugSnippet = bitmapFilters.getBlankSnippetWithBackground();
    bitmapFilters.drawPenCircles(penCirclesBeforeAnimeColor, debugSnippet);
    doStuffsAfterSteps(localTimer, bitmapFilters, debugSnippet, inputFile, "Determining pen circles (before anime color)");

    bitmapFilters.drawAnimeColor(tempSnippet, animizeColor);
    doStuffsAfterSteps(localTimer, bitmapFilters, tempSnippet, inputFile, "Drawing to anime color");

    bitmapFilters.drawWithBlurringDisimilarColors(tempSnippet, 5, 0x02);
    doStuffsAfterSteps(localTimer, bitmapFilters, tempSnippet, inputFile, "Blur disimilar colors");

    bitmapFilters.determinePenPoints(penPointsAfterAnimeColor, tempSnippet, 3, 0x08); //detect pixelation
    debugSnippet = bitmapFilters.getBlankSnippetWithBackground();
    bitmapFilters.drawPenPoints(penPointsAfterAnimeColor, tempSnippet, debugSnippet);
    doStuffsAfterSteps(localTimer, bitmapFilters, debugSnippet, inputFile, "Determining pen points (after anime color)");

    bitmapFilters.determinePenCirclesFromPenPoints(penCirclesAfterAnimeColor, penPointsAfterAnimeColor, tempSnippet, 0x08, 0.60);
    debugSnippet = bitmapFilters.getBlankSnippetWithBackground();
    bitmapFilters.drawPenCircles(penCirclesAfterAnimeColor, debugSnippet);
    doStuffsAfterSteps(localTimer, bitmapFilters, debugSnippet, inputFile, "Determining pen circles (after anime color)");

    bitmapFilters.drawNonPenPoints(penPointsAfterAnimeColor, tempSnippet, outputSnippet);
    doStuffsAfterSteps(localTimer, bitmapFilters, outputSnippet, inputFile, "Drawing non pen points");

    bitmapFilters.drawToFillGapsUsingBlur(outputSnippet, 2);
    doStuffsAfterSteps(localTimer, bitmapFilters, outputSnippet, inputFile, "Drawing to fill gaps");

    bitmapFilters.drawPenCircles(penCirclesAfterAnimeColor, outputSnippet);
    debugSnippet = bitmapFilters.getBlankSnippetWithBackground();
    bitmapFilters.drawPenCircles(penCirclesAfterAnimeColor, debugSnippet);
    doStuffsAfterSteps(localTimer, bitmapFilters, debugSnippet, inputFile, "Drawing pen circles (after anime color)");

    animeColorsInPenCircles(penCirclesBeforeAnimeColor, animizeColor);
    doStuffsAfterSteps(localTimer, "Convert pen circles (before anime color) to anime color");

    bitmapFilters.drawPenCircles(penCirclesBeforeAnimeColor, outputSnippet);
    debugSnippet = bitmapFilters.getBlankSnippetWithBackground();
    bitmapFilters.drawPenCircles(penCirclesBeforeAnimeColor, debugSnippet);
    doStuffsAfterSteps(localTimer, bitmapFilters, debugSnippet, inputFile, "Drawing pen circles (before anime color)");

    bitmapFilters.saveSnippetIntoFileWithFullFilePath(outputSnippet, outputFilePathHandler.getFullPath());
}

void doStuffsAfterSteps(
        AlbaLocalTimer & localTimer,
        string const& description)
{
    localTimer.stopTimer();
    cout << localTimer.getElapsedTimeDisplayableString()  << ": " << description<< endl;
    localTimer.resetTimer();
}

void doStuffsAfterSteps(
        AlbaLocalTimer & localTimer,
        BitmapFilters & bitmapFilters,
        BitmapSnippet const& snippet,
        string const& inputFilePath,
        string const& description)
{
    static unsigned int step=1;
    localTimer.stopTimer();
    bitmapFilters.saveSnippetIntoFileWithFullFilePath(snippet, getNewFilePath(inputFilePath, step++, description));
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
