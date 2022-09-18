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
    double getRemovalRatioForSquareErrorsInLineModel() const;
    unsigned int getMinimumLineSamples() const;

    // Line and bar parameters
    double getBitmapWidthToBarWidthMultiplier() const;
    double getLineBarWidthSearchInitialBlackPointsValue() const;
    double getLineBarWidthSearchAcceptedRunningBlackRatio() const;
    double getAcceptableDistanceOverWidthRatioFromWidthMidpoint() const;
    unsigned int getAcceptableMinimumDistanceFromWidthMidpoint() const;
    double getAcceptableSdOverMeanDeviationForLine() const;    double getAcceptableSdOverMeanDeviationForBar() const;
    double getRemovalRatioForLineAndBar() const;
    double getAcceptableSdOverMeanDeviationForBarHeight() const;
    double getRemovalRatioForBarHeight() const;
    // Choices related parameters
    unsigned int getNumberOfChoices() const;
    unsigned int getColorIntensityForWhite() const;
    double getBarHeightToDiameterMultiplier() const;
    double getMinimumPercentageOfBlackPixelsForAFilledCircle() const;

    void loadConfigurationFromFile(std::string const& filePath);
    void bufferNameAndValueString(std::string const& nameOfParameter, std::string const& valueString);
    void update();

private:
    void readNamesAndValuesFromFile(std::string const& filePath);

    // Line model parameters
    unsigned int m_acceptableLineDeviationForLineModelInPixels;
    double m_removalRatioForSquareErrorsInLineModel;
    unsigned int m_minimumLineSamples;

    // Line and bar parameters
    double m_bitmapWidthToBarWidthMultiplier;
    unsigned int m_lineBarWidthSearchInitialBlackPointsValue;
    double m_lineBarWidthSearchAcceptedRunningBlackRatio;
    double m_acceptableDistanceOverWidthRatioFromWidthMidpoint;
    unsigned int m_acceptableMinimumDistanceFromWidthMidpoint;
    double m_acceptableSdOverMeanDeviationForLine;    double m_acceptableSdOverMeanDeviationForBar;
    double m_removalRatioForLineAndBar;
    double m_acceptableSdOverMeanDeviationForBarHeight;
    double m_removalRatioForBarHeight;
    // Choices related parameters
    unsigned int m_numberOfChoices;
    unsigned int m_colorIntensityForWhite;
    double m_barHeightToDiameterMultiplier;
    double m_minimumPercentageOfBlackPixelsForAFilledCircle;

    // Buffer
    BufferMap m_nameToValueStringMapBuffer;
};

}

}
