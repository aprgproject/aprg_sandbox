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

    // Line model parameters
    unsigned int getAcceptableLineDeviationForLineModelInPixels() const;
    double getRetainRatioForSquareErrorsInLineModel() const;
    unsigned int getMinimumLineSamples() const;

    // Line and bar parameters
    unsigned int getMaximumLineAndBarWidth() const;
    double getAcceptableDistanceOverWidthRatioFromWidthMidpoint() const;
    unsigned int getAcceptableMinimumDistanceFromWidthMidpoint() const;
    double getAcceptableSdOverMeanDeviationForLine() const;
    double getAcceptableSdOverMeanDeviationForBar() const;
    double getRetainRatioForLineAndBar() const;
    double getAcceptableSdOverMeanDeviationForBarHeight() const;
    double getRetainRatioForBarHeight() const;

    // Choices related parameters
    unsigned int getNumberOfChoices() const;
    unsigned int getColorIntensityForWhite() const;
    double getRatioOfBarHeightToDiameter() const;
    double getMinimumPercentageOfBlackPixelsForAFilledCircle() const;

    void loadConfigurationFromFile(std::string const& filePath);
    void bufferNameAndValueString(std::string const& nameOfParameter, std::string const& valueString);
    void update();

private:
    void readNamesAndValuesFromFile(std::string const& filePath);

    // Line model parameters
    unsigned int m_acceptableLineDeviationForLineModelInPixels;
    double m_retainRatioForSquareErrorsInLineModel;
    unsigned int m_minimumLineSamples;

    // Line and bar parameters
    unsigned int m_maximumLineAndBarWidth;
    double m_acceptableDistanceOverWidthRatioFromWidthMidpoint;
    unsigned int m_acceptableMinimumDistanceFromWidthMidpoint;
    double m_acceptableSdOverMeanDeviationForLine;
    double m_acceptableSdOverMeanDeviationForBar;
    double m_retainRatioForLineAndBar;
    double m_acceptableSdOverMeanDeviationForBarHeight;
    double m_retainRatioForBarHeight;

    // Choices related parameters
    unsigned int m_numberOfChoices;
    unsigned int m_colorIntensityForWhite;
    double m_ratioOfBarHeightToDiameter;
    double m_minimumPercentageOfBlackPixelsForAFilledCircle;

    // Buffer
    BufferMap m_nameToValueStringMapBuffer;
};

}

}
