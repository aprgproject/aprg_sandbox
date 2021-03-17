#pragma once

#include <Optional/AlbaOptional.hpp>
#include <GrepStringEvaluator/AlbaGrepStringEvaluator.hpp>

#include <functional>
#include <string>

namespace alba
{

class AlbaCropFile
{
public:
    struct LocationsInFile
    {
        double startLocation;
        double endLocation;
    };
    using UpdateFunctionWithPercentage = std::function<void(double)>;

    AlbaCropFile(std::string const& prioritizedLineCondition, double const cropSize);
    AlbaCropFile(std::string const& prioritizedLineCondition, double const cropSize, UpdateFunctionWithPercentage const& updateFunctionAfterOneIteration);
    bool isOutputFileWritten() const;
    void processFile( std::string const& inputFilePath, std::string const& outputFilePath);

private:
    double getLocationOfPrioritizedPrint(std::string const& inputFilePath);
    void performCropForFile(std::string const& inputFilePath, std::string const& outputFilePath, double const foundLocation);
    LocationsInFile getLocationsInFile(double const foundLocation, double const fileSize) const;
    void updateAfterOneIteration(double const percentage);
    bool m_isOutputFileWritten;
    double m_cropSize;
    AlbaGrepStringEvaluator m_prioritizedLineEvaluator;
    AlbaOptional<UpdateFunctionWithPercentage const&> m_updateFunctionAfterOneIterationOptional;
};

}
