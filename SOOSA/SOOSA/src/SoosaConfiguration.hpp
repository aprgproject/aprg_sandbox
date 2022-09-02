#pragma once

#include <map>
#include <string>

namespace alba
{

namespace soosa
{

class SoosaConfiguration
{
public:
    using BufferMap = std::map<std::string, std::string>;

    SoosaConfiguration();

    unsigned int getNumberOfChoices() const;
    unsigned int getAcceptableLineDeviationForLineModelInPixels() const;
    unsigned int getAcceptableLineWidthDeviationInPixels() const;
    unsigned int getAcceptableBarWidthDeviationInPixels() const;
    unsigned int getAcceptableHalfLineWidthDeviationInPixels() const;
    unsigned int getAcceptableHalfBarWidthDeviationInPixels() const;
    unsigned int getAcceptableBarHeightDeviationInPixels() const;
    unsigned int getMinimumLineSamples() const;
    double getRetainRatioForSquareErrorsInLineModel() const;
    unsigned int getMaximumBarWidth() const;
    unsigned int getMinimumNumberOfBarWidthsForABar() const;
    double getRatioOfBarHeightToDiameter() const;
    double getMinimumPercentageOfBlackPixelsForAFilledCircle() const;

    void loadConfigurationFromFile(std::string const& filePath);
    void bufferNameAndValueString(std::string const& nameOfParameter, std::string const& valueString);
    void update();

private:
    void readNamesAndValuesFromFile(std::string const& filePath);
    unsigned int m_numberOfChoices;
    unsigned int m_acceptableLineDeviationForLineModelInPixels;
    unsigned int m_acceptableLineWidthDeviationInPixels;
    unsigned int m_acceptableBarWidthDeviationInPixels;
    unsigned int m_acceptableBarHeightDeviationInPixels;
    unsigned int m_minimumLineSamples;
    double m_retainRatioForSquareErrorsInLineModel;
    unsigned int m_maximumBarWidth;
    unsigned int m_minimumNumberOfBarWidthsForABar;
    double m_ratioOfBarHeightToDiameter;
    double m_minimumPercentageOfBlackPixelsForAFilledCircle;
    BufferMap m_nameToValueStringMapBuffer;
};

}

}
