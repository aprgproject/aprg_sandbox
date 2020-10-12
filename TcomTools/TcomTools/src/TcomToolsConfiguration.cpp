#include <TcomToolsConfiguration.hpp>

#include <AlbaFileReader.hpp>
#include <AlbaStringHelper.hpp>
#include <fstream>

using namespace alba;
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
    , isGrepErrWrnNoSpamEnabled(false)
    , isGrepBtsStatusEnabled(false)
    , isGrepRecoveryEnabled(false)
    , isGrepAllocationEnabled(false)
    , isGrepFaultEnabled(false)
    , isGrepLrmEnabled(false)
    , isGrepGrmEnabled(false)
    , isGrepToamEnabled(false)
    , isGrepTupcEnabled(false)
    , isGrepRlhEnabled(false)
    , isGrepCchhEnabled(false)
    , isGrepCchhSdlEnabled(false)
    , isGrepHschEnabled(false)
    , isGrepDmgrEnabled(false)
    , grepConditionForTcom()
    , grepConditionForErr()
    , grepConditionForErrWrn()
    , grepConditionForBtsStatus()
    , grepConditionForRecovery()
    , grepConditionForAllocation()
    , grepConditionForFault()
    , grepConditionForLrm()
    , grepConditionForGrm()
    , grepConditionForToam()
    , grepConditionForTupc()
    , grepConditionForRlh()
    , grepConditionForCchh()
    , grepConditionForCchhSdl()
    , grepConditionForHsch()
    , grepConditionForDmgr()
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
    AlbaFileReader fileReader(inputFileStream);
    while(fileReader.isNotFinished())
    {
        string lineInConfiguration(fileReader.getLineAndIgnoreWhiteSpaces());
        string beforeColon;
        string afterColon;
        stringHelper::copyBeforeStringAndAfterString(lineInConfiguration, ":", beforeColon, afterColon);

        if("isExtractStepOn" == beforeColon)
        {
            isExtractStepOn = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isCombineAndSortStepOn" == beforeColon)
        {
            isCombineAndSortStepOn = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isGrepStepOn" == beforeColon)
        {
            isGrepStepOn = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isCropStepOn" == beforeColon)
        {
            isCropStepOn = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isGrepTcomEnabled" == beforeColon)
        {
            isGrepTcomEnabled = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isGrepErrEnabled" == beforeColon)
        {
            isGrepErrEnabled = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isGrepErrWrnTcomEnabled" == beforeColon)
        {
            isGrepErrWrnNoSpamEnabled = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isGrepBtsStatusEnabled" == beforeColon)
        {
            isGrepBtsStatusEnabled = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isGrepRecoveryEnabled" == beforeColon)
        {
            isGrepRecoveryEnabled = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isGrepAllocationEnabled" == beforeColon)
        {
            isGrepAllocationEnabled = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isGrepFaultEnabled" == beforeColon)
        {
            isGrepFaultEnabled = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isGrepLrmEnabled" == beforeColon)
        {
            isGrepLrmEnabled = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isGrepGrmEnabled" == beforeColon)
        {
            isGrepGrmEnabled = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isGrepToamEnabled" == beforeColon)
        {
            isGrepToamEnabled = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isGrepTupcEnabled" == beforeColon)
        {
            isGrepTupcEnabled = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isGrepRlhEnabled" == beforeColon)
        {
            isGrepRlhEnabled = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isGrepCchhEnabled" == beforeColon)
        {
            isGrepCchhEnabled = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isGrepCchhSdlEnabled" == beforeColon)
        {
            isGrepCchhSdlEnabled = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isGrepHschEnabled" == beforeColon)
        {
            isGrepHschEnabled = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("isGrepDmgrEnabled" == beforeColon)
        {
            isGrepDmgrEnabled = !(0==stringHelper::convertStringToNumber<int>(afterColon));
        }
        else if("grepConditionForTcom" == beforeColon)
        {            grepConditionForTcom = afterColon;
        }
        else if("grepConditionForErr" == beforeColon)
        {
            grepConditionForErr = afterColon;
        }
        else if("grepConditionForErrWrn" == beforeColon)
        {
            grepConditionForErrWrn = afterColon;
        }
        else if("grepConditionForBtsStatus" == beforeColon)
        {
            grepConditionForBtsStatus = afterColon;
        }
        else if("grepConditionForRecovery" == beforeColon)
        {
            grepConditionForRecovery = afterColon;
        }
        else if("grepConditionForAllocation" == beforeColon)
        {
            grepConditionForAllocation = afterColon;
        }
        else if("grepConditionForFault" == beforeColon)
        {
            grepConditionForFault = afterColon;
        }
        else if("grepConditionForLrm" == beforeColon)
        {
            grepConditionForLrm = afterColon;
        }
        else if("grepConditionForGrm" == beforeColon)
        {
            grepConditionForGrm = afterColon;
        }
        else if("grepConditionForToam" == beforeColon)
        {
            grepConditionForToam = afterColon;
        }
        else if("grepConditionForTupc" == beforeColon)
        {
            grepConditionForTupc = afterColon;
        }
        else if("grepConditionForRlh" == beforeColon)
        {
            grepConditionForRlh = afterColon;
        }
        else if("grepConditionForCchh" == beforeColon)
        {
            grepConditionForCchh = afterColon;
        }
        else if("grepConditionForCchhSdl" == beforeColon)
        {
            grepConditionForCchhSdl = afterColon;
        }
        else if("grepConditionForHsch" == beforeColon)
        {
            grepConditionForHsch = afterColon;
        }
        else if("grepConditionForDmgr" == beforeColon)
        {
            grepConditionForDmgr = afterColon;
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
        else if("btsLogSorterConfiguration.m_pathOfLogsWithoutPcTime" == beforeColon)
        {
            btsLogSorterConfiguration.m_pathOfLogsWithoutPcTime = afterColon;
        }
        else if("btsLogSorterConfiguration.m_pathOfStartupLog" == beforeColon)
        {
            btsLogSorterConfiguration.m_pathOfStartupLog = afterColon;
        }
        else if("btsLogSorterConfiguration.m_configurationWithPcTime.m_directoryForBlocks" == beforeColon)
        {
            btsLogSorterConfiguration.m_configurationWithPcTime.m_directoryForBlocks = afterColon;
        }
        else if("btsLogSorterConfiguration.m_configurationWithPcTime.m_minimumNumberOfObjectsPerBlock" == beforeColon)
        {
            btsLogSorterConfiguration.m_configurationWithPcTime.m_minimumNumberOfObjectsPerBlock = stringHelper::convertStringToNumber<int>(afterColon);
        }
        else if("btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsPerBlock" == beforeColon)
        {
            btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsPerBlock = stringHelper::convertStringToNumber<int>(afterColon);
        }
        else if("btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsInMemory" == beforeColon)
        {
            btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsInMemory = stringHelper::convertStringToNumber<int>(afterColon);
        }
        else if("btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumFileStreams" == beforeColon)
        {
            btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumFileStreams = stringHelper::convertStringToNumber<int>(afterColon);
        }
        else if("btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumFileStreams" == beforeColon)
        {
            btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumFileStreams = stringHelper::convertStringToNumber<int>(afterColon);
        }
        else if("btsLogSorterConfiguration.m_configurationWithoutPcTime.m_directoryForBlocks" == beforeColon)
        {            btsLogSorterConfiguration.m_configurationWithoutPcTime.m_directoryForBlocks = afterColon;
        }
        else if("btsLogSorterConfiguration.m_configurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock" == beforeColon)
        {
            btsLogSorterConfiguration.m_configurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock = stringHelper::convertStringToNumber<int>(afterColon);
        }
        else if("btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock" == beforeColon)
        {
            btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock = stringHelper::convertStringToNumber<int>(afterColon);
        }
        else if("btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsInMemory" == beforeColon)
        {
            btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsInMemory = stringHelper::convertStringToNumber<int>(afterColon);
        }
        else if("btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumFileStreams" == beforeColon)
        {
            btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumFileStreams = stringHelper::convertStringToNumber<int>(afterColon);
        }
        else if("btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumFileStreams" == beforeColon)
        {
            btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumFileStreams = stringHelper::convertStringToNumber<int>(afterColon);
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
    outputFileStream << "isGrepErrWrnTcomEnabled:" << static_cast<int>(isGrepErrWrnNoSpamEnabled) << endl;
    outputFileStream << "isGrepBtsStatusEnabled:" << static_cast<int>(isGrepBtsStatusEnabled) << endl;
    outputFileStream << "isGrepRecoveryEnabled:" << static_cast<int>(isGrepRecoveryEnabled) << endl;
    outputFileStream << "isGrepAllocationEnabled:" << static_cast<int>(isGrepAllocationEnabled) << endl;
    outputFileStream << "isGrepFaultEnabled:" << static_cast<int>(isGrepFaultEnabled) << endl;
    outputFileStream << "isGrepLrmEnabled:" << static_cast<int>(isGrepLrmEnabled) << endl;
    outputFileStream << "isGrepGrmEnabled:" << static_cast<int>(isGrepGrmEnabled) << endl;
    outputFileStream << "isGrepToamEnabled:" << static_cast<int>(isGrepToamEnabled) << endl;
    outputFileStream << "isGrepTupcEnabled:" << static_cast<int>(isGrepTupcEnabled) << endl;
    outputFileStream << "isGrepRlhEnabled:" << static_cast<int>(isGrepRlhEnabled) << endl;
    outputFileStream << "isGrepCchhEnabled:" << static_cast<int>(isGrepCchhEnabled) << endl;
    outputFileStream << "isGrepCchhSdlEnabled:" << static_cast<int>(isGrepCchhSdlEnabled) << endl;
    outputFileStream << "isGrepHschEnabled:" << static_cast<int>(isGrepHschEnabled) << endl;
    outputFileStream << "isGrepDmgrEnabled:" << static_cast<int>(isGrepDmgrEnabled) << endl;
    outputFileStream << "grepConditionForTcom:" << grepConditionForTcom << endl;
    outputFileStream << "grepConditionForErr:" << grepConditionForErr << endl;
    outputFileStream << "grepConditionForErrWrn:" << grepConditionForErrWrn << endl;
    outputFileStream << "grepConditionForBtsStatus:" << grepConditionForBtsStatus << endl;
    outputFileStream << "grepConditionForRecovery:" << grepConditionForRecovery << endl;
    outputFileStream << "grepConditionForAllocation:" << grepConditionForAllocation << endl;
    outputFileStream << "grepConditionForFault:" << grepConditionForFault << endl;
    outputFileStream << "grepConditionForLrm:" << grepConditionForLrm << endl;
    outputFileStream << "grepConditionForGrm:" << grepConditionForGrm << endl;
    outputFileStream << "grepConditionForToam:" << grepConditionForToam << endl;
    outputFileStream << "grepConditionForTupc:" << grepConditionForTupc << endl;
    outputFileStream << "grepConditionForRlh:" << grepConditionForRlh << endl;
    outputFileStream << "grepConditionForCchh:" << grepConditionForCchh << endl;
    outputFileStream << "grepConditionForCchhSdl:" << grepConditionForCchhSdl << endl;
    outputFileStream << "grepConditionForHsch:" << grepConditionForHsch << endl;
    outputFileStream << "grepConditionForDmgr:" << grepConditionForDmgr << endl;
    outputFileStream << "inputFileOrDirectory:" << inputFileOrDirectory<< endl;
    outputFileStream << "extractGrepCondition:" << extractGrepCondition<< endl;
    outputFileStream << "acceptedFilesGrepCondition:" << acceptedFilesGrepCondition<< endl;
    outputFileStream << "otherGrepCondition:" << otherGrepCondition << endl;
    outputFileStream << "btsLogSorterConfiguration.m_pathOfLogsWithoutPcTime:" << btsLogSorterConfiguration.m_pathOfLogsWithoutPcTime << endl;
    outputFileStream << "btsLogSorterConfiguration.m_pathOfStartupLog:" << btsLogSorterConfiguration.m_pathOfStartupLog << endl;
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithPcTime.m_directoryForBlocks:" << btsLogSorterConfiguration.m_configurationWithPcTime.m_directoryForBlocks << endl;
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithPcTime.m_minimumNumberOfObjectsPerBlock:" << btsLogSorterConfiguration.m_configurationWithPcTime.m_minimumNumberOfObjectsPerBlock << endl;
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsPerBlock:" << btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsPerBlock << endl;
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsInMemory:" << btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumNumberOfObjectsInMemory << endl;
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumFileStreams:" << btsLogSorterConfiguration.m_configurationWithPcTime.m_maximumFileStreams << endl;
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithoutPcTime.m_directoryForBlocks:" << btsLogSorterConfiguration.m_configurationWithoutPcTime.m_directoryForBlocks << endl;
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock:" << btsLogSorterConfiguration.m_configurationWithoutPcTime.m_minimumNumberOfObjectsPerBlock << endl;
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock:" << btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsPerBlock << endl;
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsInMemory:" << btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumNumberOfObjectsInMemory << endl;
    outputFileStream << "btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumFileStreams:" << btsLogSorterConfiguration.m_configurationWithoutPcTime.m_maximumFileStreams << endl;
}

string TcomToolsConfiguration::getGrepCondition() const
{
    string condition;
    string const orOperator(" || ");
    if(isGrepTcomEnabled)
    {
        condition += grepConditionForTcom + orOperator;
    }
    if(isGrepErrEnabled)
    {
        condition += grepConditionForErr + orOperator;
    }
    if(isGrepErrWrnNoSpamEnabled)
    {
        condition += grepConditionForErrWrn + orOperator;
    }
    if(isGrepBtsStatusEnabled)
    {
        condition += grepConditionForBtsStatus + orOperator;
    }
    if(isGrepRecoveryEnabled)
    {
        condition += grepConditionForRecovery + orOperator;
    }
    if(isGrepAllocationEnabled)
    {
        condition += grepConditionForAllocation + orOperator;
    }
    if(isGrepFaultEnabled)
    {
        condition += grepConditionForFault + orOperator;
    }
    if(isGrepLrmEnabled)
    {
        condition += grepConditionForLrm + orOperator;
    }
    if(isGrepGrmEnabled)
    {
        condition += grepConditionForGrm + orOperator;
    }
    if(isGrepToamEnabled)
    {
        condition += grepConditionForToam + orOperator;
    }
    if(isGrepTupcEnabled)
    {
        condition += grepConditionForTupc + orOperator;
    }
    if(isGrepRlhEnabled)
    {
        condition += grepConditionForRlh + orOperator;
    }
    if(isGrepCchhEnabled)
    {
        condition += grepConditionForCchh + orOperator;
    }
    if(isGrepCchhSdlEnabled)
    {
        condition += grepConditionForCchhSdl + orOperator;
    }
    if(isGrepDmgrEnabled)
    {
        condition += grepConditionForDmgr + orOperator;
    }
    if(isGrepHschEnabled)
    {
        condition += grepConditionForHsch + orOperator;
    }
    if(!stringHelper::getStringWithoutStartingAndTrailingWhiteSpace(otherGrepCondition).empty())
    {
        condition += otherGrepCondition + orOperator;
    }
    if(!condition.empty())
    {
        condition = condition.substr(0, condition.length()-orOperator.length());
    }
    return condition;
}

string TcomToolsConfiguration::getGrepFileName() const
{
    string fileName;
    if(isGrepTcomEnabled)
    {
        fileName += "Tcom";
    }
    if(isGrepErrEnabled)
    {
        fileName += "Err";
    }
    if(isGrepErrWrnNoSpamEnabled)
    {
        fileName += "ErrWrn";
    }
    if(isGrepBtsStatusEnabled)
    {
        fileName += "BtsStatus";
    }
    if(isGrepRecoveryEnabled)
    {
        fileName += "Recovery";
    }
    if(isGrepAllocationEnabled)
    {
        fileName += "Allocation";
    }
    if(isGrepFaultEnabled)
    {
        fileName += "Fault";
    }
    if(isGrepLrmEnabled)
    {
        fileName += "Lrm";
    }
    if(isGrepGrmEnabled)
    {
        fileName += "Grm";
    }
    if(isGrepToamEnabled)
    {
        fileName += "Toam";
    }
    if(isGrepTupcEnabled)
    {
        fileName += "Tupc";
    }
    if(isGrepRlhEnabled)
    {
        fileName += "Rlh";
    }
    if(isGrepCchhEnabled)
    {
        fileName += "Cchh";
    }
    if(isGrepCchhSdlEnabled)
    {
        fileName += "CchhSdl";
    }
    if(isGrepDmgrEnabled)
    {
        fileName += "Dmgr";
    }
    if(isGrepHschEnabled)
    {
        fileName += "Hsch";
    }
    fileName += stringHelper::getStringWithoutCharAtTheStartAndEnd(stringHelper::getStringAndReplaceNonAlphanumericCharactersToUnderScore(otherGrepCondition), '_');
    fileName += ".log";
    return fileName;
}

}
