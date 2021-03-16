#pragma once

#include <WcdmaToolsConfiguration.hpp>

namespace wcdmaToolsGui
{

class StepHandler
{
    struct LocationsInFile
    {
        double startLocation;
        double endLocation;
    };
public:
    StepHandler();
    void execute(WcdmaToolsConfiguration const& configuration) const;
private:
    std::string executeExtractStep(WcdmaToolsConfiguration const& configuration, std::string const& inputPath) const;
    std::string executeCombineAndSortStep(WcdmaToolsConfiguration const& configuration, std::string const& inputPath) const;
    std::string executeGrepStep(WcdmaToolsConfiguration const& configuration, std::string const& inputPath) const;
    std::string grepFile(WcdmaToolsConfiguration const& configuration, std::string const& inputPath) const;
    std::string executeCropStep(WcdmaToolsConfiguration const& configuration, std::string const& inputPath) const;
    std::string cropFile(WcdmaToolsConfiguration const& configuration, std::string const& inputPath, double foundLocation) const;
    LocationsInFile getLocationsInFile(WcdmaToolsConfiguration const& configuration, double foundLocation) const;
    double getLocationOfPriotizedPrint(WcdmaToolsConfiguration const& configuration, std::string const& inputPath) const;
    std::string getTempFileFor7zBasedOnLogSorter(WcdmaToolsConfiguration const& configuration) const;
};

}
