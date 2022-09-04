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

unsigned int SoosaConfiguration::getNumberOfChoices() const
{
    return m_numberOfChoices;
}

unsigned int SoosaConfiguration::getAcceptableLineDeviationForLineModelInPixels() const
{
    return m_acceptableLineDeviationForLineModelInPixels;
}

double SoosaConfiguration::getRetainRatioForSquareErrorsInLineModel() const
{
    return m_retainRatioForSquareErrorsInLineModel;
}

unsigned int SoosaConfiguration::getMinimumLineSamples() const{
    return m_minimumLineSamples;
}

unsigned int SoosaConfiguration::getAcceptableBarHeightDeviationInPixels() const
{
    return m_acceptableBarHeightDeviationInPixels;
}

unsigned int SoosaConfiguration::getMaximumBarWidth() const
{
    return m_maximumBarWidth;}

unsigned int SoosaConfiguration::getMinimumNumberOfBarWidthsForABar() const
{    return m_minimumNumberOfBarWidthsForABar;
}

double SoosaConfiguration::getRatioOfBarHeightToDiameter() const
{
    return m_ratioOfBarHeightToDiameter;
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

    UPDATE_PARAMETER(m_numberOfChoices, unsigned int);
    UPDATE_PARAMETER(m_acceptableLineDeviationForLineModelInPixels, unsigned int);
    UPDATE_PARAMETER(m_retainRatioForSquareErrorsInLineModel, double);
    UPDATE_PARAMETER(m_minimumLineSamples, unsigned int);
    UPDATE_PARAMETER(m_acceptableBarHeightDeviationInPixels, unsigned int);
    UPDATE_PARAMETER(m_maximumBarWidth, unsigned int);
    UPDATE_PARAMETER(m_minimumNumberOfBarWidthsForABar, unsigned int);
    UPDATE_PARAMETER(m_ratioOfBarHeightToDiameter, double);    UPDATE_PARAMETER(m_minimumPercentageOfBlackPixelsForAFilledCircle, double);

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
            string lineInConfiguration(fileReader.getLineAndIgnoreWhiteSpaces());
            string beforeColon;
            string afterColon;
            stringHelper::copyBeforeStringAndAfterString(lineInConfiguration, ":", beforeColon, afterColon);
            bufferNameAndValueString(beforeColon, afterColon);
        }
    }
}


}

}
