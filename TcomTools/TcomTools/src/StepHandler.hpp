#pragma once

#include <TcomToolsConfiguration.hpp>

namespace tcomToolsGui
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
    void execute(TcomToolsConfiguration const& configuration) const;
private:
    string executeExtractStep(TcomToolsConfiguration const& configuration, string const& inputPath) const;
    string executeCombineAndSortStep(TcomToolsConfiguration const& configuration, string const& inputPath) const;
    string executeGrepStep(TcomToolsConfiguration const& configuration, string const& inputPath) const;
    string grepFile(TcomToolsConfiguration const& configuration, string const& inputPath) const;
    string executeCropStep(TcomToolsConfiguration const& configuration, string const& inputPath) const;
    string cropFile(TcomToolsConfiguration const& configuration, string const& inputPath, double foundLocation) const;
    LocationsInFile getLocationsInFile(TcomToolsConfiguration const& configuration, double foundLocation) const;
    double getLocationOfPriotizedPrint(TcomToolsConfiguration const& configuration, string const& inputPath) const;\
};

}
