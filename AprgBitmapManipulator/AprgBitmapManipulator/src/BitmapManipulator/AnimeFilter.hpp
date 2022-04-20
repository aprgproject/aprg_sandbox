#pragma once

#include <BitmapManipulator/BitmapFilters.hpp>
#include <Common/Time/AlbaLocalTimer.hpp>

#include <string>

namespace alba
{

namespace AprgBitmap
{

void animize(std::string const& inputFile,
             std::string const& outputFile);
void doStuffsAfterSteps(
        AlbaLocalTimer & localTimer,
        std::string const& description);
void doStuffsAfterSteps(
        AlbaLocalTimer & localTimer,
        BitmapFilters & bitmapFilter,
        BitmapSnippet const& snippet,
        std::string const& inputFilePath,
        std::string const& description);
std::string getNewFilePath(
        std::string const& inputFilePath,
        unsigned int const step,
        std::string const& description);

}

}
