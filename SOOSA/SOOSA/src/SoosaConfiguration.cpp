#include "SoosaConfiguration.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace soosa
{

SoosaConfiguration::SoosaConfiguration()
{}

unsigned int SoosaConfiguration::getAcceptableLineDeviationForLineModelInPixels() const
{
    return m_acceptableLineDeviationForLineModelInPixels;
}

double SoosaConfiguration::getRemovalRatioForSquareErrorsInLineModel() const
{
    return m_removalRatioForSquareErrorsInLineModel;
}

unsigned int SoosaConfiguration::getMinimumLineSamples() const
{
    return m_minimumLineSamples;
}

double SoosaConfiguration::getBitmapWidthToBarWidthMultiplier() const
{
    return m_bitmapWidthToBarWidthMultiplier;
}

double SoosaConfiguration::getAcceptableDistanceOverWidthRatioFromWidthMidpoint() const
{
    return m_acceptableDistanceOverWidthRatioFromWidthMidpoint;
}

unsigned int SoosaConfiguration::getAcceptableMinimumDistanceFromWidthMidpoint() const
{
    return m_acceptableMinimumDistanceFromWidthMidpoint;
}

double SoosaConfiguration::getAcceptableSdOverMeanDeviationForLine() const
{
    return m_acceptableSdOverMeanDeviationForLine;
}

double SoosaConfiguration::getAcceptableSdOverMeanDeviationForBar() const
{
    return m_acceptableSdOverMeanDeviationForBar;
}

double SoosaConfiguration::getRemovalRatioForLineAndBar() const
{
    return m_removalRatioForLineAndBar;
}

double SoosaConfiguration::getAcceptableSdOverMeanDeviationForBarHeight() const
{
    return m_acceptableSdOverMeanDeviationForBarHeight;
}

double SoosaConfiguration::getRemovalRatioForBarHeight() const
{
    return m_removalRatioForBarHeight;
}

unsigned int SoosaConfiguration::getNumberOfChoices() const
{
    return m_numberOfChoices;
}

unsigned int SoosaConfiguration::getColorIntensityForWhite() const
{
    return m_colorIntensityForWhite;
}

double SoosaConfiguration::getBarHeightToDiameterMultiplier() const
{
    return m_barHeightToDiameterMultiplier;
}

double SoosaConfiguration::getMinimumPercentageOfBlackPixelsForAFilledCircle() const
{
    return m_minimumPercentageOfBlackPixelsForAFilledCircle;
}

void SoosaConfiguration::loadConfigurationFromFile(string const& filePath)
{
    readNamesAndValuesFromFile(filePath);
    update();
}

void SoosaConfiguration::bufferNameAndValueString(string const& nameOfParameter, string const& valueString)
{
    m_nameToValueStringMapBuffer[nameOfParameter] = valueString;
}

void SoosaConfiguration::update()
{
    BufferMap::iterator it;

#define UPDATE_PARAMETER(nameOfParameter, type) \
    it = m_nameToValueStringMapBuffer.find(#nameOfParameter); \
    if(it != m_nameToValueStringMapBuffer.end()) \
    { \
    nameOfParameter = convertStringToNumber<type>(it->second); \
    m_nameToValueStringMapBuffer.erase(it); \
}

    // Line model parameters
    UPDATE_PARAMETER(m_acceptableLineDeviationForLineModelInPixels, unsigned int);
    UPDATE_PARAMETER(m_removalRatioForSquareErrorsInLineModel, double);
    UPDATE_PARAMETER(m_minimumLineSamples, unsigned int);

    // Line and bar parameters
    UPDATE_PARAMETER(m_bitmapWidthToBarWidthMultiplier, double);
    UPDATE_PARAMETER(m_acceptableDistanceOverWidthRatioFromWidthMidpoint, double);
    UPDATE_PARAMETER(m_acceptableMinimumDistanceFromWidthMidpoint, unsigned int);
    UPDATE_PARAMETER(m_acceptableSdOverMeanDeviationForLine, double);
    UPDATE_PARAMETER(m_acceptableSdOverMeanDeviationForBar, double);
    UPDATE_PARAMETER(m_removalRatioForLineAndBar, double);
    UPDATE_PARAMETER(m_acceptableSdOverMeanDeviationForBarHeight, double);
    UPDATE_PARAMETER(m_removalRatioForBarHeight, double);

    // Choices related parameters
    UPDATE_PARAMETER(m_numberOfChoices, unsigned int);
    UPDATE_PARAMETER(m_colorIntensityForWhite, unsigned int);
    UPDATE_PARAMETER(m_barHeightToDiameterMultiplier, double);
    UPDATE_PARAMETER(m_minimumPercentageOfBlackPixelsForAFilledCircle, double);

#undef UPDATE_PARAMETER
}

void SoosaConfiguration::readNamesAndValuesFromFile(string const& filePath)
{
    ifstream inputFileStream(filePath);
    if(inputFileStream.is_open())
    {
        AlbaFileReader fileReader(inputFileStream);
        while(fileReader.isNotFinished())
        {
            string line(fileReader.getLineAndIgnoreWhiteSpaces());
            if(!line.empty())
            {
                if(line.substr(0, 2) == "//")
                {
                    // do nothing if comment
                }
                else
                {
                    string beforeColon;
                    string afterColon;
                    copyBeforeStringAndAfterString(line, ":", beforeColon, afterColon);
                    bufferNameAndValueString(beforeColon, afterColon);
                }
            }
        }
    }
}


}

}
