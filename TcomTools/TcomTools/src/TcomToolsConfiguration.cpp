#include <TcomToolsConfiguration.hpp>

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <fstream>

using namespace std;

namespace tcomToolsGui
{

TcomToolsConfiguration::TcomToolsConfiguration()
    : isExtractStepOn(false)
    , isCombineAndSortStepOn(false)
    , isGrepStepOn(false)
    , isCropStepOn(false)
    , isGrepTcomEnabled(false)
    , isGrepErrEnabled(false)
    , isGrepErrWrnTcomEnabled(false)
    , isGrepBtsStatusEnabled(false)
    , isGrepRecoveryEnabled(false)
    , isGrepAllocationEnabled(false)
    , isGrepFaultEnabled(false)
    , isGrepLrmEnabled(false)
    , isGrepGrmEnabled(false)
    , isGrepToamEnabled(false)
    , isGrepTupcEnabled(false)
    , isGrepRlhEnabled(false)
    , isGrepCchhBchsenderEnabled(false)
    , isGrepHschEnabled(false)
    , isGrepDmgrEnabled(false)
    , inputFileOrDirectory()
    , extractGrepCondition()
    , acceptedFilesGrepCondition()
    , otherGrepCondition()
    , prioritizedLogPrint()
{
    loadConfigurationFromFile();
}

void TcomToolsConfiguration::loadConfigurationFromFile()
{
    std::ifstream inputFileStream(CONFIGURATION_FILE);
    alba::AlbaFileReader fileReader(inputFileStream);
    while(fileReader.isNotFinished())
    {
        string lineInConfiguration(fileReader.getLineAndIgnoreWhiteSpaces());
        string beforeColon;
        string afterColon;
        alba::stringHelper::copyBeforeStringAndAfterString(lineInConfiguration, ":", beforeColon, afterColon);

        if("isExtractStepOn" == beforeColon)
        {
            isExtractStepOn = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isCombineAndSortStepOn" == beforeColon)
        {
            isCombineAndSortStepOn = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepStepOn" == beforeColon)
        {
            isGrepStepOn = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isCropStepOn" == beforeColon)
        {
            isCropStepOn = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepTcomEnabled" == beforeColon)
        {
            isGrepTcomEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepErrEnabled" == beforeColon)
        {
            isGrepErrEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepErrWrnTcomEnabled" == beforeColon)
        {
            isGrepErrWrnTcomEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepBtsStatusEnabled" == beforeColon)
        {
            isGrepBtsStatusEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepRecoveryEnabled" == beforeColon)
        {
            isGrepRecoveryEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepAllocationEnabled" == beforeColon)
        {
            isGrepAllocationEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepFaultEnabled" == beforeColon)
        {
            isGrepFaultEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepLrmEnabled" == beforeColon)
        {
            isGrepLrmEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepGrmEnabled" == beforeColon)
        {
            isGrepGrmEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepToamEnabled" == beforeColon)
        {
            isGrepToamEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepTupcEnabled" == beforeColon)
        {
            isGrepTupcEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepRlhEnabled" == beforeColon)
        {
            isGrepRlhEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepCchhBchsenderEnabled" == beforeColon)
        {
            isGrepCchhBchsenderEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepHschEnabled" == beforeColon)
        {
            isGrepHschEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("isGrepDmgrEnabled" == beforeColon)
        {
            isGrepDmgrEnabled = !(0==alba::stringHelper::stringToNumber<int>(afterColon));
        }
        else if("inputFileOrDirectory" == beforeColon)
        {
            inputFileOrDirectory = afterColon;
        }
        else if("extractGrepCondition" == beforeColon)
        {
            extractGrepCondition = afterColon;
        }
        else if("acceptedFilesGrepCondition" == beforeColon)
        {
            acceptedFilesGrepCondition = afterColon;
        }
        else if("otherGrepCondition" == beforeColon)
        {
            otherGrepCondition = afterColon;
        }
        else if("prioritizedLogPrint" == beforeColon)
        {
            prioritizedLogPrint = afterColon;
        }
        else if("pathOfLogsWithoutPcTime" == beforeColon)
        {
            pathOfLogsWithoutPcTime = afterColon;
        }
        else if("sorterConfigurationWithPcTime.m_directoryForBlocks" == beforeColon)
        {
            sorterConfigurationWithPcTime.m_directoryForBlocks = afterColon;
        }
        else if("sorterConfigurationWithPcTime.m_minimumNumberOfObjectsPerBlock" == beforeColon)
        {
            sorterConfigurationWithPcTime.m_minimumNumberOfObjectsPerBlock = alba::stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithPcTime.m_maximumNumberOfObjectsPerBlock" == beforeColon)
        {
            sorterConfigurationWithPcTime.m_maximumNumberOfObjectsPerBlock = alba::stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithPcTime.m_maximumNumberOfObjectsInMemory" == beforeColon)
        {
            sorterConfigurationWithPcTime.m_maximumNumberOfObjectsInMemory = alba::stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithPcTime.m_maximumFileStreams" == beforeColon)
        {
            sorterConfigurationWithPcTime.m_maximumFileStreams = alba::stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithPcTime.m_maximumFileStreams" == beforeColon)
        {
            sorterConfigurationWithPcTime.m_maximumFileStreams = alba::stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithoutPcTime.m_directoryForBlocks" == beforeColon)
        {
            sorterConfigurationWithoutPcTime.m_directoryForBlocks = afterColon;
        }
        else if("sorterConfigurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock" == beforeColon)
        {
            sorterConfigurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock = alba::stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock" == beforeColon)
        {
            sorterConfigurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock = alba::stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithoutPcTime.m_maximumNumberOfObjectsInMemory" == beforeColon)
        {
            sorterConfigurationWithoutPcTime.m_maximumNumberOfObjectsInMemory = alba::stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithoutPcTime.m_maximumFileStreams" == beforeColon)
        {
            sorterConfigurationWithoutPcTime.m_maximumFileStreams = alba::stringHelper::stringToNumber<int>(afterColon);
        }
        else if("sorterConfigurationWithoutPcTime.m_maximumFileStreams" == beforeColon)
        {
            sorterConfigurationWithoutPcTime.m_maximumFileStreams = alba::stringHelper::stringToNumber<int>(afterColon);
        }
    }
}

void TcomToolsConfiguration::saveConfigurationToFile() const
{
    std::ofstream outputFileStream(CONFIGURATION_FILE);
    outputFileStream << "isExtractStepOn:" << static_cast<int>(isExtractStepOn) << endl;
    outputFileStream << "isCombineAndSortStepOn:" << static_cast<int>(isCombineAndSortStepOn) << endl;
    outputFileStream << "isGrepStepOn:" << static_cast<int>(isGrepStepOn) << endl;
    outputFileStream << "isCropStepOn:" << static_cast<int>(isCropStepOn) << endl;
    outputFileStream << "isGrepTcomEnabled:" << static_cast<int>(isGrepTcomEnabled) << endl;
    outputFileStream << "isGrepErrEnabled:" << static_cast<int>(isGrepErrEnabled) << endl;
    outputFileStream << "isGrepErrWrnTcomEnabled:" << static_cast<int>(isGrepErrWrnTcomEnabled) << endl;
    outputFileStream << "isGrepBtsStatusEnabled:" << static_cast<int>(isGrepBtsStatusEnabled) << endl;
    outputFileStream << "isGrepRecoveryEnabled:" << static_cast<int>(isGrepRecoveryEnabled) << endl;
    outputFileStream << "isGrepAllocationEnabled:" << static_cast<int>(isGrepAllocationEnabled) << endl;
    outputFileStream << "isGrepFaultEnabled:" << static_cast<int>(isGrepFaultEnabled) << endl;
    outputFileStream << "isGrepLrmEnabled:" << static_cast<int>(isGrepLrmEnabled) << endl;
    outputFileStream << "isGrepGrmEnabled:" << static_cast<int>(isGrepGrmEnabled) << endl;
    outputFileStream << "isGrepToamEnabled:" << static_cast<int>(isGrepToamEnabled) << endl;
    outputFileStream << "isGrepTupcEnabled:" << static_cast<int>(isGrepTupcEnabled) << endl;
    outputFileStream << "isGrepRlhEnabled:" << static_cast<int>(isGrepRlhEnabled) << endl;
    outputFileStream << "isGrepCchhBchsenderEnabled:" << static_cast<int>(isGrepCchhBchsenderEnabled) << endl;
    outputFileStream << "isGrepHschEnabled:" << static_cast<int>(isGrepHschEnabled) << endl;
    outputFileStream << "isGrepDmgrEnabled:" << static_cast<int>(isGrepDmgrEnabled) << endl;
    outputFileStream << "inputFileOrDirectory:" << inputFileOrDirectory<< endl;
    outputFileStream << "extractGrepCondition:" << extractGrepCondition<< endl;
    outputFileStream << "acceptedFilesGrepCondition:" << acceptedFilesGrepCondition<< endl;
    outputFileStream << "otherGrepCondition:" << otherGrepCondition << endl;
    outputFileStream << "pathOfLogsWithoutPcTime:" << pathOfLogsWithoutPcTime << endl;
    outputFileStream << "sorterConfigurationWithPcTime.m_directoryForBlocks:" << sorterConfigurationWithPcTime.m_directoryForBlocks << endl;
    outputFileStream << "sorterConfigurationWithPcTime.m_minimumNumberOfObjectsPerBlock:" << sorterConfigurationWithPcTime.m_minimumNumberOfObjectsPerBlock << endl;
    outputFileStream << "sorterConfigurationWithPcTime.m_maximumNumberOfObjectsPerBlock:" << sorterConfigurationWithPcTime.m_maximumNumberOfObjectsPerBlock << endl;
    outputFileStream << "sorterConfigurationWithPcTime.m_maximumNumberOfObjectsInMemory:" << sorterConfigurationWithPcTime.m_maximumNumberOfObjectsInMemory << endl;
    outputFileStream << "sorterConfigurationWithPcTime.m_maximumFileStreams:" << sorterConfigurationWithPcTime.m_maximumFileStreams << endl;
    outputFileStream << "sorterConfigurationWithoutPcTime.m_directoryForBlocks:" << sorterConfigurationWithoutPcTime.m_directoryForBlocks << endl;
    outputFileStream << "sorterConfigurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock:" << sorterConfigurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock << endl;
    outputFileStream << "sorterConfigurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock:" << sorterConfigurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock << endl;
    outputFileStream << "sorterConfigurationWithoutPcTime.m_maximumNumberOfObjectsInMemory:" << sorterConfigurationWithoutPcTime.m_maximumNumberOfObjectsInMemory << endl;
    outputFileStream << "sorterConfigurationWithoutPcTime.m_maximumFileStreams:" << sorterConfigurationWithoutPcTime.m_maximumFileStreams << endl;
}

}
