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
    std::string executeExtractStep(TcomToolsConfiguration const& configuration, std::string const& inputPath) const;
    std::string executeCombineAndSortStep(TcomToolsConfiguration const& configuration, std::string const& inputPath) const;
    std::string executeGrepStep(TcomToolsConfiguration const& configuration, std::string const& inputPath) const;
    std::string grepFile(TcomToolsConfiguration const& configuration, std::string const& inputPath) const;
    std::string executeCropStep(TcomToolsConfiguration const& configuration, std::string const& inputPath) const;
    std::string cropFile(TcomToolsConfiguration const& configuration, std::string const& inputPath, double foundLocation) const;
    LocationsInFile getLocationsInFile(TcomToolsConfiguration const& configuration, double foundLocation) const;
    double getLocationOfPriotizedPrint(TcomToolsConfiguration const& configuration, std::string const& inputPath) const;\
};

}